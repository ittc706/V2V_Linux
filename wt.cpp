/*
* =====================================================================================
*
*       Filename:  wt.cpp
*
*    Description:  高速场景类实现
*
*        Version:  1.0
*        Created:
*       Revision:
*       Compiler:  VS_2015
*
*         Author:  LN
*            LIB:  ITTC
*
* =====================================================================================
*/

#include<fstream>
#include<iterator>
#include"context.h"
#include"config.h"
#include"wt.h"
#include"vue_physics.h"
#include"vue_network.h"


using namespace std;

default_random_engine wt::s_engine(0);

std::vector<double>* wt::m_qpsk_mi = nullptr;

void wt::set_resource() {
	ifstream in;
	if (context::get_context()->get_global_control_config()->get_platform()== Windows) {
		in.open("wt\\qpsk_mi.md");
	}
	else {
		in.open("wt/qpsk_mi.md");
	}
	m_qpsk_mi = new vector<double>();
	istream_iterator<double> in_iter(in), eof;
	m_qpsk_mi->assign(in_iter, eof);
	in.close();
}

wt::wt() {

}

wt::~wt() {

}

double wt::calculate_sinr(int t_send_vue_id, int t_receive_vue_id, int t_pattern_idx, const set<int>& t_sending_vue_id_set) {
	m_ploss = vue_physics::get_pl(t_send_vue_id, t_receive_vue_id);
	int subcarrier_num = context::get_context()->get_rrm_config()->get_rb_num_per_pattern() * 12;
	m_pt = pow(10, (23 - 10 * log10(subcarrier_num * 15 * 1000)) / 10);
	m_sigma = pow(10, -17.4);

	m_inter_ploss.clear();

	for (int inter_vue_id : t_sending_vue_id_set) {
		if (t_send_vue_id == inter_vue_id) continue;
		m_inter_ploss.push_back(vue_physics::get_pl(t_receive_vue_id, inter_vue_id));
	}

	/*****求每个子载波上的信噪比****/
	vector<double> sinr(subcarrier_num);//每个子载波上的信噪比，维度为nt的向量
	for (int subcarrier_idx = 0; subcarrier_idx <subcarrier_num; subcarrier_idx++) {

		m_h = read_h(t_send_vue_id, t_receive_vue_id, t_pattern_idx, subcarrier_idx);//读入当前子载波的信道响应矩阵
		m_inter_h = read_inter_h(t_sending_vue_id_set, t_send_vue_id, t_receive_vue_id, t_pattern_idx, subcarrier_idx);//读入当前子载波干扰相应矩阵数组

		double h_sum1 = 0;
		for (int r = 0; r < m_nr; r++) {
			h_sum1 += complex::abs(m_h[r][0])*complex::abs(m_h[r][0]);
		}

		double molecule = m_pt*m_ploss*h_sum1*h_sum1;

		double h_sum2 = 0;
		for (int j = 0; j < m_inter_h.size(); j++) {
			double weight = m_pt*m_inter_ploss[j];
			complex tmp(0, 0);
			for (int r = 0; r < m_nr; r++) {
				tmp += m_h[r][0] * m_inter_h[j][r][0];
			}
			h_sum2 += weight * complex::abs(tmp)*complex::abs(tmp);
		}

		double denominator = h_sum1*m_sigma + h_sum2;

		sinr[subcarrier_idx] = 10 * log10(molecule / denominator);
	}

	//互信息方法求有效信噪比sinreff

	double sum_mi = 0, ave_mi = 0;
	double sinreff = 0;

	for (int k = 0; k < subcarrier_num; k++) {
		sum_mi = sum_mi + get_mutual_information(*m_qpsk_mi, (int)ceil((sinr[k] + 20) * 2));
	}
	ave_mi = sum_mi / subcarrier_num;

	int snr_index = closest(*m_qpsk_mi, ave_mi);
	sinreff = 0.5*(snr_index - 40);

	return sinreff;
}

matrix wt::read_h(int t_send_vue_id, int t_receive_vue_id, int t_pattern_idx, int t_subcarrier_idx) {
	matrix res(m_nr, m_nt);
	double* p = vue_physics::get_channel(t_send_vue_id, t_receive_vue_id, t_pattern_idx);
	if (p == nullptr) throw logic_error("error");

	int point_num_per_pattern = context::get_context()->get_rrm_config()->get_rb_num_per_pattern() * 12;
	for (int row = 0; row < m_nr; row++) {
		for (int col = 0; col < m_nt; col++) {
			res[row][col] = complex(p[row * (point_num_per_pattern * 2) + t_subcarrier_idx * 2], p[row * (point_num_per_pattern * 2) + t_subcarrier_idx * 2 + 1]);
		}
	}
	return res;
}

std::vector<matrix> wt::read_inter_h(const std::set<int>& t_sending_vue_id_set, int t_send_vue_id, int t_receive_vue_id, int t_pattern_idx, int t_subcarrier_idx) {
	vector<matrix> res;
	//<Warn>
	for (int inter_vue_id : t_sending_vue_id_set) {
		if (inter_vue_id == t_send_vue_id) continue;
		if (inter_vue_id == t_receive_vue_id) continue;
		
		double* p = vue_physics::get_channel(inter_vue_id, t_receive_vue_id, t_pattern_idx);
		if (p == nullptr) continue;//该信道响应矩阵没有计算，即该信道强度很弱，已被忽略

		matrix m(m_nr, m_nt);
		int point_num_per_pattern = context::get_context()->get_rrm_config()->get_rb_num_per_pattern() * 12;

		for (int row = 0; row < m_nr; row++) {
			for (int col = 0; col < m_nt; col++) {
				m[row][col] = complex(p[row * (point_num_per_pattern * 2) + t_subcarrier_idx * 2],
					p[row * (point_num_per_pattern * 2) + t_subcarrier_idx * 2 + 1]);
			}
		}
		res.push_back(m);
	}
	return res;
}

int wt::closest(std::vector<double> t_vec, double t_target) {
	int left_index = 0;
	int right_index = static_cast<int>(t_vec.size() - 1);
	double left_diff = t_vec[left_index] - t_target;
	double right_diff = t_vec[right_index] - t_target;

	while (left_index <= right_index) {
		if (right_diff <= 0) return right_index;//???
		if (left_diff >= 0) return left_index;//???

		int mid_index = left_index + ((right_index - left_index) >> 1);
		double mid_diff = t_vec[mid_index] - t_target;
		if (mid_diff == 0) return mid_index;
		else if (mid_diff < 0) {
			left_index = mid_index + 1;
			left_diff = t_vec[left_index] - t_target;
			if (abs(mid_diff) < abs(left_diff)) return mid_index;
		}
		else {
			right_index = mid_index - 1;
			right_diff = t_vec[right_index] - t_target;
			if (abs(mid_diff) < abs(right_diff)) return mid_index;
		}
	}
	return abs(t_vec[left_index] - t_target) < abs(t_vec[left_index - 1] - t_target) ? left_index : left_index - 1;//???

}

double wt::get_mutual_information(std::vector<double> t_vec, int t_index) {
	if (t_index < 0) return t_vec[0];
	if (t_index >= (int)t_vec.size()) return t_vec[t_vec.size() - 1];
	return t_vec[t_index];
}
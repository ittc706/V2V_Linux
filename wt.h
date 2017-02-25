#pragma once

#include<set>
#include<random>
#include<utility>
#include<memory>
#include"matrix.h"

class wt {
	/*------------------��Ԫ����------------------*/
	/*
	* ��context��Ϊ��Ԫ������ҪΪ��ע��������
	*/
	friend class context;

	/*---------------��̬��Ա---------------*/
private:
	/*
	* ��������棬���๲��
	*/
	static std::default_random_engine s_engine;

	/*
	* ������Դ
	*/
	static std::vector<double>* m_qpsk_mi;

	/*
	* ������Դ��Դ��ʼ����������������
	*/
	static void set_resource();
	/*----------------�ֶ�------------------*/
private:
	/*
	* ����������
	*/
	int m_nt = 1;

	/*
	* ����������
	*/
	int m_nr = 2;

	/*
	* ���书��
	*/
	double m_pt;

	/*
	* ����·�����
	*/
	double m_ploss;

	/*
	* ���ž���·�����
	*/
	std::vector<double> m_inter_ploss;

	/*
	* ��˹�����Ĺ��ʣ���λ��mw
	*/
	double m_sigma;

	/*
	* ÿ�����ز���һ��nr*nt���ŵ�����
	*/
	matrix m_h;

	/*
	* ÿ�����ز���һ��nr*nt�ĸ����ŵ�����
	* �±�Ϊ����Դ���
	*/
	std::vector<matrix> m_inter_h;

	

	/*------------------�ӿ�------------------*/
public:
	/*
	* Ĭ�Ϲ��캯
	*/
	wt();

	/*
	* ��������
	*/
	~wt();

	/*
	* �����ظɱ�
	* t_send_vue_id:��ǰ��·�ķ��Ͷ˳���id
	* t_receive_vue_id:��ǰ��·�Ľ��ն˳���id
	* t_subcarrier_interval:����·ռ�õ����ز�����
	* t_sending_vue_id_set:�ڸ����ز�������з��͵ĳ���id�б�����t_send_vue_id
	*/
	double calculate_sinr(int t_send_vue_id, int t_receive_vue_id, const std::pair<int, int>& t_subcarrier_interval, const std::set<int>& t_sending_vue_id_set);

private:
	/*
	* ��ȡ��Ӧ���ز����ŵ���Ӧ����
	*/
	matrix read_h(int t_send_vue_id, int t_receive_vue_id, int t_subcarrier_idx);

	/*
	* ��ȡ��Ӧ�����ڶ�Ӧ���ز��ϵĸ��ž�������
	*/
	std::vector<matrix> read_inter_h(const std::set<int>& t_sending_vue_id_set, int t_send_vue_id, int t_receive_vue_id, int t_subcarrier_idx);

	/*
	* ���ַ������㷨
	*/
	int closest(std::vector<double> t_vec, double t_target);

	/*
	* ���
	*/
	double get_mutual_information(std::vector<double> t_vec, int t_index);
};
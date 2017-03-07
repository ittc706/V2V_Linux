/*
* =====================================================================================
*
*       Filename:  gtt_urban.cpp
*
*    Description:  城镇类实现
*
*        Version:  1.0
*        Created:
*       Revision:
*       Compiler:  VS_2015
*
*         Author:  WYB
*            LIB:  ITTC
*
* =====================================================================================
*/

#include<fstream>
#include<utility>
#include<random>
#include"context.h"
#include"config.h"
#include"gtt_urban.h"
#include"vue.h"
#include"vue_physics.h"
#include"imta.h"
#include"function.h"


using namespace std;

void gtt_urban::initialize() {
	gtt_urban_config* __config = get_precise_config();
	int* m_pupr = new int[__config->get_road_num()];//每条路上的车辆数
	
	int tempVeUENum = 0;
	int Lambda = static_cast<int>((__config->get_road_length_ew() + __config->get_road_length_sn()) * 2 * 3.6 / (2.5 * __config->get_speed()));
	for (int temp = 0; temp != __config->get_road_num(); ++temp)
	{
		int k = 0;
		long double p = 1.0;
		long double l = exp(-Lambda);  /* 为了精度，才定义为long double的，exp(-Lambda)是接近0的小数*/
		while (p >= l)
		{
			double u = (double)(rand() % 10000)*0.0001f;
			p *= u;
			k++;
		}
		m_pupr[temp] = k - 1;
		tempVeUENum = tempVeUENum + k - 1;
	}

	//进行车辆的撒点
	context::get_context()->set_vue_array(new vue[tempVeUENum]);
	cout << "vuenum: " << tempVeUENum << endl;

	int vue_id = 0;
	double DistanceFromBottomLeft = 0;

	ofstream vue_coordinate;

	if (context::get_context()->get_global_control_config()->get_platform() == Windows) {
	vue_coordinate.open("log\\vue_coordinate.txt");
	}
	else {
	vue_coordinate.open("log/vue_coordinate.txt");
	}

	default_random_engine e((unsigned)time(0));
	uniform_real_distribution<double> u(0, 2 * (__config->get_road_length_ew() + __config->get_road_length_sn()));

	for (int RoadIdx = 0; RoadIdx != __config->get_road_num(); RoadIdx++) {
		for (int uprIdx = 0; uprIdx != m_pupr[RoadIdx]; uprIdx++) {
			auto p = context::get_context()->get_vue_array()[vue_id++].get_physics_level();
			DistanceFromBottomLeft = u(e);
			if (DistanceFromBottomLeft <= __config->get_road_length_ew()) {
				p->m_relx = -(__config->get_road_length_sn() + __config->get_road_width()) / 2;
				p->m_rely = DistanceFromBottomLeft - __config->get_road_length_ew() / 2;
				p->m_vangle = 90;
			}
			else if (DistanceFromBottomLeft > __config->get_road_length_ew() && DistanceFromBottomLeft <= (__config->get_road_length_ew() + __config->get_road_length_sn())) {
				p->m_relx = DistanceFromBottomLeft - __config->get_road_length_ew() - __config->get_road_length_sn() / 2;
				p->m_rely = (__config->get_road_length_ew() + __config->get_road_width()) / 2;
				p->m_vangle = 0;
			}
			else if (DistanceFromBottomLeft > (__config->get_road_length_ew() + __config->get_road_length_sn()) && DistanceFromBottomLeft < (__config->get_road_length_ew() * 2 + __config->get_road_length_sn())) {
				p->m_relx = (__config->get_road_length_sn() + __config->get_road_width()) / 2;
				p->m_rely = __config->get_road_length_ew() / 2 - (DistanceFromBottomLeft - (__config->get_road_length_ew() + __config->get_road_length_sn()));
				p->m_vangle = -90;
			}
			else {
				p->m_relx = __config->get_road_length_sn() / 2 - (DistanceFromBottomLeft - (__config->get_road_length_ew() * 2 + __config->get_road_length_sn()));
				p->m_rely = -(__config->get_road_length_ew() + __config->get_road_width()) / 2;
				p->m_vangle = -180;
			}
			p->m_road_id = RoadIdx;
			p->m_absx = __config->get_road_topo_ratio()[RoadIdx * 2 + 0] * (__config->get_road_length_sn() + 2 * __config->get_road_width()) + p->m_relx;
			p->m_absy = __config->get_road_topo_ratio()[RoadIdx * 2 + 1] * (__config->get_road_length_ew() + 2 * __config->get_road_width()) + p->m_rely;
			p->m_speed = __config->get_speed()/3.6;
			//将撒点后的坐标输出到txt文件
			vue_coordinate << p->m_absx << " ";
			vue_coordinate << p->m_absy << " ";
			vue_coordinate << endl;
		}
	}
	memory_clean::safe_delete(m_pupr, true);

	vue_coordinate.close();

	vue_physics::s_channel_all.assign(get_vue_num(),
		std::vector<std::vector<std::pair<bool, double*>>>(get_vue_num(),
			std::vector<std::pair<bool, double*>>(context::get_context()->get_rrm_config()->get_pattern_num(),
				std::pair<bool, double*>(false, nullptr))));

	vue_physics::s_pl_all.assign(get_vue_num(), std::vector<double>(get_vue_num(), 0));
	vue_physics::s_distance_all.assign(get_vue_num(), std::vector<double>(get_vue_num(), 0));
}

int gtt_urban::get_vue_num() {
	return vue_physics::get_vue_num();
}

void gtt_urban::fresh_location() {
	//<Warn>:将信道刷新时间和位置刷新时间分开
	if (context::get_context()->get_tti() % get_precise_config()->get_freshtime() != 0) {
		return;
	}

	for (int vue_id = 0; vue_id < get_vue_num(); vue_id++) {
		context::get_context()->get_vue_array()[vue_id].get_physics_level()->update_location_urban();
	}

	for (int vue_id1 = 0; vue_id1 < get_vue_num(); vue_id1++) {
		for (int vue_id2 = 0; vue_id2 < vue_id1; vue_id2++) {
			auto vuei = context::get_context()->get_vue_array()[vue_id1].get_physics_level();
			auto vuej = context::get_context()->get_vue_array()[vue_id2].get_physics_level();
			vue_physics::set_distance(vue_id2, vue_id1, sqrt(pow((vuei->m_absx - vuej->m_absx), 2.0f) + pow((vuei->m_absy - vuej->m_absy), 2.0f)));
		}
	}


}

void gtt_urban::clean_channel() {
	//<Warn>:将信道刷新时间和位置刷新时间分开
	if (context::get_context()->get_tti() % get_precise_config()->get_freshtime() != 0) {
		return;
	}

	for (int vue_id1 = 0; vue_id1 < get_vue_num(); vue_id1++) {
		for (int vue_id2 = 0; vue_id2 < vue_id1; vue_id2++) {
			for (int pattern_idx = 0; pattern_idx < context::get_context()->get_rrm_config()->get_pattern_num(); pattern_idx++) {
				vue_physics::s_channel_all[vue_id2][vue_id1][pattern_idx].first = false;
				memory_clean::safe_delete(vue_physics::s_channel_all[vue_id2][vue_id1][pattern_idx].second, true);


			}
		}
	}
}

void gtt_urban::calculate_channel(int t_vue_id1, int t_vue_id2, int t_pattern_idx) {

	location _location;
	_location.eNBAntH = 5;
	_location.VeUEAntH = 1.5;
	_location.RSUAntH = 5;
	_location.locationType = None;
	_location.distance = 0;
	_location.distance1 = 0;
	_location.distance2 = 0;

	antenna _antenna;
	_antenna.antGain = 3;
	_antenna.byTxAntNum = 1;
	_antenna.byRxAntNum = 2;

	imta* __imta = new imta();

	auto vuei = context::get_context()->get_vue_array()[t_vue_id1].get_physics_level();
	auto vuej = context::get_context()->get_vue_array()[t_vue_id2].get_physics_level();

	_location.locationType = Nlos;
	_location.manhattan = false;

	double angle = 0;
	_location.distance = vue_physics::get_distance(t_vue_id1, t_vue_id2);

	angle = atan2(vuei->m_absy - vuej->m_absy, vuei->m_absx - vuej->m_absx) / imta::s_DEGREE_TO_PI;

	imta::randomGaussian(_location.posCor, 5, 0.0f, 1.0f);//产生高斯随机数，为后面信道系数使用

	double m_FantennaAnglei;
	double m_FantennaAnglej;

	imta::randomUniform(&m_FantennaAnglei, 1, 180.0f, -180.0f, false);
	imta::randomUniform(&m_FantennaAnglej, 1, 180.0f, -180.0f, false);

	_antenna.TxAngle = angle - m_FantennaAnglei;
	_antenna.RxAngle = angle - m_FantennaAnglej;
	_antenna.TxSlantAngle = new double[_antenna.byTxAntNum];
	_antenna.TxAntSpacing = new double[_antenna.byTxAntNum];
	_antenna.RxSlantAngle = new double[_antenna.byRxAntNum];
	_antenna.RxAntSpacing = new double[_antenna.byRxAntNum];
	_antenna.TxSlantAngle[0] = 90.0f;
	_antenna.TxAntSpacing[0] = 0.0f;
	_antenna.RxSlantAngle[0] = 90.0f;
	_antenna.RxSlantAngle[1] = 90.0f;
	_antenna.RxAntSpacing[0] = 0.0f;
	_antenna.RxAntSpacing[1] = 0.5f;

	double t_Pl = 0;

	__imta->build(&t_Pl, imta::s_FC, _location, _antenna, vuei->m_speed, vuej->m_speed, vuei->m_vangle, vuej->m_vangle);//计算了结果代入信道模型计算UE之间信道系数

	vue_physics::set_pl(t_vue_id1, t_vue_id2, t_Pl);
	if (t_Pl>1e-15)
	{
		bool *flag = new bool();
		*flag = true;
		__imta->enable(flag);

		double *H = new double[1 * 2 * 19 * 2];
		double *FFT = new double[1 * 2 * 1024 * 2];
		double *ch_buffer = new double[1 * 2 * 19 * 20];
		double *ch_sin = new double[1 * 2 * 19 * 20];
		double *ch_cos = new double[1 * 2 * 19 * 20];

		double *t_HAfterFFT = new double[2 * 1024 * 2];

		__imta->calculate(t_HAfterFFT, 0.01f, ch_buffer, ch_sin, ch_cos, H, FFT);

		//一个pattern占用了多少个频点
		int point_num_per_pattern = context::get_context()->get_rrm_config()->get_rb_num_per_pattern() * 12;

		//将该pattern_idx对应的信道从t_HAfterFFT中取出来
		double *t_HAfterFFT_pattern = new double[2 * point_num_per_pattern * 2];

		//需要的频段相对于1024个频点的偏移量
		int offset = point_num_per_pattern*t_pattern_idx;
		for (int point_idx = 0; point_idx < point_num_per_pattern; point_idx++) {
			t_HAfterFFT_pattern[0 * (point_num_per_pattern * 2) + 2 * (point_idx)] = t_HAfterFFT[0 * (1024 * 2) + 2 * (point_idx + offset)];
			t_HAfterFFT_pattern[0 * (point_num_per_pattern * 2) + 2 * (point_idx)+1] = t_HAfterFFT[0 * (1024 * 2) + 2 * (point_idx + offset) + 1];

			t_HAfterFFT_pattern[1 * (point_num_per_pattern * 2) + 2 * point_idx] = t_HAfterFFT[1 * (1024 * 2) + 2 * (point_idx + offset)];
			t_HAfterFFT_pattern[1 * (point_num_per_pattern * 2) + 2 * point_idx + 1] = t_HAfterFFT[1 * (1024 * 2) + 2 * (point_idx + offset) + 1];
		}


		vue_physics::set_channel(t_vue_id1, t_vue_id2, t_pattern_idx, true, t_HAfterFFT_pattern);

		memory_clean::safe_delete(flag);
		memory_clean::safe_delete(H, true);
		memory_clean::safe_delete(ch_buffer, true);
		memory_clean::safe_delete(ch_sin, true);
		memory_clean::safe_delete(ch_cos, true);
		memory_clean::safe_delete(FFT, true);
		memory_clean::safe_delete(t_HAfterFFT, true);
	}
	else {
		vue_physics::set_channel(t_vue_id1, t_vue_id2, t_pattern_idx, true, nullptr);
	}
	memory_clean::safe_delete(_antenna.TxSlantAngle, true);
	memory_clean::safe_delete(_antenna.TxAntSpacing, true);
	memory_clean::safe_delete(_antenna.RxSlantAngle, true);
	memory_clean::safe_delete(_antenna.RxAntSpacing, true);

	memory_clean::safe_delete(__imta);
}

gtt_urban_config* gtt_urban::get_precise_config() {
	return (gtt_urban_config*)get_config();
}

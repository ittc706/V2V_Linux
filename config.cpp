/*
* =====================================================================================
*
*       Filename:  config.cpp
*
*    Description:  �����ļ���
*
*        Version:  1.0
*        Created:
*       Revision:
*       Compiler:  VS_2015
*
*         Author:  HCF
*            LIB:  ITTC
*
* =====================================================================================
*/

#include<iostream>
#include<fstream>
#include<sstream>
#include"config.h"
#include"context.h"
#include"config_loader.h"
#include"function.h"

using namespace std;

void global_control_config::set_config_loader(config_loader* t_config_loader) {
	m_config_loader = t_config_loader;
}

config_loader* global_control_config::get_config_loader() {
	return m_config_loader;
}

void global_control_config::set_platform(platform t_platform) {
	m_platform = t_platform;
}

platform global_control_config::get_platform() {
	return m_platform;
}

void global_control_config::set_ntti(int t_ntti) {
	m_ntti = t_ntti;
}

int global_control_config::get_ntti() {
	return m_ntti;
}

void global_control_config::set_fresh_period(int t_fresh_period) {
	m_fresh_period = t_fresh_period;
}

int global_control_config::get_fresh_period() {
	return m_fresh_period;
}

void global_control_config::load() {
	//�������жϵ�ǰ��ƽ̨������·���ı�ʾ������ƽ̨�µĲ������ж�
	ifstream inPlatformWindows("config\\global_control_config.xml"),
		inPlatformLinux("config/global_control_config.xml");

	if (inPlatformWindows.is_open()) {
		set_platform(Windows);
		cout << "����ǰ��ƽ̨Ϊ��Windows" << endl;
	}
	else if (inPlatformLinux.is_open()) {
		set_platform(Linux);
		cout << "����ǰ��ƽ̨Ϊ��Linux" << endl;
	}
	else
		throw logic_error("PlatformError");


	//��ʼ���������ļ�
	switch (get_platform()) {
	case Windows:
		get_config_loader()->resolv_config_file("config\\global_control_config.xml");
		break;
	case Linux:
		get_config_loader()->resolv_config_file("config/global_control_config.xml");
		break;
	default:
		throw logic_error("Platform Config Error!");
	}

	stringstream ss;

	const string nullString("");
	string temp;

	if ((temp = get_config_loader()->get_param("ntti")) != nullString) {
		ss << temp;
		int t_ntti;
		ss >> t_ntti;
		set_ntti(t_ntti);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	if ((temp = get_config_loader()->get_param("fresh_period")) != nullString) {
		ss << temp;
		int t_fresh_period;
		ss >> t_fresh_period;
		set_fresh_period(t_fresh_period);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	cout << "ntti: " << get_ntti() << endl;
	cout << "fresh_period: " << get_fresh_period() << endl;
}

void gtt_config::set_config_loader(config_loader* t_config_loader) {
	m_config_loader = t_config_loader;
}

config_loader* gtt_config::get_config_loader() {
	return m_config_loader;
}

int gtt_highspeed_config::get_road_num() {
	return m_road_num;
}

void gtt_highspeed_config::set_road_length(double t_road_length) {
	m_road_length = t_road_length;
}

double gtt_highspeed_config::get_road_length() {
	return m_road_length;
}

void gtt_highspeed_config::set_road_width(double t_road_width) {
	m_road_width = t_road_width;
}

double gtt_highspeed_config::get_road_width() {
	return m_road_width;
}

void gtt_highspeed_config::set_speed(double t_speed) {
	m_speed = t_speed;
}

double gtt_highspeed_config::get_speed() {
	return m_speed;
}

const double* gtt_highspeed_config::get_road_topo_ratio() {
	return m_road_topo_ratio;
}

void gtt_highspeed_config::set_freshtime(double t_freshtime) {
	m_freshtime = t_freshtime;
}

double gtt_highspeed_config::get_freshtime() {
	return m_freshtime;
}

void gtt_highspeed_config::load() {

	//��ʼ����ϵͳ�����ļ�
	switch (context::get_context()->get_global_control_config()->get_platform()) {
	case Windows:
		get_config_loader()->resolv_config_file("config\\gtt_highspeed_config.xml");
		break;
	case Linux:
		get_config_loader()->resolv_config_file("config/gtt_highspeed_config.xml");
		break;
	default:
		throw logic_error("Platform Config Error!");
	}

	stringstream ss;

	const string nullString("");
	string temp;

	if ((temp = get_config_loader()->get_param("road_length")) != nullString) {
		ss << temp;
		double t_road_length;
		ss >> t_road_length;
		set_road_length(t_road_length);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");


	if ((temp = get_config_loader()->get_param("road_width")) != nullString) {
		ss << temp;
		double t_road_width;
		ss >> t_road_width;
		set_road_width(t_road_width);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	if ((temp = get_config_loader()->get_param("speed")) != nullString) {
		ss << temp;
		double t_speed;
		ss >> t_speed;
		set_speed(t_speed);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	cout << "road_length: " << get_road_length() << endl;
	cout << "road_width: " << get_road_width() << endl;
	cout << "speed: " << get_speed() << endl;
}

void gtt_urban_config::load() {

}

void rrm_config::set_config_loader(config_loader* t_config_loader) {
	m_config_loader = t_config_loader;
}

config_loader* rrm_config::get_config_loader() {
	return m_config_loader;
}

void rrm_config::set_total_bandwidth(int t_total_bandwidth) {
	m_total_bandwidth = t_total_bandwidth;
}

int rrm_config::get_total_bandwidth() {
	return m_total_bandwidth;
}

void rrm_config::set_rb_num_per_pattern(int t_rb_num_per_pattern) {
	m_rb_num_per_pattern = t_rb_num_per_pattern;
}

int rrm_config::get_rb_num_per_pattern() {
	return m_rb_num_per_pattern;
}

void rrm_config::set_pattern_num() {
	m_pattern_num = get_total_bandwidth() / s_BANDWIDTH_OF_RB / get_rb_num_per_pattern();
}

int rrm_config::get_pattern_num() {
	return m_pattern_num;
}

void rrm_config::set_modulation_type(int t_modulation_type) {
	m_modulation_type = t_modulation_type;
}

int rrm_config::get_modulation_type() {
	return m_modulation_type;
}

void rrm_config::set_code_rate(double t_code_rate) {
	m_code_rate = t_code_rate;
}

double rrm_config::get_code_rate() {
	return m_code_rate;
}

void rrm_config::set_drop_sinr_boundary(double t_drop_sinr_boundary) {
	m_drop_sinr_boundary = t_drop_sinr_boundary;
}

double rrm_config::get_drop_sinr_boundary() {
	return m_drop_sinr_boundary;
}

void rrm_config::load() {
	//��ʼ����ϵͳ�����ļ�
	switch (context::get_context()->get_global_control_config()->get_platform()) {
	case Windows:
		get_config_loader()->resolv_config_file("config\\rrm_config.xml");
		break;
	case Linux:
		get_config_loader()->resolv_config_file("config/rrm_config.xml");
		break;
	default:
		throw logic_error("Platform Config Error!");
	}

	stringstream ss;

	const string nullString("");
	string temp;

	if ((temp = get_config_loader()->get_param("total_bandwidth")) != nullString) {
		ss << temp;
		int t_total_bandwidth;
		ss >> t_total_bandwidth;
		t_total_bandwidth *= 1000 * 1000;
		set_total_bandwidth(t_total_bandwidth);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	if ((temp = get_config_loader()->get_param("rb_num_per_pattern")) != nullString) {
		ss << temp;
		int t_rb_num_per_pattern;
		ss >> t_rb_num_per_pattern;
		set_rb_num_per_pattern(t_rb_num_per_pattern);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	if ((temp = get_config_loader()->get_param("modulation_type")) != nullString) {
		ss << temp;
		int t_modulation_type;
		ss >> t_modulation_type;
		set_modulation_type(t_modulation_type);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	if ((temp = get_config_loader()->get_param("code_rate")) != nullString) {
		ss << temp;
		double t_code_rate;
		ss >> t_code_rate;
		set_code_rate(t_code_rate);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	if ((temp = get_config_loader()->get_param("drop_sinr_boundary")) != nullString) {
		ss << temp;
		double t_drop_sinr_boundary;
		ss >> t_drop_sinr_boundary;
		set_drop_sinr_boundary(t_drop_sinr_boundary);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	set_pattern_num();

	cout << "total_bandwidth: " << get_total_bandwidth() << endl;
	cout << "rb_num_per_pattern: " << get_rb_num_per_pattern() << endl;
	cout << "pattern_num: " << get_pattern_num() << endl;
	cout << "modulation_type: " << get_modulation_type() << endl;
	cout << "code_rate: " << get_code_rate() << endl;
	cout << "drop_sinr_boundary: " << get_drop_sinr_boundary() << endl;
}

void tmc_config::set_config_loader(config_loader* t_config_loader) {
	m_config_loader = t_config_loader;
}

config_loader* tmc_config::get_config_loader() {
	return m_config_loader;
}

void tmc_config::set_congestion_level_num(int t_congestion_level_num) {
	m_congestion_level_num = t_congestion_level_num;
}

int tmc_config::get_congestion_level_num() {
	return m_congestion_level_num;
}

const std::vector<int>& tmc_config::get_periodic_event_period() {
	return m_periodic_event_period;
}

void tmc_config::set_package_num(int t_package_num) {
	m_package_num = t_package_num;
}

int tmc_config::get_package_num() {
	return m_package_num;
}

const std::vector<int>& tmc_config::get_bit_num_per_package() {
	return m_bit_num_per_package;
}

void tmc_config::load() {
	//��ʼ����ϵͳ�����ļ�
	switch (context::get_context()->get_global_control_config()->get_platform()) {
	case Windows:
		get_config_loader()->resolv_config_file("config\\tmc_config.xml");
		break;
	case Linux:
		get_config_loader()->resolv_config_file("config/tmc_config.xml");
		break;
	default:
		throw logic_error("Platform Config Error!");
	}

	stringstream ss;

	const string nullString("");
	string temp;

	if ((temp = get_config_loader()->get_param("congestion_level_num")) != nullString) {
		ss << temp;
		int t_congestion_level_num;
		ss >> t_congestion_level_num;
		set_congestion_level_num(t_congestion_level_num);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	if ((temp = get_config_loader()->get_param("periodic_event_period")) != nullString) {
		ss << temp;
		string temp2;
		while (ss >> temp2) {
			m_periodic_event_period.push_back(config_loader::string_to_int(temp2));
		}
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	if ((temp = get_config_loader()->get_param("package_num")) != nullString) {
		ss << temp;
		int t_package_num;
		ss >> t_package_num;
		set_package_num(t_package_num);
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	if ((temp = get_config_loader()->get_param("bit_num_per_package")) != nullString) {
		ss << temp;
		string temp2;
		while (ss >> temp2) {
			m_bit_num_per_package.push_back(config_loader::string_to_int(temp2));
		}
		ss.clear();//�����־λ
		ss.str("");
	}
	else
		throw logic_error("ConfigLoaderError");

	cout << "congestion_level_num: " << get_congestion_level_num() << endl;
	array_print::print_vector_dim1(get_periodic_event_period());
	cout << "package_num: " << get_package_num() << endl;
	array_print::print_vector_dim1(get_bit_num_per_package());
}
#pragma once

#include<vector>
#include"enumeration.h"

#define INVALID -1

class config_loader;

class global_control_config {
	/*------------------友元声明------------------*/
	/*
	* 将context设为友元，容器要为其注入依赖项
	*/
	friend class context;

	/*--------------------字段--------------------*/
	/*
	* 类加载器对象
	*/
private:
	config_loader* m_config_loader;
	void set_config_loader(config_loader* t_config_loader);
public:
	config_loader* get_config_loader();

	/*
	* 平台
	*/
private:
	platform m_platform;
	void set_platform(platform t_platform);
public:
	platform get_platform();

	/*
	* 仿真时长
	*/
private:
	int m_ntti;
	void set_ntti(int t_ntti);
public:
	int get_ntti();

	/*
	* gtt模式选择
	*/
private:
	gtt_mode m_gtt_mode;
	void set_gtt_mode(gtt_mode t_gtt_mode);
public:
	gtt_mode get_gtt_mode();

	/*--------------------接口--------------------*/
public:
	void load();
};


class gtt_config {
	/*------------------友元声明------------------*/
	/*
	* 将context设为友元，容器要为其注入依赖项
	*/
	friend class context;

	/*--------------------字段--------------------*/
	/*
	* 根据gtt模式来生成gtt_config配置文件对象
	*/
	static gtt_config* gtt_config_bind_by_mode(gtt_mode t_mode);

	/*--------------------字段--------------------*/
	/*
	* 类加载器对象
	*/
private:
	config_loader* m_config_loader;
	void set_config_loader(config_loader* t_config_loader);
public:
	config_loader* get_config_loader();

	/*--------------------接口--------------------*/
public:
	virtual void load() = 0;
};


class gtt_highspeed_config :public gtt_config {
	/*--------------------字段--------------------*/
	/*
	* 道路数量
	*/
private:
	const int m_road_num = 6;
public:
	int get_road_num();

	/*
	* 路长,单位m
	*/
private:
	double m_road_length = INVALID;
	void set_road_length(double t_road_length);
public:
	double get_road_length();

	/*
	* 路宽，单位m
	*/
private:
	double m_road_width = INVALID;
	void set_road_width(double t_road_width);
public:
	double get_road_width();

	/*
	* 车速,km/h
	*/
private:
	double m_speed = INVALID;
	void set_speed(double t_speed);
public:
	double get_speed();

	/*
	* 道路拓扑位置
	*/
private:
	const double m_road_topo_ratio[6 * 2]{
		0.0f, -2.5f,
		0.0f, -1.5f,
		0.0f, -0.5f,
		0.0f, 0.5f,
		0.0f, 1.5f,
		0.0f, 2.5f,
	};
public:
	const double* get_road_topo_ratio();

	/*
	* 车辆位置刷新时间,单位s
	*/
private:
	int m_freshtime = INVALID;
	void set_freshtime(int t_freshtime);
public:
	int get_freshtime();

	/*--------------------接口--------------------*/
public:
	void load() override;

};


class gtt_urban_config :public gtt_config {
	/*--------------------接口--------------------*/
public:
	void load() override;
	/*
	* 街区数量
	*/
private:
	const int m_road_num = 14;
public:
	int get_road_num();

	/*
	* 路长，分为东西向和南北向,单位m
	*/
private:
	double m_road_length_ew = INVALID;
	double m_road_length_sn = INVALID;
	void set_road_length_ew(double t_road_length_ew);
	void set_road_length_sn(double t_road_length_sn);
public:
	double get_road_length_ew();
	double get_road_length_sn();

	/*
	* 路宽，单位m
	*/
private:
	double m_road_width = INVALID;
	void set_road_width(double t_road_width);
public:
	double get_road_width();

	/*
	* 车速,km/h
	*/
private:
	double m_speed = INVALID;
	void set_speed(double t_speed);
public:
	double get_speed();

	/*
	* 道路拓扑位置
	*/
private:
	const double m_road_topo_ratio[14 * 2] = {
		-1.5f, 1.0f,
		-0.5f, 1.0f,
		0.5f, 1.0f,
		1.5f, 1.0f,
		-2.5f, 0.0f,
		-1.5f, 0.0f,
		-0.5f, 0.0f,
		0.5f, 0.0f,
		1.5f, 0.0f,
		2.5f, 0.0f,
		-1.5f,-1.0f,
		-0.5f,-1.0f,
		0.5f,-1.0f,
		1.5f,-1.0f
	};

private:
	const int m_wrap_around_road[14][9] = {
		{ 0,1,6,5,4,13,8,9,10 },
		{ 1,2,7,6,5,0,9,10,11 },
		{ 2,3,8,7,6,1,10,11,12 },
		{ 3,4,9,8,7,2,11,12,13 },
		{ 4,5,10,9,8,3,12,13,0 },
		{ 5,6,11,10,9,4,13,0,1 },
		{ 6,7,12,11,10,5,0,1,2 },
		{ 7,8,13,12,11,6,1,2,3 },
		{ 8,9,0,13,12,7,2,3,4 },
		{ 9,10,1,0,13,8,3,4,5 },
		{ 10,11,2,1,0,9,4,5,6 },
		{ 11,12,3,2,1,10,5,6,7 },
		{ 12,13,4,3,2,11,6,7,8 },
		{ 13,0,5,4,3,12,7,8,9 }
	};

public:
	const double* get_road_topo_ratio();
	const int(*get_wrap_around_road())[9];
	/*
	* 车辆位置刷新时间,单位s
	*/
private:
	int m_freshtime = INVALID;
	void set_freshtime(int t_freshtime);
public:
	int get_freshtime();

};


class rrm_config {
	/*------------------友元声明------------------*/
	/*
	* 将context设为友元，容器要为其注入依赖项
	*/
	friend class context;

	/*------------------静态成员------------------*/
public:
	/*
	* 每个RB的带宽(Hz)
	*/
	static const int s_BANDWIDTH_OF_RB = 12 * 1000 * 15;

	/*
	* 单位(个),由于RB带宽为180kHz，TTI为1ms，因此单位TTI单位RB传输的比特数为180k*1ms=180
	*/
	static const int s_BIT_NUM_PER_RB = 180;

	/*--------------------字段--------------------*/
	/*
	* 类加载器对象
	*/
private:
	config_loader* m_config_loader;
	void set_config_loader(config_loader* t_config_loader);
public:
	config_loader* get_config_loader();

	/*
	* 总带宽
	*/
private:
	int m_total_bandwidth;
	void set_total_bandwidth(int t_total_bandwidth);
public:
	int get_total_bandwidth();

	/*
	* 一个可用资源块的rb数量
	*/
private:
	int m_rb_num_per_pattern;
	void set_rb_num_per_pattern(int t_rb_num_per_pattern);
public:
	int get_rb_num_per_pattern();

	/*
	* pattern数量
	*/
private:
	int m_pattern_num;
	void set_pattern_num();
public:
	int get_pattern_num();

	/*
	* 丢包临界sinr
	*/
private:
	double m_drop_sinr_boundary;
	void set_drop_sinr_boundary(double t_drop_sinr_boundary);
public:
	double get_drop_sinr_boundary();

	/*
	* 选择算法
	*/
private:
	int m_select_altorithm;
	void set_select_altorithm(int t_select_altorithm);
public:
	int get_select_altorithm();

	/*
	* 选择算法
	*/
private:
	int m_time_division_granularity;
	void set_time_division_granularity(int t_time_division_granularity);
public:
	int get_time_division_granularity();
	/*--------------------接口--------------------*/
public:
	void load();
};


class tmc_config {
	/*------------------友元声明------------------*/
	/*
	* 将context设为友元，容器要为其注入依赖项
	*/
	friend class context;

	/*--------------------字段--------------------*/
	/*
	* 类加载器对象
	*/
private:
	config_loader* m_config_loader;
	void set_config_loader(config_loader* t_config_loader);
public:
	config_loader* get_config_loader();

	/*
	* 拥塞等级数量
	*/
private:
	int m_congestion_level_num;
	void set_congestion_level_num(int t_congestion_level_num);
public:
	int get_congestion_level_num();

	/*
	* 对应拥塞等级下周期事件周期
	*/
private:
	std::vector<int> m_periodic_event_period_per_congestion_level;
public:
	const std::vector<int>& get_periodic_event_period_per_congestion_level();

	/*
	* 周期事件包数
	*/
private:
	int m_package_num;
	void set_package_num(int t_package_num);
public:
	int get_package_num();

	/*
	* 每个包的传输时间，以TTI为单位
	*/
private:
	std::vector<int> m_tti_per_package;
public:
	const std::vector<int>& get_tti_per_package();
	/*--------------------接口--------------------*/
public:
	void load();
};
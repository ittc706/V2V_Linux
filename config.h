#pragma once

#include<vector>

enum platform{
	Windows,
	Linux
};

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
	* 信道刷新周期
	*/
private:
	int m_fresh_period;
	void set_fresh_period(int t_fresh_period);
public:
	int get_fresh_period();

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
	double m_road_length = 3464;
	void set_road_length(double t_road_length);
public:
	double get_road_length();

	/*
	* 路宽，单位m
	*/
private:
	double m_road_width = 4;
	void set_road_width(double t_road_width);
public:
	double get_road_width();

	/*
	* 车速,km/h
	*/
private:
	double m_speed = 140;
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
	double m_freshtime = 0.1;
	void set_freshtime(double t_freshtime);
public:
	double get_freshtime();

	/*--------------------接口--------------------*/
public:
	void load() override;
};


class gtt_urban_config :public gtt_config {
	/*--------------------接口--------------------*/
public:
	void load() override;
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
	* 调制方式
	* 2:QOSK
	* 4:16QAM
	* 6:64QAM
	*/
private:
	int m_modulation_type;
	void set_modulation_type(int t_modulation_type);
public:
	int get_modulation_type();

	/*
	* 信道编码码率
	*/
private:
	double m_code_rate;
	void set_code_rate(double t_code_rate);
public:
	double get_code_rate();

	/*
	* 丢包临界sinr
	*/
private:
	double m_drop_sinr_boundary;
	void set_drop_sinr_boundary(double t_drop_sinr_boundary);
public:
	double get_drop_sinr_boundary();
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
	std::vector<int> m_periodic_event_period;
public:
	const std::vector<int>& get_periodic_event_period();

	/*
	* 周期事件包数
	*/
private:
	int m_package_num;
	void set_package_num(int t_package_num);
public:
	int get_package_num();

	/*
	* 周期事件每个包对应的bit数量
	*/
private:
	std::vector<int> m_bit_num_per_package;
public:
	const std::vector<int>& get_bit_num_per_package();
	/*--------------------接口--------------------*/
public:
	void load();
};
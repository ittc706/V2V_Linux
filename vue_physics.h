#pragma once

#include<vector>
#include<random>
#include<list>

class vue_physics {
	/*------------------友元声明------------------*/
	/*
	* 将vue设为友元，由于vue_physics的构造函数设为私有，但可由vue来调用
	*/
	friend class vue;
	friend class gtt_highspeed;
	friend class gtt_urban;

	/*----------------拷贝控制成员----------------*/
private:
	/*
	* 默认构造函数
	* 设为私有，其初始化完全交给vue来完成，禁止生成该类型的实例
	*/
	vue_physics();

public:
	/*
	* 析构函数，负责清理资源
	*/
	~vue_physics();

	/*
	* 将拷贝构造函数定义为删除
	*/
	vue_physics(const vue_physics& t_vue_physics) = delete;

	/*
	* 将移动构造函数定义为删除
	*/
	vue_physics(vue_physics&& t_vue_physics) = delete;

	/*
	* 将拷贝赋值运算符定义为删除
	*/
	vue_physics& operator=(const vue_physics& t_vue_physics) = delete;

	/*
	* 将移动赋值运算符定义为删除
	*/
	vue_physics& operator=(vue_physics&& t_vue_physics) = delete;

	/*------------------静态成员------------------*/

	/*
	* 车辆总数
	*/
private:
	static int s_vue_count;
public:
	static int get_vue_num();

	/*
	* 车辆之间的小尺度衰落
	* 前两层下标为车辆id，例如s_channel_all[i][j],且i<j
	*/
private:
	static std::vector<std::vector<double*>> s_channel_all;
	static void set_channel(int i, int j, double* t_channel);
public:
	static double* get_channel(int i, int j);

	/*
	* 车辆之间的大尺度衰落
	* 前两层下标为车辆id，例如s_pl_all[i][j],且i<j
	*/
private:
	static std::vector<std::vector<double>> s_pl_all;
	static void set_pl(int i, int j, double t_pl);
public:
	static double get_pl(int i, int j);

	/*
	* 车辆与车辆之间的距离
	* 前两层下标为车辆id，例如s_distance_all[i][j],且i<j
	*/
private:
	static std::vector<std::vector<double>> s_distance_all;
	static void set_distance(int i, int j, double t_distance);
public:
	static double get_distance(int i, int j);

	/*--------------------字段--------------------*/
	/*
	* 指向上层的指针
	*/
private:
	vue* m_superior_level;
	void set_superior_level(vue* t_superior_level);
public:
	vue* get_superior_level();

	/*
	* 车辆编号
	*/
private:
	int m_vue_id = s_vue_count++;
public:
	int get_vue_id();

	/*
	* 车速，m/s
	*/
private:
	double m_speed = 0;

	/*
	* 速度方向,0代表向东，180代表向西,90代表向北，-90代表向南
	*/
private:
	double m_vangle = 0;

	/*
	* 绝对横坐标，单位m
	*/
private:
	double m_absx = 0;

	/*
	* 绝对纵坐标，单位m
	*/
private:
	double m_absy = 0;

	/*
	*相对横坐标，单位m
	*/
private:
	double m_relx = 0;

	/*
	* 相对纵坐标，单位m
	*/
private:
	double m_rely = 0;
	/*
	* 所在街区id
	*/
private:
	int m_road_id = -1;

	/*
	* 拥塞等级<Warn>:目前暂时设为0
	*/
private:
	int m_congestion_level = 0;
public:
	int get_congestion_level();
	/*----------------访问与编辑器----------------*/
public:

	/*--------------------方法--------------------*/
public:
	void update_location_highspeed();
	void update_location_urban();
};
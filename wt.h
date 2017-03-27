#pragma once

#include<set>
#include<random>
#include<utility>
#include<memory>
#include"matrix.h"

class sender_event;

class wt {
	/*------------------友元声明------------------*/
	/*
	* 将context设为友元，容器要为其注入依赖项
	*/
	friend class context;

	/*---------------静态成员---------------*/
private:
	/*
	* 随机数引擎，该类共享
	*/
	static std::default_random_engine s_engine;

	/*
	* 共享资源
	*/
	static std::vector<double>* m_qpsk_mi;

	/*
	* 公共资源资源初始化，交由容器调用
	*/
	static void set_resource();
	/*----------------字段------------------*/
private:
	/*
	* 发送天线数
	*/
	int m_nt = 1;

	/*
	* 接收天线数
	*/
	int m_nr = 2;

	/*
	* 发射功率
	*/
	double m_pt;

	/*
	* 距离路径损耗
	*/
	double m_ploss;

	/*
	* 干扰距离路径损耗
	*/
	std::vector<double> m_inter_ploss;

	/*
	* 高斯噪声的功率，单位是mw
	*/
	double m_sigma;

	/*
	* 每个子载波有一个nr*nt的信道矩阵
	*/
	matrix m_h;

	/*
	* 每个子载波有一组nr*nt的干扰信道矩阵
	* 下标为干扰源编号
	*/
	std::vector<matrix> m_inter_h;

	

	/*------------------接口------------------*/
public:
	/*
	* 默认构造函
	*/
	wt();

	/*
	* 析构函数
	*/
	~wt();

	/*
	* 计算载干比
	* t_send_vue_id:当前链路的发送端车辆id
	* t_receive_vue_id:当前链路的接收端车辆id
	* t_pattern_idx:当前占用的pattern_idx
	* t_sending_vue_id_set:在该子载波区间进行发送的车辆id列表，包括t_send_vue_id
	* 计算载干比分为屏蔽小尺度和计算小尺度两种
	*/
	double calculate_sinr(int t_send_vue_id, int t_receive_vue_id, int t_pattern_idx, const std::set<int>& t_sending_vue_id_set);
	double calculate_sinr_without_fast_fading(int t_send_vue_id, int t_receive_vue_id, int t_pattern_idx, const std::set<int>& t_sending_vue_id_set);
private:
	/*
	* 读取对应子载波的信道响应矩阵
	*/
	matrix read_h(int t_send_vue_id, int t_receive_vue_id, int t_pattern_idx, int t_subcarrier_idx);

	/*
	* 读取对应车辆在对应子载波上的干扰矩阵数组
	*/
	std::vector<matrix> read_inter_h(const std::set<int>& t_sending_vue_id_set, int t_send_vue_id, int t_receive_vue_id, int t_pattern_idx, int t_subcarrier_idx);

	/*
	* 二分法查找算法
	*/
	int closest(std::vector<double> t_vec, double t_target);

	/*
	* 查表
	*/
	double get_mutual_information(std::vector<double> t_vec, int t_index);
};
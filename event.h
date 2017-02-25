#pragma once

#include<vector>

class sender_event {
	/*------------------友元声明------------------*/
	/*
	* 将tmc设为友元，事件相关的字段需要通过tmc对象来配置
	*/
	friend class tmc;
	/*------------------静态成员------------------*/
private:
	static int s_event_count;

	/*----------------拷贝控制成员----------------*/
public:
	/*
	* 默认构造函数
	*/
	sender_event();

	/*
	* 析构函数，负责清理资源
	*/
	~sender_event();

	/*
	* 将拷贝构造函数定义为删除
	*/
	sender_event(const sender_event& t_sender_event) = delete;

	/*
	* 将移动构造函数定义为删除
	*/
	sender_event(sender_event&& t_sender_event) = delete;

	/*
	* 将拷贝赋值运算符定义为删除
	*/
	sender_event& operator=(const sender_event& t_sender_event) = delete;

	/*
	* 将移动赋值运算符定义为删除
	*/
	sender_event& operator=(sender_event&& t_sender_event) = delete;
	
	/*--------------------字段--------------------*/
	/*
	* 事件id
	*/
private:
	int m_event_id = s_event_count++;
public:
	int get_event_id();

	/*
	* 车辆id
	*/
private:
	int m_vue_id;
	void set_vue_id(int t_vue_id);
public:
	int get_vue_id();

	/*
	* 占用频段
	*/
private:
	int m_pattern_idx;
public:
	void set_pattern_idx(int t_pattern_idx);
	int get_pattern_idx();
	/*--------------------方法--------------------*/
};


class receiver_event {
	/*----------------拷贝控制成员----------------*/
public:
	/*
	* 默认构造函数
	*/
	receiver_event() = delete;

	/*
	* 构造函数
	*/
	receiver_event(sender_event* t_sender_event, int t_receiver_vue_id);

	/*
	* 析构函数，负责清理资源
	*/
	~receiver_event();

	/*
	* 将拷贝构造函数定义为删除
	*/
	receiver_event(const receiver_event& t_receiver_event) = delete;

	/*
	* 将移动构造函数定义为删除
	*/
	receiver_event(receiver_event&& t_receiver_event) = delete;

	/*
	* 将拷贝赋值运算符定义为删除
	*/
	receiver_event& operator=(const receiver_event& t_receiver_event) = delete;

	/*
	* 将移动赋值运算符定义为删除
	*/
	receiver_event& operator=(receiver_event&& t_receiver_event) = delete;

	/*--------------------字段--------------------*/
	/*
	* 事件id，与发送事件相同
	*/
private:
	int m_event_id;
	void set_event_id(int t_event_id);
public:
	int get_event_id();

	/*
	* 发送车辆id
	*/
private:
	int m_send_vue_id;
	void set_send_vue_id(int t_send_vue_id);
public:
	int get_send_vue_id();

	/*
	* 接收车辆id
	*/
private:
	int m_receive_vue_id;
	void set_receive_vue_id(int t_receive_vue_id);
public:
	int get_receive_vue_id();

	/*
	* 收发车辆之间的距离
	*/
private:
	double m_distance;
	void set_distance(double t_distance);
public:
	double get_distance();

	/*
	* 占用频段
	*/
private:
	int m_pattern_idx;
public:
	void set_pattern_idx(int t_pattern_idx);
	int get_pattern_idx();

	/*
	* 数据包总数
	*/
private:
	int m_package_num;

	/*
	* 每个包的bit数量
	*/
private:
	std::vector<int> m_bit_num_per_package;

	/*
	* 标记即将要传输的bit所在的包序号
	*/
private:
	int m_package_idx = 0;

	/*
	* 当前包剩余bit数目
	*/
private:
	int m_remain_bit_num;

	/*
	* 标记是否传输完毕(无论是否发生丢包)
	*/
private:
	bool m_is_finished = false;
public:
	bool get_is_finished();

	/*
	* 标记是否发生丢包
	*/
private:
	bool m_is_loss = false;
public:
	void set_is_loss();
	bool get_is_loss();

	/*--------------------接口--------------------*/
	void transimit(int t_transimit_max_bit_num);
};
#pragma once

#include<vector>

enum event_type {
	PERIOD
};


class sender_event {
	/*------------------��Ԫ����------------------*/
	/*
	* ��tmc��Ϊ��Ԫ���¼���ص��ֶ���Ҫͨ��tmc����������
	*/
	friend class tmc;
	/*------------------��̬��Ա------------------*/
private:
	static int s_event_count;

	/*----------------�������Ƴ�Ա----------------*/
public:
	/*
	* Ĭ�Ϲ��캯��
	*/
	sender_event();

	/*
	* ��������������������Դ
	*/
	~sender_event();

	/*
	* ���������캯������Ϊɾ��
	*/
	sender_event(const sender_event& t_sender_event) = delete;

	/*
	* ���ƶ����캯������Ϊɾ��
	*/
	sender_event(sender_event&& t_sender_event) = delete;

	/*
	* ��������ֵ���������Ϊɾ��
	*/
	sender_event& operator=(const sender_event& t_sender_event) = delete;

	/*
	* ���ƶ���ֵ���������Ϊɾ��
	*/
	sender_event& operator=(sender_event&& t_sender_event) = delete;
	
	/*--------------------�ֶ�--------------------*/
	/*
	* �¼�id
	*/
private:
	int m_event_id = s_event_count++;
public:
	int get_event_id();

	/*
	* ����id
	*/
private:
	int m_vue_id;
	void set_vue_id(int t_vue_id);
public:
	int get_vue_id();

	/*
	* ռ��Ƶ��
	*/
private:
	int m_pattern_idx;
public:
	void set_pattern_idx(int t_pattern_idx);
	int get_pattern_idx();
	/*--------------------����--------------------*/
};


class receiver_event {
	/*----------------�������Ƴ�Ա----------------*/
public:
	/*
	* Ĭ�Ϲ��캯��
	*/
	receiver_event() = delete;

	/*
	* ���캯��
	*/
	receiver_event(sender_event* t_sender_event, int t_receiver_vue_id);

	/*
	* ��������������������Դ
	*/
	~receiver_event();

	/*
	* ���������캯������Ϊɾ��
	*/
	receiver_event(const receiver_event& t_receiver_event) = delete;

	/*
	* ���ƶ����캯������Ϊɾ��
	*/
	receiver_event(receiver_event&& t_receiver_event) = delete;

	/*
	* ��������ֵ���������Ϊɾ��
	*/
	receiver_event& operator=(const receiver_event& t_receiver_event) = delete;

	/*
	* ���ƶ���ֵ���������Ϊɾ��
	*/
	receiver_event& operator=(receiver_event&& t_receiver_event) = delete;

	/*--------------------�ֶ�--------------------*/
	/*
	* �¼�id���뷢���¼���ͬ
	*/
private:
	int m_event_id;
	void set_event_id(int t_event_id);
public:
	int get_event_id();

	/*
	* ���ͳ���id
	*/
private:
	int m_send_vue_id;
	void set_send_vue_id(int t_send_vue_id);
public:
	int get_send_vue_id();

	/*
	* ���ճ���id
	*/
private:
	int m_receive_vue_id;
	void set_receive_vue_id(int t_receive_vue_id);
public:
	int get_receive_vue_id();

	/*
	* �շ�����֮��ľ���
	*/
private:
	double m_distance;
	void set_distance(double t_distance);
public:
	double get_distance();

	/*
	* ռ��Ƶ��
	*/
private:
	int m_pattern_idx;
public:
	void set_pattern_idx(int t_pattern_idx);
	int get_pattern_idx();

	/*
	* ���ݰ�����
	*/
private:
	int m_package_num;

	/*
	* ÿ������bit����
	*/
private:
	std::vector<int> m_bit_num_per_package;

	/*
	* ��Ǽ���Ҫ�����bit���ڵİ����
	*/
private:
	int m_package_idx = 0;

	/*
	* ��ǰ��ʣ��bit��Ŀ
	*/
private:
	int m_remain_bit_num;

	/*
	* ����Ƿ������(�����Ƿ�������)
	*/
private:
	bool m_is_finished = false;
public:
	bool get_is_finished();

	/*
	* ����Ƿ�������
	*/
private:
	bool m_is_loss = false;
public:
	void set_is_loss();
	bool get_is_loss();

	/*--------------------�ӿ�--------------------*/
	void transimit(int t_transimit_max_bit_num);
};
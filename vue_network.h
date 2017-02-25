#pragma once

#include<random>
#include<vector>
#include<list>
#include<set>

class sender_event;

class vue_network {
	/*------------------��Ԫ����------------------*/
	/*
	* ��vue��Ϊ��Ԫ������vue_network�Ĺ��캯����Ϊ˽�У�������vue������
	*/
	friend class vue;

	/*
	* ��tmc��Ϊ��Ԫ���¼���ص��ֶ���Ҫͨ��tmc����������
	*/
	friend class tmc;

	/*
	* ��rrm��Ϊ��Ԫ���¼���ص��ֶ���Ҫͨ��rrm����������
	*/
	friend class rrm;

	/*
	* ��vue_link��Ϊ��Ԫ
	*/
	friend class vue_link;

	/*------------------��̬��Ա------------------*/
private:
	/*
	* ���������
	*/
	static std::default_random_engine s_engine;

	/*
	* ���ڴ���ĳ���id
	* ����±�Ϊpattern���
	*/
	static std::vector<std::set<int>> s_vue_id_per_pattern;

	/*
	* ������ϵĳ���id
	* ����±�Ϊpattern���
	*/
	static std::vector<std::set<int>> s_vue_id_per_pattern_finished;

public:
	/*
	* ���ڸ���s_vue_id_per_pattern
	* ��s_vue_id_per_patternɾȥs_vue_id_per_pattern_finished
	*/
	static void update_vue_id_per_pattern();

	/*----------------�������Ƴ�Ա----------------*/
private:
	/*
	* Ĭ�Ϲ��캯��
	* ��Ϊ˽�У����ʼ����ȫ����vue����ɣ���ֹ���ɸ����͵�ʵ��
	*/
	vue_network();

public:
	/*
	* ��������������������Դ
	*/
	~vue_network();

	/*
	* ���������캯������Ϊɾ��
	*/
	vue_network(const vue_network& t_vue_network) = delete;

	/*
	* ���ƶ����캯������Ϊɾ��
	*/
	vue_network(vue_network&& t_vue_network) = delete;

	/*
	* ��������ֵ���������Ϊɾ��
	*/
	vue_network& operator=(const vue_network& t_vue_network) = delete;

	/*
	* ���ƶ���ֵ���������Ϊɾ��
	*/
	vue_network& operator=(vue_network&& t_vue_network) = delete;

	/*--------------------�ֶ�--------------------*/
	/*
	* ָ���ϲ��ָ��
	*/
private:
	vue* m_superior_level;
	void set_superior_level(vue* t_superior_level);
public:
	vue* get_superior_level();

	/*
	* �����¼���һ�δ���ʱ��
	*/
private:
	std::vector<int> m_periodic_event_next_trigger_tti;
	void set_periodic_event_next_trigger_tti(int t_congestion_level_num);
public:
	const std::vector<int>& get_periodic_event_next_trigger_tti();

	/*
	* ����Ƿ��д����¼�
	*/
private:
	/*
	* �����¼��б�
	*/
	std::list<sender_event*> m_sender_event_list;
	void add_sender_event(sender_event* t_sender_event);

	/*--------------------�ӿ�--------------------*/
public:
	/*
	* �շ�������������(���������ϵ�����)
	*/
	void send_connection();

	/*--------------------ʵ��--------------------*/
private:
	/*
	* ѡ��ռ�õ���Դ����
	*/
	int select_pattern();
};
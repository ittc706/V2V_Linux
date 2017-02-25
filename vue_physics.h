#pragma once

#include<vector>
#include<random>
#include<list>

class vue_physics {
	/*------------------��Ԫ����------------------*/
	/*
	* ��vue��Ϊ��Ԫ������vue_physics�Ĺ��캯����Ϊ˽�У�������vue������
	*/
	friend class vue;
	friend class gtt_highspeed;

	/*----------------�������Ƴ�Ա----------------*/
private:
	/*
	* Ĭ�Ϲ��캯��
	* ��Ϊ˽�У����ʼ����ȫ����vue����ɣ���ֹ���ɸ����͵�ʵ��
	*/
	vue_physics();

public:
	/*
	* ��������������������Դ
	*/
	~vue_physics();

	/*
	* ���������캯������Ϊɾ��
	*/
	vue_physics(const vue_physics& t_vue_physics) = delete;

	/*
	* ���ƶ����캯������Ϊɾ��
	*/
	vue_physics(vue_physics&& t_vue_physics) = delete;

	/*
	* ��������ֵ���������Ϊɾ��
	*/
	vue_physics& operator=(const vue_physics& t_vue_physics) = delete;

	/*
	* ���ƶ���ֵ���������Ϊɾ��
	*/
	vue_physics& operator=(vue_physics&& t_vue_physics) = delete;

	/*------------------��̬��Ա------------------*/

	/*
	* ��������
	*/
private:
	static int s_vue_count;
public:
	static int get_vue_num();

	/*
	* ����֮���С�߶�˥��
	* ǰ�����±�Ϊ����id������s_channel_all[i][j],��i<j
	*/
private:
	static std::vector<std::vector<double*>> s_channel_all;
	static void set_channel(int i, int j, double* t_channel);
public:
	static double* get_channel(int i, int j);

	/*
	* ����֮��Ĵ�߶�˥��
	* ǰ�����±�Ϊ����id������s_pl_all[i][j],��i<j
	*/
private:
	static std::vector<std::vector<double>> s_pl_all;
	static void set_pl(int i, int j, double t_pl);
public:
	static double get_pl(int i, int j);

	/*
	* �����복��֮��ľ���
	* ǰ�����±�Ϊ����id������s_distance_all[i][j],��i<j
	*/
private:
	static std::vector<std::vector<double>> s_distance_all;
	static void set_distance(int i, int j, double t_distance);
public:
	static double get_distance(int i, int j);

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
	* �������
	*/
private:
	int m_vue_id = s_vue_count++;
public:
	int get_vue_id();

	/*
	* ���٣�km/h
	*/
private:
	double m_speed = 0;

	/*
	* �ٶȷ���,0�����򶫣�180��������
	*/
private:
	double m_vangle = 0;

	/*
	* ���Ժ����꣬��λm
	*/
private:
	double m_absx = 0;

	/*
	* ���������꣬��λm
	*/
private:
	double m_absy = 0;

	/*
	*��Ժ����꣬��λm
	*/
private:
	double m_relx = 0;

	/*
	* ��������꣬��λm
	*/
private:
	double m_rely = 0;

	/*
	* ӵ���ȼ�<Warn>:Ŀǰ��ʱ��Ϊ0
	*/
private:
	int m_congestion_level = 0;
public:
	int get_congestion_level();
	/*----------------������༭��----------------*/
public:

	/*--------------------����--------------------*/
public:
	void update_location();
};
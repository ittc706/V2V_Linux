#pragma once

class gtt_config;

class gtt {
	/*------------------��Ԫ����------------------*/
	/*
	* ��context��Ϊ��Ԫ������ҪΪ��ע��������
	*/
	friend class context;

	/*--------------------�ֶ�--------------------*/
	/*
	* �������ò�������
	*/
private:
	gtt_config* m_config;
	void set_config(gtt_config* t_config);
public:
	gtt_config* get_config();

	/*--------------------�ӿ�--------------------*/

	virtual void initialize() = 0;

	virtual int get_vue_num() = 0;

	virtual void update_channel() = 0;
};
#pragma once

class gtt_config;

class gtt {
	/*------------------友元声明------------------*/
	/*
	* 将context设为友元，容器要为其注入依赖项
	*/
	friend class context;

	/*--------------------字段--------------------*/
	/*
	* 场景配置参数对象
	*/
private:
	gtt_config* m_config;
	void set_config(gtt_config* t_config);
public:
	gtt_config* get_config();

	/*--------------------接口--------------------*/

	virtual void initialize() = 0;

	virtual int get_vue_num() = 0;

	virtual void update_channel() = 0;
};
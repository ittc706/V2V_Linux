#pragma once

#include<string>
#include"enumeration.h"

class gtt_config;

class gtt {
	/*------------------友元声明------------------*/
	/*
	* 将context设为友元，容器要为其注入依赖项
	*/
	friend class context;

	/*--------------------静态--------------------*/
public:
	/*
	* 根据gtt模式来生成gtt组件对象
	*/
	static gtt* gtt_bind_by_mode(gtt_mode t_mode);

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

	/*
	* 用于清空上一次的信道响应
	*/
	virtual void clean_channel() = 0;

	/*
	* 用于计算指定信道响应矩阵
	*/
	virtual void calculate_channel(int t_vue_id1, int t_vue_id2, int t_pattern_idx) = 0;
};
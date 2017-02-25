/*
* =====================================================================================
*
*       Filename:  system_control.cpp
*
*    Description:  系统类实现
*
*        Version:  1.0
*        Created:
*       Revision:
*       Compiler:  VS_2015
*
*         Author:  HCF
*            LIB:  ITTC
*
* =====================================================================================
*/

#include"system_control.h"
#include"function.h"
#include"context.h"
#include"config.h"
#include"gtt.h"
#include"gtt_highspeed.h"
#include"rrm.h"
#include"tmc.h"
#include"vue.h"

using namespace std;

system_control::system_control() {

}

system_control::~system_control() {
	memory_clean::safe_delete(m_context);
}

void system_control::process() {
	initialize();//初始化

	while (m_context->get_tti() < m_context->get_global_control_config()->get_ntti()) {
		cout << "TTI: " << m_context->get_tti() << endl;

		if (m_context->get_tti() % m_context->get_global_control_config()->get_fresh_period() == 0) {
			m_context->get_gtt()->update_channel();
		}
		m_context->get_tmc()->event_trigger();

		m_context->get_rrm()->schedule();

		m_context->increase_tti();
	}

	m_context->get_tmc()->statistic();
}


void system_control::initialize() {
	//产生容器唯一单例
	context::context_factory();

	//为成员变量赋值
	m_context = context::get_context();

	//gtt单元初始化工作
	m_context->get_gtt()->initialize();

	//rrm单元初始化工作
	m_context->get_rrm()->initialize();

	//tmc单元初始化工作
	m_context->get_tmc()->initialize();
}


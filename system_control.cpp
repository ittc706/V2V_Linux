/*
* =====================================================================================
*
*       Filename:  system_control.cpp
*
*    Description:  ϵͳ��ʵ��
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
	initialize();//��ʼ��

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
	//��������Ψһ����
	context::context_factory();

	//Ϊ��Ա������ֵ
	m_context = context::get_context();

	//gtt��Ԫ��ʼ������
	m_context->get_gtt()->initialize();

	//rrm��Ԫ��ʼ������
	m_context->get_rrm()->initialize();

	//tmc��Ԫ��ʼ������
	m_context->get_tmc()->initialize();
}


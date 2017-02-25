/*
* =====================================================================================
*
*       Filename:  tmc.cpp
*
*    Description:  ҵ��ģ���������ʵ��
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

#include<random>
#include<fstream>
#include"context.h"
#include"gtt.h"
#include"tmc.h"
#include"vue.h"
#include"vue_physics.h"
#include"vue_link.h"
#include"vue_network.h"
#include"event.h"
#include"config.h"

using namespace std;

tmc::tmc() {

}

tmc::~tmc() {

}

void tmc::set_config(tmc_config* t_config) {
	m_config = t_config;
}

tmc_config* tmc::get_config() {
	return m_config;
}

void tmc::initialize() {
	context* __context = context::get_context();

	__context->set_tti_event_list();//��ʼ��tti_event_list��Ա

	default_random_engine e;
	for (int vue_id = 0; vue_id < __context->get_gtt()->get_vue_num(); vue_id++) {
		//��ʼ���������period_event_next_trigger_tti�ֶ�
		__context->get_vue_array()[vue_id].get_network_level()->set_periodic_event_next_trigger_tti(__context->get_tmc_config()->get_congestion_level_num());
		
		//Ϊÿ�������ó�ʼ���¼�����ʱ��
		for (int congestion_level = 0; congestion_level < __context->get_tmc_config()->get_congestion_level_num(); congestion_level++) {
			uniform_int_distribution<int> u(0, get_config()->get_periodic_event_period()[congestion_level]);
			__context->get_vue_array()[vue_id].get_network_level()->m_periodic_event_next_trigger_tti[congestion_level] = u(e);
		}	
	}

}

void tmc::event_trigger() {
	context* __context = context::get_context();
	for (int vue_id = 0; vue_id < __context->get_gtt()->get_vue_num(); vue_id++) {
		int tti = __context->get_tti();
		//<Warn>:�������ᵼ�£���ӵ���ȼ��ı�ǰ�󣬳�����Զ�������¼���
		int congestion_level = __context->get_vue_array()[vue_id].get_physics_level()->get_congestion_level();
		if (__context->get_vue_array()[vue_id].get_network_level()->get_periodic_event_next_trigger_tti()[congestion_level] != tti)continue;
		
		sender_event* __sender_event = new sender_event();
		__sender_event->set_vue_id(vue_id);

		__context->get_event_array().push_back(__sender_event);
		__context->get_tti_event_list()[tti].push_back(__sender_event);

		//���¼�״̬���Ϊ����״̬
		__context->get_vue_array()[vue_id].get_network_level()->add_sender_event(__sender_event);

		for (int congestion_level = 0; congestion_level < __context->get_tmc_config()->get_congestion_level_num(); congestion_level++) {
			__context->get_vue_array()[vue_id].get_network_level()->m_periodic_event_next_trigger_tti[congestion_level] = tti + __context->get_tmc_config()->get_periodic_event_period()[congestion_level];
		}
	}
}


void tmc::statistic() {
	//<Warn>
	ofstream loss_package_distance = ofstream("log\\loss_package_distance.txt");
	ofstream distance = ofstream("log\\distance.txt");
	context* __context = context::get_context();
	for (int vue_id = 0; vue_id < __context->get_gtt()->get_vue_num(); vue_id++) {
		
		for (receiver_event* __receiver_event : __context->get_vue_array()[vue_id].get_link_level()->get_loss_event_list()) {
			loss_package_distance << __receiver_event->get_distance() << " ";
			distance << __receiver_event->get_distance() << " ";
		}

		for (receiver_event* __receiver_event : __context->get_vue_array()[vue_id].get_link_level()->get_success_event_list()) {
			distance << __receiver_event->get_distance() << " ";
		}
	}
}
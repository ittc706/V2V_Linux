/*
* =====================================================================================
*
*       Filename:  rrm.cpp
*
*    Description:  无限资源管理类实现
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

#include"context.h"
#include"config.h"
#include"gtt.h"
#include"rrm.h"
#include"vue.h"
#include"vue_link.h"
#include"vue_network.h"

using namespace std;

rrm::rrm() {

}

rrm::~rrm() {

}

void rrm::set_config(rrm_config* t_config) {
	m_config = t_config;
}

rrm_config* rrm::get_config() {
	return m_config;
}

void rrm::initialize() {
	vue_network::s_vue_id_per_pattern.assign(m_config->get_pattern_num(),set<int>());
	vue_network::s_vue_id_per_pattern_finished.assign(m_config->get_pattern_num(), set<int>());
}

void rrm::schedule() {
	context* __context = context::get_context();
	for (int vue_id = 0; vue_id < __context->get_gtt()->get_vue_num(); vue_id++) {
		__context->get_vue_array()[vue_id].get_network_level()->send_connection();
	}

	for (int vue_id = 0; vue_id < __context->get_gtt()->get_vue_num(); vue_id++) {
		__context->get_vue_array()[vue_id].get_link_level()->receive();
	}

	vue_network::update_vue_id_per_pattern();
}
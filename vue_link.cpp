/*
* =====================================================================================
*
*       Filename:  vue_link.cpp
*
*    Description:  车辆类的链路层部分实现
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
#include"wt.h"
#include"vue.h"
#include"vue_physics.h"
#include"vue_link.h"
#include"vue_network.h"
#include"event.h"

using namespace std;

vue_link::vue_link() {

}

vue_link::~vue_link() {

}

void vue_link::set_superior_level(vue* t_superior_level) {
	m_superior_level = t_superior_level;
}

vue* vue_link::get_superior_level() {
	return m_superior_level;
}

const std::list<receiver_event*>& vue_link::get_success_event_list() {
	return m_success_event_list;
}

const std::list<receiver_event*>& vue_link::get_loss_event_list() {
	return m_loss_event_list;
}

void vue_link::receive_connection(sender_event* t_sender_event) {
	int vue_id = get_superior_level()->get_physics_level()->get_vue_id();
	receiver_event* __receiver_event = new receiver_event(t_sender_event, vue_id);

	m_receiver_event_list.push_back(__receiver_event);
}

void vue_link::receive() {
	context* __context = context::get_context();
	std::list<receiver_event*>::iterator it = m_receiver_event_list.begin();

	while (it != m_receiver_event_list.end()) {
		receiver_event* __cur_event = *it;

		double factor = __context->get_rrm_config()->get_modulation_type()* __context->get_rrm_config()->get_code_rate();

		//该编码方式下，该pattern在一个tti最多可传输的有效信息bit数量
		int transimit_max_bit_num = (int)((double)(__context->get_rrm_config()->get_rb_num_per_pattern() * rrm_config::s_BIT_NUM_PER_RB)* factor);
		__cur_event->transimit(transimit_max_bit_num);

		//计算SINR
		wt* __wt = context::get_context()->get_wt();

		double sinr = 0;
		int vue_send_id = __cur_event->get_send_vue_id();
		int vue_receive_id = __cur_event->get_receive_vue_id();

		if (vue_physics::get_channel(vue_send_id, vue_receive_id, __cur_event->get_pattern_idx()) == nullptr) {
			sinr = __context->get_rrm_config()->get_drop_sinr_boundary() - 1;
		}
		else {
			sinr = __wt->calculate_sinr(vue_send_id,
				vue_receive_id,
				__cur_event->get_pattern_idx(),
				vue_network::s_vue_id_per_pattern[__cur_event->get_pattern_idx()]);
		}

		if (sinr < __context->get_rrm_config()->get_drop_sinr_boundary()) {
			__cur_event->set_is_loss();//记录丢包
		}

		if (__cur_event->get_is_finished()) {
			if (__cur_event->get_is_loss()) {
				m_loss_event_list.push_back(__cur_event);
			}
			else {
				m_success_event_list.push_back(__cur_event);
			}
			vue_network::s_vue_id_per_pattern_finished[__cur_event->get_pattern_idx()].insert(__cur_event->get_send_vue_id());

			it = m_receiver_event_list.erase(it);
		}
		else {
			++it;
		}
	}
}

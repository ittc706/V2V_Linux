/*
* =====================================================================================
*
*       Filename:  event.cpp
*
*    Description:  事件类实现
*
*        Version:  1.0
*        Created:
*       Revision:
*       Compiler:  VS_2015
*
*         Author:  WYB
*            LIB:  ITTC
*
* =====================================================================================
*/

#include<iostream>
#include"context.h"
#include"event.h"
#include"config.h"
#include"vue_physics.h"

using namespace std;

int sender_event::s_event_count = 0;

sender_event::sender_event() {

}

sender_event::~sender_event() {

}

int sender_event::get_event_id() {
	return m_event_id;
}

void sender_event::set_vue_id(int t_vue_id) {
	m_vue_id = t_vue_id;
}

int sender_event::get_vue_id() {
	return m_vue_id;
}

void sender_event::set_pattern_idx(int t_pattern_idx) {
	m_pattern_idx = t_pattern_idx;
}

int sender_event::get_pattern_idx() {
	return m_pattern_idx;
}

receiver_event::receiver_event(sender_event* t_sender_event, int t_receiver_vue_id) {
	set_event_id(t_sender_event->get_event_id());
	set_send_vue_id(t_sender_event->get_vue_id());
	set_receive_vue_id(t_receiver_vue_id);

	m_package_num = context::get_context()->get_tmc_config()->get_package_num();
	m_bit_num_per_package = context::get_context()->get_tmc_config()->get_bit_num_per_package();

	m_remain_bit_num = m_bit_num_per_package[0];

	set_distance(vue_physics::get_distance(get_send_vue_id(), get_receive_vue_id()));
}

receiver_event::~receiver_event() {

}

void receiver_event::set_event_id(int t_event_id) {
	m_event_id = t_event_id;
}

int receiver_event::get_event_id() {
	return m_event_id;
}

void receiver_event::set_send_vue_id(int t_send_vue_id) {
	m_send_vue_id = t_send_vue_id;
}

int receiver_event::get_send_vue_id() {
	return m_send_vue_id;
}

void receiver_event::set_receive_vue_id(int t_receive_vue_id) {
	m_receive_vue_id = t_receive_vue_id;
}

int receiver_event::get_receive_vue_id() {
	return m_receive_vue_id;
}

void receiver_event::set_distance(double t_distance) {
	m_distance = t_distance;
}

double receiver_event::get_distance() {
	return m_distance;
}

void receiver_event::set_pattern_idx(int t_pattern_idx) {
	m_pattern_idx = t_pattern_idx;
}

int receiver_event::get_pattern_idx() {
	return m_pattern_idx;
}

bool receiver_event::get_is_finished() {
	return m_is_finished;
}

void receiver_event::set_is_loss() {
	m_is_loss = true;
}

bool receiver_event::get_is_loss() {
	return m_is_loss;
}

void receiver_event::transimit(int t_transimit_max_bit_num) {
	if (t_transimit_max_bit_num >= m_remain_bit_num) {
		if (++m_package_idx == m_package_num) {
			m_remain_bit_num = 0;
			m_is_finished = true;
		}
		else {
			m_remain_bit_num = m_bit_num_per_package[m_package_idx];
		}
	}
	else {
		m_remain_bit_num -= t_transimit_max_bit_num;
	}
}


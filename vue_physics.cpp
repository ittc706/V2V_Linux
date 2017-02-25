/*
* =====================================================================================
*
*       Filename:  vue_physics.cpp
*
*    Description:  车辆类的物理层部分实现
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

#include"vue.h"
#include"vue_physics.h"
#include"context.h"
#include"gtt.h"
#include"gtt_highspeed.h"
#include"config.h"
#include"imta.h"
#include"function.h"

using namespace std;

int vue_physics::s_vue_count = 0;


vector<vector<double*>> vue_physics::s_channel_all(0);

vector<vector<double>> vue_physics::s_pl_all(0);

vector<vector<double>> vue_physics::s_distance_all(0);

int vue_physics::get_vue_num() {
	return s_vue_count;
}

void vue_physics::set_channel(int i, int j, double* t_channel) {
	if (i < j) {
		memory_clean::safe_delete(s_channel_all[i][j], true);
		s_channel_all[i][j] = t_channel;
	}
	else {
		memory_clean::safe_delete(s_channel_all[j][i], true);
		s_channel_all[j][i] = t_channel;
	}
}

double* vue_physics::get_channel(int i, int j) {
	if (i < j) {
		return s_channel_all[i][j];
	}
	else {
		return s_channel_all[j][i];
	}
}

void vue_physics::set_pl(int i, int j, double t_pl) {
	if (i < j) {
		s_pl_all[i][j] = t_pl;
	}
	else {
		s_pl_all[j][i] = t_pl;
	}
}

double vue_physics::get_pl(int i, int j) {
	if (i < j) {
		return s_pl_all[i][j];
	}
	else {
		return s_pl_all[j][i];
	}
}

void vue_physics::set_distance(int i, int j, double t_distance) {
	if (i < j) {
		s_distance_all[i][j] = t_distance;
	}
	else {
		s_distance_all[j][i] = t_distance;
	}
}

double vue_physics::get_distance(int i, int j) {
	if (i < j) {
		return s_distance_all[i][j];
	}
	else {
		return s_distance_all[j][i];
	}
}

vue_physics::vue_physics() {

}

vue_physics::~vue_physics() {
	
}

int vue_physics::get_congestion_level() {
	return m_congestion_level;
}

void vue_physics::update_location() {
	auto p = (gtt_highspeed*)context::get_context()->get_gtt();
	if (m_vangle == 0)
	{
		if ((m_absx + p->get_precise_config()->get_freshtime()*m_speed)>(p->get_precise_config()->get_road_length() / 2))
		{
			m_absx = (m_absx + p->get_precise_config()->get_freshtime()*m_speed) - p->get_precise_config()->get_road_length();
			m_relx = m_absx;
		}
		else
		{
			m_absx = m_absx + p->get_precise_config()->get_freshtime()*m_speed;
			m_relx = m_absx;
		}
	}
	else
	{
		if ((m_absx - p->get_precise_config()->get_freshtime()*m_speed)<(-p->get_precise_config()->get_road_length() / 2))
		{
			m_absx = m_absx - p->get_precise_config()->get_freshtime()*m_speed + p->get_precise_config()->get_road_length();
			m_relx = m_absx;
		}
		else
		{
			m_absx = m_absx - p->get_precise_config()->get_freshtime()*m_speed;
			m_relx = m_absx;
		}
	}
}

void vue_physics::set_superior_level(vue* t_superior_level) {
	m_superior_level = t_superior_level;
}

vue* vue_physics::get_superior_level() {
	return m_superior_level;
}

int vue_physics::get_vue_id() {
	return m_vue_id;
}
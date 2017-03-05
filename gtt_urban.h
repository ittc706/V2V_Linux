#pragma once

#include"gtt.h"

class gtt_urban_config;

class gtt_urban :public gtt {
	/*--------------------接口--------------------*/
public:
	void initialize() override;

	int get_vue_num() override;

	void clean_channel() override;

	void calculate_channel(int t_vue_id1, int t_vue_id2, int t_pattern_idx) override;

	gtt_urban_config* get_precise_config();
}; 

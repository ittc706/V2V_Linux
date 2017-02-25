#pragma once

#include"gtt.h"

class gtt_highspeed_config;

class gtt_highspeed:public gtt{
	/*--------------------½Ó¿Ú--------------------*/
public:
	void initialize() override;

	int get_vue_num() override;

	void update_channel() override;

	gtt_highspeed_config* get_precise_config();
};
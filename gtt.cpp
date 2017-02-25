 

#include"gtt.h"

using namespace std;

void gtt::set_config(gtt_config* t_config) {
	m_config = t_config;
}

gtt_config* gtt::get_config() {
	return m_config;
}
 

#include"gtt.h"
#include"gtt_highspeed.h"
#include"gtt_urban.h"

using namespace std;

gtt* gtt::gtt_bind_by_mode(gtt_mode t_mode) {
	if (t_mode == HIGHSPEED) {
		return new gtt_highspeed();
	}
	else {
		return new gtt_urban();
	}
}

void gtt::set_config(gtt_config* t_config) {
	m_config = t_config;
}

gtt_config* gtt::get_config() {
	return m_config;
}
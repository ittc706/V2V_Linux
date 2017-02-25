/*
* =====================================================================================
*
*       Filename:  ConfigLoader.cpp
*
*    Description:  �����ļ�������
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

#include<iostream>
#include<sstream>
#include<stdexcept>
#include"config_loader.h"

using namespace std;

int config_loader::string_to_int(std::string t_string) {
	if (t_string.size() > 10) throw logic_error("IntOverFlow");
	stringstream ss;
	ss << t_string;
	long res;
	ss >> res;
	if(res>(numeric_limits<int>::max)()|| res<(numeric_limits<int>::min)()) throw logic_error("IntOverFlow");
	return static_cast<int>(res);
}

double config_loader::string_to_double(std::string t_string) {
	//����doubleʵ��̫���ˣ��ݲ���������ˣ���Ĭ������Ϊ������Χ
	stringstream ss;
	ss << t_string;
	double res;
	ss >> res;
	return res;
}

void config_loader::resolv_config_file(string t_file) {
	//��ջ���
	m_content.clear();
	m_tag_content_map.clear();

	//��ȡ�������ַ���
	ifstream in(t_file);
	istreambuf_iterator<char> if_it(in), if_eof;
	m_content.assign(if_it, if_eof);
	in.close();

	//���������洢
	regex r("<([^<>]*)>([^<>]*)</([^<>]*)>");
	for (sregex_iterator it(m_content.begin(), m_content.end(), r), eof; it != eof; ++it) {
		string leftTag = it->operator[](1);
		string rightTag = it->operator[](3);
		string content = it->operator[](2);
		if (leftTag != rightTag) {
			throw logic_error("tag not match");
		}
		m_tag_content_map[leftTag] = content;
	}
}

std::string config_loader::get_param(std::string t_param) {
	if (m_tag_content_map.find(t_param) == m_tag_content_map.end()) return "";
	return m_tag_content_map[t_param];
}
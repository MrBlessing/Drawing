
#include "stdafx.h"
#include "string"
#include "sstream"
using namespace std;
#ifndef _CUSTOM_H_
#define _CUSTOM_H_

inline int strToInt(string str) {
	int res;
	stringstream ss;
	ss << str;
	ss >> res;
	return res;
}

inline string intToStr(int i) {
	string res;
	stringstream ss;
	ss << i;
	ss >> res;
	return res;
}

inline string longToStr(long i) {
	string res;
	stringstream ss;
	ss << i;
	ss >> res;
	return res;
}


#endif // !_CUSTOM_H_




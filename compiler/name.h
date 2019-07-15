#ifndef NAME_H
#define NAME_H

#include<iostream>
#include<vector>
#include<string>

#include"lex.h"

class Name {
private:
	std::vector<std::string> names = { "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7" };
	std::vector<std::string>::iterator name = names.begin();
	const int& line_no;

public:
	Name(const int&);
	std::string newname();
	void freename(std::string);
};

#endif

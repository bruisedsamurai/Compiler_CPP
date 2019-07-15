#include "pch.h"
#include<iostream>
#include<vector>
#include<string>

#include"lex.h"
#include"name.h"

Name::Name(const int& lineNo) : line_no(lineNo) {}

std::string Name::newname()
{
	if (name == names.end())
	{
		std::cerr << line_no << ": Expression too complex\n";
		exit(1);
	}

	return (*name++);
}

void Name::freename(std::string s)
{
	if (name != names.begin())
	{
		*--name = s; //Pre-decrement is done because at current and above position there is already a free name available.
	}
	else
		std::cerr << line_no << ": (Internal error) Name stack underflow\n";
}


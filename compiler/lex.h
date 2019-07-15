#ifndef LEX_H
#define LEX_H

#include<iostream>
#include<string>


enum class token { EOI, SEMI, PLUS, TIMES, LP, RP, NUM_OR_ID };

class Lex {
private:
	std::string input_buffer;
	std::string::iterator yytext; //Note: Is it legal? Since, input buffer is default initialised. It will be empty. So, it should be right to get the end or not?
	std::string::size_type yyleng;
	int yylineno;
	token lookahead;

public:
	Lex();
	std::string get_num_or_id() const { return std::string(yytext, yytext + yyleng); }
	token lex();
	bool match(token);
	void advance();
	const int& get_line_no() const { return yylineno; }
};

#endif

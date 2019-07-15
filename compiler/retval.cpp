#include "pch.h"
#include<iostream>
#include<string>

#include"lex.h"
#include"name.h"

std::string factor();
std::string term();
std::string expression();

static Lex lexer;
const int& line_no = lexer.get_line_no();

static Name name(line_no);

void statements()
{
	/* statements -> expression SEMI | expression SEMI statements */

	std::string tempvar;

	while (!lexer.match(token::EOI))
	{
		tempvar = expression();

		if (lexer.match(token::SEMI))
			lexer.advance();
		else
			std::cerr << line_no << ": Inserting missing semicolon\n";
	}

	name.freename(tempvar);

}

std::string expression()
{
	/*
	expression -> term expression'
	expression -> PLUS term expression' | epsilon
	 */

	std::string tempvar, tempvar2;

	tempvar = term();
	while (lexer.match(token::PLUS))
	{
		lexer.advance();
		tempvar2 = term();
		std::cout << "\t" << tempvar + " = " + tempvar << " + " << tempvar2 << std::endl;
		name.freename(tempvar2);
	}

	return tempvar;
}

std::string term()
{
	/*
	term -> factor term'
	term' -> TIMEs term' | epsilon
	 */

	std::string tempvar, tempvar2;

	tempvar = factor();

	while (lexer.match(token::TIMES))
	{
		lexer.advance();
		tempvar2 = factor();
		std::cout << "\t" << tempvar + " = " + tempvar << " * " << tempvar2 << std::endl;
		name.freename(tempvar2);
	}

	return tempvar;
}

std::string factor()
{
	/*
	factor -> NUM_OR_ID | LP expression RP
	 */

	std::string tempvar;

	if (lexer.match(token::NUM_OR_ID))
	{
		tempvar = name.newname();
		std::cout << "\t" << tempvar << " = " << lexer.get_num_or_id() << std::endl;
		lexer.advance();
	}
	else if (lexer.match(token::LP))
	{
		lexer.advance();
		tempvar = expression();
		if (lexer.match(token::RP))
			lexer.advance();
		else
			std::cerr << line_no << ": Mismatched parenthesis\n";
	}
	else
		std::cerr << line_no << ": Number or identifier expected\n";

	return tempvar;
}
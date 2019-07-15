#include"pch.h"
#include<iostream>
#include<string>
#include<cctype>

#include"lex.h"

Lex::Lex() : yyleng(0), yylineno(0), lookahead(token::EOI)
{
	yytext = input_buffer.end();
}

token Lex::lex() {
	std::string::iterator current;

	current = yytext + yyleng;

	while (true)
	{
		while (current == input_buffer.end()) /* This makes sense when it is a repeating call in case when last character checked was the last one of the string and now due to increase in length the iterator points to end. */
		{

			input_buffer.clear();
			if (!std::getline(std::cin, input_buffer)) {
				yytext = input_buffer.end();
				return token::EOI;
			}

			current = input_buffer.begin();
			++yylineno;

			while (current != input_buffer.end() && std::isspace(*current))
				++current;
		}

		for (; current != input_buffer.end(); ++current)
		{
			yytext = current;
			yyleng = 1;

			switch (*current)
			{
			case EOF: return token::EOI;
			case ';': return token::SEMI;
			case '+': return token::PLUS;
			case '*': return token::TIMES;
			case '(': return token::LP;
			case ')': return token::RP;

			case '\n':
			case '\t':
			case ' ': break;

			default:
				if (!std::isalnum(*current))
					std::cerr << "Ignoring illegal input: " << *current << std::endl;
				else
				{
					while (current != input_buffer.end() && std::isalnum(*current))
						++current;

					yyleng = current - yytext;
					return token::NUM_OR_ID;
				}

				break;
			}
		}
	}

}

bool Lex::match(token tok) {
	if (lookahead == token::EOI)
	{
		lookahead = lex();
	}

	return tok == lookahead;
}

void Lex::advance()
{
	lookahead = lex();
}
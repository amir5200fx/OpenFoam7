#include <iostream>

#include "parser.h"

using namespace std;

// this function is called syntax parser
// just the parser, the parse
extern int yyparse();


int main()
{
	yyparse();

	return 0;
}

// we have to code this function
void yyerror(const char* msg)
{
	cout <<"Error: " <<msg << endl;

}
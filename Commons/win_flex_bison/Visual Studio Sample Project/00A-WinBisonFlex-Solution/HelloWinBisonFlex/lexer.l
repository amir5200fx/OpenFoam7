%option noyywrap

%{ 
	
	#pragma warning (disable: 4005)

	#include <iostream>
	#include <cmath>

	

	using namespace std;

	#include "parser.h"

%}

NUMB	([0-9]+)|([0-9]*\.[0-9]+)

%%

{NUMB}			{ yylval = atof(yytext); return NUM; }
[+*/()-]		{ return yytext[0]; }
[\n]			{ return '\n'; }
[ \t]			{ /* empty */ }
"quit"			{ yyterminate(); }
.				/* nothing, eat up */


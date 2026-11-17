%option noyywrap

%{
#include<bits/stdc++.h>

#include"symbol_info.h"

#define YYSTYPE symbol_info*

#include "y.tab.h"

extern YYSTYPE yylval;

using namespace std;

void yyerror(const char *);



extern int line_num;

extern ofstream outlog;

%}

/* Regular Definitions */

delim	 [ \t\v\r]

/* write regular expressions for whitespace and newline */
ws   {delim}+

newline \n

letter_	 [A-Za-z_]
digit	 [0-9]

/* write regular expressions for id, float and integers */

id	{letter_}({letter_}|{digit})*
integer	{digit}+
/* e.g. 10.11E-10 */
float  ({digit}*\.{digit}+([Ee][+-]?{digit}+)?)|({digit}+[Ee][+-]?{digit}+)


%%

{ws}		{ /* ignore whitespace */ }
{newline}	{ line_num = line_num+1; }

 /* brenching*/
if          { 
                return IF; }

else        { 
                return ELSE; }

 /*loop*/
for         { 
                return FOR; }

while       { 
                return WHILE; }

do          { 
                return DO; }

break       { 
                return BREAK; }

 /*Data type*/
int         { 
                return INT; }

char        { 
                return CHAR; }

float       { 
                return FLOAT; }

double      { 
                return DOUBLE; }
 /*basic commands*/
void        { 
                return VOID; }

return      { 
                return RETURN; }
printf      { 
                return PRINTLN; }

default     { 
                return DEFAULT; }
continue    { 
                return CONTINUE; }

goto        { 
                return GOTO; }

switch      { 
                return SWITCH; }

case        { 
                return CASE; }

 /*Data type*/
{integer}   {
                symbol_info *s = new symbol_info((string)yytext,"CONST_INT");
                yylval = (YYSTYPE)s;
                return CONST_INT;
		    }

{float}     {
                symbol_info *s = new symbol_info((string)yytext,"CONST_FLOAT");
                yylval = (YYSTYPE)s;
                return CONST_FLOAT;
		    }

{id}       {
                symbol_info *s = new symbol_info((string)yytext,"ID");
                yylval = (YYSTYPE)s;
                return ID;
            }
 /*operators*/
"+"|"-"	    {
                symbol_info *s = new symbol_info((string)yytext,"ADDOP");
                yylval = (YYSTYPE)s;
                return ADDOP;
		    }
 /*punctuators*/
"*"|"/"|"%"	    {
                symbol_info *s = new symbol_info((string)yytext,"MULOP");
                yylval = (YYSTYPE)s;
                return MULOP;
		    }
 /*increment decrement*/
"++"	    {
                symbol_info *s = new symbol_info((string)yytext,"INCOP");
                yylval = (YYSTYPE)s;
                return INCOP;
		    }

"--"	    {
                symbol_info *s = new symbol_info((string)yytext,"DECOP");
                yylval = (YYSTYPE)s;
                return DECOP;
		    }
 /*comparator*/
"<"|">"|"=="|"<="|">="|"!="	    {
                symbol_info *s = new symbol_info((string)yytext,"RELOP");
                yylval = (YYSTYPE)s;
                return RELOP;
		    }

"="	    {
                symbol_info *s = new symbol_info((string)yytext,"ASSIGNOP");
                yylval = (YYSTYPE)s;
                return ASSIGNOP;
		    }

"&&"|"||"	    {
                symbol_info *s = new symbol_info((string)yytext,"LOGICOP");
                yylval = (YYSTYPE)s;
                return LOGICOP;
		    }

"!"	    {
                symbol_info *s = new symbol_info((string)yytext,"NOT");
                yylval = (YYSTYPE)s;
                return NOT;
		    }
 /*parenthesis*/
"("        { 
                return LPAREN; }

")"        { 
                return RPAREN; }

"{"        { 
                return LCURL; }

"}"        { 
                return RCURL; }

"["        { 
                return LTHIRD; }

"]"        { 
                return RTHIRD; }

","        { 
                return COMMA; }

":"        { 
                return COLON; }

";"        { 
                return SEMICOLON; }

%%

%option noyywrap

%{
#include "symbol_info.h"
#include "y.tab.h"

extern YYSTYPE yylval;

using namespace std;
extern int line_count;
extern ofstream outputlog;
%}

DELIM       [ \t\v\r\f]
WHITESPACE          {DELIM}+
NEWLINE     \n
LETTER     [A-Za-z_]
DIGIT       [0-9]
IDENTIFIER          {LETTER}({LETTER}|{DIGIT})*
INTEGER     {DIGIT}+
FLOAT_NUMBER    (({DIGIT}+\.{DIGIT}*|\.{DIGIT}+)([eE][+-]?{DIGIT}+)?|{DIGIT}+[eE][+-]?{DIGIT}+)

%%

{WHITESPACE}        { /* ignore whitespace */ }
{NEWLINE}   { line_count++; }

"if"    {
        symbol_info *p = new symbol_info((string)yytext,"IF");
        yylval.sp = p;
        return IF;
    }

"else"    {
        symbol_info *p = new symbol_info((string)yytext,"ELSE");
        yylval.sp = p;
        return ELSE;
    }

"for"    {
        symbol_info *p = new symbol_info((string)yytext,"FOR");
        yylval.sp = p;
        return FOR;
    }

"while"    {
        symbol_info *p = new symbol_info((string)yytext,"WHILE");
        yylval.sp = p;
        return WHILE;
    }

"int"    {
        symbol_info *p = new symbol_info((string)yytext,"INT");
        yylval.sp = p;
        return INT;
    }

"float"    {
        symbol_info *p = new symbol_info((string)yytext,"FLOAT");
        yylval.sp = p;
        return FLOAT;
    }

"void"    {
        symbol_info *p = new symbol_info((string)yytext,"VOID");
        yylval.sp = p;
        return VOID;
    }

"return"    {
        symbol_info *p = new symbol_info((string)yytext,"RETURN");
        yylval.sp = p;
        return RETURN;
    }

"printf"    {
        symbol_info *p = new symbol_info((string)yytext,"PRINTLN");
        yylval.sp = p;
        return PRINTLN;
    }

{IDENTIFIER}    {
        symbol_info *p = new symbol_info((string)yytext,"ID");
        yylval.sp = p;
        return ID;
    }

{INTEGER}    {
        symbol_info *p = new symbol_info((string)yytext,"CONST_INT");
        yylval.sp = p;
        return CONST_INT;
    }

{FLOAT_NUMBER}    {
        symbol_info *p = new symbol_info((string)yytext,"CONST_FLOAT");
        yylval.sp = p;
        return CONST_FLOAT;
    }

"+"|"-"    {
        symbol_info *p = new symbol_info((string)yytext,"ADDOP");
        yylval.sp = p;
        return ADDOP;
    }

"*"|"/"|"%"    {
        symbol_info *p = new symbol_info((string)yytext,"MULOP");
        yylval.sp = p;
        return MULOP;
    }

"++"|"--"    {
        symbol_info *p = new symbol_info((string)yytext,"INCOP");
        yylval.sp = p;
        return INCOP;
    }

"<"|"<="|">"|">="|"=="|"!="    {
        symbol_info *p = new symbol_info((string)yytext,"RELOP");
        yylval.sp = p;
        return RELOP;
    }

"="    {
        symbol_info *p = new symbol_info((string)yytext,"ASSIGNOP");
        yylval.sp = p;
        return ASSIGNOP;
    }

"&&"|"||"    {
        symbol_info *p = new symbol_info((string)yytext,"LOGICOP");
        yylval.sp = p;
        return LOGICOP;
    }

"!"    {
        symbol_info *p = new symbol_info((string)yytext,"NOT");
        yylval.sp = p;
        return NOT;
    }

"("    {
        symbol_info *p = new symbol_info((string)yytext,"LPAREN");
        yylval.sp = p;
        return LPAREN;
    }

")"    {
        symbol_info *p = new symbol_info((string)yytext,"RPAREN");
        yylval.sp = p;
        return RPAREN;
    }

"{"    {
        symbol_info *p = new symbol_info((string)yytext,"LCURL");
        yylval.sp = p;
        return LCURL;
    }

"}"    {
        symbol_info *p = new symbol_info((string)yytext,"RCURL");
        yylval.sp = p;
        return RCURL;
    }

"["    {
        symbol_info *p = new symbol_info((string)yytext,"LTHIRD");
        yylval.sp = p;
        return LTHIRD;
    }

"]"    {
        symbol_info *p = new symbol_info((string)yytext,"RTHIRD");
        yylval.sp = p;
        return RTHIRD;
    }

","    {
        symbol_info *p = new symbol_info((string)yytext,"COMMA");
        yylval.sp = p;
        return COMMA;
    }

";"    {
        symbol_info *p = new symbol_info((string)yytext,"SEMICOLON");
        yylval.sp = p;
        return SEMICOLON;
    }

.           {
                outputlog<<"Error at line no: "<<line_count<<": Unrecognized character "<<yytext<<endl<<endl;
                return yytext[0];
            }

%%

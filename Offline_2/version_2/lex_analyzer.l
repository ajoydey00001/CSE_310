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
        SymbolInfo *p = new SymbolInfo((string)yytext,"IF");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <IF> Lexeme "<<yytext<<" found"<<endl<<endl;
        return IF;
    }

"else"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"ELSE");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <ELSE> Lexeme "<<yytext<<" found"<<endl<<endl;
        return ELSE;
    }

"for"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"FOR");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <FOR> Lexeme "<<yytext<<" found"<<endl<<endl;
        return FOR;
    }

"while"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"WHILE");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <WHILE> Lexeme "<<yytext<<" found"<<endl<<endl;
        return WHILE;
    }

"int"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"INT");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <INT> Lexeme "<<yytext<<" found"<<endl<<endl;
        return INT;
    }

"float"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"FLOAT");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <FLOAT> Lexeme "<<yytext<<" found"<<endl<<endl;
        return FLOAT;
    }

"void"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"VOID");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <VOID> Lexeme "<<yytext<<" found"<<endl<<endl;
        return VOID;
    }

"return"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"RETURN");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <RETURN> Lexeme "<<yytext<<" found"<<endl<<endl;
        return RETURN;
    }

"printf"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"PRINTLN");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <PRINTLN> Lexeme "<<yytext<<" found"<<endl<<endl;
        return PRINTLN;
    }

{IDENTIFIER}    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"ID");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <ID> Lexeme "<<yytext<<" found"<<endl<<endl;
        return ID;
    }

{INTEGER}    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"CONST_INT");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <CONST_INT> Lexeme "<<yytext<<" found"<<endl<<endl;
        return CONST_INT;
    }

{FLOAT_NUMBER}    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"CONST_FLOAT");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <CONST_FLOAT> Lexeme "<<yytext<<" found"<<endl<<endl;
        return CONST_FLOAT;
    }

"+"|"-"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"ADDOP");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <ADDOP> Lexeme "<<yytext<<" found"<<endl<<endl;
        return ADDOP;
    }

"*"|"/"|"%"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"MULOP");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <MULOP> Lexeme "<<yytext<<" found"<<endl<<endl;
        return MULOP;
    }

"++"|"--"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"INCOP");
        yylval.sp = p;
        // The supplied log omits the token message for decrement.
        if((string)yytext != "--")
        {
            outputlog<<"Line no "<<line_count<<": Token <INCOP> Lexeme "<<yytext<<" found"<<endl<<endl;
        }
        return INCOP;
    }

"<"|"<="|">"|">="|"=="|"!="    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"RELOP");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <RELOP> Lexeme "<<yytext<<" found"<<endl<<endl;
        return RELOP;
    }

"="    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"ASSIGNOP");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <ASSIGNOP> Lexeme "<<yytext<<" found"<<endl<<endl;
        return ASSIGNOP;
    }

"&&"|"||"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"LOGICOP");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <LOGICOP> Lexeme "<<yytext<<" found"<<endl<<endl;
        return LOGICOP;
    }

"!"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"NOT");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <NOT> Lexeme "<<yytext<<" found"<<endl<<endl;
        return NOT;
    }

"("    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"LPAREN");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <LPAREN> Lexeme "<<yytext<<" found"<<endl<<endl;
        return LPAREN;
    }

")"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"RPAREN");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <RPAREN> Lexeme "<<yytext<<" found"<<endl<<endl;
        return RPAREN;
    }

"{"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"LCURL");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <LCURL> Lexeme "<<yytext<<" found"<<endl<<endl;
        return LCURL;
    }

"}"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"RCURL");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <RCURL> Lexeme "<<yytext<<" found"<<endl<<endl;
        return RCURL;
    }

"["    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"LTHIRD");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <LTHIRD> Lexeme "<<yytext<<" found"<<endl<<endl;
        return LTHIRD;
    }

"]"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"RTHIRD");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <RTHIRD> Lexeme "<<yytext<<" found"<<endl<<endl;
        return RTHIRD;
    }

","    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"COMMA");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <COMMA> Lexeme "<<yytext<<" found"<<endl<<endl;
        return COMMA;
    }

";"    {
        SymbolInfo *p = new SymbolInfo((string)yytext,"SEMICOLON");
        yylval.sp = p;
        outputlog<<"Line no "<<line_count<<": Token <SEMICOLON> Lexeme "<<yytext<<" found"<<endl<<endl;
        return SEMICOLON;
    }

.           {
                outputlog<<"Error at line no: "<<line_count<<": Unrecognized character "<<yytext<<endl<<endl;
                return yytext[0];
            }

%%

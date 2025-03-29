%option noyywrap

%x STATE_CHAR
%x STATE_STRING
%x STATE_STRING_M
%x STATE_1_COMMENT
%x STATE_2_COMMENT


%{

#include<bits/stdc++.h>
#include "SymbolInfo_ScopeTable_SymbolTable.cpp"

#include "y.tab.h"

using namespace std;

extern YYSTYPE yylval;

extern ofstream outputlog;
extern ofstream outputerror;
extern int err_count;
extern int line_count;


void yyerror(char *);



int line_str = 0;
int line1 = 0;
int line2=0;

string input_chars = "";
string chars = "";
string input_str = "";
string str = "";
string s = "";
string c_str="";




//ofstream outputlog("1905038_log.txt");
//ofstream outputtoken("1905038_token.txt");






%}


LETTER [a-zA-Z_]
ALPHANUMERIC [a-zA-Z_0-9]
DIGIT [0-9]
NEWLINE [\r]?\n
WHITESPACE [ \t\f\r\v]+ 

%%

{WHITESPACE} {}

{NEWLINE} {line_count++;}

"if"    {
	SymbolInfo *p = new SymbolInfo(yytext , "IF");
		p->set_parent("IF");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);

		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <IF> Lexeme "<<yytext<<" found"<<endl; 
    
    return IF;
    //outputtoken<<"<IF, "<<yytext<<">"<<endl;
}

"println"    {
	SymbolInfo *p = new SymbolInfo(yytext , "PRINTLN");
		p->set_parent("PRINTLN");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);

		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <PRINTLN> Lexeme "<<yytext<<" found"<<endl; 
    
    return PRINTLN;
    //outputtoken<<"<PRINTLN, "<<yytext<<">"<<endl;
}


"else"	{
    SymbolInfo *p = new SymbolInfo(yytext , "ELSE");
		p->set_parent("ELSE");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <ELSE> Lexeme "<<yytext<<" found"<<endl; 
    
    return ELSE;
    //outputtoken<<"<ELSE, "<<yytext<<">"<<endl;
}

"while"	{
	SymbolInfo *p = new SymbolInfo(yytext , "WHILE");
		p->set_parent("WHILE");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <WHILE> Lexeme "<<yytext<<" found"<<endl; 
    
    return WHILE;
    //outputtoken<<"<WHILE, "<<yytext<<">"<<endl;
}	
"for"	{
	SymbolInfo *p = new SymbolInfo(yytext , "FOR");
		p->set_parent("FOR");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <FOR> Lexeme "<<yytext<<" found"<<endl; 
    
    return FOR;
    //outputtoken<<"<FOR, "<<yytext<<">"<<endl;
}
"do"	{
	SymbolInfo *p = new SymbolInfo(yytext , "DO");
		p->set_parent("DO");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <DO> Lexeme "<<yytext<<" found"<<endl; 
    
    return DO;
    //outputtoken<<"<DO, "<<yytext<<">"<<endl;
}

"int"	{
	SymbolInfo *p = new SymbolInfo(yytext , "NONE","INT");
		p->set_parent("INT");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <INT> Lexeme "<<yytext<<" found"<<endl; 
    return INT;
    
    //outputtoken<<"<INT, "<<yytext<<">"<<endl;
}
"char"	{
	SymbolInfo *p = new SymbolInfo(yytext ,"NONE" ,"CHAR");
		p->set_parent("CHAR");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <CHAR> Lexeme "<<yytext<<" found"<<endl; 
    return CHAR;
    
    //outputtoken<<"<CHAR, "<<yytext<<">"<<endl;
}
"float"	{
	SymbolInfo *p = new SymbolInfo(yytext , "NONE","FLOAT");
		p->set_parent("FLOAT");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <FLOAT> Lexeme "<<yytext<<" found"<<endl; 
    return FLOAT;
    
    //outputtoken<<"<FLOAT, "<<yytext<<">"<<endl;
}

"void"	{
	SymbolInfo *p = new SymbolInfo(yytext ,"NONE","VOID");
		p->set_parent("VOID");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		p->set_dtype("VOID");
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <VOID> Lexeme "<<yytext<<" found"<<endl; 
    return VOID;
    
    //outputtoken<<"<VOID, "<<yytext<<">"<<endl;
}
"return"	{
	SymbolInfo *p = new SymbolInfo(yytext , "RETURN");
		p->set_parent("RETURN");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <RETURN> Lexeme "<<yytext<<" found"<<endl; 
    return RETURN;
    
    //outputtoken<<"<RETURN, "<<yytext<<">"<<endl;
}

"default"	{
	SymbolInfo *p = new SymbolInfo(yytext , "DEFAULT");
		p->set_parent("DEFAULT");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <DEFAULT> Lexeme "<<yytext<<" found"<<endl; 
    return DEFAULT;
    
    //outputtoken<<"<DEFAULT, "<<yytext<<">"<<endl;
}


"continue"	{
	SymbolInfo *p = new SymbolInfo(yytext , "CONTINUE");
		p->set_parent("CONTINUE");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <CONTINUE> Lexeme "<<yytext<<" found"<<endl; 
    return CONTINUE;
    
    //outputtoken<<"<CONTINUE, "<<yytext<<">"<<endl;
}


{DIGIT}+	{
	SymbolInfo *p = new SymbolInfo(yytext , "CONST_INT");
		p->set_dtype("INT");
        p->set_stype("VARIABLE");
        p->set_parent("CONST_INT");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
        yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <CONST_INT> Lexeme "<<yytext<<" found"<<endl;
    return CONST_INT;
    
    //outputtoken<<"<CONST_INT, "<<yytext<<">"<<endl;
}
{DIGIT}+(\.{DIGIT}+)?([E][-]?{DIGIT}+)?	{
	SymbolInfo *p = new SymbolInfo(yytext , "CONST_FLOAT");
		p->set_stype("VARIABLE");
        p->set_dtype("FLOAT");
        p->set_parent("CONST_FLOAT");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <CONST_FLOAT> Lexeme "<<yytext<<" found"<<endl;
    return CONST_FLOAT;
    
    //outputtoken<<"<CONST_FLOAT, "<<yytext<<">"<<endl;
}
{DIGIT}*(\.{DIGIT}+)\.[0-9\.E-]*(\.)*   {
    
    outputerror<<"Error at line# "<< line_count << ": TOO_MANY_DECIMAL_POINTS "<<yytext <<endl;
    err_count++;
}

([0-9]*(\.[0-9]*)?[E][+-]?[0-9]*[0-9\.E-]*(\.)*)|([0-9]+\.) {
    
    outputlog<<"Error at line# "<<line_count <<": ILLFORMED_NUMBER "<<yytext <<endl;
    err_count++;
}


{LETTER}{ALPHANUMERIC}*	{
	SymbolInfo *p = new SymbolInfo(yytext , "ID");
		p->set_parent("ID");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <ID> Lexeme "<<yytext <<" found"<<endl;
	
    return ID;
    //if(table->insert((string)yytext,"ID")){
	//	table->print_all_scope_table();
	//}
    //outputtoken<<"<ID, "<<yytext<<">"<<endl;
}


{DIGIT}*(\.{DIGIT}+)?(E[-]?{DIGIT}+)?{LETTER}{ALPHANUMERIC}*   {

    outputerror<<"Error at line# "<<line_count <<": INVALID_ID_SUFFIX_NUM_PREFIX "<<yytext <<endl;

    err_count++;
}


"+"|"-"	{
	SymbolInfo *p = new SymbolInfo(yytext , "ADDOP");
		p->set_parent("ADDOP");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <ADDOP> Lexeme "<<yytext<<" found"<<endl;
    
    return ADDOP;
    //outputtoken<<"<ADDOP, "<<yytext<<">"<<endl;
}
"*"|"/"|"%"	{
	SymbolInfo *p = new SymbolInfo(yytext , "MULOP");
		p->set_parent("MULOP");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <MULOP> Lexeme "<<yytext<<" found"<<endl;
    return MULOP;
    
    //outputtoken<<"<MULOP, "<<yytext<<">"<<endl;
}
"++"	{
	SymbolInfo *p = new SymbolInfo(yytext , "INCOP");
		p->set_parent("INCOP");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <INCOP> Lexeme "<<yytext<<" found"<<endl;
    return INCOP;
    
    
    //outputtoken<<"<INCOP, "<<yytext<<">"<<endl;
}

"--"    {
    SymbolInfo *p = new SymbolInfo(yytext , "DECOP");
		p->set_parent("DECOP");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
    outputlog<<"Line# "<<line_count<<": Token <DECOP> Lexeme "<<yytext<<" found"<<endl;
    return DECOP;
}

"<"|"<="|">"|">="|"=="|"!="		{
	SymbolInfo *p = new SymbolInfo(yytext , "RELOP");
		p->set_parent("RELOP");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <RELOP> Lexeme "<<yytext<<" found"<<endl;
    return RELOP;
    
    //outputtoken<<"<RELOP, "<<yytext<<">"<<endl;
}
"="	{
	SymbolInfo *p = new SymbolInfo(yytext , "ASSIGNOP");
		p->set_parent("ASSIGNOP");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <ASSIGNOP> Lexeme "<<yytext<<" found"<<endl;
    return ASSIGNOP;
    
    //outputtoken<<"<ASSIGNOP, "<<yytext<<">"<<endl;
}

"&&"|"||"	{
	SymbolInfo *p = new SymbolInfo(yytext , "LOGICOP");
		p->set_parent("LOGICOP");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <LOGICOP> Lexeme "<<yytext<<" found"<<endl;
    return LOGICOP;
    
    //outputtoken<<"<LOGICOP, "<<yytext<<">"<<endl;
}
"&"|"|"|"^"|"<<"|">>"	{
	SymbolInfo *p = new SymbolInfo(yytext , "BITOP");
		p->set_parent("BITOP");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <BITOP> Lexeme "<<yytext<<" found"<<endl;
    return BITOP;
    
    //outputtoken<<"<BITOP, "<<yytext<<">"<<endl;
}

"!"	{
	SymbolInfo *p = new SymbolInfo(yytext , "NOT");
		p->set_parent("NOT");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <NOT> Lexeme "<<yytext<<" found"<<endl;
    return NOT;
    
    
    //outputtoken<<"<NOT, "<<yytext<<">"<<endl;
}
"("	{
	SymbolInfo *p = new SymbolInfo(yytext , "LPAREN");
	p->set_parent("LPAREN");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
	yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <LPAREN> Lexeme "<<yytext<<" found"<<endl;
    return LPAREN;
    
    //outputtoken<<"<LPAREN, "<<yytext<<">"<<endl;
}
")"	{
	SymbolInfo *p = new SymbolInfo(yytext , "RPAREN");
		p->set_parent("RPAREN");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <RPAREN> Lexeme "<<yytext<<" found"<<endl;
    return RPAREN;
    
    //outputtoken<<"<RPAREN, "<<yytext<<">"<<endl;
}
"{"	{
	SymbolInfo *p = new SymbolInfo(yytext , "LCURL");
		p->set_parent("LCURL");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <LCURL> Lexeme "<<yytext<<" found"<<endl;
	return LCURL;
    //table->enter_scope();
    //outputtoken<<"<LCURL, "<<yytext<<">"<<endl;
}
"}"	{
	SymbolInfo *p = new SymbolInfo(yytext , "RCURL");
		p->set_parent("RCURL");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <RCURL> Lexeme "<<yytext<<" found"<<endl;
	return RCURL;
    //table->exit_scope();
    //outputtoken<<"<RCURL, "<<yytext<<">"<<endl;
}

"["	{
	SymbolInfo *p = new SymbolInfo(yytext , "LSQUARE");
		p->set_parent("LSQUARE");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <LSQUARE> Lexeme "<<yytext<<" found"<<endl;
    return LSQUARE;
    
    //outputtoken<<"<LSQUARE, "<<yytext<<">"<<endl;
}
"]"	{
	SymbolInfo *p = new SymbolInfo(yytext , "RSQUARE");
		p->set_parent("RSQUARE");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <RSQUARE> Lexeme "<<yytext<<" found"<<endl;
    return RSQUARE;
    
    //outputtoken<<"<RSQUARE, "<<yytext<<">"<<endl;
}
","	{
	SymbolInfo *p = new SymbolInfo(yytext , "COMMA");
		p->set_parent("COMMA");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <COMMA> Lexeme "<<yytext<<" found"<<endl;
    return COMMA;
    
    //outputtoken<<"<COMMA, "<<yytext<<">"<<endl;
}
";"	{
	SymbolInfo *p = new SymbolInfo(yytext , "SEMICOLON");
		p->set_parent("SEMICOLON");
		p->set_child(yytext);
		p->set_is_child_or_not(true);
		p->set_startline(line_count);
		p->set_endline(line_count);
		
		yylval.sp = p;
	outputlog<<"Line# "<<line_count<<": Token <SEMICOLON> Lexeme "<<yytext<<" found"<<endl;
    return SEMICOLON;
    
    //outputtoken<<"<SEMICOLON, "<<yytext<<">"<<endl;
}


.   {
        
        
        outputlog<<"Error at line# "<<line_count<<": UNRECOGNIZED_CHAR "<< yytext <<endl;
        outputerror<<"Error at line# "<<line_count<<": UNRECOGNIZED_CHAR "<< yytext <<endl;
        
        err_count = err_count + 1;
        
}



%%


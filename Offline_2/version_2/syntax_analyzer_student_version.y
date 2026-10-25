%{
#include<bits/stdc++.h>
#include "symbol_info.h"

using namespace std;


int yyparse(void);
int yylex(void);
void yyerror(const char *s);
extern FILE *yyin;

ofstream outputlog;
int line_count = 1;
%}

%union {
    SymbolInfo* sp;
}

%token <sp> IF ELSE FOR WHILE INT FLOAT VOID RETURN PRINTLN
%token <sp> ID CONST_INT CONST_FLOAT ADDOP MULOP INCOP RELOP ASSIGNOP LOGICOP NOT
%token <sp> LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON
%type <sp> start program unit func_definition param_list compound_statement variable_decl type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%destructor { delete $$; } <sp>


%%

start : program
    {
        outputlog<<"At line no: "<<line_count<<" start : program "<<endl<<endl;
        delete $1;
        $$ = NULL;
    }
    ;

program : program unit
    {
        outputlog<<"At line no: "<<line_count<<" program : program unit "<<endl<<endl;
        outputlog<<$1->get_name()+"\n"+$2->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+"\n"+$2->get_name(),"program");
        delete $1;
        delete $2;
    }
    | unit
    {
        outputlog<<"At line no: "<<line_count<<" program : unit "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"program");
        delete $1;
    }
    ;

unit : variable_decl
    {
        outputlog<<"At line no: "<<line_count<<" unit : variable_decl "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"unit");
        delete $1;
    }
    | func_definition
    {
        outputlog<<"At line no: "<<line_count<<" unit : func_definition "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"unit");
        delete $1;
    }
    ;

func_definition : type_specifier ID LPAREN param_list RPAREN compound_statement
    {
        outputlog<<"At line no: "<<line_count<<" func_definition : type_specifier ID LPAREN param_list RPAREN compound_statement "<<endl<<endl;
        outputlog<<$1->get_name()+" "+$2->get_name()+"("+$4->get_name()+")\n"+$6->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+"("+$4->get_name()+")\n"+$6->get_name(),"func_def");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
        delete $5;
        delete $6;
    }
    | type_specifier ID LPAREN RPAREN compound_statement
    {
        outputlog<<"At line no: "<<line_count<<" func_definition : type_specifier ID LPAREN RPAREN compound_statement "<<endl<<endl;
        outputlog<<$1->get_name()+" "+$2->get_name()+"()\n"+$5->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+"()\n"+$5->get_name(),"func_def");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
        delete $5;
    }
    ;

param_list : param_list COMMA type_specifier ID
    {
        outputlog<<"At line no: "<<line_count<<" param_list : param_list COMMA type_specifier ID "<<endl<<endl;
        outputlog<<$1->get_name()+","+$3->get_name()+" "+$4->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+","+$3->get_name()+" "+$4->get_name(),"param_list");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
    }
    | param_list COMMA type_specifier
    {
        outputlog<<"At line no: "<<line_count<<" param_list : param_list COMMA type_specifier "<<endl<<endl;
        outputlog<<$1->get_name()+","+$3->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+","+$3->get_name(),"param_list");
        delete $1;
        delete $2;
        delete $3;
    }
    | type_specifier ID
    {
        outputlog<<"At line no: "<<line_count<<" param_list : type_specifier ID "<<endl<<endl;
        outputlog<<$1->get_name()+" "+$2->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+" "+$2->get_name(),"param_list");
        delete $1;
        delete $2;
    }
    | type_specifier
    {
        outputlog<<"At line no: "<<line_count<<" param_list : type_specifier "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"param_list");
        delete $1;
    }
    ;

compound_statement : LCURL statements RCURL
    {
        outputlog<<"At line no: "<<line_count<<" compound_statement : LCURL statements RCURL "<<endl<<endl;
        outputlog<<"{\n"+$2->get_name()+"\n}"<<endl<<endl;
        $$ = new SymbolInfo("{\n"+$2->get_name()+"\n}","compound_statement");
        delete $1;
        delete $2;
        delete $3;
    }
    | LCURL RCURL
    {
        outputlog<<"At line no: "<<line_count<<" compound_statement : LCURL RCURL "<<endl<<endl;
        outputlog<<"{\n}"<<endl<<endl;
        $$ = new SymbolInfo("{\n}","compound_statement");
        delete $1;
        delete $2;
    }
    ;

variable_decl : type_specifier declaration_list SEMICOLON
    {
        outputlog<<"At line no: "<<line_count<<" variable_decl : type_specifier declaration_list SEMICOLON "<<endl<<endl;
        outputlog<<$1->get_name()+" "+$2->get_name()+";"<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+" "+$2->get_name()+";","variable_decl");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

type_specifier : INT
    {
        outputlog<<"At line no: "<<line_count<<" type_specifier : INT "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"type_specifier");
        delete $1;
    }
    | FLOAT
    {
        outputlog<<"At line no: "<<line_count<<" type_specifier : FLOAT "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"type_specifier");
        delete $1;
    }
    | VOID
    {
        outputlog<<"At line no: "<<line_count<<" type_specifier : VOID "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"type_specifier");
        delete $1;
    }
    ;

declaration_list : declaration_list COMMA ID
    {
        outputlog<<"At line no: "<<line_count<<" declaration_list : declaration_list COMMA ID "<<endl<<endl;
        outputlog<<$1->get_name()+","+$3->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+","+$3->get_name(),"declaration_list");
        delete $1;
        delete $2;
        delete $3;
    }
    | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
    {
        outputlog<<"At line no: "<<line_count<<" declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
        outputlog<<$1->get_name()+","+$3->get_name()+"["+$5->get_name()+"]"<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+","+$3->get_name()+"["+$5->get_name()+"]","declaration_list");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
        delete $5;
        delete $6;
    }
    | ID
    {
        outputlog<<"At line no: "<<line_count<<" declaration_list : ID "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"declaration_list");
        delete $1;
    }
    | ID LTHIRD CONST_INT RTHIRD
    {
        outputlog<<"At line no: "<<line_count<<" declaration_list : ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
        outputlog<<$1->get_name()+"["+$3->get_name()+"]"<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+"["+$3->get_name()+"]","declaration_list");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
    }
    ;

statements : statement
    {
        outputlog<<"At line no: "<<line_count<<" statements : statement "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"statements");
        delete $1;
    }
    | statements statement
    {
        outputlog<<"At line no: "<<line_count<<" statements : statements statement "<<endl<<endl;
        outputlog<<$1->get_name()+"\n"+$2->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+"\n"+$2->get_name(),"statements");
        delete $1;
        delete $2;
    }
    ;

statement : variable_decl
    {
        outputlog<<"At line no: "<<line_count<<" statement : variable_decl "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"stmnt");
        delete $1;
    }
    | expression_statement
    {
        outputlog<<"At line no: "<<line_count<<" statement : expression_statement "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"stmnt");
        delete $1;
    }
    | compound_statement
    {
        outputlog<<"At line no: "<<line_count<<" statement : compound_statement "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"stmnt");
        delete $1;
    }
    | FOR LPAREN expression_statement expression_statement expression RPAREN statement
    {
        outputlog<<"At line no: "<<line_count<<" statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement "<<endl<<endl;
        outputlog<<"for("+$3->get_name()+$4->get_name()+$5->get_name()+")\n"+$7->get_name()<<endl<<endl;
        $$ = new SymbolInfo("for("+$3->get_name()+$4->get_name()+$5->get_name()+")\n"+$7->get_name(),"stmnt");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
        delete $5;
        delete $6;
        delete $7;
    }
    | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
    {
        outputlog<<"At line no: "<<line_count<<" statement : IF LPAREN expression RPAREN statement "<<endl<<endl;
        outputlog<<"if("+$3->get_name()+")\n"+$5->get_name()<<endl<<endl;
        $$ = new SymbolInfo("if("+$3->get_name()+")\n"+$5->get_name(),"stmnt");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
        delete $5;
    }
    | IF LPAREN expression RPAREN statement ELSE statement
    {
        outputlog<<"At line no: "<<line_count<<" statement : IF LPAREN expression RPAREN statement ELSE statement "<<endl<<endl;
        outputlog<<"if("+$3->get_name()+")\n"+$5->get_name()+"\nelse\n"+$7->get_name()<<endl<<endl;
        $$ = new SymbolInfo("if("+$3->get_name()+")\n"+$5->get_name()+"\nelse\n"+$7->get_name(),"stmnt");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
        delete $5;
        delete $6;
        delete $7;
    }
    | WHILE LPAREN expression RPAREN statement
    {
        outputlog<<"At line no: "<<line_count<<" statement : WHILE LPAREN expression RPAREN statement "<<endl<<endl;
        outputlog<<"while("+$3->get_name()+")\n"+$5->get_name()<<endl<<endl;
        $$ = new SymbolInfo("while("+$3->get_name()+")\n"+$5->get_name(),"stmnt");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
        delete $5;
    }
    | PRINTLN LPAREN ID RPAREN SEMICOLON
    {
        outputlog<<"At line no: "<<line_count<<" statement : PRINTLN LPAREN ID RPAREN SEMICOLON "<<endl<<endl;
        outputlog<<"printf("+$3->get_name()+");"<<endl<<endl;
        $$ = new SymbolInfo("printf("+$3->get_name()+");","stmnt");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
        delete $5;
    }
    | RETURN expression SEMICOLON
    {
        outputlog<<"At line no: "<<line_count<<" statement : RETURN expression SEMICOLON "<<endl<<endl;
        outputlog<<"return "+$2->get_name()+";"<<endl<<endl;
        $$ = new SymbolInfo("return "+$2->get_name()+";","stmnt");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

expression_statement : SEMICOLON
    {
        outputlog<<"At line no: "<<line_count<<" expression_statement : SEMICOLON "<<endl<<endl;
        outputlog<<";"<<endl<<endl;
        $$ = new SymbolInfo(";","expression_statement");
        delete $1;
    }
    | expression SEMICOLON
    {
        outputlog<<"At line no: "<<line_count<<" expression_statement : expression SEMICOLON "<<endl<<endl;
        outputlog<<$1->get_name()+";"<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+";","expression_statement");
        delete $1;
        delete $2;
    }
    ;

variable : ID
    {
        outputlog<<"At line no: "<<line_count<<" variable : ID "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"variable");
        delete $1;
    }
    | ID LTHIRD expression RTHIRD
    {
        outputlog<<"At line no: "<<line_count<<" variable : ID LTHIRD expression RTHIRD "<<endl<<endl;
        outputlog<<$1->get_name()+"["+$3->get_name()+"]"<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+"["+$3->get_name()+"]","variable");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
    }
    ;

expression : logic_expression
    {
        outputlog<<"At line no: "<<line_count<<" expression : logic_expression "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"expression");
        delete $1;
    }
    | variable ASSIGNOP logic_expression
    {
        outputlog<<"At line no: "<<line_count<<" expression : variable ASSIGNOP logic_expression "<<endl<<endl;
        outputlog<<$1->get_name()+"="+$3->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+"="+$3->get_name(),"expression");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

logic_expression : rel_expression
    {
        outputlog<<"At line no: "<<line_count<<" logic_expression : rel_expression "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"logic_expression");
        delete $1;
    }
    | rel_expression LOGICOP rel_expression
    {
        outputlog<<"At line no: "<<line_count<<" logic_expression : rel_expression LOGICOP rel_expression "<<endl<<endl;
        outputlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"logic_expression");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

rel_expression : simple_expression
    {
        outputlog<<"At line no: "<<line_count<<" rel_expression : simple_expression "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"rel_expression");
        delete $1;
    }
    | simple_expression RELOP simple_expression
    {
        outputlog<<"At line no: "<<line_count<<" rel_expression : simple_expression RELOP simple_expression "<<endl<<endl;
        outputlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"rel_expression");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

simple_expression : term
    {
        outputlog<<"At line no: "<<line_count<<" simple_expression : term "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"simple_expression");
        delete $1;
    }
    | simple_expression ADDOP term
    {
        outputlog<<"At line no: "<<line_count<<" simple_expression : simple_expression ADDOP term "<<endl<<endl;
        outputlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"simple_expression");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

term : unary_expression
    {
        outputlog<<"At line no: "<<line_count<<" term : unary_expression "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"term");
        delete $1;
    }
    | term MULOP unary_expression
    {
        outputlog<<"At line no: "<<line_count<<" term : term MULOP unary_expression "<<endl<<endl;
        outputlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+$2->get_name()+$3->get_name(),"term");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

unary_expression : ADDOP unary_expression
    {
        outputlog<<"At line no: "<<line_count<<" unary_expression : ADDOP unary_expression "<<endl<<endl;
        outputlog<<$1->get_name()+$2->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+$2->get_name(),"unary_expression");
        delete $1;
        delete $2;
    }
    | NOT unary_expression
    {
        outputlog<<"At line no: "<<line_count<<" unary_expression : NOT unary_expression "<<endl<<endl;
        outputlog<<"!"+$2->get_name()<<endl<<endl;
        $$ = new SymbolInfo("!"+$2->get_name(),"unary_expression");
        delete $1;
        delete $2;
    }
    | factor
    {
        outputlog<<"At line no: "<<line_count<<" factor_info : factor "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        outputlog<<"At line no: "<<line_count<<" unary_expression : factor "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"unary_expression");
        delete $1;
    }
    ;

factor : variable
    {
        outputlog<<"At line no: "<<line_count<<" factor : variable "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"factor");
        delete $1;
    }
    | ID LPAREN argument_list RPAREN
    {
        outputlog<<"At line no: "<<line_count<<" factor : ID LPAREN argument_list RPAREN "<<endl<<endl;
        outputlog<<$1->get_name()+"("+$3->get_name()+")"<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+"("+$3->get_name()+")","factor");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
    }
    | LPAREN expression RPAREN
    {
        outputlog<<"At line no: "<<line_count<<" factor : LPAREN expression RPAREN "<<endl<<endl;
        outputlog<<"("+$2->get_name()+")"<<endl<<endl;
        $$ = new SymbolInfo("("+$2->get_name()+")","factor");
        delete $1;
        delete $2;
        delete $3;
    }
    | CONST_INT
    {
        outputlog<<"At line no: "<<line_count<<" factor : CONST_INT "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"factor");
        delete $1;
    }
    | CONST_FLOAT
    {
        outputlog<<"At line no: "<<line_count<<" factor : CONST_FLOAT "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"factor");
        delete $1;
    }
    | variable INCOP
    {
        if($2->get_name() == "--")
        {
            outputlog<<"At line no: "<<line_count<<" factor : variable DECOP "<<endl<<endl;
        }
        else
        {
            outputlog<<"At line no: "<<line_count<<" factor : variable INCOP "<<endl<<endl;
        }
        outputlog<<$1->get_name()+$2->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+$2->get_name(),"factor");
        delete $1;
        delete $2;
    }
    ;

argument_list : arguments
    {
        outputlog<<"At line no: "<<line_count<<" argument_list : arguments "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"argument_list");
        delete $1;
    }
    | 
    {
        outputlog<<"At line no: "<<line_count<<" argument_list :  "<<endl<<endl;
        outputlog<<""<<endl<<endl;
        $$ = new SymbolInfo("","argument_list");
    }
    ;

arguments : arguments COMMA logic_expression
    {
        outputlog<<"At line no: "<<line_count<<" arguments : arguments COMMA logic_expression "<<endl<<endl;
        outputlog<<$1->get_name()+","+$3->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name()+","+$3->get_name(),"arguments");
        delete $1;
        delete $2;
        delete $3;
    }
    | logic_expression
    {
        outputlog<<"At line no: "<<line_count<<" arguments : logic_expression "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new SymbolInfo($1->get_name(),"arguments");
        delete $1;
    }
    ;

%%

void yyerror(const char *s)
{
    outputlog<<"Error at line no: "<<line_count<<": "<<s<<endl<<endl;
}

int main(int c, char *v[])
{
    if(c != 2)
    {
        cout<<"Please provide input file name"<<endl;
        return 1;
    }
    yyin = fopen(v[1], "r");
    if(yyin == NULL)
    {
        cout<<"Couldn't open file"<<endl;
        return 1;
    }
    outputlog.open("my_log.txt", ios::trunc);
    if(!outputlog)
    {
        cout<<"Couldn't open log file"<<endl;
        fclose(yyin);
        return 1;
    }
    int result = yyparse();
    outputlog<<endl<<"Total lines: "<<line_count<<endl;
    outputlog.close();
    fclose(yyin);
    return result;
}

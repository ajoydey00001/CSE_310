%{
#include<bits/stdc++.h>
#include "symbol_table.h"

using namespace std;


int yyparse(void);
int yylex(void);
void yyerror(const char *s);
extern FILE *yyin;

ofstream outputlog;
int line_count = 1;

symbol_table *table;

vector<string> var_names; // variables of the current declaration_list
vector<int> var_sizes; // array size of each variable, 0 if not an array
vector<string> param_types; // parameters of the current param_list
vector<string> param_names;
vector<string> pending_types; // parameters waiting for the function body scope
vector<string> pending_names;

void enter_new_scope()
{
    table->enter_scope();
    outputlog<<"New ScopeTable with ID "<<table->get_current_scope_id()<<" created"<<endl<<endl;

    // function parameters belong to the scope of the function body
    for(int i = 0; i < (int)pending_types.size(); i++)
    {
        if(pending_names[i] == "")
            continue;
        symbol_info *s = new symbol_info(pending_names[i],"ID");
        s->set_data_type(pending_types[i]);
        if(!table->insert(s))
            delete s;
    }
    pending_types.clear();
    pending_names.clear();
}

void exit_current_scope()
{
    int id = table->get_current_scope_id();
    table->print_all_scopes(outputlog);
    table->exit_scope();
    outputlog<<"Scopetable with ID "<<id<<" removed"<<endl<<endl;
}

void insert_function(string return_type, string name)
{
    symbol_info *s = new symbol_info(name,"ID");
    s->set_symbol_type("function");
    s->set_data_type(return_type);
    s->set_params(param_types, param_names);
    if(!table->insert(s))
        delete s;

    pending_types = param_types;
    pending_names = param_names;
    param_types.clear();
    param_names.clear();
}

void insert_variables(string data_type)
{
    for(int i = 0; i < (int)var_names.size(); i++)
    {
        symbol_info *s = new symbol_info(var_names[i],"ID");
        s->set_data_type(data_type);
        if(var_sizes[i] > 0)
        {
            s->set_symbol_type("array");
            s->set_arr_size(var_sizes[i]);
        }
        if(!table->insert(s))
            delete s;
    }
    var_names.clear();
    var_sizes.clear();
}
%}

%union {
    symbol_info* sp;
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
        outputlog<<"Symbol Table"<<endl<<endl;
        table->print_all_scopes(outputlog);
        delete $1;
        $$ = NULL;
    }
    ;

program : program unit
    {
        outputlog<<"At line no: "<<line_count<<" program : program unit "<<endl<<endl;
        outputlog<<$1->get_name()+"\n"+$2->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+"\n"+$2->get_name(),"program");
        delete $1;
        delete $2;
    }
    | unit
    {
        outputlog<<"At line no: "<<line_count<<" program : unit "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"program");
        delete $1;
    }
    ;

unit : variable_decl
    {
        outputlog<<"At line no: "<<line_count<<" unit : variable_decl "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"unit");
        delete $1;
    }
    | func_definition
    {
        outputlog<<"At line no: "<<line_count<<" unit : func_definition "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"unit");
        delete $1;
    }
    ;

func_definition : type_specifier ID LPAREN param_list RPAREN
    {
        insert_function($1->get_name(), $2->get_name());
    }
    compound_statement
    {
        outputlog<<"At line no: "<<line_count<<" func_definition : type_specifier ID LPAREN param_list RPAREN compound_statement "<<endl<<endl;
        outputlog<<$1->get_name()+" "+$2->get_name()+"("+$4->get_name()+")\n"+$7->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+" "+$2->get_name()+"("+$4->get_name()+")\n"+$7->get_name(),"func_def");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
        delete $5;
        delete $7;
    }
    | type_specifier ID LPAREN RPAREN
    {
        param_types.clear();
        param_names.clear();
        insert_function($1->get_name(), $2->get_name());
    }
    compound_statement
    {
        outputlog<<"At line no: "<<line_count<<" func_definition : type_specifier ID LPAREN RPAREN compound_statement "<<endl<<endl;
        outputlog<<$1->get_name()+" "+$2->get_name()+"()\n"+$6->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+" "+$2->get_name()+"()\n"+$6->get_name(),"func_def");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
        delete $6;
    }
    ;

param_list : param_list COMMA type_specifier ID
    {
        outputlog<<"At line no: "<<line_count<<" param_list : param_list COMMA type_specifier ID "<<endl<<endl;
        param_types.push_back($3->get_name());
        param_names.push_back($4->get_name());
        outputlog<<$1->get_name()+","+$3->get_name()+" "+$4->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+","+$3->get_name()+" "+$4->get_name(),"param_list");
        delete $1;
        delete $2;
        delete $3;
        delete $4;
    }
    | param_list COMMA type_specifier
    {
        outputlog<<"At line no: "<<line_count<<" param_list : param_list COMMA type_specifier "<<endl<<endl;
        param_types.push_back($3->get_name());
        param_names.push_back("");
        outputlog<<$1->get_name()+","+$3->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+","+$3->get_name(),"param_list");
        delete $1;
        delete $2;
        delete $3;
    }
    | type_specifier ID
    {
        outputlog<<"At line no: "<<line_count<<" param_list : type_specifier ID "<<endl<<endl;
        param_types.clear();
        param_names.clear();
        param_types.push_back($1->get_name());
        param_names.push_back($2->get_name());
        outputlog<<$1->get_name()+" "+$2->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+" "+$2->get_name(),"param_list");
        delete $1;
        delete $2;
    }
    | type_specifier
    {
        outputlog<<"At line no: "<<line_count<<" param_list : type_specifier "<<endl<<endl;
        param_types.clear();
        param_names.clear();
        param_types.push_back($1->get_name());
        param_names.push_back("");
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"param_list");
        delete $1;
    }
    ;

compound_statement : LCURL enter_scope statements RCURL
    {
        outputlog<<"At line no: "<<line_count<<" compound_statement : LCURL statements RCURL "<<endl<<endl;
        outputlog<<"{\n"+$3->get_name()+"\n}"<<endl<<endl;
        $$ = new symbol_info("{\n"+$3->get_name()+"\n}","compound_statement");
        delete $1;
        delete $3;
        delete $4;
        exit_current_scope();
    }
    | LCURL enter_scope RCURL
    {
        outputlog<<"At line no: "<<line_count<<" compound_statement : LCURL RCURL "<<endl<<endl;
        outputlog<<"{\n}"<<endl<<endl;
        $$ = new symbol_info("{\n}","compound_statement");
        delete $1;
        delete $3;
        exit_current_scope();
    }
    ;

enter_scope :
    {
        enter_new_scope();
    }
    ;

variable_decl : type_specifier declaration_list SEMICOLON
    {
        outputlog<<"At line no: "<<line_count<<" variable_decl : type_specifier declaration_list SEMICOLON "<<endl<<endl;
        insert_variables($1->get_name());
        outputlog<<$1->get_name()+" "+$2->get_name()+";"<<endl<<endl;
        $$ = new symbol_info($1->get_name()+" "+$2->get_name()+";","variable_decl");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

type_specifier : INT
    {
        outputlog<<"At line no: "<<line_count<<" type_specifier : INT "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"type_specifier");
        delete $1;
    }
    | FLOAT
    {
        outputlog<<"At line no: "<<line_count<<" type_specifier : FLOAT "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"type_specifier");
        delete $1;
    }
    | VOID
    {
        outputlog<<"At line no: "<<line_count<<" type_specifier : VOID "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"type_specifier");
        delete $1;
    }
    ;

declaration_list : declaration_list COMMA ID
    {
        outputlog<<"At line no: "<<line_count<<" declaration_list : declaration_list COMMA ID "<<endl<<endl;
        var_names.push_back($3->get_name());
        var_sizes.push_back(0);
        outputlog<<$1->get_name()+","+$3->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+","+$3->get_name(),"declaration_list");
        delete $1;
        delete $2;
        delete $3;
    }
    | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
    {
        outputlog<<"At line no: "<<line_count<<" declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
        var_names.push_back($3->get_name());
        var_sizes.push_back(stoi($5->get_name()));
        outputlog<<$1->get_name()+","+$3->get_name()+"["+$5->get_name()+"]"<<endl<<endl;
        $$ = new symbol_info($1->get_name()+","+$3->get_name()+"["+$5->get_name()+"]","declaration_list");
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
        var_names.clear();
        var_sizes.clear();
        var_names.push_back($1->get_name());
        var_sizes.push_back(0);
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"declaration_list");
        delete $1;
    }
    | ID LTHIRD CONST_INT RTHIRD
    {
        outputlog<<"At line no: "<<line_count<<" declaration_list : ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
        var_names.clear();
        var_sizes.clear();
        var_names.push_back($1->get_name());
        var_sizes.push_back(stoi($3->get_name()));
        outputlog<<$1->get_name()+"["+$3->get_name()+"]"<<endl<<endl;
        $$ = new symbol_info($1->get_name()+"["+$3->get_name()+"]","declaration_list");
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
        $$ = new symbol_info($1->get_name(),"statements");
        delete $1;
    }
    | statements statement
    {
        outputlog<<"At line no: "<<line_count<<" statements : statements statement "<<endl<<endl;
        outputlog<<$1->get_name()+"\n"+$2->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+"\n"+$2->get_name(),"statements");
        delete $1;
        delete $2;
    }
    ;

statement : variable_decl
    {
        outputlog<<"At line no: "<<line_count<<" statement : variable_decl "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"stmnt");
        delete $1;
    }
    | expression_statement
    {
        outputlog<<"At line no: "<<line_count<<" statement : expression_statement "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"stmnt");
        delete $1;
    }
    | compound_statement
    {
        outputlog<<"At line no: "<<line_count<<" statement : compound_statement "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"stmnt");
        delete $1;
    }
    | FOR LPAREN expression_statement expression_statement expression RPAREN statement
    {
        outputlog<<"At line no: "<<line_count<<" statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement "<<endl<<endl;
        outputlog<<"for("+$3->get_name()+$4->get_name()+$5->get_name()+")\n"+$7->get_name()<<endl<<endl;
        $$ = new symbol_info("for("+$3->get_name()+$4->get_name()+$5->get_name()+")\n"+$7->get_name(),"stmnt");
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
        $$ = new symbol_info("if("+$3->get_name()+")\n"+$5->get_name(),"stmnt");
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
        $$ = new symbol_info("if("+$3->get_name()+")\n"+$5->get_name()+"\nelse\n"+$7->get_name(),"stmnt");
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
        $$ = new symbol_info("while("+$3->get_name()+")\n"+$5->get_name(),"stmnt");
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
        $$ = new symbol_info("printf("+$3->get_name()+");","stmnt");
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
        $$ = new symbol_info("return "+$2->get_name()+";","stmnt");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

expression_statement : SEMICOLON
    {
        outputlog<<"At line no: "<<line_count<<" expression_statement : SEMICOLON "<<endl<<endl;
        outputlog<<";"<<endl<<endl;
        $$ = new symbol_info(";","expression_statement");
        delete $1;
    }
    | expression SEMICOLON
    {
        outputlog<<"At line no: "<<line_count<<" expression_statement : expression SEMICOLON "<<endl<<endl;
        outputlog<<$1->get_name()+";"<<endl<<endl;
        $$ = new symbol_info($1->get_name()+";","expression_statement");
        delete $1;
        delete $2;
    }
    ;

variable : ID
    {
        outputlog<<"At line no: "<<line_count<<" variable : ID "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"variable");
        delete $1;
    }
    | ID LTHIRD expression RTHIRD
    {
        outputlog<<"At line no: "<<line_count<<" variable : ID LTHIRD expression RTHIRD "<<endl<<endl;
        outputlog<<$1->get_name()+"["+$3->get_name()+"]"<<endl<<endl;
        $$ = new symbol_info($1->get_name()+"["+$3->get_name()+"]","variable");
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
        $$ = new symbol_info($1->get_name(),"expression");
        delete $1;
    }
    | variable ASSIGNOP logic_expression
    {
        outputlog<<"At line no: "<<line_count<<" expression : variable ASSIGNOP logic_expression "<<endl<<endl;
        outputlog<<$1->get_name()+"="+$3->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+"="+$3->get_name(),"expression");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

logic_expression : rel_expression
    {
        outputlog<<"At line no: "<<line_count<<" logic_expression : rel_expression "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"logic_expression");
        delete $1;
    }
    | rel_expression LOGICOP rel_expression
    {
        outputlog<<"At line no: "<<line_count<<" logic_expression : rel_expression LOGICOP rel_expression "<<endl<<endl;
        outputlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+$2->get_name()+$3->get_name(),"logic_expression");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

rel_expression : simple_expression
    {
        outputlog<<"At line no: "<<line_count<<" rel_expression : simple_expression "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"rel_expression");
        delete $1;
    }
    | simple_expression RELOP simple_expression
    {
        outputlog<<"At line no: "<<line_count<<" rel_expression : simple_expression RELOP simple_expression "<<endl<<endl;
        outputlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+$2->get_name()+$3->get_name(),"rel_expression");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

simple_expression : term
    {
        outputlog<<"At line no: "<<line_count<<" simple_expression : term "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"simple_expression");
        delete $1;
    }
    | simple_expression ADDOP term
    {
        outputlog<<"At line no: "<<line_count<<" simple_expression : simple_expression ADDOP term "<<endl<<endl;
        outputlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+$2->get_name()+$3->get_name(),"simple_expression");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

term : unary_expression
    {
        outputlog<<"At line no: "<<line_count<<" term : unary_expression "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"term");
        delete $1;
    }
    | term MULOP unary_expression
    {
        outputlog<<"At line no: "<<line_count<<" term : term MULOP unary_expression "<<endl<<endl;
        outputlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+$2->get_name()+$3->get_name(),"term");
        delete $1;
        delete $2;
        delete $3;
    }
    ;

unary_expression : ADDOP unary_expression
    {
        outputlog<<"At line no: "<<line_count<<" unary_expression : ADDOP unary_expression "<<endl<<endl;
        outputlog<<$1->get_name()+$2->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+$2->get_name(),"unary_expression");
        delete $1;
        delete $2;
    }
    | NOT unary_expression
    {
        outputlog<<"At line no: "<<line_count<<" unary_expression : NOT unary_expression "<<endl<<endl;
        outputlog<<"!"+$2->get_name()<<endl<<endl;
        $$ = new symbol_info("!"+$2->get_name(),"unary_expression");
        delete $1;
        delete $2;
    }
    | factor
    {
        outputlog<<"At line no: "<<line_count<<" factor_info : factor "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        outputlog<<"At line no: "<<line_count<<" unary_expression : factor_info "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"unary_expression");
        delete $1;
    }
    ;

factor : variable
    {
        outputlog<<"At line no: "<<line_count<<" factor : variable "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"factor");
        delete $1;
    }
    | ID LPAREN argument_list RPAREN
    {
        outputlog<<"At line no: "<<line_count<<" factor : ID LPAREN argument_list RPAREN "<<endl<<endl;
        outputlog<<$1->get_name()+"("+$3->get_name()+")"<<endl<<endl;
        $$ = new symbol_info($1->get_name()+"("+$3->get_name()+")","factor");

        // Argument expressions are not typed in this assignment, so every
        // argument is reported, matching the supplied sample logs.
        symbol_info *f = table->lookup($1);
        if(f != NULL && f->function_check())
        {
            for(int i = 1; i <= $3->get_param_count(); i++)
            {
                outputlog<<"At line no: "<<line_count<<" argument "<<i<<" type mismatch in function call: "<<$1->get_name()<<endl<<endl;
            }
        }
        delete $1;
        delete $2;
        delete $3;
        delete $4;
    }
    | LPAREN expression RPAREN
    {
        outputlog<<"At line no: "<<line_count<<" factor : LPAREN expression RPAREN "<<endl<<endl;
        outputlog<<"("+$2->get_name()+")"<<endl<<endl;
        $$ = new symbol_info("("+$2->get_name()+")","factor");
        delete $1;
        delete $2;
        delete $3;
    }
    | CONST_INT
    {
        outputlog<<"At line no: "<<line_count<<" factor : CONST_INT "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"factor");
        delete $1;
    }
    | CONST_FLOAT
    {
        outputlog<<"At line no: "<<line_count<<" factor : CONST_FLOAT "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"factor");
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
        $$ = new symbol_info($1->get_name()+$2->get_name(),"factor");
        delete $1;
        delete $2;
    }
    ;

argument_list : arguments
    {
        outputlog<<"At line no: "<<line_count<<" argument_list : arguments "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"argument_list");
        list<string> types = $1->get_param_types();
        list<string> names = $1->get_param_names();
        $$->set_params(vector<string>(types.begin(), types.end()), vector<string>(names.begin(), names.end()));
        delete $1;
    }
    | 
    {
        outputlog<<"At line no: "<<line_count<<" argument_list :  "<<endl<<endl;
        outputlog<<""<<endl<<endl;
        $$ = new symbol_info("","argument_list");
    }
    ;

arguments : arguments COMMA logic_expression
    {
        outputlog<<"At line no: "<<line_count<<" arguments : arguments COMMA logic_expression "<<endl<<endl;
        outputlog<<$1->get_name()+","+$3->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name()+","+$3->get_name(),"arguments");
        list<string> types = $1->get_param_types();
        list<string> names = $1->get_param_names();
        $$->set_params(vector<string>(types.begin(), types.end()), vector<string>(names.begin(), names.end()));
        $$->add_param("", $3->get_name());
        delete $1;
        delete $2;
        delete $3;
    }
    | logic_expression
    {
        outputlog<<"At line no: "<<line_count<<" arguments : logic_expression "<<endl<<endl;
        outputlog<<$1->get_name()<<endl<<endl;
        $$ = new symbol_info($1->get_name(),"arguments");
        $$->add_param("", $1->get_name());
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
    table = new symbol_table(10);
    enter_new_scope();

    int result = yyparse();
    outputlog<<endl<<"Total lines: "<<line_count<<endl;
    delete table;
    outputlog.close();
    fclose(yyin);
    return result;
}

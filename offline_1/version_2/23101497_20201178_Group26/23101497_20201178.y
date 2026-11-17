%{

#include<cstdio>
#include"symbol_table.h"

#define YYSTYPE symbol_info*

int yyparse(void);
int yylex(void);

extern FILE *yyin;


ofstream outlog;

int line_num = 1;

symbol_table *table;

vector<string> var_names;     // names in the current declaration_list
vector<int> var_sizes;        // array size per name, 0 = not an array
vector<string> param_types;   // params of the current param_list
vector<string> param_names;
vector<string> pending_types; // params waiting to go into the function body scope
vector<string> pending_names;

void enter_new_scope()
{
	table->enter_scope();
	outlog<<"New ScopeTable with ID "<<table->get_current_scope_id()<<" created"<<endl<<endl;

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
	table->print_all_scopes(outlog);
	table->exit_scope();
	outlog<<"Scopetable with ID "<<id<<" removed"<<endl<<endl;
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

void yyerror(const char *s)
{
	outlog<<"At line no: "<<line_num<<" "<<s<<endl<<endl;
}

%}

%token IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN PRINTLN DEFAULT CONTINUE GOTO SWITCH CASE ADDOP MULOP INCOP DECOP RELOP ASSIGNOP LOGICOP NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA COLON SEMICOLON CONST_INT CONST_FLOAT ID

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%

start : program
	{
		outlog<<"At line no: "<<line_num<<" start : program "<<endl<<endl;
		outlog<<"Symbol Table"<<endl<<endl;
		table->print_all_scopes(outlog);
	}
	;

program : program unit
	{
		outlog<<"At line no: "<<line_num<<" program : program unit "<<endl<<endl;
		outlog<<$1->get_name()+"\n"+$2->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+"\n"+$2->get_name(),"program");
	}
	| unit
	{
		outlog<<"At line no: "<<line_num<<" program : unit "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"program");
	}
	;

unit : variable_decl
	{
		outlog<<"At line no: "<<line_num<<" unit : variable_decl "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"unit");
	}
	| func_definition
	{
		outlog<<"At line no: "<<line_num<<" unit : func_definition "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"unit");
	}
	;

func_definition : type_specifier ID LPAREN param_list RPAREN
	{
		insert_function($1->get_name(), $2->get_name());
	}
	compound_statement
	{
		outlog<<"At line no: "<<line_num<<" func_definition : type_specifier ID LPAREN param_list RPAREN compound_statement "<<endl<<endl;
		outlog<<$1->get_name()+" "+$2->get_name()+"("+$4->get_name()+")\n"+$7->get_name()<<endl<<endl;

		$$ = new symbol_info($1->get_name()+" "+$2->get_name()+"("+$4->get_name()+")\n"+$7->get_name(),"func_def");
	}
	| type_specifier ID LPAREN RPAREN
		{
			param_types.clear();
			param_names.clear();
			insert_function($1->get_name(), $2->get_name());
		}
		compound_statement
		{

			outlog<<"At line no: "<<line_num<<" func_definition : type_specifier ID LPAREN RPAREN compound_statement "<<endl<<endl;
			outlog<<$1->get_name()<<" "<<$2->get_name()<<"()\n"<<$6->get_name()<<endl<<endl;

			$$ = new symbol_info($1->get_name()+" "+$2->get_name()+"()\n"+$6->get_name(),"func_def");
		}
	;

param_list : param_list COMMA type_specifier ID
	{
		outlog<<"At line no: "<<line_num<<" param_list : param_list COMMA type_specifier ID "<<endl<<endl;
		param_types.push_back($3->get_name());
		param_names.push_back($4->get_name());
		outlog<<$1->get_name()+","+$3->get_name()+" "+$4->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+","+$3->get_name()+" "+$4->get_name(),"param_list");
	}
	| param_list COMMA type_specifier
	{
		outlog<<"At line no: "<<line_num<<" param_list : param_list COMMA type_specifier "<<endl<<endl;
		param_types.push_back($3->get_name());
		param_names.push_back("");
		outlog<<$1->get_name()+","+$3->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+","+$3->get_name(),"param_list");
	}
	| type_specifier ID
	{
		outlog<<"At line no: "<<line_num<<" param_list : type_specifier ID "<<endl<<endl;
		param_types.clear();
		param_names.clear();
		param_types.push_back($1->get_name());
		param_names.push_back($2->get_name());
		outlog<<$1->get_name()+" "+$2->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+" "+$2->get_name(),"param_list");
	}
	| type_specifier
	{
		outlog<<"At line no: "<<line_num<<" param_list : type_specifier "<<endl<<endl;
		param_types.clear();
		param_names.clear();
		param_types.push_back($1->get_name());
		param_names.push_back("");
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"param_list");
	}
	;

compound_statement : LCURL enter_scope statements RCURL
	{
		outlog<<"At line no: "<<line_num<<" compound_statement : LCURL statements RCURL "<<endl<<endl;
		outlog<<"{\n"+$3->get_name()+"\n}"<<endl<<endl;

		$$ = new symbol_info("{\n"+$3->get_name()+"\n}","comp_stmnt");
		exit_current_scope();
	}
	| LCURL enter_scope RCURL
	{
		outlog<<"At line no: "<<line_num<<" compound_statement : LCURL RCURL "<<endl<<endl;
		outlog<<"{\n}"<<endl<<endl;

		$$ = new symbol_info("{\n}","comp_stmnt");
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
		outlog<<"At line no: "<<line_num<<" variable_decl : type_specifier declaration_list SEMICOLON "<<endl<<endl;
		insert_variables($1->get_name());
		outlog<<$1->get_name()+" "+$2->get_name()+";"<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+" "+$2->get_name()+";","var_decl");
	}
	;

type_specifier : INT
	{
		outlog<<"At line no: "<<line_num<<" type_specifier : INT "<<endl<<endl;
		outlog<<"int"<<endl<<endl;
		
		$$ = new symbol_info("int","type");
	}
	| FLOAT
	{
		outlog<<"At line no: "<<line_num<<" type_specifier : FLOAT "<<endl<<endl;
		outlog<<"float"<<endl<<endl;
		
		$$ = new symbol_info("float","type");
	}
	| VOID
	{
		outlog<<"At line no: "<<line_num<<" type_specifier : VOID "<<endl<<endl;
		outlog<<"void"<<endl<<endl;
		
		$$ = new symbol_info("void","type");
	}
	| CHAR
	{
		outlog<<"At line no: "<<line_num<<" type_specifier : CHAR "<<endl<<endl;
		outlog<<"char"<<endl<<endl;
		
		$$ = new symbol_info("char","type");
	}
	;

declaration_list : declaration_list COMMA ID
	{
		outlog<<"At line no: "<<line_num<<" declaration_list : declaration_list COMMA ID "<<endl<<endl;
		var_names.push_back($3->get_name());
		var_sizes.push_back(0);
		outlog<<$1->get_name()+","+$3->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+","+$3->get_name(),"decl_list");
	}
	| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
	{
		outlog<<"At line no: "<<line_num<<" declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
		var_names.push_back($3->get_name());
		var_sizes.push_back(stoi($5->get_name()));
		outlog<<$1->get_name()+","+$3->get_name()+"["+$5->get_name()+"]"<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+","+$3->get_name()+"["+$5->get_name()+"]","decl_list");
	}
	| ID
	{
		outlog<<"At line no: "<<line_num<<" declaration_list : ID "<<endl<<endl;
		var_names.clear();
		var_sizes.clear();
		var_names.push_back($1->get_name());
		var_sizes.push_back(0);
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"decl_list");
	}
	| ID LTHIRD CONST_INT RTHIRD
	{
		outlog<<"At line no: "<<line_num<<" declaration_list : ID LTHIRD CONST_INT RTHIRD "<<endl<<endl;
		var_names.clear();
		var_sizes.clear();
		var_names.push_back($1->get_name());
		var_sizes.push_back(stoi($3->get_name()));
		outlog<<$1->get_name()+"["+$3->get_name()+"]"<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+"["+$3->get_name()+"]","decl_list");
	}
	;

statements : statement
	{
		outlog<<"At line no: "<<line_num<<" statements : statement "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"stmnts");
	}
	| statements statement
	{
		outlog<<"At line no: "<<line_num<<" statements : statements statement "<<endl<<endl;
		outlog<<$1->get_name()+"\n"+$2->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+"\n"+$2->get_name(),"stmnts");
	}
	;

statement : variable_decl
	{
		outlog<<"At line no: "<<line_num<<" statement : variable_decl "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"stmnt");
	}
	| expression_statement
	{
		outlog<<"At line no: "<<line_num<<" statement : expression_statement "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"stmnt");
	}
	| compound_statement
	{
		outlog<<"At line no: "<<line_num<<" statement : compound_statement "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"stmnt");
	}
	| FOR LPAREN expression_statement expression_statement expression RPAREN statement
	  {
	    	outlog<<"At line no: "<<line_num<<" statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement "<<endl<<endl;
			outlog<<"for("<<$3->get_name()<<$4->get_name()<<$5->get_name()<<")\n"<<$7->get_name()<<endl<<endl;
			
			$$ = new symbol_info("for("+$3->get_name()+$4->get_name()+$5->get_name()+")\n"+$7->get_name(),"stmnt");
	  }
	| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
	{
		outlog<<"At line no: "<<line_num<<" statement : IF LPAREN expression RPAREN statement "<<endl<<endl;
		outlog<<"if("+$3->get_name()+")\n"+$5->get_name()<<endl<<endl;
		
		$$ = new symbol_info("if("+$3->get_name()+")\n"+$5->get_name(),"stmnt");
	}
	| IF LPAREN expression RPAREN statement ELSE statement
	{
		outlog<<"At line no: "<<line_num<<" statement : IF LPAREN expression RPAREN statement ELSE statement "<<endl<<endl;
		outlog<<"if("+$3->get_name()+")\n"+$5->get_name()+"\nelse\n"+$7->get_name()<<endl<<endl;
		
		$$ = new symbol_info("if("+$3->get_name()+")\n"+$5->get_name()+"\nelse\n"+$7->get_name(),"stmnt");
	}
	| WHILE LPAREN expression RPAREN statement
	{
		outlog<<"At line no: "<<line_num<<" statement : WHILE LPAREN expression RPAREN statement "<<endl<<endl;
		outlog<<"while("+$3->get_name()+")\n"+$5->get_name()<<endl<<endl;
		
		$$ = new symbol_info("while("+$3->get_name()+")\n"+$5->get_name(),"stmnt");
	}
	| PRINTLN LPAREN ID RPAREN SEMICOLON
	{
		outlog<<"At line no: "<<line_num<<" statement : PRINTLN LPAREN ID RPAREN SEMICOLON "<<endl<<endl;
		outlog<<"printf("+$3->get_name()+");"<<endl<<endl;
		
		$$ = new symbol_info("printf("+$3->get_name()+");","stmnt");
	}
	| RETURN expression SEMICOLON
	{
		outlog<<"At line no: "<<line_num<<" statement : RETURN expression SEMICOLON "<<endl<<endl;
		outlog<<"return "+$2->get_name()+";"<<endl<<endl;
		
		$$ = new symbol_info("return "+$2->get_name()+";","stmnt");
	}
	;

expression_statement : SEMICOLON
	{
		outlog<<"At line no: "<<line_num<<" expression_statement : SEMICOLON "<<endl<<endl;
		outlog<<";"<<endl<<endl;
		
		$$ = new symbol_info(";","expr_stmt");
	}
	| expression SEMICOLON
	{
		outlog<<"At line no: "<<line_num<<" expression_statement : expression SEMICOLON "<<endl<<endl;
		outlog<<$1->get_name()+";"<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+";","expr_stmt");
	}
	;

variable : ID
	{
		outlog<<"At line no: "<<line_num<<" variable : ID "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"varbl");
	}
	| ID LTHIRD expression RTHIRD
	{
		outlog<<"At line no: "<<line_num<<" variable : ID LTHIRD expression RTHIRD "<<endl<<endl;
		outlog<<$1->get_name()+"["+$3->get_name()+"]"<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+"["+$3->get_name()+"]","varbl");
	}
	;

expression : logic_expression
	{
		outlog<<"At line no: "<<line_num<<" expression : logic_expression "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"expr");
	}
	| variable ASSIGNOP logic_expression
	{
		outlog<<"At line no: "<<line_num<<" expression : variable ASSIGNOP logic_expression "<<endl<<endl;
		outlog<<$1->get_name()+"="+$3->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+"="+$3->get_name(),"expr");
	}
	;

logic_expression : rel_expression
	{
		outlog<<"At line no: "<<line_num<<" logic_expression : rel_expression "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"lgc_expr");
	}
	| rel_expression LOGICOP rel_expression
	{
		outlog<<"At line no: "<<line_num<<" logic_expression : rel_expression LOGICOP rel_expression "<<endl<<endl;
		outlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+$2->get_name()+$3->get_name(),"lgc_expr");
	}
	;

rel_expression : simple_expression
	{
		outlog<<"At line no: "<<line_num<<" rel_expression : simple_expression "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"rel_expr");
	}
	| simple_expression RELOP simple_expression
	{
		outlog<<"At line no: "<<line_num<<" rel_expression : simple_expression RELOP simple_expression "<<endl<<endl;
		outlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+$2->get_name()+$3->get_name(),"rel_expr");
	}
	;

simple_expression : term
	{
		outlog<<"At line no: "<<line_num<<" simple_expression : term "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"simp_expr");
	}
	| simple_expression ADDOP term
	{
		outlog<<"At line no: "<<line_num<<" simple_expression : simple_expression ADDOP term "<<endl<<endl;
		outlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+$2->get_name()+$3->get_name(),"simp_expr");
	}
	;

term : unary_expression
	{
		outlog<<"At line no: "<<line_num<<" term : unary_expression "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"term");
	}
	| term MULOP unary_expression
	{
		outlog<<"At line no: "<<line_num<<" term : term MULOP unary_expression "<<endl<<endl;
		outlog<<$1->get_name()+$2->get_name()+$3->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+$2->get_name()+$3->get_name(),"term");
	}
	;

unary_expression : ADDOP unary_expression
	{
		outlog<<"At line no: "<<line_num<<" unary_expression : ADDOP unary_expression "<<endl<<endl;
		outlog<<$1->get_name()+$2->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+$2->get_name(),"un_expr");
	}
	| NOT unary_expression
	{
		outlog<<"At line no: "<<line_num<<" unary_expression : NOT unary_expression "<<endl<<endl;
		outlog<<"!"+$2->get_name()<<endl<<endl;
		
		$$ = new symbol_info("!"+$2->get_name(),"un_expr");
	}
	| factor_info
	{
		outlog<<"At line no: "<<line_num<<" unary_expression : factor_info "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"un_expr");
	}
	;

factor_info : factor
	{
		outlog<<"At line no: "<<line_num<<" factor_info : factor "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"fctr_info");
	}
	;

factor : variable
	{
		outlog<<"At line no: "<<line_num<<" factor : variable "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"fctr");
	}
	| ID LPAREN argument_list RPAREN
	{
		outlog<<"At line no: "<<line_num<<" factor : ID LPAREN argument_list RPAREN "<<endl<<endl;
		outlog<<$1->get_name()+"("+$3->get_name()+")"<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+"("+$3->get_name()+")","fctr");

		// arguments are untyped in this assignment, so every argument of a
		// known function is reported (matches the supplied sample logs)
		symbol_info *f = table->lookup($1);
		if(f != NULL && f->function_check())
		{
			for(int i = 1; i <= $3->get_param_count(); i++)
			{
				outlog<<"At line no: "<<line_num<<" argument "<<i<<" type mismatch in function call: "<<$1->get_name()<<endl<<endl;
			}
		}
	}
	| LPAREN expression RPAREN
	{
		outlog<<"At line no: "<<line_num<<" factor : LPAREN expression RPAREN "<<endl<<endl;
		outlog<<"("+$2->get_name()+")"<<endl<<endl;
		
		$$ = new symbol_info("("+$2->get_name()+")","fctr");
	}
	| CONST_INT
	{
		outlog<<"At line no: "<<line_num<<" factor : CONST_INT "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"fctr");
	}
	| CONST_FLOAT
	{
		outlog<<"At line no: "<<line_num<<" factor : CONST_FLOAT "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"fctr");
	}
	| variable INCOP
	{
		outlog<<"At line no: "<<line_num<<" factor : variable INCOP "<<endl<<endl;
		outlog<<$1->get_name()+"++"<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+"++","fctr");
	}
	| variable DECOP
	{
		outlog<<"At line no: "<<line_num<<" factor : variable DECOP "<<endl<<endl;
		outlog<<$1->get_name()+"--"<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+"--","fctr");
	}
	;

argument_list : arguments
	{
		outlog<<"At line no: "<<line_num<<" argument_list : arguments "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"arg_list");
		list<string> types = $1->get_param_types();
		list<string> names = $1->get_param_names();
		$$->set_params(vector<string>(types.begin(), types.end()), vector<string>(names.begin(), names.end()));
	}
	| 
	{
		outlog<<"At line no: "<<line_num<<" argument_list :  "<<endl<<endl;
		outlog<<""<<endl<<endl;
		
		$$ = new symbol_info("","arg_list");
	}
	;

arguments : arguments COMMA logic_expression
	{
		outlog<<"At line no: "<<line_num<<" arguments : arguments COMMA logic_expression "<<endl<<endl;
		outlog<<$1->get_name()+","+$3->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name()+","+$3->get_name(),"arg");
		list<string> types = $1->get_param_types();
		list<string> names = $1->get_param_names();
		$$->set_params(vector<string>(types.begin(), types.end()), vector<string>(names.begin(), names.end()));
		$$->add_param("", $3->get_name());
	}
	| logic_expression
	{
		outlog<<"At line no: "<<line_num<<" arguments : logic_expression "<<endl<<endl;
		outlog<<$1->get_name()<<endl<<endl;
		
		$$ = new symbol_info($1->get_name(),"arg");
		$$->add_param("", $1->get_name());
	}
	;

%%

int main(int c, char *v[])
{
	if(c != 2) 
	{
		  // check if filename given
		  cout<<"Please provide input file name"<<endl;
		  return 0;
	}
	yyin = fopen(v[1], "r");
	outlog.open("23101497_20201178_log.txt", ios::trunc);
	
	if(yyin == NULL)
	{
		cout<<"Couldn't open file"<<endl;
		return 0;
	}

	table = new symbol_table(10); // 10 buckets per scope table
	enter_new_scope();            // global scope = ScopeTable 1

	yyparse();

	//print number of total lines
	outlog<<endl<<"Total lines: "<<line_num<<endl;

	delete table;

	outlog.close();
	
	fclose(yyin);
	
	return 0;
}

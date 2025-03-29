
%{
#include<bits/stdc++.h>

#include "SymbolInfo_ScopeTable_SymbolTable.cpp"


using namespace std;

int err_count = 0;
int line_count = 1;

extern FILE *yyin;

ofstream outputlog("1905038_log.txt");
ofstream outputerror("1905038_error.txt");
ofstream outputparsetree("1905038_parsetree.txt");


int yylex(void);
int yyparse(void);


void yyerror(string str)
{
	//write your code
	
}




SymbolTable* table = new SymbolTable(11);
vector<SymbolInfo*> par_list;

vector<SymbolInfo*> arg_list;

string recentFunctionName = "\0";

string recentDataType = "\0";
vector<string> dec_func_complete;
bool par_flag = true;


void print_parse_tree(SymbolInfo* p, int depth){
    
     
      for(int i=0;i<depth ; i++){
        outputparsetree<<" ";
      }
      
    if(p->get_is_child_or_not()){
        outputparsetree<< p->get_parent() <<" : "<< p->get_child() <<"	";
        outputparsetree<<"<Line: "<< p->get_startline() <<">"<<endl;
    }
    else{
        outputparsetree<< p->get_parent() <<" : "<< p->get_child() <<" 	";
        outputparsetree<<"<Line: "<< p->get_startline()<<"-"<< p->get_endline() <<">"<<endl;
        
        for( auto k : p->get_childlist()){
            
            print_parse_tree(k,depth+1);
            
        }

    }

}


void delete_parse_tree(SymbolInfo* p){
    if(p->get_is_child_or_not()){
        delete p;
        return;
    }


    for(auto k : p->get_childlist()){
        delete_parse_tree(k);
    }
    delete p;

}


%}

%union {
    SymbolInfo* sp;
     }

%token <sp> IF ELSE FOR WHILE DO INT CHAR FLOAT VOID RETURN DEFAULT CONTINUE CONST_FLOAT CONST_INT ID ADDOP MULOP INCOP DECOP RELOP ASSIGNOP LOGICOP BITOP NOT LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON PRINTLN


%type <sp> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments dummy_enterScope



%nonassoc LOWER_THAN_ELSE

%nonassoc ELSE


%%

start : program
	{

        outputlog<< "start : program "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("start");
        $$->set_child("program");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);


        print_parse_tree($$,0);
        delete_parse_tree($$);
        outputlog<<"Total Lines: "<<line_count<<endl;
         outputlog<<"Total Errors: "<< err_count<<endl;
        

	}
	;

program : program unit 
    {
        
        outputlog<<"program : program unit "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("program");
        $$->set_child("program unit");
        $$->set_startline($1->get_startline());
        $$->set_endline($2->get_endline());
        $$->add_child($1);
        $$->add_child($2);

    }
	| unit
    {
        outputlog<<"program : unit "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("program");
        $$->set_child("unit");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);


    }
	;
	
unit : var_declaration
     {
        outputlog<<"unit : var_declaration  "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("unit");
        $$->set_child("var_declaration");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);


     }
     | func_declaration
     {
        outputlog<<"unit : func_declaration "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("unit");
        $$->set_child("func_declaration");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);


     }
     | func_definition
     {
        outputlog<<"unit : func_definition  "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("unit");
        $$->set_child("func_definition");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);


     }
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
        {
            outputlog<<"func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON "<<endl;
            $$ = new SymbolInfo("none","none");
            $$->set_parent("func_declaration");
            $$->set_child("type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
            $$->set_startline($1->get_startline());
            $$->set_endline($6->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);
            $$->add_child($4);
            $$->add_child($5);
            $$->add_child($6);
            
            
            
            SymbolInfo* p = table->look_up($2->get_name());
            if(p != NULL){
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Multiple declaration of "+$2->get_name()<<endl;
               
            }
            else{
                table->insert($2->get_name(),"FUNCTION",$1->get_dtype());
                SymbolInfo* k = table->look_up($2->get_name());

                k->add_para(par_list);

                par_list.clear();
            }

        }
		| type_specifier ID LPAREN RPAREN SEMICOLON
        {
            $$ = new SymbolInfo("none","none");
            $$->set_parent("func_declaration");
            $$->set_child("type_specifier ID LPAREN RPAREN SEMICOLON");
            $$->set_startline($1->get_startline());
            $$->set_endline($5->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);
            $$->add_child($4);
            $$->add_child($5);


            outputlog<<"func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON "<<endl;
            
            SymbolInfo* p = table->look_up($2->get_name());
            if(p != NULL){
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Multiple declaration of "+$2->get_name()<<endl;
                
            }
            else{
                table->insert($2->get_name(),"FUNCTION",$1->get_dtype());

            }

        }
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN {
                    SymbolInfo* p = table->look_up($2->get_name());
            if(p!= NULL){

                if(p->get_stype().compare("FUNCTION") != 0){
                    err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": '"+$2->get_name()<<"' redeclared as different kind of symbol"<<endl;
                
                }
                else{
                    if(p->get_dtype().compare($1->get_dtype()) != 0){
                        err_count = err_count + 1;
                        outputerror<<"Line# "<<line_count<<": Conflicting types for '"+$2->get_name()<<"'"<<endl;
                        
                    }
                    
                    vector<SymbolInfo*> k = p->get_para();
                    if(par_list.size()-k.size() != 0){
                        err_count = err_count + 1;
                         outputerror<<"Line# "<<line_count<<": Conflicting types for '"+$2->get_name()<<"'"<<endl;
                        
                    }

                    if(k.size()-par_list.size()>=0){
                        for(int y = 0 ; y < par_list.size() ; y++){
                            if(k[y]->get_dtype().compare(par_list[y]->get_dtype()) !=0){
                                err_count = err_count + 1;
                                 outputerror<<"Line# "<<line_count<<": "+$2->get_name()+" parameter type error"<<endl;
                                
                            }
                        }
                    }
                    else{
                        for(int y = 0 ; y < k.size() ; y++){
                            if(k[y]->get_dtype().compare(par_list[y]->get_dtype()) !=0){
                                err_count = err_count + 1;
                                 outputerror<<"Line# "<<line_count<<": "+$2->get_name()+" parameter type error"<<endl;
                                
                            }
                        }
                    }

                }



            }
            else{

                table->insert($2->get_name(),"FUNCTION",$1->get_dtype());
                
                SymbolInfo* k = table->look_up($2->get_name());
                
                k->add_para(par_list);

                
                
            }
            recentFunctionName = $2->get_name();

                }
 compound_statement
        {
            
                    for(auto j : dec_func_complete){
                        if(j.compare($2->get_name()) ==0){
                                err_count = err_count + 1;
                                outputerror<<"Line# "<<line_count<<": Multiple definition of "<<$2->get_name()<<endl;
                                
                            break;
                        }
                    }
            
            dec_func_complete.push_back($2->get_name());

            outputlog<<"func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement "<<endl;
            $$ = new SymbolInfo("none","none");
            $$->set_parent("func_definition");
            $$->set_child("type_specifier ID LPAREN parameter_list RPAREN compound_statement");
            $$->set_startline($1->get_startline());
            $$->set_endline($7->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);
            $$->add_child($4);
            $$->add_child($5);
            $$->add_child($7);
            
            

       
        }
		| type_specifier ID LPAREN RPAREN {
            SymbolInfo* p = table->look_up($2->get_name());
            if(p!= NULL){
                if(p->get_stype().compare("FUNCTION") != 0){
                    err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": '"+$2->get_name()<<"' redeclared as different kind of symbol"<<endl;
               
                }
                if(p->get_dtype().compare($1->get_dtype()) != 0){
                        err_count = err_count + 1;
                        outputerror<<"Line# "<<line_count<<": Conflicting types for '"+$2->get_name()<<"'"<<endl;
                        
                    }
                

            }
            else{
                table->insert($2->get_name(),"FUNCTION",$1->get_dtype());

            }
            recentFunctionName = $2->get_name();
        }
         compound_statement
        {
            
            
            outputlog<<"func_definition : type_specifier ID LPAREN RPAREN compound_statement"<<endl;
            $$ = new SymbolInfo("none","none");
            $$->set_parent("func_definition");
            $$->set_child("type_specifier ID LPAREN RPAREN compound_statement");
            $$->set_startline($1->get_startline());
            $$->set_endline($6->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);
            $$->add_child($4);
            $$->add_child($6);

            for(auto j : dec_func_complete){
                        if(j.compare($2->get_name()) ==0){
                                err_count = err_count + 1;
                                outputerror<<"Line# "<<line_count<<": Multiple definition of "<<$2->get_name()<<endl;
                                
 
                            break;
                        }
                    }


            dec_func_complete.push_back($2->get_name());
        }
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
        {
            SymbolInfo* p = new SymbolInfo($4->get_name(),$4->get_stype(),$3->get_dtype());
            

            outputlog<<"parameter_list  : parameter_list COMMA type_specifier ID"<<endl;
            if(par_flag){

                int i = 1;
                for(auto j : par_list){
                if(j->get_name().compare(p->get_name())== 0){
                    i=0;
                    par_flag = false;
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Redefinition of parameter '"+j->get_name()+"'"<<endl;
                
                    break;
                }

                 }
                 if(i==1){
                par_list.push_back(p);
                }


            }

            $$ = new SymbolInfo("none","none");
            $$->set_parent("parameter_list");
            $$->set_child("parameter_list COMMA type_specifier ID");
            $$->set_startline($1->get_startline());
            $$->set_endline($4->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);
            $$->add_child($4);


        }
		| parameter_list COMMA type_specifier
        {
            SymbolInfo* p = new SymbolInfo($3->get_name(),$3->get_stype(),$3->get_dtype());
            if(par_flag){
                    par_list.push_back(p);
            }
            
            outputlog<<"parameter_list  : parameter_list COMMA type_specifier"<<endl;
            $$ = new SymbolInfo("none","none");
            $$->set_parent("parameter_list");
            $$->set_child("parameter_list COMMA type_specifier");
            $$->set_startline($1->get_startline());
            $$->set_endline($3->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);



        }
 		| type_specifier ID
        {
            SymbolInfo* p = new SymbolInfo($2->get_name(),$2->get_stype(),$1->get_dtype());
            par_flag = true;
            par_list.push_back(p);

            outputlog<<"parameter_list  : type_specifier ID"<<endl;
            $$ = new SymbolInfo("none","none");
            $$->set_parent("parameter_list");
            $$->set_child("type_specifier ID");
            $$->set_startline($1->get_startline());
            $$->set_endline($2->get_endline());
            $$->add_child($1);
            $$->add_child($2);


        }
		| type_specifier
        {
            SymbolInfo* p = new SymbolInfo($1->get_name(),$1->get_stype(),$1->get_dtype());
            par_flag = true;
            par_list.push_back(p);

            outputlog<<"parameter_list  : type_specifier"<<endl;
            $$ = new SymbolInfo("none","none");
            $$->set_parent("parameter_list");
            $$->set_child("type_specifier");
            $$->set_startline($1->get_startline());
            $$->set_endline($1->get_endline());
            $$->add_child($1);


        }
 		;

 		
compound_statement : LCURL dummy_enterScope statements RCURL
            {
                

                outputlog<<"compound_statement : LCURL statements RCURL  "<<endl;
                table->print_all_scope_table(outputlog);
                table->exit_scope();

                $$ = new SymbolInfo("none","none");
                $$->set_parent("compound_statement");
                $$->set_child("LCURL statements RCURL");
                $$->set_startline($1->get_startline());
                $$->set_endline($4->get_endline());
                $$->add_child($1);
                $$->add_child($3);
                $$->add_child($4);



            }
 		    | LCURL dummy_enterScope RCURL
            {
               

                outputlog<<"compound_statement : LCURL RCURL  "<<endl;
                table->print_all_scope_table(outputlog);
                table->exit_scope();
                $$ = new SymbolInfo("none","none");
                $$->set_parent("compound_statement");
                $$->set_child("LCURL RCURL");
                $$->set_startline($1->get_startline());
                $$->set_endline($3->get_endline());
                $$->add_child($1);
                $$->add_child($3);


            }
 		    ;
dummy_enterScope : {
                    table->enter_scope();
                
                    for(auto j : par_list){
                        table->insert(j->get_name(),j->get_stype(),j->get_dtype());

                    }
                
                par_list.clear();


                    }
                ;
var_declaration : type_specifier declaration_list SEMICOLON
         {

            $$ = new SymbolInfo("none","none");
            $$->set_parent("var_declaration");
            $$->set_child("type_specifier declaration_list SEMICOLON");
            $$->set_startline($1->get_startline());
            $$->set_endline($3->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);

            outputlog<<"var_declaration : type_specifier declaration_list SEMICOLON  "<<endl;

            if($1->get_dtype().compare("VOID") ==0){
                err_count = err_count + 1;
                
                outputerror<<"Line# "<<line_count<<": Variable or field '"<<$2->get_name()<<"' declared void"<<endl;
               
            }

         }
 		 ;
 		 
type_specifier	: INT
        {
            $$ = new SymbolInfo($1->get_name(),$1->get_stype(),$1->get_dtype());
            
            recentDataType = "INT";

            outputlog<<"type_specifier	: INT "<<endl;

            $$->set_parent("type_specifier");
            $$->set_child("INT");
            $$->set_startline($1->get_startline());
            $$->set_endline($1->get_endline());
            $$->add_child($1);



        }
 		| FLOAT
        {
            $$ = new SymbolInfo($1->get_name(),$1->get_stype(),$1->get_dtype());
            
            recentDataType = "FLOAT";
            outputlog<<"type_specifier	: FLOAT "<<endl;
            $$->set_parent("type_specifier");
            $$->set_child("FLOAT");
            $$->set_startline($1->get_startline());
            $$->set_endline($1->get_endline());
            $$->add_child($1);


        }
 		| VOID
        {
            $$ = new SymbolInfo($1->get_name(),$1->get_stype(),$1->get_dtype());

            recentDataType = "VOID";
            outputlog<<"type_specifier	: VOID"<<endl;
            $$->set_parent("type_specifier");
            $$->set_child("VOID");
            $$->set_startline($1->get_startline());
            $$->set_endline($1->get_endline());
            $$->add_child($1);
            $$->set_dtype($1->get_dtype());


        }
 		;
 		
declaration_list : declaration_list COMMA ID
          {
            
            $$ = new SymbolInfo("none","none");
            $$->set_parent("declaration_list");
            $$->set_child("declaration_list COMMA ID");
            $$->set_startline($1->get_startline());
            $$->set_endline($3->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);
            


            string s = $1->get_name()+$2->get_name()+$3->get_name();
            $$->set_name(s);
            outputlog<<"declaration_list : declaration_list COMMA ID  "<<endl;

            ScopeTable* k = table->get_current_scopeTable();
            if(k->look_up($3->get_name()) != NULL){
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Conflicting types for'"<<$3->get_name()<<"'"<<endl;
                
            }
            if(recentDataType.compare("VOID") !=0 ){
                table->insert($3->get_name(),"VARIABLE",recentDataType);
            }
            

          }
 		  | declaration_list COMMA ID LSQUARE CONST_INT RSQUARE
          {
            
            
            $$ = new SymbolInfo("none","none");
            $$->set_parent("declaration_list");
            $$->set_child("declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
            $$->set_startline($1->get_startline());
            $$->set_endline($6->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);
            $$->add_child($4);
            $$->add_child($5);
            $$->add_child($6);


            string s = $1->get_name()+$2->get_name()+$3->get_name()+$4->get_name()+$5->get_name()+ $6->get_name();
            $$->set_name(s);
            outputlog<<"declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE "<<endl;

            ScopeTable* k = table->get_current_scopeTable();
            if(k->look_up($3->get_name()) != NULL){
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Conflicting types for'"<<$3->get_name()<<"'"<<endl;
                
            }
            
            if(recentDataType.compare("VOID") !=0 ){
                table->insert($3->get_name(),"ARRAY",recentDataType);
            }
            

          }
 		  | ID
          {
            
            
            $$ = new SymbolInfo("none","none");
            $$->set_parent("declaration_list");
            $$->set_child("ID");
            $$->set_startline($1->get_startline());
            $$->set_endline($1->get_endline());
            $$->add_child($1);
            $$->set_name($1->get_name());

            outputlog<<"declaration_list : ID "<<endl;
            ScopeTable* k = table->get_current_scopeTable();
            if(k->look_up($1->get_name()) != NULL){
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Conflicting types for'"<<$1->get_name()<<"'"<<endl;
                
            }
            
            if(recentDataType.compare("VOID") !=0 ){
                table->insert($1->get_name(),"VARIABLE",recentDataType);
            }


          }
 		  | ID LSQUARE CONST_INT RSQUARE
          {
            
            $$ = new SymbolInfo("none","none");
            $$->set_parent("declaration_list");
            $$->set_child("ID LSQUARE CONST_INT RSQUARE");
            $$->set_startline($1->get_startline());
            $$->set_endline($4->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);
            $$->add_child($4);


            string s = $1->get_name()+$2->get_name()+$3->get_name()+$4->get_name();
            $$->set_name(s);

            outputlog<<"declaration_list : ID LSQUARE CONST_INT RSQUARE "<<endl;
            ScopeTable* k = table->get_current_scopeTable();
            if(k->look_up($1->get_name()) != NULL){
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Conflicting types for'"<<$1->get_name()<<"'"<<endl;
                
            }
            if(recentDataType.compare("VOID") !=0 ){
                table->insert($1->get_name(),"ARRAY",recentDataType);
            }


          }
 		  ;
 		  
statements : statement
       {
        outputlog<<"statements : statement  "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("statements");
        $$->set_child("statement");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);

       }
	   | statements statement
       {
        outputlog<<"statements : statements statement  "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("statements");
        $$->set_child("statements statement");
        $$->set_startline($1->get_startline());
        $$->set_endline($2->get_endline());
        $$->add_child($1);
        $$->add_child($2);


       }
	   ;
	   
statement : var_declaration
      {
        outputlog<<"statement : var_declaration "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("statement");
        $$->set_child("var_declaration");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);


      }
	  | expression_statement
      {
        outputlog<<"statement : expression_statement  "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("statement");
        $$->set_child("expression_statement");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);

      }
	  | compound_statement
      {
        outputlog<<"statement : compound_statement "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("statement");
        $$->set_child("compound_statement");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);


      }
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
      {
        outputlog<<"statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement"<<endl;

        $$ = new SymbolInfo("none","none");
        $$->set_parent("statement");
        $$->set_child("FOR LPAREN expression_statement expression_statement expression RPAREN statement");
        $$->set_startline($1->get_startline());
        $$->set_endline($7->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->add_child($3);
        $$->add_child($4);
        $$->add_child($5);
        $$->add_child($6);
        $$->add_child($7);


      }
	  | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
      {

        outputlog<<"statement : IF LPAREN expression RPAREN statement"<<endl;

        $$ = new SymbolInfo("none","none");
        $$->set_parent("statement");
        $$->set_child("IF LPAREN expression RPAREN statement");
        $$->set_startline($1->get_startline());
        $$->set_endline($5->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->add_child($3);
        $$->add_child($4);
        $$->add_child($5);



      }
	  | IF LPAREN expression RPAREN statement ELSE statement
      {
        outputlog<<"statement : IF LPAREN expression RPAREN statement ELSE statement"<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("statement");
        $$->set_child("IF LPAREN expression RPAREN statement ELSE statement");
        $$->set_startline($1->get_startline());
        $$->set_endline($7->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->add_child($3);
        $$->add_child($4);
        $$->add_child($5);
        $$->add_child($6);
        $$->add_child($7);


      }
	  | WHILE LPAREN expression RPAREN statement
      {
        outputlog<<"statement : WHILE LPAREN expression RPAREN statement"<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("statement");
        $$->set_child("WHILE LPAREN expression RPAREN statement");
        $$->set_startline($1->get_startline());
        $$->set_endline($5->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->add_child($3);
        $$->add_child($4);
        $$->add_child($5);


      }
      
      
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
      {

        SymbolInfo* p = table->look_up($3->get_name());
        outputlog<<"statement : PRINTLN LPAREN ID RPAREN SEMICOLON"<<endl;
        if(p==NULL){
            err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Undeclared variable '"<<$3->get_name()<<"'"<<endl;
               
        }

        $$ = new SymbolInfo("none","none");
        $$->set_parent("statement");
        $$->set_child("PRINTLN LPAREN ID RPAREN SEMICOLON");
        $$->set_startline($1->get_startline());
        $$->set_endline($5->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->add_child($3);
        $$->add_child($4);
        $$->add_child($5);
        

      }
      
      
	  | RETURN expression SEMICOLON
      {
        $$ = new SymbolInfo("none","none");
        $$->set_parent("statement");
        $$->set_child("RETURN expression SEMICOLON");
        $$->set_startline($1->get_startline());
        $$->set_endline($3->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->add_child($3);


        SymbolInfo* p = table->look_up(recentFunctionName);
        outputlog<<"statement : RETURN expression SEMICOLON"<<endl;
        if(p->get_dtype().compare("VOID") == 0){
            err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": warning: ‘return’ with a value, in function returning void"<<endl;
                
        }
        else if((p->get_dtype().compare($2->get_dtype()) != 0) && (p->get_dtype().compare("FLOAT") != 0)){
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Function return type error"<<endl;
                

        }

        

      }
	  ;
	  
expression_statement 	: SEMICOLON	
            {


                outputlog<<"expression_statement : SEMICOLON 		 "<<endl;
                $$ = new SymbolInfo("none","none");
                $$->set_parent("expression_statement");
                $$->set_child("SEMICOLON");
                $$->set_startline($1->get_startline());
                $$->set_endline($1->get_endline());
                $$->add_child($1);



            }
			| expression SEMICOLON 
            {

                outputlog<<"expression_statement : expression SEMICOLON 		 "<<endl;
                $$ = new SymbolInfo("none","none");
                $$->set_parent("expression_statement");
                $$->set_child("expression SEMICOLON");
                $$->set_startline($1->get_startline());
                $$->set_endline($2->get_endline());
                $$->add_child($1);
                $$->add_child($2);


            }
			;
	  
variable : ID 		
     {
        $$ = new SymbolInfo("none","none");
        $$->set_parent("variable");
        $$->set_child("ID");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);

        
        SymbolInfo* p = table->look_up($1->get_name());
        outputlog<<"variable : ID 	 "<<endl;
        if(p != NULL){
            
            
            $$->set_stype(p->get_stype());
            $$->set_dtype(p->get_dtype());

        }
        else{
            $$->set_stype("VARIABLE");
            $$->set_dtype("NONE");
            err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Undeclared variable '"<<$1->get_name()<<"'"<<endl;
                
        }

        


     }
	 | ID LSQUARE expression RSQUARE 
     {
        $$ = new SymbolInfo("none","none");
        $$->set_parent("variable");
        $$->set_child("ID LSQUARE expression RSQUARE");
        $$->set_startline($1->get_startline());
        $$->set_endline($4->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->add_child($3);
        $$->add_child($4);


        SymbolInfo* p = table->look_up($1->get_name());
        outputlog<<"variable : ID LSQUARE expression RSQUARE  	 "<<endl;
        if(p != NULL){

            if($3->get_dtype().compare("FLOAT") == 0){
               err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Array subscript is not an integer"<<endl;
                
            }

            if(p->get_stype().compare("ARRAY") != 0){
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": '"<<p->get_name()<<"' is not an array"<<endl;
                
            }
            $$->set_stype("ARRAY");
            $$->set_dtype(p->get_dtype());

        }
        else{
            $$->set_dtype("NONE");
            $$->set_stype("ARRAY");

            err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Undeclared variable '"<<$1->get_name()<<"'"<<endl;
                
        }


        


     }
	 ;
	 
 expression : logic_expression
       {
        
        outputlog<<"expression 	: logic_expression	 "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("expression");
        $$->set_child("logic_expression");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);
        $$->set_dtype($1->get_dtype());

       }
	   | variable ASSIGNOP logic_expression
       {
        outputlog<<"expression 	: variable ASSIGNOP logic_expression 		 "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("expression");
        $$->set_child("variable ASSIGNOP logic_expression");
        $$->set_startline($1->get_startline());
        $$->set_endline($3->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->add_child($3);
        $$->set_dtype($1->get_dtype());

        if($1->get_dtype().compare("NONE") != 0 && ($3->get_dtype().compare("NONE") != 0)){
                if($3->get_dtype().compare("VOID") == 0  || ($1->get_dtype().compare("VOID") == 0)) {
                
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                
                    }
                    else if(($3->get_dtype().compare("INT") ==0) && ($1->get_dtype().compare("FLOAT") ==0)){
                        
                
                    }
                else if(($1->get_dtype().compare("INT") ==0) && ($3->get_dtype().compare("FLOAT") ==0)){
                        err_count = err_count + 1;
                        outputerror<<"Line# "<<line_count<<": Warning: possible loss of data in assignment of FLOAT to INT"<<endl;
                
                    }
                else if($1->get_dtype().compare($3->get_dtype()) != 0) {
                         err_count = err_count + 1;
                     outputerror<<"Line# "<<line_count<<": Mismatch type for assignment operation"<<endl;
                
                    }


        }

        


       }
	   ;
			
logic_expression : rel_expression 
         {
            $$ = new SymbolInfo("none","none");
            $$->set_parent("logic_expression");
            $$->set_child("rel_expression");
            $$->set_startline($1->get_startline());
            $$->set_endline($1->get_endline());
            $$->add_child($1);
            $$->set_dtype($1->get_dtype());
            $$->set_stype($1->get_stype());

            outputlog<<"logic_expression : rel_expression 	 "<<endl;

         }
		 | rel_expression LOGICOP rel_expression
         {
            $$ = new SymbolInfo("none","none");
            $$->set_parent("logic_expression");
            $$->set_child("rel_expression LOGICOP rel_expression");
            $$->set_startline($1->get_startline());
            $$->set_endline($3->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);


            $$->set_dtype("INT");
            outputlog<<"logic_expression : rel_expression LOGICOP rel_expression 	 	 "<<endl;
            if(($3->get_dtype().compare("VOID") == 0)||($1->get_dtype().compare("VOID") == 0)){
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Void cannot be used in expression"<<endl;
                
            }

         }
		 ;
			
rel_expression	: simple_expression 
        {
            

            outputlog<<"rel_expression	: simple_expression "<<endl;
            $$ = new SymbolInfo("none","none");
            $$->set_parent("rel_expression");
            $$->set_child("simple_expression");
            $$->set_startline($1->get_startline());
            $$->set_endline($1->get_endline());
            $$->add_child($1);
            $$->set_dtype($1->get_dtype());
            $$->set_stype($1->get_stype());


        }
		| simple_expression RELOP simple_expression	
        {
            
            $$ = new SymbolInfo("none","none");
            $$->set_parent("rel_expression");
            $$->set_child("simple_expression RELOP simple_expression");
            $$->set_startline($1->get_startline());
            $$->set_endline($3->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);


            $$->set_dtype("INT");
            outputlog<<"rel_expression	: simple_expression RELOP simple_expression	  "<<endl;
            if(($3->get_dtype().compare("VOID") == 0)||($1->get_dtype().compare("VOID") == 0)){
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Void cannot be used in expression"<<endl;
                
            }

        }
		;
				
simple_expression : term 
          {
            
        outputlog<<"simple_expression : term "<<endl;
            $$ = new SymbolInfo("none","none");
            $$->set_parent("simple_expression");
            $$->set_child("term");
            $$->set_startline($1->get_startline());
            $$->set_endline($1->get_endline());
            $$->add_child($1);
            $$->set_dtype($1->get_dtype());
            $$->set_stype($1->get_stype());
        
         }
		  | simple_expression ADDOP term 
          {
            
            $$ = new SymbolInfo("none","none");
            $$->set_parent("simple_expression");
            $$->set_child("simple_expression ADDOP term");
            $$->set_startline($1->get_startline());
            $$->set_endline($3->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);


            outputlog<<"simple_expression : simple_expression ADDOP term  "<<endl;
            if($3->get_dtype().compare("VOID") == 0 || ($1->get_dtype().compare("VOID") == 0)){
                err_count = err_count + 1;
                outputerror<<"Line# "<<line_count<<": Void cannot be used in expression"<<endl;
                
            }
            else if(($3->get_dtype().compare("FLOAT") == 0)|| ($1->get_dtype().compare("FLOAT") == 0)){
                $$->set_dtype("FLOAT");
            }
            else  {
                $$->set_dtype("INT");
            }


        
        
         }
		  ;
					
term :	unary_expression
     {
        
        outputlog<<"term :	unary_expression "<<endl;
        $$ = new SymbolInfo("none","none");
        $$->set_parent("term");
        $$->set_child("unary_expression");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);
        $$->set_dtype($1->get_dtype());
        $$->set_stype($1->get_stype());
        
     }
     |  term MULOP unary_expression
     {
        $$ = new SymbolInfo("none","none");
        $$->set_parent("term");
        $$->set_child("term MULOP unary_expression");
        $$->set_startline($1->get_startline());
        $$->set_endline($3->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->add_child($3);
        $$->set_stype($1->get_stype());

        outputlog<<"term :	term MULOP unary_expression "<<endl;
        if($3->get_dtype().compare("VOID") == 0 || ($1->get_dtype().compare("VOID") == 0)){
            outputerror<<"Line# "<<line_count<<": Void cannot be used in expression "<<endl;
                
                err_count = err_count + 1;
        }
        

        if($2->get_name().compare("%") == 0){
            $$->set_dtype("INT");

           
            if($3->get_name().compare("0") == 0){
                outputerror<<"Line# "<<line_count<<": Warning: division by zero i=0f=1Const=0"<<endl;
                
                err_count = err_count + 1;
            }
            if(($3->get_dtype().compare("INT") != 0)|| ($1->get_dtype().compare("INT") != 0)){
                outputerror<<"Line# "<<line_count<<": Operands of modulus must be integers "<<endl;
                
                err_count = err_count + 1;
            }
        }
        else if(($3->get_dtype().compare("FLOAT") == 0) || ($1->get_dtype().compare("FLOAT") == 0)){
            $$->set_dtype("FLOAT");
        }
        else{
            $$->set_dtype("INT");
        }


        
        
     }
     ;

unary_expression : ADDOP unary_expression
         {
            
        outputlog<<"unary_expression : ADDOP unary_expression "<<endl;
            $$ = new SymbolInfo("none","none");
            $$->set_parent("unary_expression");
            $$->set_child("ADDOP unary_expression");
            $$->set_startline($1->get_startline());
            $$->set_endline($2->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->set_dtype($2->get_dtype());
            $$->set_stype($2->get_stype());
         }
		 | NOT unary_expression 
         {
            
        outputlog<<"unary_expression : NOT unary expression "<<endl;
            $$ = new SymbolInfo("none","none");
            $$->set_parent("unary_expression");
            $$->set_child("NOT unary expression");
            $$->set_startline($1->get_startline());
            $$->set_endline($2->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->set_dtype($2->get_dtype());
            $$->set_stype($2->get_stype());
        
         }
		 | factor 
         {
        outputlog<<"unary_expression : factor "<<endl;
        
            $$ = new SymbolInfo($1->get_name(),"none");
            $$->set_parent("unary_expression");
            $$->set_child("factor");
            $$->set_startline($1->get_startline());
            $$->set_endline($1->get_endline());
            $$->add_child($1);
            $$->set_dtype($1->get_dtype());
            $$->set_stype($1->get_stype());

         }
		 ;
	
factor	: variable 
    {
        outputlog<<"factor	: variable "<<endl;

        $$ = new SymbolInfo($1->get_name(),"none");
        $$->set_parent("factor");
        $$->set_child("variable");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);
        $$->set_dtype($1->get_dtype());
        $$->set_stype($1->get_stype());

    }
	| ID LPAREN argument_list RPAREN
    {
        $$ = new SymbolInfo($1->get_name(),"none");
        $$->set_parent("factor");
        $$->set_child("ID LPAREN argument_list RPAREN");
        $$->set_startline($1->get_startline());
        $$->set_endline($4->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->add_child($3);
        $$->add_child($4);

        
        outputlog<<"factor	: ID LPAREN argument_list RPAREN  "<<endl;
        
        SymbolInfo* p = table->look_up($1->get_name());
        if(p!= NULL){
            vector<SymbolInfo*> k = p->get_para();

             if(arg_list.size() < k.size()){
                outputerror<<"Line# "<<line_count<<": Too few arguments to function '"<<$1->get_name()<<"'"<<endl;
                
                err_count = err_count + 1;
                

            }
            else if(arg_list.size() > k.size()){
                outputerror<<"Line# "<<line_count<<": Too many arguments to function '"<<$1->get_name()<<"'"<<endl;
                
                err_count = err_count + 1;
                
            }
            else{
                

                for(int j=0;j<k.size();j++){
                    if(arg_list[j]->get_dtype().compare(k[j]->get_dtype()) != 0){
                        //if(k[j]->get_dtype().compare("FLOAT") && arg_list[j]->get_dtype().compare("INT")) continue;
                        outputerror<<"Line# "<<line_count<<": Type mismatch for argument "<<j+1<<" of '"<<$1->get_name()<<"'"<<endl;
                         
                         err_count = err_count + 1;
                        //break;
                    }
                }

            }
            
            
            $$->set_dtype(p->get_dtype());
        }
        else{
            
            outputerror<<"Line# "<<line_count<<": Undeclared function '"<<$1->get_name()<<"'"<<endl;
            
            err_count = err_count + 1;

        }
        for(auto l : arg_list){
            delete l;
        }
        
        arg_list.clear();

        


    }
	| LPAREN expression RPAREN
    {
        outputlog<<"factor	: LPAREN expression RPAREN   "<<endl;
        
        $$ = new SymbolInfo($1->get_name(),"none");
        $$->set_parent("factor");
        $$->set_child("LPAREN expression RPAREN");
        $$->set_startline($1->get_startline());
        $$->set_endline($3->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->add_child($3);
        $$->set_dtype($2->get_dtype());


    }
	| CONST_INT 
    {
        outputlog<<"factor	: CONST_INT   "<<endl;
        
        $$ = new SymbolInfo($1->get_name(),"none");
        $$->set_parent("factor");
        $$->set_child("CONST_INT");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);
        $$->set_stype("VARIABLE");
        $$->set_dtype("INT");


    }
	| CONST_FLOAT
    {
        outputlog<<"factor	: CONST_FLOAT   "<<endl;
        $$ = new SymbolInfo($1->get_name(),"none");
        $$->set_parent("factor");
        $$->set_child("CONST_FLOAT");
        $$->set_startline($1->get_startline());
        $$->set_endline($1->get_endline());
        $$->add_child($1);
        $$->set_stype("VARIABLE");
        $$->set_dtype("FLOAT");

    }
	| variable INCOP
    {
        outputlog<<"factor	: variable INCOP   "<<endl;
        $$ = new SymbolInfo($1->get_name(),"none");
        $$->set_parent("factor");
        $$->set_child("variable INCOP");
        $$->set_startline($1->get_startline());
        $$->set_endline($2->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->set_dtype($1->get_dtype());

    }
	| variable DECOP
    {
        outputlog<<"factor	: variable DECOP   "<<endl;
        $$ = new SymbolInfo($1->get_name(),"none");
        $$->set_parent("factor");
        $$->set_child("variable DECOP");
        $$->set_startline($1->get_startline());
        $$->set_endline($2->get_endline());
        $$->add_child($1);
        $$->add_child($2);
        $$->set_dtype($1->get_dtype());

    }
	;
	
argument_list : arguments
              {
                outputlog<<"argument_list : arguments  "<<endl;
                $$ = new SymbolInfo("none","none");
                $$->set_parent("argument_list");
                $$->set_child("arguments");
                $$->set_startline($1->get_startline());
                $$->set_endline($1->get_endline());
                $$->add_child($1);
                $$->set_dtype($1->get_dtype());


              }
			  |
              {
                outputlog<<"arguments : | ";
                $$ = new SymbolInfo("none","none");
                $$->set_parent("arguments");
                $$->set_child("|");
                $$->set_startline(line_count);
                $$->set_endline(line_count);
            

              }
			  ;
	
arguments : arguments COMMA logic_expression
          {
            outputlog<<"arguments : arguments COMMA logic_expression "<<endl;
            SymbolInfo* p = new SymbolInfo($3->get_name(),$3->get_stype(),$3->get_dtype());

            arg_list.push_back(p);
            $$ = new SymbolInfo("none","none");
            $$->set_parent("arguments");
            $$->set_child("arguments COMMA logic_expression");
            $$->set_startline($1->get_startline());
            $$->set_endline($3->get_endline());
            $$->add_child($1);
            $$->add_child($2);
            $$->add_child($3);
            $$->set_dtype($1->get_dtype());

          }
	      | logic_expression
          {
            outputlog<<"arguments : logic_expression"<<endl;
            SymbolInfo* p = new SymbolInfo($1->get_name(),$1->get_stype(),$1->get_dtype());
            

            arg_list.push_back(p);
            $$ = new SymbolInfo("none","none");
            $$->set_parent("arguments");
            $$->set_child("logic_expression");
            $$->set_startline($1->get_startline());
            $$->set_endline($1->get_endline());
            $$->add_child($1);
            $$->set_dtype($1->get_dtype());


          }
	      ;
 

%%
int main(int argc,char *argv[])
{
    FILE *fp;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	
	
    yyin=fp;
	yyparse();
	
    
   
    

    delete table;

	fclose(yyin);
	return 0;
}


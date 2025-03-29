
#include <bits/stdc++.h>
#include "SymbolInfo_ScopeTable_SymbolTable.cpp"
extern ofstream outassemble;

using namespace std;

extern SymbolTable *table;

int level = 0;
int idcount = 0;
int localvariablecount = 0;

string type;

vector<SymbolInfo *> listunit;

vector<SymbolInfo *> globalvarlist;
vector<SymbolInfo *> parameterlist;
int currentstack = 0;
string currentfunction;
int totallocalvariablelcount = 0;
string name_return_level;

void func_logic_expression(SymbolInfo *k);
void func_arguments(SymbolInfo *k);
void func_argument_list(SymbolInfo *k);
void func_variable(SymbolInfo *k);
void func_variable_2(SymbolInfo *k);
void func_expression(SymbolInfo *k);
void func_factor(SymbolInfo *k);
void func_unary_expression(SymbolInfo *k);
void func_term(SymbolInfo *k);
void func_simple_expression(SymbolInfo *k);
void func_rel_expression(SymbolInfo *k);
void func_logic_expression(SymbolInfo *k);
void func_expression(SymbolInfo *k);
void func_expression_statement(SymbolInfo *k);
void func_statement(SymbolInfo *k);
void func_compound_statement_1(SymbolInfo *k);

void func_var_declaration(SymbolInfo *k);
void func_statements(SymbolInfo *k);
void func_declaration_list(SymbolInfo *k);
void func_type_specifier(SymbolInfo *k);
void func_parameter_list(SymbolInfo *k);
void func_func_definition(SymbolInfo *k);
void func_func_declaration(SymbolInfo *k);
void func_local_statements(SymbolInfo *k);
void func_local_var_declaration(SymbolInfo *k);
void func_local_declarationlist_count(SymbolInfo *k);
void func_id(SymbolInfo *k);
void func_variable_3(SymbolInfo *k);
void func_local_statement(SymbolInfo* k);

string new_level()
{
    return "L" + to_string(level++);
}

void func_local_declarationlist_count(SymbolInfo *k)
{
    if (k->get_childlist().size() == 1)
    {
        localvariablecount += 2;
    }
    else if (k->get_childlist().size() == 4)
    {
        

        int h = stoi((string)k->get_childlist()[2]->get_name());
        localvariablecount += (h * 2);
    }
    else if (k->get_childlist().size() == 3)
    {
        localvariablecount += 2;
        func_local_declarationlist_count(k->get_childlist()[0]);
    }
    else
    {
        

        int h = stoi((string)k->get_childlist()[4]->get_name());
        localvariablecount += (h * 2);
        func_local_declarationlist_count(k->get_childlist()[0]);
    }
}

void func_local_var_declaration(SymbolInfo *k)
{
    func_local_declarationlist_count(k->get_childlist()[1]);
}

void func_local_statement(SymbolInfo* k){

        SymbolInfo *t = k;
        if (t->get_child() == "var_declaration")
        {
            
            func_local_var_declaration(t->get_childlist()[0]);
        }
        else if (t->get_child() == "compound_statement")
        {
            
            SymbolInfo* cd = t->get_childlist()[0];
            if(cd->get_childlist().size()==3){
                func_local_statements(cd->get_childlist()[1]);
            }


        }
        else if (t->get_child() == "FOR LPAREN expression_statement expression_statement expression RPAREN statement")
        {
            
            func_local_statement(t->get_childlist()[6]);
        }
        else if (t->get_child() == "IF LPAREN expression RPAREN statement")
        {
           
            func_local_statement(t->get_childlist()[4]);
        }
        else if (t->get_child() == "IF LPAREN expression RPAREN statement ELSE statement")
        {
            
            func_local_statement(t->get_childlist()[4]);
            func_local_statement(t->get_childlist()[6]);
        }
        else if (t->get_child() == "WHILE LPAREN expression RPAREN statement")
        {
            
            func_local_statement(t->get_childlist()[4]);
        }
        




}

void func_local_statements(SymbolInfo *k)
{
    if (k->get_childlist().size() == 1)
    {
        func_local_statement(k->get_childlist()[0]);
    }
    else
    {
         func_local_statements(k->get_childlist()[0]);

        func_local_statement(k->get_childlist()[1]);

       
    }
}

void func_declaration_list(SymbolInfo *k)
{
    

    if (k->get_childlist().size() == 1)
    { // ID
        if (table->get_current_scopeTable()->get_id() == 1)
        {
            string temp = k->get_childlist()[0]->get_name();
            SymbolInfo *t = table->look_up(temp);
            temp = temp + "_" + to_string(idcount++);
            t->set_newname(temp);
            t->set_stackoffset(-2);
            t->set_global(true);

            SymbolInfo *y = new SymbolInfo(temp, "VARIABLE", type);
            y->set_newname(temp);
            y->set_stackoffset(-2);
            globalvarlist.push_back(y);
        }
        else
        {
            string temp = k->get_childlist()[0]->get_name();
            table->insert(temp, "VARIABLE", type);
            SymbolInfo *t = table->look_up(temp);
            temp = temp + "_" + to_string(idcount++);
            t->set_newname(temp);
            t->set_stackoffset( currentstack - 2);
            currentstack -= 2;
            
        }
    }
    else if (k->get_childlist().size() == 4)
    { // ID LTHIRD CONST_INT RTHIRD
        if (table->get_current_scopeTable()->get_id() == 1)
        {
            string temp = k->get_childlist()[0]->get_child();
            SymbolInfo *t = table->look_up(temp);
            temp = temp + "_" + to_string(idcount++);
            t->set_newname(temp);
            t->set_global(true);
            

            t->set_arraysize(stoi((string)k->get_childlist()[2]->get_name()));
            

            t->set_stackoffset(-2 * t->get_arraysize() + currentstack);
            currentstack = t->get_stackoffset();
            SymbolInfo *y = new SymbolInfo(temp, "ARRAY", type);
            y->set_newname(temp);
            y->set_arraysize(t->get_arraysize());
            y->set_stackoffset(t->get_stackoffset());

            globalvarlist.push_back(y);
        }
        else
        {
            string temp = k->get_childlist()[0]->get_child();
            table->insert(temp, "ARRAY", type);
            SymbolInfo *t = table->look_up(temp);
            temp = temp + "_" + to_string(idcount++);
            t->set_newname(temp);
           

            t->set_arraysize(stoi((string)k->get_childlist()[2]->get_name()));
            t->set_stackoffset(-2 * t->get_arraysize() + currentstack);
            currentstack = t->get_stackoffset();

            
        }
    }
    else if (k->get_childlist().size() == 3)
    {

        func_declaration_list(k->get_childlist()[0]);
        if (table->get_current_scopeTable()->get_id() == 1)
        {
            string temp = k->get_childlist()[2]->get_name();
            SymbolInfo *t = table->look_up(temp);
            temp = temp + "_" + to_string(idcount++);
            t->set_newname(temp);
            t->set_stackoffset(-2);
            t->set_global(true);
            SymbolInfo *y = new SymbolInfo(temp, "VARIABLE", type);
            y->set_newname(temp);
            y->set_stackoffset(-2);
            globalvarlist.push_back(y);
        }
        else
        {
            string temp = k->get_childlist()[2]->get_name();
            table->insert(temp, "VARIABLE", type);
            SymbolInfo *t = table->look_up(temp);
            temp = temp + "_" + to_string(idcount++);
            t->set_newname(temp);
            t->set_stackoffset(currentstack - 2);
            currentstack -= 2;
            
        }
        
    }
    else
    {
        func_declaration_list(k->get_childlist()[0]);

        if (table->get_current_scopeTable()->get_id() == 1)
        {
            string temp = k->get_childlist()[2]->get_child();
            SymbolInfo *t = table->look_up(temp);
            temp = temp + "_" + to_string(idcount++);
            t->set_newname(temp);
            t->set_global(true);
            

            t->set_arraysize(stoi((string)k->get_childlist()[4]->get_name()));
            t->set_stackoffset(-2 * t->get_arraysize() + currentstack);
            currentstack = t->get_stackoffset();
            SymbolInfo *y = new SymbolInfo(temp, "ARRAY", type);
            y->set_newname(temp);
            y->set_arraysize(t->get_arraysize());
            y->set_stackoffset(t->get_stackoffset());

            globalvarlist.push_back(y);
        }
        else
        {
            string temp = k->get_childlist()[2]->get_child();
            table->insert(temp, "ARRAY", type);
            SymbolInfo *t = table->look_up(temp);
            temp = temp + "_" + to_string(idcount++);
            t->set_newname(temp);
            

            t->set_arraysize(stoi((string)k->get_childlist()[4]->get_name()));
            t->set_stackoffset(-2 * t->get_arraysize() + currentstack);
            currentstack = t->get_stackoffset();

            
        }
        
    }
}

void func_var_declaration(SymbolInfo *k)
{
    SymbolInfo *temp = k->get_childlist()[0];
    type = temp->get_childlist()[0]->get_parent();
    func_declaration_list(k->get_childlist()[1]);
}

void func_start(SymbolInfo *node)
{

    outassemble << ".MODEL SMALL" << endl;
    outassemble << ".STACK 1000H\n";
    outassemble << ".DATA\n";
    outassemble << "CR EQU 0DH\n";
    outassemble << "LF EQU 0AH\n";
    outassemble << "number DB \"00000$\"\n";

    level = 0;

    SymbolInfo *k = node->get_childlist()[0];

    while (k->get_parent().compare("program") == 0)
    {
        if (k->get_childlist().size() == 1)
        {
            listunit.push_back(k->get_childlist()[0]);
        }
        else
        {
            listunit.push_back(k->get_childlist()[1]);
        }

        k = k->get_childlist()[0];
    }

    for (int i = 0; i < listunit.size(); i++)
    {
        if (listunit[i]->get_childlist()[0]->get_parent() == "var_declaration")
        {
            func_var_declaration(listunit[i]->get_childlist()[0]);
        }
    }

    for (int i = 0; i < globalvarlist.size(); i++)
    {
        SymbolInfo *y = globalvarlist[i];
        if (y->get_stype() == "ARRAY")
        {
            outassemble << y->get_newname() << " DW " << y->get_arraysize() << " DUP (0000H)" << endl;
        }
        else
        {
            outassemble << y->get_newname() << " DW 0" << endl;
        }
    }
    
    outassemble << ".CODE" << endl;

    ////////////////write code for function

    ////traverse unitlist for function

    for (int i = listunit.size() - 1; i >= 0; i--)
    {
        if (listunit[i]->get_childlist()[0]->get_parent() == "func_definition")
        {
            localvariablecount = 0;
            currentstack = 0;
            SymbolInfo *fd = listunit[i]->get_childlist()[0];
            SymbolInfo *com;
            if (fd->get_childlist().size() == 5)
                com = fd->get_childlist()[4];
            else
            {
                com = fd->get_childlist()[5];
            }
            SymbolInfo *stcom = NULL;
            if (com->get_childlist().size() == 3)
            {
                stcom = com->get_childlist()[1];
                func_local_statements(stcom);
            }

            if (fd->get_childlist()[1]->get_name() == "main")
            {

                 SymbolInfo *fn = table->look_up("main");
                 fn->set_newname("main");
                outassemble << "main PROC" << endl;
                outassemble << "\t MOV AX , @DATA" << endl;
                outassemble << "\t MOV DS , AX" << endl;
                outassemble << "\t PUSH BP" << endl;
                outassemble << "\t MOV BP , SP" << endl;
                if (localvariablecount != 0)
                {
                    outassemble << "\t SUB SP , " << localvariablecount << endl;
                }
                name_return_level = new_level();
                func_func_definition(fd);
                outassemble << name_return_level << ":" << endl;
                if (localvariablecount != 0)
                {
                    outassemble << "\t ADD SP , " << localvariablecount << endl;
                }
                outassemble << "\t POP BP" << endl;
                outassemble << "\t MOV AH , 4CH" << endl;
                outassemble << "\t INT 21H" << endl;
               
                outassemble << "main ENDP" << endl;
                outassemble << "println proc" << endl;
                outassemble << "\t push ax" << endl;
                outassemble << "\t push bx" << endl;
                outassemble << "\t push cx" << endl;
                outassemble << "\t push dx" << endl;
                outassemble << "\t push si" << endl;
                outassemble << "\t lea si , number" << endl;
                outassemble << "\t mov bx , 10" << endl;
                outassemble << "\t mov si , 4" << endl;
                outassemble << "\t cmp ax , 0" << endl;
                outassemble << "\t jnge negate" << endl;
                outassemble << "print:" << endl;
                outassemble << "\t xor dx , dx" << endl;
                outassemble << "\t div bx" << endl;
                outassemble << "\t mov [si] , dl" << endl;
                outassemble << "\t add [si] , '0'" << endl;
                outassemble << "\t dec si" << endl;
                outassemble << "\t cmp ax , 0" << endl;
                outassemble << "\t jne print" << endl;
                outassemble << "\t inc si" << endl;
                outassemble << "\t lea dx , si" << endl;
                outassemble << "\t mov ah , 9" << endl;
                outassemble << "\t int 21h" << endl;
                outassemble << "\t mov ah , 2" << endl;
                outassemble << "\t mov dl , 0DH" << endl;
                outassemble << "\t int 21h" << endl;
                outassemble << "\t mov ah , 2" << endl;
                outassemble << "\t mov dl , 0AH" << endl;
                outassemble << "\t int 21h" << endl;
                outassemble << "\t pop si" << endl;
                outassemble << "\t pop dx" << endl;
                outassemble << "\t pop cx" << endl;
                outassemble << "\t pop bx" << endl;
                outassemble << "\t pop ax" << endl;
                outassemble << "\t ret" << endl;
                outassemble << "negate:" << endl;
                outassemble << "\t push ax" << endl;
                outassemble << "\t mov ah , 2" << endl;
                outassemble << "\t mov dl , \'-\'" << endl;
                outassemble << "\t int 21h" << endl;
                outassemble << "\t pop ax" << endl;
                outassemble << "\t neg ax" << endl;
                outassemble << "\t jmp print" << endl;
                outassemble << "println endp" << endl;
               
                outassemble << "END MAIN" << endl;
            }
            else
            {

                string temp = fd->get_childlist()[1]->get_name();
                SymbolInfo *fn = table->look_up(temp);
                temp = temp + "_" + to_string(idcount++);

                fn->set_newname(temp);

                outassemble << temp << " PROC" << endl;
                outassemble << "\t PUSH BP" << endl;
                outassemble << "\t MOV BP , SP" << endl;
                if (localvariablecount != 0)
                {
                    outassemble << "\t SUB SP , " << localvariablecount << endl;
                }
                name_return_level = new_level();
                func_func_definition(fd);
                outassemble << name_return_level << ":" << endl;
                if (localvariablecount != 0)
                {
                    outassemble << "\t ADD SP , " << localvariablecount << endl;
                }
                outassemble << "\t POP BP" << endl;
                SymbolInfo *ooo = table->look_up(fd->get_childlist()[1]->get_name());
                int ioi = ooo->get_para().size();
                outassemble << "\t RET " << ioi * 2 << endl;
                outassemble << temp << " ENDP" << endl;
            }
        }
    }
}

void func_func_definition(SymbolInfo *k)
{

    
    string temp = k->get_childlist()[1]->get_name();
    SymbolInfo *t = table->look_up(temp);
    parameterlist = t->get_para();

    if (k->get_childlist().size() == 5)
    {
        func_compound_statement_1(k->get_childlist()[4]);
    }
    else
    {
        func_compound_statement_1(k->get_childlist()[5]);
    }

   
}
void func_compound_statement_1(SymbolInfo *k)
{
    outassemble << "\t ; Compound statement starts at line number " << k->get_startline() << endl;
    if (k->get_childlist().size() == 3)
    {
        table->enter_scope();
        if (parameterlist.size() != 0)
        {
            for (int i = 0; i < parameterlist.size(); i++)
            {
                table->insert(parameterlist[i]->get_name(), "VARIABLE", "INT");
                SymbolInfo *hp = table->look_up(parameterlist[i]->get_name());
                hp->set_inparalist(true);
                hp->set_stackoffset(i * 2 + 4);
            }
            parameterlist.clear();
        }

        func_statements(k->get_childlist()[1]);
        table->exit_scope();
    }
    outassemble<<"\t ; Compound statement end at line number "<<k->get_endline()<<endl;
}

void func_statements(SymbolInfo *k)
{
    if (k->get_childlist().size() == 1)
    {
        func_statement(k->get_childlist()[0]);
    }
    else
    {

        func_statements(k->get_childlist()[0]);
        func_statement(k->get_childlist()[1]);
    }
}

void func_statement(SymbolInfo *k)
{

    if (k->get_child() == "var_declaration")
    {
        func_var_declaration(k->get_childlist()[0]);
    }
    else if (k->get_child() == "expression_statement")
    {
        func_expression_statement(k->get_childlist()[0]);
    }
    else if (k->get_child() == "PRINTLN LPAREN ID RPAREN SEMICOLON")
    {
        SymbolInfo *t = k->get_childlist()[2];
        func_id(t);
        outassemble << "\t POP AX" << endl;
        outassemble << "\t CALL println      ; PRINTLN FUNCTION call at line number "<<k->get_startline() << endl;
    }
    else if (k->get_child() == "compound_statement")
    {
        parameterlist.clear();
        func_compound_statement_1(k->get_childlist()[0]);

    }
    else if(k->get_child() == "IF LPAREN expression RPAREN statement"){
        outassemble<<"\t ; if statement start at line number "<<k->get_startline()<<endl;
        string endlevel = new_level();

        func_expression(k->get_childlist()[2]);
        outassemble<<"\t POP AX"<<endl;
        outassemble<<"\t CMP AX , 0"<<endl;
        outassemble<<"\t JE "<<endlevel<<endl;
        func_statement(k->get_childlist()[4]);
        outassemble<<endlevel<<":"<<endl;
        outassemble<<"\t ; if statement end at line number "<< k->get_endline()<<endl;


    }
    else if(k->get_child() == "IF LPAREN expression RPAREN statement ELSE statement"){
        outassemble<<"\t ; if and else statement start at line number "<<k->get_startline()<<endl;
        string elselevel = new_level();
        string endlevel = new_level();

        func_expression(k->get_childlist()[2]);
        outassemble<<"\t POP AX"<<endl;
        outassemble<<"\t CMP AX , 0"<<endl;
        outassemble<<"\t JE "<<elselevel<<endl;
        func_statement(k->get_childlist()[4]);
        outassemble<<"\t JMP "<<endlevel<<endl;
        outassemble<<elselevel<<":"<<endl;
        func_statement(k->get_childlist()[6]);
        outassemble<<endlevel<<":"<<endl;
        outassemble<<"\t ; if and else statement end at line number "<< k->get_endline()<<endl;

    }
    else if(k->get_child() == "FOR LPAREN expression_statement expression_statement expression RPAREN statement"){
        outassemble<<"\t ; For loop start at line number "<<k->get_startline()<<endl;
        string beginlevel = new_level();
        string endlevel = new_level();
        func_expression_statement(k->get_childlist()[2]);
        outassemble<<beginlevel<<":"<<endl;
        func_expression_statement(k->get_childlist()[3]);
        
        outassemble<<"\t CMP AX , 0"<<endl;
        outassemble<<"\t JE "<<endlevel<<endl;
        func_statement(k->get_childlist()[6]);
        func_expression(k->get_childlist()[4]);
        outassemble<<"\t POP AX"<<endl;
        outassemble<<"\t JMP "<<beginlevel<<endl;
        outassemble<<endlevel<<":"<<endl;


        outassemble<<"\t ; For loop end at line number "<<k->get_endline()<<endl;

    }
    else if(k->get_child() == "WHILE LPAREN expression RPAREN statement"){
        outassemble<<"\t ; While loop start at line number "<<k->get_startline()<<endl;
        string beginlevel = new_level();
        string endlevel = new_level();
        outassemble<<beginlevel<<":"<<endl;
        func_expression(k->get_childlist()[2]);
        outassemble<<"\t POP AX"<<endl;
        outassemble<<"\t CMP AX , 0"<<endl;
        outassemble<<"\t JE "<<endlevel<<endl;
        func_statement(k->get_childlist()[4]);
        outassemble<<"\t JMP "<<beginlevel<<endl;
        outassemble<<endlevel<<":"<<endl;

        outassemble<<"\t ; While loop end at line number "<<k->get_endline()<<endl;


    }
    else{
        outassemble<<"\t ; Return statement start at line number "<<k->get_startline()<<endl;

        func_expression(k->get_childlist()[1]);
        outassemble<<"\t POP AX"<<endl;
        outassemble<<"\t JMP "<<name_return_level<<endl;


        outassemble<<"\t ; Return statement end at line number "<<k->get_endline()<<endl;

    }


}

void func_arguments(SymbolInfo *k)
{
    if(k->get_childlist().size()==1){
        func_logic_expression(k->get_childlist()[0]);
    }
    else{
        
        func_logic_expression(k->get_childlist()[2]);
        func_arguments(k->get_childlist()[0]);
    }

}
void func_argument_list(SymbolInfo *k)
{
    if(k->get_childlist().size()==1){
        func_arguments(k->get_childlist()[0]);
    }

}
void func_variable(SymbolInfo *k)
{

    if (k->get_childlist().size() == 1)
    {
        SymbolInfo *id = k->get_childlist()[0];
        id = table->look_up(id->get_name());
        if (id->get_global())
        {
            outassemble << "\t PUSH " << id->get_newname() << endl;
        }
        else
        {
            outassemble << "\t PUSH BP[" << id->get_stackoffset() << "]" << endl;
        }
    }
    else
    {
        SymbolInfo *id = k->get_childlist()[0];
        id = table->look_up(id->get_name());
        func_expression(k->get_childlist()[2]);

        if (id->get_global())
        {
            outassemble << "\t POP SI" << endl;
            outassemble << "\t SHL SI , 1" << endl;
            outassemble << "\t PUSH " << id->get_newname() << "[SI]" << endl;
        }
        else
        {
            outassemble << "\t POP SI" << endl;
            outassemble << "\t SHL SI , 1" << endl;
            string up = to_string(id->get_stackoffset());
            outassemble << "\t ADD SI , " << up << endl;
            outassemble << "\t PUSH BP[SI]" << endl;
        }
    }
}

void func_variable_2(SymbolInfo *k)
{

    if (k->get_childlist().size() == 1)
    {
        outassemble << "\t POP AX" << endl;

        SymbolInfo *id = k->get_childlist()[0];
        id = table->look_up(id->get_name());
        if (id->get_global())
        {
            outassemble << "\t MOV " << id->get_newname() << " , AX" << endl;
        }
        else
        {
            outassemble << "\t MOV BP[" << id->get_stackoffset() << "] , AX" << endl;
        }
        outassemble << "\t PUSH AX" << endl;
        outassemble << "\t POP AX" << endl;
    }
    else
    {
        outassemble << "\t POP BX" << endl;
        SymbolInfo *id = k->get_childlist()[0];
        id = table->look_up(id->get_name());
        func_expression(k->get_childlist()[2]);

        if (id->get_global())
        {
            outassemble << "\t POP SI" << endl;
            outassemble << "\t SHL SI , 1" << endl;
            outassemble << "\t MOV " << id->get_newname() << "[SI] , BX" << endl;
        }
        else
        {
            outassemble << "\t POP SI" << endl;
            outassemble << "\t SHL SI , 1" << endl;
            string up = to_string(id->get_stackoffset());
            outassemble << "\t ADD SI , " << up << endl;
            outassemble << "\t MOV BP[SI] , BX" << endl;
        }

        outassemble << "\t PUSH BX" << endl;
        outassemble << "\t POP AX" << endl;
    }
}

void func_variable_3(SymbolInfo *k)
{

    if (k->get_childlist().size() == 1)
    {
        SymbolInfo *id = k->get_childlist()[0];
        id = table->look_up(id->get_name());
        if (id->get_global())
        {
            outassemble << "\t PUSH " << id->get_newname() << endl;
            outassemble << "\t ADD WORD PTR " << id->get_newname() << " , 1" << endl;
        }
        else
        {
            outassemble << "\t PUSH BP[" << id->get_stackoffset() << "]" << endl;
            outassemble << "\t ADD WORD PTR BP[" << id->get_stackoffset() << "] , 1" << endl;
        }
    }
    else
    {
        SymbolInfo *id = k->get_childlist()[0];
        id = table->look_up(id->get_name());
        func_expression(k->get_childlist()[2]);

        if (id->get_global())
        {
            outassemble << "\t POP SI" << endl;
            outassemble << "\t SHL SI , 1" << endl;
            outassemble << "\t PUSH " << id->get_newname() << "[SI]" << endl;
            outassemble << "\t ADD WORD PTR " << id->get_newname() << "[SI] , 1" << endl;
        }
        else
        {
            outassemble << "\t POP SI" << endl;
            outassemble << "\t SHL SI , 1" << endl;
            string up = to_string(id->get_stackoffset());
            outassemble << "\t ADD SI , " << up << endl;
            outassemble << "\t PUSH BP[SI]" << endl;
            outassemble << "\t ADD WORD PTR BP[SI] , 1" << endl;
        }
    }
}

void func_variable_4(SymbolInfo *k)
{

    if (k->get_childlist().size() == 1)
    {
        SymbolInfo *id = k->get_childlist()[0];
        id = table->look_up(id->get_name());
        if (id->get_global())
        {
            outassemble << "\t PUSH " << id->get_newname() << endl;
            outassemble << "\t SUB WORD PTR " << id->get_newname() << " , 1" << endl;
        }
        else
        {
            outassemble << "\t PUSH BP[" << id->get_stackoffset() << "]" << endl;
            outassemble << "\t SUB WORD PTR BP[" << id->get_stackoffset() << "] , 1" << endl;
        }
    }
    else
    {
        SymbolInfo *id = k->get_childlist()[0];
        id = table->look_up(id->get_name());
        func_expression(k->get_childlist()[2]);

        if (id->get_global())
        {
            outassemble << "\t POP SI" << endl;
            outassemble << "\t SHL SI , 1" << endl;
            outassemble << "\t PUSH " << id->get_newname() << "[SI]" << endl;
            outassemble << "\t SUB WORD PTR " << id->get_newname() << "[SI] , 1" << endl;
        }
        else
        {
            outassemble << "\t POP SI" << endl;
            outassemble << "\t SHL SI , 1" << endl;
            string up = to_string(id->get_stackoffset());
            outassemble << "\t ADD SI , " << up << endl;
            outassemble << "\t PUSH BP[SI]" << endl;
            outassemble << "\t SUB WORD PTR BP[SI] , 1" << endl;
        }
    }
}

void func_id(SymbolInfo *k)
{

    SymbolInfo *id = table->look_up(k->get_name());
    if (id->get_global())
    {
        outassemble << "\t PUSH " << id->get_newname() << endl;
    }
    else
    {
        outassemble << "\t PUSH BP[" << id->get_stackoffset() << "]" << endl;
    }
}

void func_factor(SymbolInfo *k)
{
    if (k->get_child() == "variable")
    {
        func_variable(k->get_childlist()[0]);
    }
    else if (k->get_child() == "CONST_INT")
    {
        outassemble << "\t MOV AX , " << k->get_childlist()[0]->get_name() << endl;
        outassemble << "\t PUSH AX" << endl;
    }
    else if (k->get_child() == "variable INCOP")
    {
        func_variable_3(k->get_childlist()[0]);
    }
    else if (k->get_child() == "variable DECOP")
    {
        func_variable_4(k->get_childlist()[0]);
    }
    else if(k->get_child() == "LPAREN expression RPAREN"){
        func_expression(k->get_childlist()[1]);
    }
    else{
        outassemble<<"\t ; Function call start at line number "<<k->get_startline()<<endl;
        func_argument_list(k->get_childlist()[2]);
        string fn = k->get_childlist()[0]->get_name();
        SymbolInfo* t = table->look_up(fn);
        outassemble<<"\t CALL "<<t->get_newname()<<endl;
        outassemble<<"\t PUSH AX "<<endl;
        



    }

}
void func_unary_expression(SymbolInfo *k)
{
    if (k->get_childlist().size() == 1)
    {
        func_factor(k->get_childlist()[0]);
    }
    else if (k->get_child() == "NOT unary_expression")
    {
        string ltrue = new_level();
        string lfalse = new_level();
        func_unary_expression(k->get_childlist()[1]);
        outassemble << "\t POP AX" << endl;
        outassemble << "\t CMP AX , 0" << endl;
        outassemble << "\t JE " << ltrue << endl;
        outassemble << "\t MOV AX , 0" << endl;
        outassemble << "\t JMP " << lfalse << endl;
        outassemble << ltrue << ":" << endl;
        outassemble << "\t MOV AX , 1" << endl;
        outassemble << lfalse << ":" << endl;
        outassemble << "\t PUSH AX" << endl;
    }
    else
    {
        func_unary_expression(k->get_childlist()[1]);
        if (k->get_childlist()[0]->get_name() == "-")
        {
            outassemble << "\t POP AX" << endl;
            outassemble << "\t NEG AX" << endl;
            outassemble << "\t PUSH AX" << endl;
        }
    }
}
void func_term(SymbolInfo *k)
{
    if (k->get_childlist().size() == 1)
    {
        func_unary_expression(k->get_childlist()[0]);
    }
    else
    {
        func_term(k->get_childlist()[0]);
        func_unary_expression(k->get_childlist()[2]);

        // do some work
        if (k->get_childlist()[1]->get_name() == "*")
        {
            outassemble << "\t POP CX" << endl;
            outassemble << "\t POP AX" << endl;
            outassemble << "\t IMUL CX" << endl;
            outassemble << "\t PUSH AX" << endl;
        }
        else if (k->get_childlist()[1]->get_name() == "/")
        {
            outassemble << "\t POP CX" << endl;
            outassemble << "\t POP AX" << endl;
            outassemble << "\t CWD" << endl;
            outassemble << "\t IDIV CX" << endl;
            outassemble << "\t PUSH AX" << endl;
        }
        else
        {

            outassemble << "\t POP CX" << endl;
            outassemble << "\t POP AX" << endl;
            outassemble << "\t CWD" << endl;
            outassemble << "\t IDIV CX" << endl;
            outassemble << "\t PUSH DX" << endl;
        }
    }
}
void func_simple_expression(SymbolInfo *k)
{
    if (k->get_childlist().size() == 1)
    {
        func_term(k->get_childlist()[0]);
    }
    else
    {
        func_simple_expression(k->get_childlist()[0]);
        func_term(k->get_childlist()[2]);

        // do some work
        if (k->get_childlist()[1]->get_name() == "+")
        {
            outassemble << "\t POP CX" << endl;
            outassemble << "\t POP AX" << endl;
            outassemble << "\t ADD AX , CX" << endl;
            outassemble << "\t PUSH AX" << endl;
        }
        else
        {
            outassemble << "\t POP CX" << endl;
            outassemble << "\t POP AX" << endl;
            outassemble << "\t SUB AX , CX" << endl;
            outassemble << "\t PUSH AX" << endl;
        }
    }
}
void func_rel_expression(SymbolInfo *k)
{
    if (k->get_childlist().size() == 1)
    {
        func_simple_expression(k->get_childlist()[0]);
    }
    else
    {
        string ltrue = new_level();
        string lfalse = new_level();

        func_simple_expression(k->get_childlist()[0]);
        func_simple_expression(k->get_childlist()[2]);

        // do some work
        outassemble << "\t POP CX" << endl;
        outassemble << "\t POP AX" << endl;
        outassemble << "\t CMP AX , CX" << endl;
        string op = k->get_childlist()[1]->get_name();
        if (op == "<")
        {
            outassemble << "\t JL " << ltrue << endl;
        }
        else if (op == "<=")
        {
            outassemble << "\t JLE " << ltrue << endl;
        }
        else if (op == ">")
        {
            outassemble << "\t JG " << ltrue << endl;
        }
        else if (op == ">=")
        {
            outassemble << "\t JGE " << ltrue << endl;
        }
        else if (op == "==")
        {
            outassemble << "\t JE " << ltrue << endl;
        }
        else
        {
            outassemble << "\t JNE " << ltrue << endl;
        }
        outassemble << "\t MOV AX , 0" << endl;
        outassemble << "\t JMP " << lfalse << endl;
        outassemble << ltrue << ":" << endl;
        outassemble << "\t MOV AX , 1" << endl;
        outassemble << lfalse << ":" << endl;
        outassemble << "\t PUSH AX" << endl;
    }
}
void func_logic_expression(SymbolInfo *k)
{
    if (k->get_childlist().size() == 1)
    {
        func_rel_expression(k->get_childlist()[0]);
    }
    else
    {

        string op = k->get_childlist()[1]->get_name();
        string ltrue = new_level();
        string lfalse = new_level();

        if (op == "||")
        {
            func_rel_expression(k->get_childlist()[0]);
            outassemble << "\t POP AX" << endl;
            outassemble << "\t CMP AX , 0" << endl;
            outassemble << "\t JNE " << ltrue << endl;

            func_rel_expression(k->get_childlist()[2]);
            outassemble << "\t POP AX" << endl;
            outassemble << "\t CMP AX , 0" << endl;
            outassemble << "\t JNE " << ltrue << endl;
            outassemble << "\t MOV AX , 0" << endl;
            outassemble << "\t JMP " << lfalse << endl;
            outassemble << ltrue << ":" << endl;
            outassemble << "\t MOV AX , 1" << endl;
            outassemble << lfalse << ":" << endl;
            outassemble << "\t PUSH AX" << endl;
        }
        else
        {

            func_rel_expression(k->get_childlist()[0]);
            outassemble << "\t POP AX" << endl;
            outassemble << "\t CMP AX , 0" << endl;
            outassemble << "\t JE " << ltrue << endl;

            func_rel_expression(k->get_childlist()[2]);
            outassemble << "\t POP AX" << endl;
            outassemble << "\t CMP AX , 0" << endl;
            outassemble << "\t JE " << ltrue << endl;
            outassemble << "\t MOV AX , 1" << endl;
            outassemble << "\t JMP " << lfalse << endl;
            outassemble << ltrue << ":" << endl;
            outassemble << "\t MOV AX , 0" << endl;
            outassemble << lfalse << ":" << endl;
            outassemble << "\t PUSH AX" << endl;
        }
    }
}
void func_expression(SymbolInfo *k)
{
    
    if (k->get_childlist().size() == 1)
    {
        func_logic_expression(k->get_childlist()[0]);
    }
    else
    {
        func_logic_expression(k->get_childlist()[2]);

        //////////here is some work
        func_variable_2(k->get_childlist()[0]);
        outassemble<<"\t PUSH AX"<<endl;
    }
    
}
void func_expression_statement(SymbolInfo *k)
{
    outassemble<<"\t ; Expression statement start at line number "<<k->get_startline()<<endl;
    if (k->get_childlist().size() == 2)
    {
        func_expression(k->get_childlist()[0]);
       outassemble<<"\t POP AX"<<endl;
    }
    outassemble<<"\t ; Expression statement end at line number "<<k->get_endline()<<endl;
}

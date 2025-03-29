%option noyywrap

%x STATE_CHAR
%x STATE_STRING
%x STATE_STRING_M
%x STATE_1_COMMENT
%x STATE_2_COMMENT


%{

#include<bits/stdc++.h>

using namespace std;

int line_count=1;
int err_count=0;
int line_str = 0;
int line1 = 0;
int line2=0;

string input_chars = "";
string chars = "";
string input_str = "";
string str = "";
string s = "";
string c_str="";




ofstream outputlog("1905038_log.txt");
ofstream outputtoken("1905038_token.txt");


class SymbolInfo
{
    string name, type;
    SymbolInfo *next;

public:
    SymbolInfo(string s, string r)
    {
        name = s;
        type = r;
        next = NULL;
    }

    void set_name(string s)
    {
        name = s;
    }
    void set_type(string s)
    {
        type = s;
    }
    void set_next(SymbolInfo *x)
    {
        next = x;
    }
    string get_name()
    {
        return name;
    }
    string get_type()
    {
        return type;
    }
    SymbolInfo *get_next()
    {
        return next;
    }
};




class ScopeTable
{
    int bucketNumber, id;
    SymbolInfo **array;
    ScopeTable *parent;

public:
    ScopeTable(int s, int i)
    {
        bucketNumber = s;
        id = i;
        array = new SymbolInfo *[bucketNumber];
        for(int j=0;j<bucketNumber;j++){
            array[j]=NULL;
        }

        parent = NULL;
        
    }
    ~ScopeTable()
    {
        

        for (int i = 0; i < bucketNumber; i++)
        {
            SymbolInfo *p = array[i];
            while (p != NULL)
            {
                SymbolInfo *q = p->get_next();
                delete p;
                p = q;
            }
            array[i]=NULL;
        }
        
        delete[] array;
    }

    int sdbm_hash(string str, int mod)
    {
        unsigned long long hash = 0;
        int i = 0;
        int len = str.length();

        for (i = 0; i < len; i++)
        {
            hash = (((int)str[i])  + (hash << 6)  + (hash << 16)  - hash) ;
        }

        return (int)(hash % mod);
    }

    void set_parent(ScopeTable *s)
    {
        parent = s;
    }
    ScopeTable *get_parent()
    {
        return parent;
    }
    int get_id(){
        return id;
    }
    bool insert(string s, string r)
    {
        int k = sdbm_hash(s, bucketNumber);
        SymbolInfo *q = array[k];
        while (q != NULL)
        {
            SymbolInfo *w = q->get_next();
            if (q->get_name().compare(s) == 0)
            {
                outputlog<<"	"<<s<<" already exisits in the current ScopeTable"<<endl;
                return false;
            }
            q = w;
        }

        SymbolInfo *p = new SymbolInfo(s, r);
        int i=1;
        if(array[k]==NULL){
            array[k]=p;
        }
        else{

            SymbolInfo* q = array[k];
            
            while (q->get_next()!=NULL)
            {
                i++;
                q=q->get_next();
            }
            i++;
            q->set_next(p);
            
        }

        
        return true;
    }

    SymbolInfo *look_up(string s)
    {
        int i=1;
        int k = sdbm_hash(s, bucketNumber) % bucketNumber;
        SymbolInfo *q = array[k];
        while (q != NULL)
        {
            SymbolInfo *w = q->get_next();
            if (q->get_name().compare(s) == 0)
            {
                
                return q;
            }
            q = w;
            i++;
        }
        return NULL;
    }

    bool Delete(string s)
    {
        int i=1;
        int k = sdbm_hash(s, bucketNumber) % bucketNumber;
        SymbolInfo *q = array[k];
        SymbolInfo *prev = NULL;
        while (q != NULL)
        {

            SymbolInfo *w = q->get_next();
            if (q->get_name().compare(s) == 0)
            {
                
                if (prev == NULL)
                {
                    array[k] = q->get_next();
                    delete q;
                }
                else
                {
                    prev->set_next(q->get_next());
                    delete q;
                }
                return true;
            }
            prev = q;
            q = w;
            i++;
        }
        
        return false;
    }

    void print()
    {
        outputlog<<"	ScopeTable# "<<id<<endl;
        for(int i=0;i<bucketNumber;i++){
            
            SymbolInfo * p = array[i];
            if(p==NULL) continue;
            outputlog<<"	"<<i+1<<"--> ";
            while (p!= NULL)
            {
                outputlog<<"<"<<p->get_name()<<","<<p->get_type()<<"> ";
                p=p->get_next();
            }
            outputlog<<endl;
        }
    }
};

class SymbolTable
{
    int count, bucket_number;
    ScopeTable *current;

public:
    SymbolTable(int n)
    {
        count = 1;
        bucket_number = n;
        current = new ScopeTable(n, 1);
        current->set_parent(NULL);
    }

    ~SymbolTable()
    {
        while (current != NULL)
        {
            ScopeTable *p = current->get_parent();
            delete current;
            current = p;
        }
    }

    void enter_scope()
    {
        count++;
        ScopeTable *p = new ScopeTable(bucket_number, count);
        p->set_parent(current);
        current = p;
    }

    void exit_scope()
    {
        if(current->get_id()==1){
            //cout<<"	ScopeTable# 1 cannot be removed"<<endl;
            return;
        }
        ScopeTable *p = current->get_parent();
        delete current;
        current = p;
    }

    bool insert(string s, string t)
    {
        return current->insert(s, t);
    }
    bool remove(string s)
    {
        
        return current->Delete(s);
    }

    SymbolInfo *look_up(string s)
    {
        ScopeTable *p = current;
        while (p != NULL)
        {
            if (p->look_up(s) != NULL)
            {

                //return p->look_up(s);
                return NULL;
            }
            p = p->get_parent();
        }
        //cout<<"	'"<<s<<"' not found in any of the ScopeTables"<<endl;
        return NULL;
    }

    void print_current_scope_table()
    {
        current->print();
    }

    void print_all_scope_table()
    {
        ScopeTable *p = current;
        while (p != NULL)
        {
            p->print();
            p = p->get_parent();
            
        }
    }
};



int bucket_size = 10;
SymbolTable *table = new SymbolTable(bucket_size);

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
	
	outputlog<<"Line# "<<line_count<<": Token <IF> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<IF, "<<yytext<<">"<<endl;
}

"else"	{
    
	outputlog<<"Line# "<<line_count<<": Token <ELSE> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<ELSE, "<<yytext<<">"<<endl;
}

"while"	{
	
	outputlog<<"Line# "<<line_count<<": Token <WHILE> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<WHILE, "<<yytext<<">"<<endl;
}	
"for"	{
	
	outputlog<<"Line# "<<line_count<<": Token <FOR> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<FOR, "<<yytext<<">"<<endl;
}
"do"	{
	
	outputlog<<"Line# "<<line_count<<": Token <DO> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<DO, "<<yytext<<">"<<endl;
}
"break"	{
	
	outputlog<<"Line# "<<line_count<<": Token <BREAK> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<BREAK, "<<yytext<<">"<<endl;
}
"int"	{
	
	outputlog<<"Line# "<<line_count<<": Token <INT> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<INT, "<<yytext<<">"<<endl;
}
"char"	{
	
	outputlog<<"Line# "<<line_count<<": Token <CHAR> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<CHAR, "<<yytext<<">"<<endl;
}
"float"	{
	
	outputlog<<"Line# "<<line_count<<": Token <FLOAT> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<FLOAT, "<<yytext<<">"<<endl;
}
"double"	{
	
	outputlog<<"Line# "<<line_count<<": Token <DOUBLE> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<DOUBLE, "<<yytext<<">"<<endl; 
}
"void"	{
	
	outputlog<<"Line# "<<line_count<<": Token <VOID> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<VOID, "<<yytext<<">"<<endl;
}
"return"	{
	
	outputlog<<"Line# "<<line_count<<": Token <RETURN> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<RETURN, "<<yytext<<">"<<endl;
}
"switch"	{
	
	outputlog<<"Line# "<<line_count<<": Token <SWITCH> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<SWITCH, "<<yytext<<">"<<endl;
}
"case"	{
	
	outputlog<<"Line# "<<line_count<<": Token <CASE> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<CASE, "<<yytext<<">"<<endl;
}
"default"	{
	
	outputlog<<"Line# "<<line_count<<": Token <DEFAULT> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<DEFAULT, "<<yytext<<">"<<endl;
}
"continue"	{
	
	outputlog<<"Line# "<<line_count<<": Token <CONTINUE> Lexeme "<<yytext<<" found"<<endl; 
    outputtoken<<"<CONTINUE, "<<yytext<<">"<<endl;
}


{DIGIT}+	{
	
	outputlog<<"Line# "<<line_count<<": Token <CONST_INT> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<CONST_INT, "<<yytext<<">"<<endl;
}
{DIGIT}+(\.{DIGIT}+)?([E][-]?{DIGIT}+)?	{
	
	outputlog<<"Line# "<<line_count<<": Token <CONST_FLOAT> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<CONST_FLOAT, "<<yytext<<">"<<endl;
}
{DIGIT}*(\.{DIGIT}+)\.[0-9\.E-]*(\.)*   {
    outputlog<<"Error at line# "<< line_count << ": TOO_MANY_DECIMAL_POINTS "<<yytext <<endl;
    
    err_count++;
}

([0-9]*(\.[0-9]*)?[E][+-]?[0-9]*[0-9\.E-]*(\.)*)|([0-9]+\.) {
    outputlog<<"Error at line# "<<line_count <<": ILLFORMED_NUMBER "<<yytext <<endl;

    err_count++;
}


{LETTER}{ALPHANUMERIC}*	{
	
	outputlog<<"Line# "<<line_count<<": Token <ID> Lexeme "<<yytext <<" found"<<endl;
	if(table->insert((string)yytext,"ID")){
		table->print_all_scope_table();
	}
    outputtoken<<"<ID, "<<yytext<<">"<<endl;
}


{DIGIT}*(\.{DIGIT}+)?(E[-]?{DIGIT}+)?{LETTER}{ALPHANUMERIC}*   {

    outputlog<<"Error at line# "<<line_count <<": INVALID_ID_SUFFIX_NUM_PREFIX "<<yytext <<endl;

    err_count++;
}


"+"|"-"	{
	
	outputlog<<"Line# "<<line_count<<": Token <ADDOP> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<ADDOP, "<<yytext<<">"<<endl;
}
"*"|"/"|"%"	{
	
	outputlog<<"Line# "<<line_count<<": Token <MULOP> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<MULOP, "<<yytext<<">"<<endl;
}
"++"|"--"	{
	
	outputlog<<"Line# "<<line_count<<": Token <INCOP> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<INCOP, "<<yytext<<">"<<endl;
}

"<"|"<="|">"|">="|"=="|"!="		{
	
	outputlog<<"Line# "<<line_count<<": Token <RELOP> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<RELOP, "<<yytext<<">"<<endl;
}
"="	{
	
	outputlog<<"Line# "<<line_count<<": Token <ASSIGNOP> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<ASSIGNOP, "<<yytext<<">"<<endl;
}

"&&"|"||"	{
	
	outputlog<<"Line# "<<line_count<<": Token <LOGICOP> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<LOGICOP, "<<yytext<<">"<<endl;
}
"&"|"|"|"^"|"<<"|">>"	{
	
	outputlog<<"Line# "<<line_count<<": Token <BITOP> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<BITOP, "<<yytext<<">"<<endl;
}

"!"	{
	
	outputlog<<"Line# "<<line_count<<": Token <NOT> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<NOT, "<<yytext<<">"<<endl;
}
"("	{
	
	outputlog<<"Line# "<<line_count<<": Token <LPAREN> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<LPAREN, "<<yytext<<">"<<endl;
}
")"	{
	
	outputlog<<"Line# "<<line_count<<": Token <RPAREN> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<RPAREN, "<<yytext<<">"<<endl;
}
"{"	{
	
	outputlog<<"Line# "<<line_count<<": Token <LCURL> Lexeme "<<yytext<<" found"<<endl;
	table->enter_scope();
    outputtoken<<"<LCURL, "<<yytext<<">"<<endl;
}
"}"	{
	
	outputlog<<"Line# "<<line_count<<": Token <RCURL> Lexeme "<<yytext<<" found"<<endl;
	table->exit_scope();
    outputtoken<<"<RCURL, "<<yytext<<">"<<endl;
}

"["	{
	
	outputlog<<"Line# "<<line_count<<": Token <LSQUARE> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<LSQUARE, "<<yytext<<">"<<endl;
}
"]"	{
	
	outputlog<<"Line# "<<line_count<<": Token <RSQUARE> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<RSQUARE, "<<yytext<<">"<<endl;
}
","	{
	
	outputlog<<"Line# "<<line_count<<": Token <COMMA> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<COMMA, "<<yytext<<">"<<endl;
}
";"	{
	
	outputlog<<"Line# "<<line_count<<": Token <SEMICOLON> Lexeme "<<yytext<<" found"<<endl;
    outputtoken<<"<SEMICOLON, "<<yytext<<">"<<endl;
}

\'  {
    input_chars = "";
    chars = "";
    BEGIN STATE_CHAR;
}
\"  {
    input_str = "";
    str = "";
    line_str = 0;
    BEGIN STATE_STRING;
}
\/\/    {
    c_str = "";
    c_str +="//";
    line1=0;
    BEGIN STATE_1_COMMENT;
}
\/\*    {
    c_str = "";
    c_str +="/*";
    line2 = 0;
    BEGIN STATE_2_COMMENT;

}


<STATE_1_COMMENT>\\\r\n {
    line1++;
    c_str +="\\\r\n";
}
<STATE_1_COMMENT>\\\n   {
    line1++;
    c_str +="\\\n";
}
<STATE_1_COMMENT><<EOF>>    {
    line_count += line1;
    outputlog<<"Line# "<<line_count<<": Token <SINGLE LINE COMMENT> Lexeme "<<c_str<<" found"<<endl;
    
    line1 = 0;
    BEGIN INITIAL;
}
<STATE_1_COMMENT>[\r]?\n    {
    line1++;
    outputlog<<"Line# "<<line_count<<": Token <SINGLE LINE COMMENT> Lexeme "<<c_str<<" found"<<endl;
    line_count +=line1;
    line1 = 0;
    BEGIN INITIAL;
}
<STATE_1_COMMENT>\\ {
    c_str +="\\";
}
<STATE_1_COMMENT>.  {
    c_str += yytext[0];
}
<STATE_2_COMMENT>\r {
    c_str += "\r";
}
<STATE_2_COMMENT>\n {
    line2++;
    c_str +="\n";

}
<STATE_2_COMMENT><<EOF>>    {
    line_count += line2;
    
    outputlog<<"Error at line# "<<line_count<<": UNFINISHED_COMMENT "<< c_str <<endl;

    err_count++;
    
    line2 = 0;
    BEGIN INITIAL;

}

<STATE_2_COMMENT>\*\/   {

    c_str += "*/";
    outputlog<<"Line# "<<line_count<<": Token <MULTI LINE COMMENT> Lexeme "<< c_str <<" found"<<endl;
    line_count += line2;
    line2 = 0;
    BEGIN INITIAL;


}



<STATE_2_COMMENT>.  {
    c_str += yytext[0];
}





<STATE_CHAR>\\0 {
        input_chars+="\\0";
        chars+="\0";
}

<STATE_CHAR>\\f {
        input_chars+="\\f";
        chars+="\f";
}
<STATE_CHAR>\\v {
        input_chars+="\\v";
        chars+="\v";
}
<STATE_CHAR>\\t {
        input_chars+="\\t";
        chars+="\t";
}
<STATE_CHAR>\\\' {
        input_chars+="\\\'";
        chars+="\'";
}
<STATE_CHAR>\\a {
        input_chars+="\\a";
        chars+="\a";
}
<STATE_CHAR>\\b {
        input_chars+="\\b";
        chars+="\b";
}
<STATE_CHAR>\\r {
        input_chars+="\\r";
        chars+="\r";
}
<STATE_CHAR>\\n {
        input_chars+="\\n";
        chars+="\n";
}
<STATE_CHAR>\\\" {
        input_chars+="\\\"";
        chars+="\"";
}
<STATE_CHAR>\\\\ {
        input_chars+="\\\\";
        chars+="\\";
}
<STATE_CHAR>[\r]?\n  {
         s = "";
        s+="'";
        s+=input_chars;
        err_count++;
        outputlog<<"Error at line# "<<line_count<<": UNFINISHED_CONST_CHAR "<< s <<endl;
        line_count++;
        BEGIN INITIAL;
}

<STATE_CHAR>;   {
         s = "";
        s+="'";
        s+=input_chars;
        err_count++;
        outputlog<<"Error at line# "<<line_count<<": UNFINISHED_CONST_CHAR "<< s <<endl;
        outputtoken<<"<SEMICOLON, "<<yytext<<">"<<endl;
	    outputlog<<"Line# "<<line_count<<": Token <SEMICOLON> Lexeme "<<yytext<<" found"<<endl;


        
        BEGIN INITIAL;
}


<STATE_CHAR><<EOF>> {
        s="";
        s+="'";
        s+=input_chars;
        err_count++;
        outputlog<<"Error at line# "<<line_count<<": UNFINISHED_CONST_CHAR "<< s <<endl;
        
        BEGIN INITIAL;
}
<STATE_CHAR>\'  {
        s = "";
        s+="'";
        s+=input_chars;
        s+="'";

        
        if(chars.size()==1){
            
            outputlog<<"Line# "<<line_count<<": Token <CONST_CHAR> Lexeme "<< chars <<" found"<<endl;
            outputtoken<<"<CONST_CHAR, "<<chars<<">"<<endl;
        }
        else if(chars.size()==0){
            if(input_chars=="\\0"){
                
                outputlog<<"Line# "<<line_count<<": Token <CONST_CHAR> Lexeme "<< chars <<" found"<<endl;
                outputtoken<<"<CONST_CHAR, "<<chars<<">"<<endl;
            }
            else{
                err_count++;
                outputlog<<"Error at line# "<<line_count<<": EMPTY_CONST_CHAR "<< s <<endl;
            }
        }

        else{
            err_count++;
            outputlog<<"Error at line# "<<line_count<<": MULTICHAR_CONST_CHAR "<< s <<endl;
        }
        BEGIN INITIAL;
}

<STATE_CHAR>.   {
        input_chars +=yytext[0];
        chars +=yytext[0];
}



<STATE_STRING>\\0 {
        input_str+="\\0";
        str +="\0";
}

<STATE_STRING>\\f {
        input_str +="\\f";
        str +="\f";
}
<STATE_STRING>\\v {
        input_str +="\\v";
        str +="\v";
}
<STATE_STRING>\\t {
        input_str +="\\t";
        str +="\t";
}
<STATE_STRING>\\\' {
        input_str +="\\\'";
        str +="\'";
}
<STATE_STRING>\\a {
        input_str +="\\a";
        str +="\a";
}
<STATE_STRING>\\b {
        input_str +="\\b";
        str +="\b";
}
<STATE_STRING>\\r {
        input_str +="\\r";
        str +="\r";
        
}
<STATE_STRING>\\n {
        input_str +="\\n";
        str +="\n";
        
}
<STATE_STRING>\\\" {
        input_str +="\\\"";
        str +="\"";
}
<STATE_STRING>\\\\ {
        input_str +="\\\\";
        str +="\\";
}

<STATE_STRING>\\\r\n    {
        line_str++;
        input_str +="\\\r\n";
        BEGIN STATE_STRING_M;
}
<STATE_STRING>\\\n  {
        line_str++;
        input_str +="\\\n";
        BEGIN STATE_STRING_M;
}

<STATE_STRING>\"    {
        s = "";
        s +="\"";
        s +=input_str;
        s +="\"";
        
        outputlog<<"Line# "<< line_count <<": Token <SINGLE LINE STRING> Lexeme "<< s <<" found"<<endl;
        outputtoken<<"<SINGLE LINE STRING, "<< str <<">"<<endl;
        line_count += line_str;
        line_str = 0;
        BEGIN INITIAL;
}




<STATE_STRING>[\r]?\n   {
        
        s = "";
        s +="\"";
        s += input_str;
        line_count += line_str;
        outputlog<<"Error at line# "<<line_count<<": UNFINISHED_STRING "<< s <<endl;
        line_count++;
        err_count++;
        
        line_str = 0;
        BEGIN INITIAL;

}
<STATE_STRING><<EOF>>   {
        s = "";
        s +="\"";
        s += input_str;
        line_count += line_str;
        outputlog<<"Error at line# "<<line_count<<": UNFINISHED_STRING "<< s <<endl;

        err_count++;
        
        line_str = 0;
        str = "";
        input_str = "";
        BEGIN INITIAL;

}


<STATE_STRING>. {
        str += yytext[0];
        input_str += yytext[0];
}

<STATE_STRING_M>\\0 {
        input_str+="\\0";
        str +="\0";
}

<STATE_STRING_M>\\f {
        input_str +="\\f";
        str +="\f";
}
<STATE_STRING_M>\\v {
        input_str +="\\v";
        str +="\v";
}
<STATE_STRING_M>\\t {
        input_str +="\\t";
        str +="\t";
}
<STATE_STRING_M>\\\' {
        input_str +="\\\'";
        str +="\'";
}
<STATE_STRING_M>\\a {
        input_str +="\\a";
        str +="\a";
}
<STATE_STRING_M>\\b {
        input_str +="\\b";
        str +="\b";
}
<STATE_STRING_M>\\r {
        input_str +="\\r";
        str +="\r";
}
<STATE_STRING_M>\\n {
        input_str +="\\n";
        str +="\n";
}
<STATE_STRING_M>\\\" {
        input_str +="\\\"";
        str +="\"";
}
<STATE_STRING_M>\\\\ {
        input_str +="\\\\";
        str +="\\";
}

<STATE_STRING_M>\\\r\n    {
        line_str++;
        input_str +="\\\r\n";
        
}
<STATE_STRING_M>\\\n  {
        line_str++;
        input_str +="\\\n";
        
}

<STATE_STRING_M>\"    {
        s = "";
        s +="\"";
        s +=input_str;
        s +="\"";
        
        outputlog<<"Line# "<< line_count <<": Token <MULTI LINE STRING> Lexeme "<< s <<" found"<<endl;
        outputtoken<<"<MULTI LINE STRING, "<< str <<">"<<endl;
        line_count += line_str;
        line_str = 0;
        str = "";
        input_str = "";
        BEGIN INITIAL;
}




<STATE_STRING_M>[\r]?\n   {
        
        s = "";
        s +="\"";
        s += input_str;
        line_count += line_str;
        outputlog<<"Error at line# "<<line_count<<": UNFINISHED_STRING "<< s <<endl;
        line_count++;
        err_count++;
        
        line_str = 0;
        BEGIN INITIAL;

}
<STATE_STRING_M><<EOF>>   {
        s = "";
        s +="\"";
        s += input_str;
        line_count += line_str;
        outputlog<<"Error at line# "<<line_count<<": UNFINISHED_STRING "<< s <<endl;

        err_count++;
        
        line_str = 0;
        str = "";
        input_str = "";
        BEGIN INITIAL;

}


<STATE_STRING_M>. {
        str += yytext[0];
        input_str += yytext[0];
}



.   {
        
        
        outputlog<<"Error at line# "<<line_count<<": UNRECOGNIZED_CHAR "<< yytext <<endl;
        err_count++;
        
}



%%

int main(int argc, char** argv) {
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	

	yyin= fin;
	yylex();
	
    table->print_all_scope_table();
	
    outputlog<<"Total lines: "<< line_count <<endl;
	outputlog<<"Total errors: "<< err_count <<endl;

	fclose(yyin);
	outputtoken.close();
	outputlog.close();

    delete table;
	return 0;
}

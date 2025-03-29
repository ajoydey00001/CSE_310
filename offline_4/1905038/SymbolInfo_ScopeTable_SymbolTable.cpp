#include<bits/stdc++.h>


using namespace std;

class SymbolInfo
{
    string newname,name, type, stype, dtype,parent,child;
    int startline,endline,stackoffset,arraysize;
    bool leaf_or_not,global,inparalist;
    vector<SymbolInfo*> childernlist;

    vector<SymbolInfo*> fpara;
    SymbolInfo *next;


public:


    SymbolInfo(string s,string r){
        name = s;
        type = r;
        stype = "NONE";
        dtype = "NONE";
        next = NULL;
        leaf_or_not  = false;
        stackoffset = 0;
        arraysize = 0;
        global = false;
        inparalist = false;
    }
    SymbolInfo(string s, string structure, string r)
    {
        name = s;
        
        type = "NONE";
        next = NULL;
        stype = structure;
        dtype = r;
        leaf_or_not = false;
        stackoffset = 0;
        arraysize = 0;
        global = false;
        inparalist = false;

    }
    ~SymbolInfo(){
        
        for(auto j : fpara){
            delete j;
        }
        

    }
    void set_inparalist(bool f){
        inparalist = f;
    }
    bool get_inparalist(){
        return inparalist;
    }
    
    void set_global(bool f){
        global = f;
    }
    bool get_global(){
        return global;
    }

    void set_arraysize(int i){
        arraysize = i;
    }
    int get_arraysize(){
        return arraysize;
    }
    void set_stackoffset(int i){
        stackoffset = i;
    }
    int get_stackoffset(){
        return stackoffset;
    }
    void set_newname(string s){
        newname = s;
    }
    string get_newname(){
        return newname;
    }

    void set_is_child_or_not(bool k){
        leaf_or_not = k;
    }
    bool get_is_child_or_not(){
        return leaf_or_not;
    }
    void add_child(SymbolInfo* k){
        childernlist.push_back(k);
    }
    vector<SymbolInfo*> get_childlist(){
        return childernlist;
    }
    string get_parent(){
        return parent;
    }
    string get_child(){
        return child;
    }
    void set_parent(string k){
        parent = k;
    }
    void set_child(string k){
        child = k;
    }
    void set_startline(int k){
        startline = k;
    }
    void set_endline(int k){
        endline = k;
    }
    int get_startline(){
        return startline;
    }
    int get_endline(){
        return endline;
    }


    void add_para(vector<SymbolInfo*> h){
        
        for(auto i : h){
            fpara.push_back(i);
        }

    }
    
    vector<SymbolInfo*> get_para(){
        return fpara;
    }
    
    void set_stype(string s){
        stype = s;
    }
    void set_dtype(string s){
        dtype = s;
    }
    string get_stype(){
        return stype;
    }
    string get_dtype(){
        return dtype;
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
    bool insert(string s, string structure , string r)
    {
        int k = sdbm_hash(s, bucketNumber);
        SymbolInfo *q = array[k];
        while (q != NULL)
        {
            SymbolInfo *w = q->get_next();
            if (q->get_name().compare(s) == 0)
            {
               // outputlog<<"	"<<s<<" already exisits in the current ScopeTable"<<endl;
                return false;
            }
            q = w;
        }

        SymbolInfo *p = new SymbolInfo(s,structure, r);
        
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

    void print(ofstream& outputlog)
    {
        outputlog<<"	ScopeTable# "<<id<<endl;
        for(int i=0;i<bucketNumber;i++){
            
            SymbolInfo * p = array[i];
            if(p==NULL) continue;
            outputlog<<"	"<<i+1<<"--> ";
            while (p!= NULL)
            {
              outputlog<<"<"<<p->get_name()<<", ";
              if(p->get_stype().compare("FUNCTION") == 0 || (p->get_stype().compare("ARRAY") == 0)){
                outputlog<<p->get_stype()<<", ";
              }
              outputlog<<p->get_dtype()<<"> ";
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

    ScopeTable* get_current_scopeTable(){
        return current;
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

    bool insert(string s,string structure, string t)
    {
        return current->insert(s,structure, t);
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

                return p->look_up(s);
                
            }
            p = p->get_parent();
        }
        //cout<<"	'"<<s<<"' not found in any of the ScopeTables"<<endl;
        return NULL;
    }

    void print_current_scope_table(ofstream outputlog)
    {
        current->print(outputlog);
    }

    void print_all_scope_table(ofstream& outputlog)
    {
        ScopeTable *p = current;
        while (p != NULL)
        {
            p->print(outputlog);
            p = p->get_parent();
            
        }
    }
};
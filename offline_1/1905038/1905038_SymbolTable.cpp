#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

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
        cout << "	ScopeTable# " << id << " created" << endl;
    }
    ~ScopeTable()
    {
        cout<<"	ScopeTable# "<<id<<" removed"<<endl;

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
        int hash = 0;
        int i = 0;
        int len = str.length();

        for (i = 0; i < len; i++)
        {
            hash = (((int)str[i]) % mod + (hash << 6) % mod + (hash << 16) % mod - hash) % mod;
        }

        return hash;
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
                cout<<"	'"<<s<<"' already exists in the current ScopeTable"<<endl;
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

        cout << "	Inserted in ScopeTable# " << id << " at position " << k + 1 << ", "
             << i << endl;
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
                cout<<"	'"<<s<<"' found in ScopeTable# "<<id<<" at position "<<k+1<<", "<< i<<endl;
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
                cout<<"	Deleted '"<<s<<"' from ScopeTable# "<<id<<" at position "<<k+1<<", "<<i<<endl;
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
        cout<<"	Not found in the current ScopeTable"<<endl;
        return false;
    }

    void print()
    {
        cout<<"	ScopeTable# "<<id<<endl;
        for(int i=0;i<bucketNumber;i++){
            cout<<"	"<<i+1<<"--> ";
            SymbolInfo * p = array[i];
            while (p!= NULL)
            {
                cout<<"<"<<p->get_name()<<","<<p->get_type()<<"> ";
                p=p->get_next();
            }
            cout<<endl;
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
            cout<<"	ScopeTable# 1 cannot be removed"<<endl;
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
        cout<<"	'"<<s<<"' not found in any of the ScopeTables"<<endl;
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

int main()
{

    freopen("input.txt", "r", stdin);

    freopen("output.txt", "w", stdout);
    int n;

    int i = 1, p = 0;
    string ajoy;
    cin >> n;
    getline(cin, ajoy);

    SymbolTable *table = new SymbolTable(n);

    while (1)
    {
        p++;
        
        getline(cin, ajoy);
        int m = ajoy.size();
        cout << "Cmd " << p << ": " << ajoy << endl;
        char c = ajoy[0];

        if (c == 'I')
        {
            string a = "";
            string b = "";
            i = 2;
            if (i >= m)
            {
                cout << "	Number of parameters mismatch for the command I" << endl;
                continue;
            }
            while (1)
            {
                if (i == m)
                    break;
                if (ajoy[i] == ' ')
                    break;
                a += ajoy[i];
                i++;
            }
            i++;
            if (i >= m)
            {
                cout << "	Number of parameters mismatch for the command I" << endl;
                continue;
            }
            while (1)
            {
                if (i == m)
                    break;
                if (ajoy[i] == ' ')
                    break;
                b += ajoy[i];
                i++;
            }
            if (i < m)
            {
                cout << "	Number of parameters mismatch for the command I" << endl;
                continue;
            }
            
            table->insert(a, b);
            
        }
        else if (c == 'L')
        {
            
            string a = "";
            
            i = 2;
            if (i >= m)
            {
                cout << "	Number of parameters mismatch for the command L" << endl;
                continue;
            }
            while (1)
            {
                if (i == m)
                    break;
                if (ajoy[i] == ' ')
                    break;
                a += ajoy[i];
                i++;
            }
            if(i<m){
                cout<<"	Number of parameters mismatch for the command L"<<endl;
                continue;
            }
            
            
            table->look_up(a);

        }
        else if(c=='P'){
            string a = "";
            string b="C";
            i = 2;
            if (i >= m)
            {
                cout << "	Number of parameters mismatch for the command P" << endl;
                continue;
            }
            while (1)
            {
                if (i == m)
                    break;
                if (ajoy[i] == ' ')
                    break;
                a += ajoy[i];
                i++;
            }
            if(i<m){
                cout<<"	Number of parameters mismatch for the command P"<<endl;
                continue;
            }
            
            
            if(a[0]=='C'){
                table->print_current_scope_table();
            }
            else{
                
                table->print_all_scope_table();
            }
            
            
        }
        else if(c=='D'){
            string a = "";
            
            i = 2;
            if (i >= m)
            {
                cout << "	Number of parameters mismatch for the  command D" << endl;
                continue;
            }
            while (1)
            {
                if (i == m)
                    break;
                if (ajoy[i] == ' ')
                    break;
                a += ajoy[i];
                i++;
            }
            if(i<m){
                cout<<"	Number of parameters mismatch for the command D"<<endl;
                continue;
            }
            
            
            table->remove(a);
        }
        else if(c=='S'){
            if(m>1){
                cout<<"	Number of parameters mismatch for the command S"<<endl;
                continue;
            }
            table->enter_scope();
        }
        else if(c=='E'){
            if(m>1){
                cout<<"	Number of parameters mismatch for the command E"<<endl;
                continue;
            }
            table->exit_scope();
        }
        else if(c=='Q'){
            if(m>1){
                cout<<"	Number of parameters mismatch for the command Q"<<endl;
                continue;
            }

            delete table;
            break;
        }
        else{
            //cout<<""
        }
    }

    return 0;
}

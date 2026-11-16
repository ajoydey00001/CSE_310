#ifndef SCOPE_TABLE_H
#define SCOPE_TABLE_H

#include "symbol_info.h"

class scope_table
{
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope = NULL;
    vector<list<symbol_info *>> table;

    int hash_function(string name)
    {
        int sum = 0;
        for (int i = 0; i < name.length(); i++)
            sum = sum + name[i];
        int idx = sum % bucket_count;
        return idx;
    }
public:
    scope_table()
    {
        bucket_count =4;
        unique_id =0;
        parent_scope = NULL;
        table.resize(bucket_count);
        return ;
    }
    scope_table(int bucket_count, int unique_id, scope_table *parent_scope)
    {
        this->bucket_count =bucket_count;
        this->unique_id= unique_id;
        this->parent_scope =parent_scope;
        table.resize(bucket_count);
        return;
    }
    scope_table *get_parent_scope()
    {
       return parent_scope;
    }
    int get_unique_id()
    {
       return unique_id;
    }

    symbol_info *lookup_in_scope(symbol_info* symbol)
    {
        int indx =hash_function(symbol->get_name());
        for (symbol_info *s:table[indx])
    {
            if (s->get_name() ==symbol->get_name())
                 return s;
    }
        return NULL;
    }

    bool insert_in_scope(symbol_info* symbol)
    {
        if (lookup_in_scope(symbol) != NULL)
            return false;   
        int indx = hash_function(symbol->get_name());
        table[indx].push_back(symbol);
        return true;
    }

    bool delete_from_scope(symbol_info* symbol)
    {
       int idx = hash_function(symbol->get_name());
       for (auto it = table[idx].begin(); it != table[idx].end(); ++it)
       {
            if ((*it)->get_name() == symbol->get_name())
            {
                delete *it;
                table[idx].erase(it);
                return true;
            }
        }
        return false;
    }


    void print_scope_table(ofstream& outlog)
    {
        outlog << "ScopeTable # "+ to_string(unique_id) << endl;

        for (int i = 0; i < bucket_count; i++)
        {
            if (table[i].empty())
                continue;
            outlog << i << " --> " << endl;
            for (symbol_info *s :table[i])
            {
                outlog << "< " << s->get_name() << " : " << s->get_type() << " >" << endl;

                if (s->function_check())
                {
                    outlog << "Function Definition" << endl;
                    outlog << "Return Type: " << s->get_data_type() << endl;
                    outlog << "Number of Parameters: " << s->get_param_count() << endl;
                    outlog << "Parameter Details: ";
                    list<string> types = s->get_param_types();
                    list<string> names = s->get_param_names();
                    auto t = types.begin();
                    auto n = names.begin();
                    for (; t != types.end(); ++t, ++n)
                    {
                        if (t != types.begin()) outlog << ", ";
                        outlog << *t;
                        if (*n != "") outlog << " " << *n;
                    }
                    outlog << endl;
                }
                else if (s->array_check())
                {
                    outlog << "Array" << endl;
                    outlog << "Type: " << s->get_data_type() << endl;
                    outlog << "Size: " << s->get_arr_size() << endl;
                    outlog << endl;
                }
                else
                {
                    outlog << "Variable" << endl;
                    outlog << "Type: " << s->get_data_type() << endl;
                    outlog << endl;
                }
            }
        }
        outlog << endl;
    }

    ~scope_table()
    {
        for (auto &bucket : table)
        {
            for (symbol_info *s : bucket)
                delete s;
            bucket.clear();
        }
        table.clear();
    }
};

#endif

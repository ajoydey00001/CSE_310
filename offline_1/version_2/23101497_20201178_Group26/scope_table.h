#ifndef SCOPE_TABLE_H
#define SCOPE_TABLE_H

#include "symbol_info.h"

class scope_table
{
private:
    int bucket_count;
    int unique_id;
    scope_table *parent_scope = NULL;
    symbol_info **table; // array of pointers: table[i] is the head of bucket i's chain

    int hash_function(string name)
    {
        int sum = 0;
        for (int i = 0; i < name.length(); i++)
            sum = sum + name[i];
        int idx = sum % bucket_count; // keep the hash value in the range of the bucket size
        return idx;
    }

public:
    // allocates n buckets for the hash table
    scope_table(int n)
    {
        bucket_count = n;
        unique_id = 0;
        parent_scope = NULL;
        table = new symbol_info *[bucket_count];
        for (int i = 0; i < bucket_count; i++)
            table[i] = NULL;
    }

    scope_table *get_parent_scope()
    {
        return parent_scope;
    }
    void set_parent_scope(scope_table *parent)
    {
        parent_scope = parent;
    }
    int get_unique_id()
    {
        return unique_id;
    }
    void set_unique_id(int id)
    {
        unique_id = id;
    }

    symbol_info *lookup_in_scope(symbol_info *symbol)
    {
        int idx = hash_function(symbol->get_name());
        symbol_info *cur = table[idx];
        while (cur != NULL)
        {
            if (cur->get_name() == symbol->get_name())
                return cur;
            cur = cur->get_next();
        }
        return NULL;
    }

    bool insert_in_scope(symbol_info *symbol)
    {
        if (lookup_in_scope(symbol) != NULL)
            return false;

        int idx = hash_function(symbol->get_name());
        symbol->set_next(NULL);

        // append at the end of the chain so symbols print in insertion order
        if (table[idx] == NULL)
        {
            table[idx] = symbol;
        }
        else
        {
            symbol_info *cur = table[idx];
            while (cur->get_next() != NULL)
                cur = cur->get_next();
            cur->set_next(symbol);
        }
        return true;
    }

    bool delete_from_scope(symbol_info *symbol)
    {
        int idx = hash_function(symbol->get_name());
        symbol_info *cur = table[idx];
        symbol_info *prev = NULL;
        while (cur != NULL)
        {
            if (cur->get_name() == symbol->get_name())
            {
                if (prev == NULL)
                    table[idx] = cur->get_next();
                else
                    prev->set_next(cur->get_next());
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->get_next();
        }
        return false;
    }

    void print_scope_table(ofstream &outlog)
    {
        outlog << "ScopeTable # " + to_string(unique_id) << endl;

        for (int i = 0; i < bucket_count; i++)
        {
            if (table[i] == NULL)
                continue;
            outlog << i << " --> " << endl;
            for (symbol_info *s = table[i]; s != NULL; s = s->get_next())
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
        for (int i = 0; i < bucket_count; i++)
        {
            symbol_info *cur = table[i];
            while (cur != NULL)
            {
                symbol_info *nxt = cur->get_next();
                delete cur;
                cur = nxt;
            }
            table[i] = NULL;
        }
        delete[] table;
    }
};

#endif

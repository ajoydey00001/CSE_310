#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "scope_table.h"

class symbol_table
{
private:
    scope_table *current_scope;
    int bucket_count;
    int current_scope_id;

public:
    symbol_table(int bucket_count);
    ~symbol_table();
    void enter_scope();
    void exit_scope();
    bool insert(symbol_info* symbol);
    bool remove(symbol_info* symbol);
    symbol_info* lookup(symbol_info* symbol);
    int get_current_scope_id();
    void print_current_scope(ofstream& outlog);
    void print_all_scopes(ofstream& outlog);
};

symbol_table::symbol_table(int bucket_count)
{
    this->bucket_count =bucket_count;
    this->current_scope_id =0;
    current_scope = NULL;
}

symbol_table::~symbol_table()
{
    while (current_scope != NULL)
        exit_scope();
}

void symbol_table::enter_scope()
{
    current_scope_id++;
    scope_table *new_scope = new scope_table(bucket_count);
    new_scope->set_unique_id(current_scope_id);
    new_scope->set_parent_scope(current_scope);
    current_scope = new_scope;
}

void symbol_table::exit_scope()
{
    if (current_scope == NULL)
        return;
    scope_table *temp = current_scope;
    current_scope = current_scope->get_parent_scope();
    delete temp;
}

bool symbol_table::insert(symbol_info* symbol)
{
    if (current_scope == NULL)
        return false;
    return current_scope->insert_in_scope(symbol);
}

bool symbol_table::remove(symbol_info* symbol)
{
    if (current_scope == NULL)
        return false;
    return current_scope->delete_from_scope(symbol);
}

symbol_info* symbol_table::lookup(symbol_info* symbol)
{
    scope_table *temp = current_scope;
    while (temp != NULL)
    {
        symbol_info *s = temp->lookup_in_scope(symbol);
        if (s != NULL)
            return s;
        temp = temp->get_parent_scope();
    }
    return NULL;
}

int symbol_table::get_current_scope_id()
{
    if (current_scope == NULL)
        return 0;
    return current_scope->get_unique_id();
}

void symbol_table::print_current_scope(ofstream& outlog)
{
    if (current_scope != NULL)
        current_scope->print_scope_table(outlog);
}

void symbol_table::print_all_scopes(ofstream& outlog)
{
    outlog<<"################################"<<endl<<endl;
    scope_table *temp = current_scope;
    while (temp != NULL)
    {
        temp->print_scope_table(outlog);
        temp = temp->get_parent_scope();
    }
    outlog<<"################################"<<endl<<endl;
}

#endif

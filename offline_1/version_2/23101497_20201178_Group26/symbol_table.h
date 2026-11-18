/*
 * symbol_table.h
 * --------------
 * The SYMBOL TABLE = a stack of scope tables.
 *
 * The scopes are linked through scope_table::parent_scope, and
 * `current_scope` always points to the top of the stack (the innermost
 * block we are in). Example from the spec, while inside the if-block of func:
 *
 *   current_scope
 *        |
 *        v
 *   [ScopeTable 3] --parent--> [ScopeTable 2] --parent--> [ScopeTable 1] --> NULL
 *     if-block: a                func body: x, t             global: a, b, c, func
 *
 * How the parser (.y file) uses it:
 *   - start of main()   : new symbol_table(10), enter_scope()  -> ScopeTable 1 (global)
 *   - every '{'         : enter_scope()                        -> push a new scope
 *   - every declaration : insert()                             -> goes into the top scope
 *   - every '}'         : print_all_scopes(), exit_scope()     -> pop the top scope
 *   - function call     : lookup()                             -> find the function
 *
 * lookup() searches from the top scope down to the global scope and returns
 * the FIRST match, so an inner declaration hides (shadows) an outer one with
 * the same name, e.g. the "a" of the if-block hides the global "a".
 *
 * Note: the member functions are defined below the class, in this header.
 * The header must therefore be included by ONLY ONE source file (the .y);
 * the lexer (.l) includes symbol_info.h only. Otherwise the linker would see
 * the same functions twice.
 */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "scope_table.h"

class symbol_table
{
private:
    scope_table *current_scope; // top of the stack (innermost scope), NULL when empty
    int bucket_count;           // bucket count given to every new scope_table
    int current_scope_id;       // counter used to give each new scope a unique id

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

// Starts EMPTY: no scope exists until enter_scope() is called the first time.
symbol_table::symbol_table(int bucket_count)
{
    this->bucket_count =bucket_count;
    this->current_scope_id =0;
    current_scope = NULL;
}

// Pops (and frees) every scope that is still on the stack.
symbol_table::~symbol_table()
{
    while (current_scope != NULL)
        exit_scope();
}

// ENTER SCOPE: push a new scope_table on top of the stack.
// The id counter only goes up and ids are never reused: after ScopeTable 2
// is removed, the next new scope is 3 (as in the sample logs).
void symbol_table::enter_scope()
{
    current_scope_id++;
    scope_table *new_scope = new scope_table(bucket_count);
    new_scope->set_unique_id(current_scope_id);
    new_scope->set_parent_scope(current_scope);     // old top becomes the parent
    current_scope = new_scope;                      // new scope is now the top
}

// EXIT SCOPE: pop the top scope; its parent becomes the current scope.
// Deleting the scope_table also frees all symbols declared in that block.
void symbol_table::exit_scope()
{
    if (current_scope == NULL)
        return;
    scope_table *temp = current_scope;
    current_scope = current_scope->get_parent_scope();
    delete temp;
}

// INSERT: always into the CURRENT (top) scope.
// false = no scope exists, or the name is already declared in this scope.
bool symbol_table::insert(symbol_info* symbol)
{
    if (current_scope == NULL)
        return false;
    return current_scope->insert_in_scope(symbol);
}

// REMOVE: delete a symbol from the CURRENT scope only.
bool symbol_table::remove(symbol_info* symbol)
{
    if (current_scope == NULL)
        return false;
    return current_scope->delete_from_scope(symbol);
}

// LOOK UP: search the current scope first, then its parent, and so on up to
// the global scope. The first match wins (this is what makes shadowing work).
// Returns NULL if the name is not declared in any visible scope.
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

// Id of the top scope (0 if no scope exists). The parser uses it to print
// "New ScopeTable with ID N created" and "Scopetable with ID N removed".
int symbol_table::get_current_scope_id()
{
    if (current_scope == NULL)
        return 0;
    return current_scope->get_unique_id();
}

// PRINT CURRENT: print only the top scope.
void symbol_table::print_current_scope(ofstream& outlog)
{
    if (current_scope != NULL)
        current_scope->print_scope_table(outlog);
}

// PRINT ALL: print every scope on the stack, from the top (innermost) down to
// the global scope, between two lines of '#'. Called before every exit_scope()
// and once more at the end of the program.
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

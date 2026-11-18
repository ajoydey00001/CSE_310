/*
 * symbol_info.h
 * -------------
 * ONE entry (one "symbol") of the symbol table.
 *
 * This class has two jobs in the compiler:
 *
 *  1. Parser value (YYSTYPE)
 *     The lexer and every grammar rule pass a symbol_info* up the parse tree.
 *     For these, `name` holds the matched source text (e.g. "a+b", "int a,b;")
 *     and `type` holds a label ("ID", "CONST_INT", "expr", ...).
 *
 *  2. Symbol table entry
 *     For every identifier that is DECLARED in the input program, the parser
 *     creates a symbol_info with name = the identifier, type = "ID", fills the
 *     extra details below and inserts it into the current scope_table.
 *
 * Three kinds of identifiers are stored (field `symbol_type`):
 *
 *   "variable"  -> name + data type                       e.g.  int a;
 *   "array"     -> name + data type + array size          e.g.  int f[10];
 *   "function"  -> name + return type + parameter list    e.g.  int func(int a, float b)
 */

#ifndef SYMBOL_INFO_H   // include guard: the file is pulled in by several headers,
#define SYMBOL_INFO_H   // the guard makes sure the class is defined only once

//#include<bits/stdc++.h> Removing this line because clang doesn’t have bits/stdc++.h
#include <iostream>
#include <fstream>      // ofstream, used to write the log file
#include <string>
#include <vector>       // the parser collects parameters in vectors
#include <list>         // parameters are stored in lists inside the symbol
using namespace std;

class symbol_info
{
private:
    string name;        // identifier name ("a", "func") or code text for parser values
    string type;        // token / grammar label; "ID" for every stored identifier

    string symbol_type; // kind of identifier: "variable", "array" or "function"
    string data_type;   // variable/array: its data type (int, float ...)
                        // function: its RETURN type
    list<string> param_names; // function only: parameter names, "" if unnamed (int f(int))
    list<string> param_types; // function only: parameter types, same order as param_names
    int arr_size;       // array only: number of elements, 0 for non-arrays

    // Hash-table chaining: several symbols can hash to the same bucket.
    // They are kept in a singly linked list, and `next` points to the
    // following symbol of that bucket (NULL = end of the chain).
    symbol_info *next;

public:
    // Every symbol starts as a plain variable with no extra details;
    // the parser changes symbol_type / data_type / arr_size / params after creating it.
    symbol_info(string name, string type)
    {
        this->name = name;
        this->type = type;
        this->symbol_type = "variable";
        this->data_type = "";
        this->arr_size = 0;
        this->next = NULL;
    }

    // ---- chaining (used only by scope_table) ----
    symbol_info *get_next()
    {
        return next;
    }
    void set_next(symbol_info *next)
    {
        this->next = next;
    }

    // ---- basic getters / setters ----
    string get_name()
    {
        return name;
    }
    void set_name(string name)
    {
        this->name = name;
    }
    string get_type()
    {
        return type;
    }
    void set_type(string type)
    {
        this->type =type;
    }
    string get_symbol_type()
    {
        return symbol_type;
    }
    void set_symbol_type(string stp)
    {
        symbol_type =stp;
    }

    string get_data_type()
    {
        return data_type;
    }
    void set_data_type(string dtp)
    {
        data_type = dtp;
    }
    int get_arr_size()
    {
        return arr_size;
    }
    void set_arr_size(int size)
    {
        arr_size = size;
    }

    // ---- kind checks (used when printing and when checking a function call) ----
    bool function_check()
    {
        return symbol_type == "function";
    }
    bool array_check()
    {
        return symbol_type == "array";
    }

    // ---- function parameters ----

    // Append ONE parameter at the end (also used by the parser to count call arguments).
    void add_param(string ptype, string pname)
    {
        param_types.push_back(ptype);
        param_names.push_back(pname);
    }
    // Replace the WHOLE parameter list at once. The parser collects the
    // parameters of a definition in two vectors, then copies them in here.
    void set_params(vector<string> types, vector<string> names)
    {
        param_types.assign(types.begin(), types.end());
        param_names.assign(names.begin(), names.end());
    }
    list<string> get_param_types()
    {
         return param_types;
        }
    list<string> get_param_names()
    {
         return param_names;
    }
    // number of parameters = number of stored types
    int get_param_count()
    {
        return (int)param_types.size();
    }

    // The lists free their own memory; clear() just makes the clean-up explicit.
    // The `next` symbol is NOT deleted here, the scope_table owns the chain.
    ~symbol_info()
    {
        param_types.clear();
        param_names.clear();
    }
};

#endif

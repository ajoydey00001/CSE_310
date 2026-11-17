#ifndef SYMBOL_INFO_H
#define SYMBOL_INFO_H

//#include<bits/stdc++.h> Removing this line because clang doesn’t have bits/stdc++.h
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

class symbol_info
{
private:
    string name;
    string type;

    string symbol_type; // type (array,func etc)
    string data_type; // data type of stored data
    list<string> param_names; // parameter name
    list<string> param_types; // parameter type
    int arr_size; // if array

    symbol_info *next; // next symbol in the same hash bucket (chaining)

public:
    symbol_info(string name, string type)
    {
        this->name = name;
        this->type = type;
        this->symbol_type = "variable";
        this->data_type = "";
        this->arr_size = 0;
        this->next = NULL;
    }

    symbol_info *get_next()
    {
        return next;
    }
    void set_next(symbol_info *next)
    {
        this->next = next;
    }

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

    bool function_check() 
    { 
        return symbol_type == "function"; 
    }
    bool array_check() 
    { 
        return symbol_type == "array"; 
    }

    void add_param(string ptype, string pname)
    {
        param_types.push_back(ptype);
        param_names.push_back(pname);
    }
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
    int get_param_count() 
    { 
        return (int)param_types.size(); 
    }

    ~symbol_info()
    {
        param_types.clear();
        param_names.clear();
    }
};

#endif

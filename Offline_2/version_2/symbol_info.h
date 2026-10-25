#ifndef SYMBOL_INFO_H
#define SYMBOL_INFO_H

#include<bits/stdc++.h>

using namespace std;

class SymbolInfo
{
    string name, type;

public:
    SymbolInfo(string s, string r)
    {
        name = s;
        type = r;
    }

    void set_name(string s)
    {
        name = s;
    }
    void set_type(string s)
    {
        type = s;
    }
    string get_name()
    {
        return name;
    }
    string get_type()
    {
        return type;
    }
};

#endif

/*
 * scope_table.h
 * -------------
 * ONE scope (one block { ... } of the program) = ONE hash table.
 *
 * Structure: an array of `bucket_count` pointers. Each slot (bucket) is the
 * head of a linked list of symbol_info objects (separate chaining).
 *
 *     table
 *     +---+
 *     | 0 | -> NULL
 *     | 1 | -> [main] -> NULL
 *     | . |
 *     | 7 | -> [a] -> [k] -> NULL     <- "a" and "k" both hash to 7 (collision),
 *     | 8 | -> [func] -> NULL            so they share the bucket via `next`
 *     | 9 | -> NULL
 *     +---+
 *
 * Hash function: sum of the ASCII codes of the name, modulo bucket_count.
 *     "a"    = 97                    -> 97  % 10 = 7
 *     "func" = 102+117+110+99 = 428  -> 428 % 10 = 8
 *     "main" = 109+97+105+110 = 421  -> 421 % 10 = 1
 * These are exactly the bucket numbers in the instructor's sample logs.
 *
 * Every scope_table also stores:
 *   - unique_id    : its number (1 = global scope), printed as "ScopeTable # N"
 *   - parent_scope : the scope that encloses it, so symbol_table can chain
 *                    the scopes into a stack (see symbol_table.h)
 *
 * Insert / lookup / delete only touch ONE bucket, so they are O(1) on average
 * (O(length of that chain) in the worst case).
 */

#ifndef SCOPE_TABLE_H
#define SCOPE_TABLE_H

#include "symbol_info.h"

class scope_table
{
private:
    int bucket_count;                   // number of buckets n (10 in our parser)
    int unique_id;                      // scope number, set by symbol_table
    scope_table *parent_scope = NULL;   // enclosing scope, NULL for the global scope
    symbol_info **table; // array of pointers: table[i] is the head of bucket i's chain

    // Maps a name to a bucket index in the range 0 .. bucket_count-1.
    int hash_function(string name)
    {
        int sum = 0;
        for (int i = 0; i < name.length(); i++)
            sum = sum + name[i];        // add the ASCII value of every character
        int idx = sum % bucket_count; // keep the hash value in the range of the bucket size
        return idx;
    }

public:
    // allocates n buckets for the hash table
    // Every bucket starts empty (NULL). The id is assigned later by symbol_table.
    scope_table(int n)
    {
        bucket_count = n;
        unique_id = 0;
        parent_scope = NULL;
        table = new symbol_info *[bucket_count];
        for (int i = 0; i < bucket_count; i++)
            table[i] = NULL;
    }

    // ---- links between scopes (used by symbol_table) ----
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

    // LOOK UP: search THIS scope only. Symbols are matched by name.
    // Steps: hash the name -> go to that bucket -> walk its chain.
    // Returns the stored symbol, or NULL if the name is not in this scope.
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

    // INSERT: add a symbol to this scope.
    // Returns false if the same name is already declared in THIS scope
    // (a redeclaration), true if it was inserted.
    // The same name in an OUTER scope is allowed: that is shadowing.
    bool insert_in_scope(symbol_info *symbol)
    {
        if (lookup_in_scope(symbol) != NULL)
            return false;

        int idx = hash_function(symbol->get_name());
        symbol->set_next(NULL);         // the new symbol becomes the last node of the chain

        // append at the end of the chain so symbols print in insertion order
        if (table[idx] == NULL)
        {
            table[idx] = symbol;        // empty bucket: the symbol becomes the head
        }
        else
        {
            symbol_info *cur = table[idx];
            while (cur->get_next() != NULL)   // walk to the last node
                cur = cur->get_next();
            cur->set_next(symbol);            // link the new symbol after it
        }
        return true;
    }

    // DELETE: remove a symbol (matched by name) from this scope and free it.
    // `prev` remembers the node before `cur`, so the chain can be re-linked
    // around the removed node. Returns false if the name was not found.
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
                    table[idx] = cur->get_next();       // removing the head: bucket now starts at the 2nd node
                else
                    prev->set_next(cur->get_next());    // removing from the middle/end: skip over cur
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->get_next();
        }
        return false;
    }

    // PRINT: write this scope to the log file in the sample-log format.
    // Empty buckets are skipped; for each non-empty bucket every symbol of its
    // chain is printed with the details that match its kind.
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
                    // function: return type, parameter count and "type name" pairs
                    outlog << "Function Definition" << endl;
                    outlog << "Return Type: " << s->get_data_type() << endl;
                    outlog << "Number of Parameters: " << s->get_param_count() << endl;
                    outlog << "Parameter Details: ";
                    list<string> types = s->get_param_types();
                    list<string> names = s->get_param_names();
                    // walk both lists together: t = type, n = matching name
                    auto t = types.begin();
                    auto n = names.begin();
                    for (; t != types.end(); ++t, ++n)
                    {
                        if (t != types.begin()) outlog << ", ";   // comma between parameters
                        outlog << *t;
                        if (*n != "") outlog << " " << *n;        // unnamed parameter: print the type only
                    }
                    outlog << endl;
                }
                else if (s->array_check())
                {
                    // array: element type and size
                    outlog << "Array" << endl;
                    outlog << "Type: " << s->get_data_type() << endl;
                    outlog << "Size: " << s->get_arr_size() << endl;
                    outlog << endl;
                }
                else
                {
                    // plain variable: data type only
                    outlog << "Variable" << endl;
                    outlog << "Type: " << s->get_data_type() << endl;
                    outlog << endl;
                }
            }
        }
        outlog << endl;
    }

    // DESTRUCTOR: the scope owns its symbols, so when the scope is removed
    // every symbol of every chain is deleted, then the bucket array itself.
    // `nxt` is saved first because `cur` is gone after `delete cur`.
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

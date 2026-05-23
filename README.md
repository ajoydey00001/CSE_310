# CSE 310 Compiler Sessional

This repository contains a set of CSE 310 compiler-construction offline assignments. The work builds up from a scoped symbol table, to lexical analysis, to syntax/semantic analysis, and finally to intermediate code generation and simple assembly optimization for a C-like language.

## Repository Structure

```text
.
|-- offline_1/1905038/
|   |-- 1905038_SymbolTable.cpp
|   |-- input.txt
|   |-- output.txt
|   `-- CSE310_Assignment1_Specification.pdf
|-- Offline_2/
|   `-- 1905038.l
|-- Offline_3/1905038/
|   |-- 1905038.l
|   |-- 1905038.y
|   |-- SymbolInfo_ScopeTable_SymbolTable.cpp
|   `-- CSE310_July_2022_YACC_Assignment_Spec.pdf
`-- offline_4/1905038/
    |-- 1905038.l
    |-- 1905038.y
    |-- SymbolInfo_ScopeTable_SymbolTable.cpp
    |-- icg.cpp
    |-- optimized.cpp
    |-- command.sh
    |-- input.txt
    `-- CSE_310_July_2023_ICG_Spec.docx
```

## Offline 1: Symbol Table

Location: `offline_1/1905038`

This assignment implements a scoped symbol table in C++ using separate chaining hash tables.

Main components:

- `SymbolInfo`: stores a symbol name, symbol type, and linked-list pointer.
- `ScopeTable`: stores one hash table for a single scope.
- `SymbolTable`: manages nested scopes through parent links.

Supported commands include:

- `I name type`: insert a symbol in the current scope.
- `L name`: look up a symbol.
- `D name`: delete a symbol from the current scope.
- `S`: enter a new scope.
- `E`: exit the current scope.
- `P C`: print current scope table.
- `P A`: print all scope tables.
- `Q`: quit.

Build and run:

```bash
cd offline_1/1905038
g++ 1905038_SymbolTable.cpp -o symbol_table
./symbol_table
```

The program reads from `input.txt` and writes to `output.txt` because the source uses `freopen`-style standard input and output redirection.

## Offline 2: Lexical Analyzer

Location: `Offline_2`

This assignment implements a Flex lexical analyzer for a C-like language. It recognizes keywords, identifiers, constants, operators, separators, comments, character literals, and string literals.

Features include:

- Token recognition for keywords such as `if`, `else`, `while`, `for`, `int`, `float`, `void`, `return`, `continue`, and others.
- Integer and floating-point constants.
- Identifier validation and malformed-number detection.
- Single-line and multi-line comments.
- Character and string literal handling with escape sequences.
- Error reporting for unfinished strings, unfinished comments, invalid suffixes, empty character constants, and unrecognized characters.
- Output files for token and log information.

Build and run:

```bash
cd Offline_2
flex 1905038.l
g++ lex.yy.c -lfl -o lexer
./lexer <input-file>
```

Generated outputs include:

- `1905038_log.txt`
- `1905038_token.txt`

## Offline 3: Parser and Semantic Analyzer

Location: `Offline_3/1905038`

This assignment adds a YACC/Bison parser on top of the Flex scanner. It parses a C-like grammar and performs semantic checks using the symbol table.

Main files:

- `1905038.l`: scanner used by the parser.
- `1905038.y`: grammar rules, parser actions, semantic checks, and parse-tree generation.
- `SymbolInfo_ScopeTable_SymbolTable.cpp`: extended symbol table classes used by the parser.

Supported language constructs include:

- Variable and array declarations.
- Function declarations and definitions.
- Parameter lists and argument lists.
- Compound statements and nested scopes.
- `if`, `else`, `for`, `while`, `return`, and `println` statements.
- Assignment, relational, logical, additive, multiplicative, unary, increment, and decrement expressions.

Semantic checks include:

- Multiple declarations and definitions.
- Conflicting function declarations and definitions.
- Parameter count and parameter type mismatches.
- Use of undeclared variables or functions.
- Invalid array usage and array subscript type errors.
- Void usage in expressions.
- Assignment type mismatch warnings/errors.
- Return type mismatches.

Build and run:

```bash
cd Offline_3/1905038
yacc -d -y 1905038.y
g++ -w -c -o y.o y.tab.c
flex 1905038.l
g++ -w -c -o l.o lex.yy.c
g++ y.o l.o -lfl -o parser
./parser <input-file>
```

Generated outputs include:

- `1905038_log.txt`
- `1905038_error.txt`
- `1905038_parsetree.txt`

## Offline 4: Intermediate Code Generation and Optimization

Location: `offline_4/1905038`

This is the most complete compiler-stage assignment in the repository. It combines lexical analysis, parsing, semantic analysis, parse-tree generation, intermediate assembly generation, and simple assembly optimization.

Main files:

- `1905038.l`: Flex scanner.
- `1905038.y`: YACC grammar, semantic analysis, parser driver, and output generation.
- `SymbolInfo_ScopeTable_SymbolTable.cpp`: symbol table and parse-tree metadata classes.
- `icg.cpp`: intermediate code generation from the parse tree.
- `optimized.cpp`: simple optimization pass over generated assembly.
- `command.sh`: helper script to build, run, and clean generated Flex/YACC files.
- `input.txt`: sample C-like input program.

Generated outputs include:

- `1905038_log.txt`: grammar reductions, token logs, scope table information, and totals.
- `1905038_error.txt`: lexical and semantic errors.
- `1905038_parsetree.txt`: formatted parse tree with line ranges.
- `Code.asm`: generated assembly-like code.
- `optimized_code.asm`: optimized assembly-like code.

The optimizer removes or simplifies patterns such as:

- Redundant `MOV AX, x` followed by `MOV x, AX`.
- Redundant `PUSH AX` followed by `POP AX`.
- `PUSH AX` followed by `POP destination`, rewritten as `MOV destination, AX`.
- Arithmetic no-ops such as adding zero, subtracting zero, and multiplying by one.

Build and run with the helper script:

```bash
cd offline_4/1905038
bash command.sh
```

The script currently runs the parser with `input.c`. If you want to use the included `input.txt`, either rename/copy it or run the generated executable manually after building:

```bash
yacc -d -y 1905038.y
g++ -w -c -o y.o y.tab.c
flex 1905038.l
g++ -w -c -o l.o lex.yy.c
g++ y.o l.o -lfl -o compiler
./compiler input.txt
```

## Requirements

Install the following tools before building the assignments:

- `g++`
- `flex`
- `yacc` or `bison` with YACC-compatible mode
- `bash` for `offline_4/1905038/command.sh`

On many Linux systems:

```bash
sudo apt update
sudo apt install g++ flex bison
```

On macOS with Homebrew:

```bash
brew install flex bison
```

## Notes

- Generated files such as `lex.yy.c`, `y.tab.c`, `y.tab.h`, object files, executables, and output logs are build artifacts and can be regenerated.
- The folder names preserve the original assignment structure and student ID directories.
- The later assignments reuse and extend the symbol table from the earlier assignments.
- Source files are written in C++ and use Flex/YACC generated C/C++ code during compilation.

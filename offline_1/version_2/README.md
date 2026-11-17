# Lab 2 – Symbol Table Generation: integration & testing guide

This README explains how to plug the **symbol table** (`symbol_info.h`, `scope_table.h`,
`symbol_table.h`) into the **Lab 1 lex/yacc files** (`.l`, `.y`) and check the output
against the instructor's sample logs.

> Keep this README **outside** the submission folder. The spec only allows the
> `.l`, `.y`, `script.sh`, the three `.h` files and `input.c` in the zip.

---

## 1. Folder layout

```text
version_2/
├── README.md                              ← this file (do NOT submit)
├── Lab2_spec_Symbol table Generation.pdf  ← the spec
├── CSE420 Assignment 2 (All Nesse Files)/ ← instructor starter code
│   └── InputOutput-.../InputOutput/       ← sample input1-3.c and log1-3.txt
└── 23101497_20201178_Group26/             ← submission folder
    ├── symbol_info.h     ← one symbol (variable / array / function) + `next` pointer
    ├── scope_table.h     ← ONE hash table: array of symbol_info* buckets, constructor scope_table(n)
    ├── symbol_table.h    ← stack of scope tables (enter/exit scope, insert, lookup, print)
    ├── 23101497_20201178.l ← lexer  (partner's Lab 1 .l, integrated – section 3)
    ├── 23101497_20201178.y ← parser (partner's Lab 1 .y, integrated – section 4)
    ├── script.sh         ← build + run
    └── input.c           ← test input
```

The three `.h` files are finished and **do not need changes**. Only the `.l` and `.y`
need edits after you get the Lab 1 files.

Key facts about the symbol table:

| Item | Value |
|---|---|
| Bucket count `n` | **10**, set in `main()` of the `.y`: `table = new symbol_table(10);` |
| Hash function | sum of the name's characters `% 10` (matches the sample logs, e.g. `a`→7, `func`→8) |
| Bucket storage | `symbol_info **table` – array of pointers, chained with `symbol_info::next` |

---

## 2. Status: integration done

Sections 3–4 are already applied to `23101497_20201178.l` / `23101497_20201178.y`
(the old `lex_analyzer.l` / `syntax_analyzer.y` working copies, called `.mine` below,
were folded in and deleted). The partner's names are kept: `outlog`, `line_num`,
log file `23101497_20201178_log.txt`. Their `getnameofsymbol()` calls were renamed to
`get_name()`, and the lexer no longer writes `Token <...> found` lines (the sample logs
have none). `script.sh` builds these two files.

---

## 3. Changes to the `.l` (lexer)

The lexer usually needs **little or nothing**. Check these:

1. It includes the header before the parser header:
   ```c
   #include "symbol_info.h"
   #include "y.tab.h"
   ```
2. The line counter name is the same one the `.y` uses (`lines` in the starter code,
   `line_count` in the `.mine` version). The `extern` in the `.l` must match the
   variable defined in the `.y`.
3. `ID`, `CONST_INT`, `CONST_FLOAT`, type keywords (`int`, `float`, `void`) and
   operators return a `symbol_info*` in `yylval` with the matched text as its name.
   The `.y` reads these names to fill the symbol table.

---

## 4. Changes to the `.y` (parser)

### 4.0 Method-name mismatch (check first!)

The starter/Lab 1 code calls **`getname()`**, but our `symbol_info.h` uses
**`get_name()`** (also `get_type()`, `set_name()` …).
If the partner's `.y`/`.l` uses `getname()`, either:
- find & replace `getname(` → `get_name(` (and `gettype(` → `get_type(`) in the `.l`/`.y`, **or**
- add small aliases inside `class symbol_info` in `symbol_info.h`:
  ```cpp
  string getname() { return get_name(); }
  string gettype() { return get_type(); }
  ```

Also note the names the partner uses for the log stream and line counter
(starter: `outlog` and `lines`; `.mine`: `outputlog` and `line_count`). The code
snippets below use `outlog`/`lines` – rename them to whatever the partner's file uses.

### 4.1 Prologue (`%{ ... %}` at the top)

Replace `#include "symbol_info.h"` with `#include "symbol_table.h"`, then add the globals and
helper functions. Copy them from `syntax_analyzer.y.mine` (lines ~13–85):

```cpp
symbol_table *table;

vector<string> var_names;     // names in the current declaration_list
vector<int>    var_sizes;     // array size per name, 0 = not an array
vector<string> param_types;   // params of the current param_list
vector<string> param_names;
vector<string> pending_types; // params waiting to go into the function-body scope
vector<string> pending_names;

void enter_new_scope();       // enter scope, log "New ScopeTable with ID N created", insert pending params
void exit_current_scope();    // print all scopes, exit scope, log "Scopetable with ID N removed"
void insert_function(string return_type, string name);
void insert_variables(string data_type);
```

### 4.2 Grammar-rule changes

| Rule | What to add |
|---|---|
| `start : program` | after logging the rule: `outlog<<"Symbol Table"<<endl<<endl; table->print_all_scopes(outlog);` |
| `func_definition` (both alternatives) | a **mid-rule action** before `compound_statement` that calls `insert_function($1->get_name(), $2->get_name());` (for the no-param version clear `param_types`/`param_names` first). ⚠ This shifts `$N` numbers: `compound_statement` becomes `$7` (with params) / `$6` (without). |
| `param_list` (4 alternatives) | push type (and name, or `""` if unnamed) into `param_types`/`param_names`. The two base alternatives (`type_specifier ID`, `type_specifier`) **clear** the vectors first. |
| `compound_statement` | add an empty rule `enter_scope : { enter_new_scope(); } ;` and use it right after `LCURL`: `LCURL enter_scope statements RCURL` and `LCURL enter_scope RCURL`. Call `exit_current_scope();` at the **end** of both actions. ⚠ `statements` becomes `$3`, `RCURL` becomes `$4`/`$3`. |
| `declaration_list` (4 alternatives) | push name into `var_names` and size into `var_sizes` (`0` for plain, `stoi(CONST_INT text)` for arrays). Base alternatives (`ID`, `ID LTHIRD CONST_INT RTHIRD`) **clear** the vectors first. |
| `variable_decl` | call `insert_variables($1->get_name());` |
| `arguments` | build up the argument list (`add_param`) so the count is known |
| `factor : ID LPAREN argument_list RPAREN` | the sample logs print `argument i type mismatch in function call: <name>` for every argument of a known function – see the `.mine` file (~line 613) |

### 4.3 `main()`

After opening the input and log files, before `yyparse()`:

```cpp
table = new symbol_table(10);   // n = 10 buckets
enter_new_scope();              // global scope = ScopeTable 1
```

After `yyparse()`:

```cpp
outlog<<endl<<"Total lines: "<<lines<<endl;
delete table;
```

### 4.4 Log file name

The spec wants the log named **`<student_id>_log.txt`**. Set it in `main()`
(`outlog.open("<student_id>_log.txt", ios::trunc);`) and use the same name in the
commands below.

---

## 5. Build and run

```bash
cd 23101497_20201178_Group26
bash script.sh input.c
```

`script.sh` runs bison → g++ → flex → g++ → `./parser input.c`.
It fails on any shift/reduce or reduce/reduce conflict, so the grammar must be clean.

Delete generated files before zipping:

```bash
rm -f lex.yy.c y.tab.c y.tab.h y.output *.o parser *_log.txt
```

---

## 6. Check against the sample logs

Run from the `version_2` folder. It builds in a temporary folder (so the submission
folder stays clean), runs all three sample inputs and diffs each log:

```bash
cd offline_1/version_2               # from the root of the CSE_310 repo
G=23101497_20201178_Group26
IO="CSE420 Assignment 2 (All Nesse Files)/InputOutput-20261105T090938Z-1-001/InputOutput"
LOG=23101497_20201178_log.txt
T=$(mktemp -d)
cp $G/*.h $G/*.l $G/*.y "$T"/
( cd "$T" && bison -d -o y.tab.c 23101497_20201178.y && flex 23101497_20201178.l \
           && g++ -w y.tab.c lex.yy.c -o parser ) || echo "BUILD FAILED"
for i in 1 2 3; do
  ( cd "$T" && ./parser "$OLDPWD/$IO/input$i.c" > /dev/null )
  if diff -q --strip-trailing-cr "$T/$LOG" "$IO/log$i.txt" > /dev/null; then
    echo "input$i: IDENTICAL"
  else
    echo "input$i: DIFFERENT"; diff --strip-trailing-cr "$T/$LOG" "$IO/log$i.txt" | head -20
  fi
done
```

### Expected result (current version)

```text
input1: DIFFERENT
609a610
>
input2: IDENTICAL
input3: DIFFERENT
1069a1070
>
```

The only difference in input1/input3 is **one blank line after `Total lines: N`**.
The instructor's samples disagree with each other here (log2 has no blank line,
log1/log3 do), so this is fine. Any **other** diff line means something is wrong.

`--strip-trailing-cr` is needed because the sample logs use Windows line endings (`\r\n`).

### Reading a diff

- `<` lines = your output, `>` lines = expected.
- Missing `New ScopeTable` / `Scopetable ... removed` → `enter_scope` / `exit_current_scope` not wired (4.2).
- Missing parameters inside a function's scope → `insert_function` mid-rule action missing or placed after `compound_statement`.
- Wrong bucket numbers → bucket count is not 10 (4.3).
- Missing `type mismatch` lines → `factor : ID LPAREN argument_list RPAREN` / `arguments` (4.2).
- Garbled function text → `$N` numbers not shifted after adding a mid-rule action / `enter_scope`.

---

## 7. Submission checklist (spec section 5)

- [ ] Folder named with student ID, zipped as `<student_id>.zip`
- [ ] `<student_id>.l`, `<student_id>.y`, `script.sh` (updated to those names)
- [ ] `symbol_info.h`, `scope_table.h`, `symbol_table.h`, `input.c`
- [ ] Log file written as `<student_id>_log.txt`
- [ ] **No** output/log files, `lex.yy.c`, `y.tab.*`, `*.o`, executables, `.mine` backups
- [ ] **No** `.DS_Store` / `__MACOSX` – zip from Linux:
      `zip -r <student_id>.zip <student_id>/ -x '*.DS_Store' '*.mine'`

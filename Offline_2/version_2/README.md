# Version 2: syntax analyzer

This completes the supplied Flex/YACC starter. It follows the previous work's
style from Offline 3: `bits/stdc++.h`, `using namespace std`, a small
`SymbolInfo` class with `get_name()`/`get_type()` and setters,
explicit scanner actions, and grammar actions using `$$`, `$1`, getters,
`new SymbolInfo`, and stream output. The parser uses `%union`, typed tokens/nonterminals, and `yylval.sp`, like
Offline 3. Scanner rules log directly through `outputlog`, and `line_count`
tracks source lines. Each reduction reconstructs its source
fragment and writes it to `my_log.txt`.

## Run

The built `parser` can be run directly from this directory:

```bash
./parser "Sample Input :Output File/input.txt"
cat my_log.txt
```

To rebuild, install Flex, Bison, and g++, then run:

```bash
sudo apt-get install flex bison g++
bash script.sh
bash script.sh "Sample Input :Output File/input1.txt"
bash script.sh "Sample Input :Output File/input2.txt"
```

Each run overwrites `my_log.txt` in this directory. Expected logs in the sample
folder are preserved. The script in that folder delegates to the main script.

## Output conventions

The three supplied input files correspond to `my_log.txt`, `my_log(1).txt`,
and `my_log(2).txt` in the sample folder. Compare text after normalizing Windows
CRLF and Linux LF line endings.

The scanner maps `printf` to `PRINTLN`, brackets to `LTHIRD`/`RTHIRD`, and both
postfix operators to `INCOP`. The parser logs decrement as `variable DECOP`.
To match the supplied reference, decrement does not write a separate token
message. The extra `factor_info : factor` log entry is also preserved.

This assignment performs syntax analysis and source reconstruction; it does
not check declarations/types or generate executable code. Syntax errors and
unrecognized characters are logged. Invalid arguments, missing input files,
and parsing errors return a nonzero exit status.

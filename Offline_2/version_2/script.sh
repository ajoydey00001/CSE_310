#!/bin/bash
set -e
cd -- "$(dirname -- "$0")"

bison -d -o y.tab.c --debug --verbose -Werror=conflicts-sr -Werror=conflicts-rr syntax_analyzer_student_version.y
echo 'Generated the parser C file as well the header file'
g++ -c -o y.o y.tab.c
echo 'Generated the parser object file'
flex lex_analyzer.l
echo 'Generated the scanner C file'
g++ -c -o l.o lex.yy.c
echo 'Generated the scanner object file'
g++ y.o l.o -o parser
echo 'All ready, running'
./parser "${1:-Sample Input :Output File/input.txt}"
echo 'Output written to my_log.txt'

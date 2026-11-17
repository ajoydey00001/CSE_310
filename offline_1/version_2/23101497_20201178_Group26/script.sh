#!/bin/bash
set -e
cd -- "$(dirname -- "$0")"

bison -d -o y.tab.c --debug --verbose -Werror=conflicts-sr -Werror=conflicts-rr 23101497_20201178.y
echo 'Generated the parser C file as well the header file'
g++ -c -o y.o y.tab.c
echo 'Generated the parser object file'
flex 23101497_20201178.l
echo 'Generated the scanner C file'
g++ -c -o l.o lex.yy.c
echo 'Generated the scanner object file'
g++ y.o l.o -o parser
echo 'All ready, running'
./parser "${1:-input.c}"
echo 'Output written to 23101497_20201178_log.txt'

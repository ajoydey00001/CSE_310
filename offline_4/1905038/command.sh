#!/bin/bash

yacc -d -y 1905038.y
echo 'Generated the parser C file as well the header file'
g++ -w -c -o y.o y.tab.c
echo 'Generated the parser object file'
flex 1905038.l
echo 'Generated the scanner C file'
g++ -w -c -o l.o lex.yy.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'
g++ y.o l.o -lfl 
echo 'All ready, running'
./a.out input.c
rm lex.yy.c l.o y.tab.c y.tab.h y.o a.out
echo 'Deleted lex yacc files'
#!/bin/bash

flex lexer.l
bison -d parser.y
gcc -Wall -o calc *.c
rm -f lex.yy.c parser.tab.?
echo Run ./calc for test

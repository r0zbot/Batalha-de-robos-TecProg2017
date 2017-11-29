@echo off
bison -d compila.y
gcc -c compila.tab.c
flex compila.l
gcc -c lex.yy.c
gcc -c symrec.c
gcc -c acertos.c
gcc -c maq.c
gcc -c pilha.c
gcc -c motor.c
gcc -L"C:\MinGW\msys\1.0\lib" compila.tab.o lex.yy.o symrec.o acertos.o maq.o pilha.o motor.o -lfl -lm

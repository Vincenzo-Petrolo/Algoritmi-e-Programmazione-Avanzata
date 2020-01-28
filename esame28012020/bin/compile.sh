#! /bin/bash
gcc -c -g ../Graph.c
gcc -c -g ../Queue.c
gcc -c -g ../ST.c
gcc -c -g ../math.c
gcc -c -g ../main.c

gcc  Graph.o Queue.o ST.o main.o  math.o -o main

#! /bin/bash
gcc -c -g ../lib/best_sol.c
gcc -c -g ../lib/Graph.c
gcc -c -g ../lib/Queue.c
gcc -c -g ../lib/ST.c
gcc -c -g ../lib/math.c
gcc -c -g ../src/main.c

gcc best_sol.o DAG.o Graph.o Queue.o ST.o main.o  math.o -o main

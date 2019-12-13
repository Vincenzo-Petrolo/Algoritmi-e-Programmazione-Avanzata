#!/bin/bash
gcc -c ../src/gdr.c
gcc -c ../lib/equipArray/src/equipArray.c
gcc -c ../lib/inv/src/inv.c
gcc -c ../lib/invArray/src/invArray.c
gcc -c ../lib/pg/src/pg.c
gcc -c ../lib/pgList/src/pgList.c
gcc gdr.o equipArray.o inv.o invArray.o pg.o pgList.o -o main

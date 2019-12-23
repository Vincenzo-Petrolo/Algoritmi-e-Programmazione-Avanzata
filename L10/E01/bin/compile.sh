gcc -c -g ../lib/f_ric/src/f_ric.c
gcc -c -g ../lib/matr4dp/src/matr4dp.c
gcc -c -g ../lib/pietre/src/pietre.c
gcc -c -g ../src/main.c
gcc f_ric.o matr4dp.o pietre.o main.o -o main

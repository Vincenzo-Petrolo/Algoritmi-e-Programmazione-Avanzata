gcc -c -g  ../lib/f_ric/src/f_ric.c
gcc -c -g ../lib/elementi/src/elementi.c
gcc -c -g ../src/main.c
gcc f_ric.o elementi.o main.o -o main

gcc -c -g ../lib/titolo.c
gcc -c -g ../lib/BST.c
gcc -c -g ../lib/data.c
gcc -c -g ../lib/LIST.c
gcc -c -g ../lib/menu.c
gcc -c -g ../lib/ora.c
gcc -c -g ../lib/quotazioni.c
gcc -c -g ../lib/transazioni.c
gcc -c -g ../src/main.c
gcc  BST.o data.o LIST.o menu.o ora.o quotazioni.o titolo.o transazioni.o main.o -o main

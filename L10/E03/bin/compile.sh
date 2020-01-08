gcc -c -g  ../src//f_ric.c
gcc -c -g  ../src/f_app.c
gcc -c -g ../src/elementi.c
gcc -c -g ../src/main.c
gcc f_ric.o elementi.o main.o f_app.o -o main

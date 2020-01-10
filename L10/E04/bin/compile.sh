gcc -c -g ../lib/grafo.c
gcc -c -g ../lib/item.c
gcc -c -g ../lib/lista.c
gcc -c -g ../lib/menu.c
gcc -c -g ../lib/st.c
gcc -c -g ../src/main.c

gcc grafo.o item.o lista.o menu.o st.o main.o -o main

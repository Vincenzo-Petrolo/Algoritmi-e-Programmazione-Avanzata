#include "../include/lista.h"


link new_node(link head,Item dati,int peso){
    link t = (link) malloc(sizeof(struct node));
    t->dati = dati;
    t->peso = peso;
    t->next = head;
    return t;
}

void free_list(link t){
    free(t);
}

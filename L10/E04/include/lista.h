#ifndef __LISTA__H__
#define __LISTA__H__

#include <stdlib.h>

#include "../include/item.h"

typedef struct node *link;

struct node{
    Item dati;
    int peso;
    link next;
};

link new_node(link head,Item dati,int peso);
void free_list(link t);

#endif
#ifndef __ST__H__
#define __ST__H__

#include "../include/item.h"

typedef struct symboltable *ST;


ST      STinit(int maxN);
void    STfree(ST st);

Key     KeyGet(Item val);

int     GetIndex(ST st,Item k);
int     STcount(ST st);
void    STinsert(ST st, Item val);

int     STsearchByKey(ST st, Item k);
Item    STsearchByIndex(ST st, int index);  //dato l'indice ritorna il vertice

void    STdelete(ST st, Item k);


#endif
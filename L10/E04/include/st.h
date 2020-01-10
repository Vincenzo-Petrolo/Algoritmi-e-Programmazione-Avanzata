#ifndef __ST__H__
#define __ST__H__

#include "../include/item.h"

typedef struct symboltable *ST;


ST      STinit(int maxN);
void    STfree(ST st);

void    KeyGet(Item val,Key k);

int     GetIndex(ST st,Key k);
int     STcount(ST st);
void    STinsert(ST st, Item val);
void    STsort(ST st);

int     STsearchByKey(ST st, Key k); //wrapper
Item    STsearchByIndex(ST st, int index);  //dato l'indice ritorna il vertice

void    STdelete(ST st, Key k);


#endif
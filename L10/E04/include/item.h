#ifndef __ITEM__H__
#define __ITEM__H__

#include <string.h>

#include "../include/mytypes.h"

typedef char *Key;


typedef struct Item{
    char id_elaboratore[31];
    char id_rete[31];
}Item;


Item ItemsetNull();
boolean Keycmp(Key k1,Key k2);
void Keycpy(Key k1,Key k2);
void Itemcpy(Item *i1,Item *i2); 



#endif
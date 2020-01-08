#ifndef __ITEM__H__
#define __ITEM__H__

#include <string.h>


typedef char *Key;

typedef enum{FALSE,TRUE} boolean;

typedef struct Item{
    char id_elaboratore[30];
    char id_rete[30];
}Item;


Item ItemsetNull();
boolean Keycmp(Key k1,Key k2);
void Keycpy(Key k1,Key k2);



#endif
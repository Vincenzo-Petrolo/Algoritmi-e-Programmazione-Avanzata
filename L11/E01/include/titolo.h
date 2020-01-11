#ifndef __TITOLO__H__
#define __TITOLO__H__

#include "../include/transazioni.h"
#include "../include/BST.h"

#include <stdlib.h>

typedef struct titolo_t *Titolo;

Titolo  titInit();              /**crea una istanza del titolo azionario*/
void    titFree(Titolo titolo); //libera un istanza del titolo azionario

Titolo  titCarica(Titolo titolo,FILE* fin); //carica su un istanza di un titolo azionario tutti i dati relativi a quel titolo

data_t  titGetData(Titolo titolo);
float   getSommaValoriperQnt(Titolo titolo,data_t giorno);
int     getSommaQnt(Titolo titolo,data_t giorno);
char*   getCodice(Titolo titolo);
BST     getBinSearchTree(Titolo titolo);
#endif

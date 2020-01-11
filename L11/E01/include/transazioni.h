#ifndef __TRANSAZIONI__H__
#define __TRANSAZIONI__H__

#include "../include/mytypes.h"
#include "../include/data.h"
#include "../include/ora.h"

#include <stdio.h>

typedef struct transazioni *Transazione;

Transazione *init(int n);
void        transazioneFree(Transazione transazione);

Transazione load(data_t data,ora_t ora,float valore,int qnt);

Transazione transRead(FILE *fin);
float       getValore(Transazione transazione);
int         getQnt(Transazione transazione);
ora_t       getOra(Transazione transazione);
data_t      getData(Transazione transazione);

#endif
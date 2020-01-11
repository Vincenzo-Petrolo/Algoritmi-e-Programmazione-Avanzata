#include "../include/transazioni.h"
#include <stdlib.h>

struct transazioni{
    data_t  data;
    ora_t   ora;
    float   valore;
    int     qnt;     
};

Transazione *init(int n){
    Transazione *tmp = malloc(n * sizeof(*tmp));
    return tmp;
}

void        transazioneFree(Transazione transazione){
    free(transazione);
}

Transazione load(data_t data,ora_t ora,float valore,int qnt){
    Transazione tmp = malloc(sizeof(*tmp));
    tmp->data   = data;
    tmp->ora    = ora;
    tmp->valore = valore;
    tmp->qnt    = qnt;
    return tmp;
}

Transazione transRead(FILE *fin){
    Transazione tmp;
    tmp->data   =   dataRead(fin);
    tmp->ora    =   oraRead(fin);
    fscanf(fin,"%f %d",&(tmp->valore),&(tmp->qnt));
    return tmp;
}

float       getValore(Transazione transazione){
    return transazione->valore;
}

int         getQnt(Transazione transazione){
    return transazione->qnt;
}

ora_t       getOra(Transazione transazione){
    return transazione->ora;
}

data_t      getData(Transazione transazione){
    return transazione->data;
}

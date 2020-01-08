#include "../include/st.h"

#include <stdlib.h>

struct symboltable{
    Item *vettore;
    int     N;
    int     M;
};


ST STinit(int maxN){
    ST st;
    int i;
    st = (ST) malloc( sizeof(*st));
    st->vettore = (Item*) malloc(maxN*sizeof(Item));
    st->M = maxN;
    st->N = 0;
    for ( i = 0; i < maxN; i++){
        st->vettore[i] = ItemsetNull();
    }
    return st;
}

void STfree(ST st){
    free(st->vettore);
    free(st);
}

int  GetIndex(ST st,Item k){
    int i;
    boolean trovato = FALSE;
    for ( i = 0; i < st->M && !trovato; i++){
        if (Keycmp(k.id_elaboratore,st->vettore[i].id_elaboratore) == 0){
            if (Keycmp(k.id_rete,st->vettore[i].id_rete) == 0)
            trovato = TRUE;
        }
    }

    if (trovato)
        return i;
    return -1;    
}

Key  KeyGet(Item val){
    return val.id_elaboratore;
}


int  STcount(ST st){
    return st->N;
}

void STinsert(ST st, Item val){
    Keycpy(st->vettore[st->N].id_elaboratore,val.id_elaboratore);
    Keycpy(st->vettore[st->N].id_rete,val.id_rete);
    st->N++;
}

int STsearchByKey(ST st, Item k){ //wrapper
    return GetIndex(st,k);
}

Item STsearchByIndex(ST st, int index){
    return st->vettore[index];
}

void STdelete(ST st, Item k){
    st->vettore[STsearchByKey(st,k)] = ItemsetNull();
    st->N--;
}

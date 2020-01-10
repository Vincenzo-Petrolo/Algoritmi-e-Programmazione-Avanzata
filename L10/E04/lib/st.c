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

int  GetIndex(ST st,Key k){
    int i;
    for ( i = 0; i < st->M; i++)
        if (Keycmp(k,st->vettore[i].id_elaboratore) == 0)
            return i;
    return -1;
}

void  KeyGet(Item val,Key k){
    Keycpy(k,val.id_elaboratore);
}


int  STcount(ST st){
    return st->N;
}

void STinsert(ST st, Item val){
    Keycpy(st->vettore[st->N].id_elaboratore,val.id_elaboratore);
    Keycpy(st->vettore[st->N].id_rete,val.id_rete);
    st->N++;
}

void STsort(ST st){  //insertion sort
    Item k;
    int i,j;
    for ( i = 1; i < st->N; i++){
        Itemcpy(&k,&(st->vettore[i]));
        for ( j = i-1; j >= 0 && strcmp(st->vettore[j].id_elaboratore,k.id_elaboratore) > 0; j--){
            Itemcpy(&(st->vettore[j+1]),&(st->vettore[j]));
        }
        Itemcpy(&(st->vettore[j+1]),&k);
    }
}


int STsearchByKey(ST st, Key k){ //wrapper
    return GetIndex(st,k);
}

Item STsearchByIndex(ST st, int index){
    return st->vettore[index];
}

void STdelete(ST st, Key k){
    st->vettore[STsearchByKey(st,k)] = ItemsetNull();
    st->N--;
}

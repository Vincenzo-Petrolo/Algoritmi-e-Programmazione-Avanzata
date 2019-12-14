#include "../include/invArray.h"

typedef struct invArray_s {
    inv_t*  vettInv;
    int     nInv;
    int     maxInv;
}invArray_s;

invArray_t invArray_init() {
    invArray_t inv_Arrtmp   = (invArray_t) malloc(sizeof(invArray_s));
    inv_Arrtmp->nInv        = 0;
    return inv_Arrtmp;
}

void invArray_free(invArray_t invArray) { 
    free(invArray);
}

void invArray_read(FILE *fp, invArray_t invArray) {
    
    fscanf(fp,"%d",&(invArray->nInv));

    invArray->vettInv = (inv_t*) malloc(invArray->nInv* sizeof(inv_t));
    
    for (int i = 0; i < invArray->nInv; i++) {
        inv_read(fp,&(invArray->vettInv[i]));
    }
}

void invArray_print(FILE *fp, invArray_t invArray) { 
    for (int i = 0; i < invArray->nInv; i++) {
        inv_print(fp,&(invArray->vettInv[i]));
    }
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index) {
    inv_print(fp,&(invArray->vettInv[index]));    
}

inv_t *invArray_getByIndex(invArray_t invArray, int index) {
    if (index < invArray->nInv && index != -1)
        return &(invArray->vettInv[index]);
    else
        return NULL;
}

int invArray_searchByName(invArray_t invArray, char *name){
    int i;

    for (i = 0; i < invArray->nInv; i++)
        if (strcmp(invArray->vettInv[i].nome,name) == 0)
            return i;
    return OBJ_NOT_FOUND;
}


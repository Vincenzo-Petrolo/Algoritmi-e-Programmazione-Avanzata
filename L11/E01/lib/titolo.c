#include "../include/titolo.h"

#define MAX_NOME 20

struct titolo_t {
    char            codice[20];
    Transazione     *transazioni;
    BST             quotazioni;
    int             n_quotazioni;
    int             n_transazioni;
};


Titolo  titInit(){     
    
    Titolo tmp      = malloc(sizeof(*tmp));
    tmp->quotazioni = BSTinit();
    return tmp;
}

void titFree(Titolo titolo){
    free(titolo);
}

static float valoreRead(FILE *fin){
    float tmp;
    fscanf(fin,"%f",&tmp);
    return tmp;
}

static int qntRead(FILE *fin){
    int tmp;
    fscanf(fin,"%d",&tmp);
    return tmp;
}

Titolo  titCarica(Titolo titolo,FILE* fin){
    int i;

    fscanf(fin,"%s%d",titolo->codice,&(titolo->n_transazioni));

    titolo->transazioni = init(titolo->n_transazioni);
    data_t  datatmp;
    ora_t   oratmp;
    float   valore;
    int     qnt;
    for ( i = 0; i < titolo->n_transazioni; i++){
        fscanf(fin,"%d/%d/%d %d:%d %f %d",&(datatmp.anno),&(datatmp.mese),&(datatmp.giorno),&(oratmp.h),&(oratmp.min),&valore,&qnt);
        titolo->transazioni[i] = load(datatmp,oratmp,valore,qnt);
    }
    
    quotazioni_t*   ptr;
    quotazioni_t    tmp;

    //inserisco la nuova quotazione se non la trovo, altrimenti ne aggiungo il valore a quella già esistente
    for ( i = 0; i < titolo->n_transazioni; i++){
        ptr = BSTsearch(titolo->quotazioni,getData(titolo->transazioni[i]));
        if ( ptr == NULL ){
            tmp.giorno      = getData(titolo->transazioni[i]);
            tmp.quotazione  = getSommaValoriperQnt(titolo,tmp.giorno)/getSommaQnt(titolo,tmp.giorno);
            BSTinsert_leafR(titolo->quotazioni,tmp);
        }else {
          tmp.giorno        = getData(titolo->transazioni[i]);
          tmp.quotazione    = getSommaValoriperQnt(titolo,tmp.giorno)/getSommaQnt(titolo,tmp.giorno);
          ptr->quotazione   = tmp.quotazione;
        }
    }
    return titolo;
}

float getSommaValoriperQnt(Titolo titolo,data_t giorno){
    int i;
    float somma = 0;
    
    for ( i = 0; i < titolo->n_transazioni; i++){
        if (dataCmp(getData(titolo->transazioni[i]),giorno) == 0){
            somma += getValore(titolo->transazioni[i])*getQnt(titolo->transazioni[i]);
        }
    }
    return somma;
}
int getSommaQnt(Titolo titolo,data_t giorno){
    int i;
    int somma = 0;
    
    for ( i = 0; i < titolo->n_transazioni; i++){
        if (dataCmp(getData(titolo->transazioni[i]),giorno) == 0){
            somma += getQnt(titolo->transazioni[i]);
        }
    }
    return somma;
}

char*   getCodice(Titolo titolo){
    return titolo->codice;
}

BST     getBinSearchTree(Titolo titolo){
    return titolo->quotazioni;
}

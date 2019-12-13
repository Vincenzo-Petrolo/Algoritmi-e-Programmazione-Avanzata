#include "../include/pgList.h"

typedef struct node* link;

struct node {
    pg_t val;
    link next;
};

typedef struct pgList_s{
    link    head;
    int     N;
};

pgList_t pgList_init(){
    pgList_t tmp    = (pgList_t) malloc(sizeof *tmp);
    tmp->N          = 0;
    return tmp;
}

void pgList_free(pgList_t pgList) { 
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList){ 
    link x,p;
    pg_t* tmp;
    while (pg__read(fp,tmp) != EOF) {
        pgList_insert(pgList,*tmp);
    }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;
    for (x = pgList->head; x != NULL; x = x->next){
        pg_print(fp,&(x->val),invArray);
    }
}

void pgList_insert(pgList_t pgList, pg_t pg){
    link x,t;
    for(x = pgList->head; x !=NULL; x = x->next);
    t = (link) malloc ( sizeof (struct node));
    t->next = NULL;
    x->next = t;
}

void pgList_remove(pgList_t pgList, char* cod){
    link x,p;
    for (x= pgList->head->next,p = pgList->head; x != NULL && strcmp(cod,x->val.cod) != 0;p = x,x = x->next);
    p->next = x->next;
    free(x);
}


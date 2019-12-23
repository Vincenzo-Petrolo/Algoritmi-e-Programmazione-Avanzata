#ifndef __PIETRE__H__
#define __PIETRE__H__

#include <stdio.h>

typedef enum{ZAFFIRO,RUBINO,TOPAZIO,SMERALDO} tipo_pietra;

typedef enum{FALSE,TRUE} boolean;

struct pietre_bag {
    int zaffiri;
    int rubini;
    int topazi;
    int smeraldi;
};

void pietre_init(struct pietre_bag* pietre,int zaffiri,int rubini,int topazi,int smeraldi);

int somma_pietre(struct pietre_bag* pietre);
#endif
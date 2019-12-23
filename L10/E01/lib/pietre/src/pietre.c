#include "../include/pietre.h"

int somma_pietre(struct pietre_bag* pietre) {
    return (pietre->rubini+pietre->smeraldi+pietre->zaffiri+pietre->topazi);
}

void pietre_init(struct pietre_bag* pietre,int zaffiri,int rubini,int topazi,int smeraldi){
    pietre->zaffiri     = zaffiri;
    pietre->rubini      = rubini;
    pietre->topazi      = topazi;
    pietre->smeraldi    = smeraldi; 
}

#include "../include/quotazioni.h"

quotazioni_t    quotSetNull(){
    quotazioni_t tmp;
    tmp.quotazione  = -1;
    tmp.giorno.anno = -1; 
    tmp.giorno.mese = -1; 
    tmp.giorno.giorno = -1;
    return tmp; 
}

void quot_display(FILE* fout,quotazioni_t quotazione){
    printf("\nQuotazione: %f",quotazione.quotazione);
}

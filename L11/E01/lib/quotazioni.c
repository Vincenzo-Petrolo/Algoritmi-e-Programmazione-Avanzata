#include "../include/quotazioni.h"

quotazioni_t    quotAdd(quotazioni_t quot,quotazioni_t to_sum){
    quot.quotazione += to_sum.quotazione;
    return quot;
}


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

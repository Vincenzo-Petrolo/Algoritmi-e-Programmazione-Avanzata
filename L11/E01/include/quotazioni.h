#ifndef __QUOTAZIONI__H__
#define __QUOTAZIONI__H__

#include "../include/data.h"

typedef struct quotazioni{
    data_t  giorno;
    float   quotazione;
}quotazioni_t;

quotazioni_t    quotSetNull();
void            quot_display(FILE* fout,quotazioni_t quotazione);
#endif
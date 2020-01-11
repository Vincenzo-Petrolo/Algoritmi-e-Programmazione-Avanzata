#ifndef __QUOTAZIONI__H__
#define __QUOTAZIONI__H__

#include "../include/data.h"

typedef struct quotazioni{
    data_t  giorno;
    float   quotazione;
}quotazioni_t;

quotazioni_t    quotAdd(quotazioni_t quot,quotazioni_t to_sum);
quotazioni_t    quotSetNull();

#endif
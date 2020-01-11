#ifndef __DATA__H__
#define __DATA__H__

#include <stdio.h>

typedef struct data{
    int anno;
    int mese;
    int giorno;
}data_t;

data_t dataRead(FILE *fin);

int dataCmp(data_t data1,data_t data2);
int dataCpy(data_t *data1,data_t *data2);

int dataDisplay(FILE *fout,data_t data);

#endif
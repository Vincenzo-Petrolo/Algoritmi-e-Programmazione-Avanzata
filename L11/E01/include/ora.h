#ifndef __ORA__H__
#define __ORA__H__

#include <stdio.h>

typedef struct ora{
    int h;
    int min;
}ora_t;

ora_t   oraRead(FILE *fin);

int     oraCmp(ora_t ora1,ora_t ora2);
int     oraCpy(ora_t *ora1,ora_t *ora2);
void    oraDisplay(FILE *fout,ora_t ora);

#endif
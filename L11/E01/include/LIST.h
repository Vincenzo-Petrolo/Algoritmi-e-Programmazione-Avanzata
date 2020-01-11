#ifndef __LIST__H__
#define __LIST__H__

#include <stdio.h>

#include "../include/titolo.h"

typedef struct nodo *link;

link list_init();
link list_free(link x);

link crea_lista_titoli(FILE *fin);

#endif
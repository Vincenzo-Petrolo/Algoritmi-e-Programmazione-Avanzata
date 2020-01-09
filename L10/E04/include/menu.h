#ifndef __MENU__H__
#define __MENU__H__

#include <stdio.h>

#define __MAX_S__ 50

typedef enum{FALSE,TRUE} boolean;

typedef enum{	R_MOSTRA,
                R_SOTTOGRAFO,
                R_LISTA,
                R_FINE
			} comando;


void stampa_menu(const char menu_str[][30],int m);

comando leggi_comando(char menu[][30]);


#endif
#ifndef __MENU__H__
#define __MENU__H__

#include <stdio.h>
#include <string.h>

#include "../include/mytypes.h"

#define __MAX_S__ 50


typedef enum{	R_MOSTRA,
                R_SOTTOGRAFO,
                R_LISTA,
                R_FINE
			} comando;


void stampa_menu(const char **menu_str,int m);

comando leggi_comando(const char **menu);


#endif
#ifndef __MENU__H__
#define __MENU__H__

#include <stdio.h>
#include <string.h>

#include "../include/mytypes.h"

#define __MAX_S__ 50


typedef enum{	R_FILE,
                R_RICERCA_TITOLO,
                R_FINE
			} comando1;

typedef enum{	R_QUOTAZIONE,
                R_QUOT_MIN_MAX,
                R_QUOT_MIN_MAX_alltime,
                R_BILANCIO
			} comando2;

void stampa_menu(const char **menu_str,int m);

int leggi_comando(const char **menu,int n);


#endif
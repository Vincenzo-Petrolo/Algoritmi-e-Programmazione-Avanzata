#include "../include/menu.h"

void stampa_menu(const char **menu_str,int m){
    printf("\nMENU");
    for (int i = 0; i <=m; i++) {
        printf("\n>%s",menu_str[i]);
    }
}

comando leggi_comando(const char **menu) {
	comando r_tipo;
	char 	letto[__MAX_S__];
	fflush(stdin);
	printf("\nInserisci cosa vuoi fare: ");
	scanf("%s",letto);

	for ( int i = 0; i <=R_FINE; i++){
		if (strcmp(letto,menu[i]) == 0){
			return i;	//i corrisponde ad un valore della enum dei comandi
		}
	}
	return -1;			//altrimenti torna -1 per indicare il comando non valido

}

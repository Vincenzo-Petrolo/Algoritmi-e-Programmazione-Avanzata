#include "../lib/pg.h"
#include "../lib/inv.h"
#include <stdio.h>
/**Constants*/
const char  menu[][30]	=  		{	
									"pg_upload",
									"pg_add",
									"pg_del",
									"equip_obj",
									"unequip_obj",
									"display",
									"search_pg",
									"search_obj",
									"fine"
};

const char  sottomenu[][30] = 	{	"si",
									"no"
};
/**Constants*/


/**Data structures*/

/**Major Data structures*/
/**Major Data structures*/

/**Minor Data structures*/
typedef enum {	
			FALSE,
			TRUE
}boolean;

typedef enum{
			R_LIST_UP,	
			R_PG_ADD,
			R_PG_DEL,
			R_EQUIP_OBJ,
			R_UNEQUIP_OBJ,
			R_DISPLAY,
			R_SEARCH_PG,
			R_SEARCH_OBJ,
			R_FINE
} comando;

/**Minor Data structures*/


/**Data structures*/

/**Prototypes*/
boolean decisione();
char* leggi_nome_equip(char* nome_oggetto);
char* leggi_nome_file(char* nome_file);
int leggi_codice();

comando leggi_comando(char menu[][30]);
void stampa_menu(const char menu_str[][30],int m);

/**Prototypes*/

/**GLOBAL VARIABLES*/

/**GLOBAL VARIABLES*/


int main(int argc, char *argv[]) {

	/**Variables declaration*/
	char 		nome_oggetto[__MAX_S__]		= {'\0'};
	char 		nome_file[__MAX_S__]		= {'\0'};
	/**Variables declaration*/
	tabPg		tabella_pg;
	tabInv_t 	inventario;
	comando 	comando_letto;

	tabPg*		tabella_pg_ptr 				= tabPg_init(&tabella_pg);
	tabInv_t*	ptr_inv						= tabInv_init(&inventario);
	/**Variables declaration*/

	do {
		stampa_menu(menu,R_FINE);
		comando_letto	= leggi_comando((char (*)[30])menu);
		switch (comando_letto)
		{
			case R_LIST_UP:
				printf("\nVuoi eliminare i personaggi caricati precedentemente?");
				stampa_menu(sottomenu,2);
				if (decisione())
					tabPg_destroy(tabella_pg_ptr);
				carica_pg_file(tabella_pg_ptr,leggi_nome_file(nome_file));
				break;

			case R_PG_ADD:
				carica_pg_stdin(tabella_pg_ptr);
				break;

			case R_PG_DEL:
				delPg(leggi_codice(),tabella_pg_ptr);
				break;

			case R_EQUIP_OBJ:
				add_equip(leggi_codice(),tabella_pg_ptr->headPg,ptr_inv,leggi_nome_equip(nome_oggetto));
				break;

			case R_UNEQUIP_OBJ:
				rm_equip(leggi_codice(),tabella_pg_ptr->headPg,ptr_inv,leggi_nome_equip(nome_oggetto));
				break;

			case R_DISPLAY:
				for (link x = tabella_pg.headPg; x != NULL ; x = x->next) {
					stampa_pg(x->personaggio);
				}
				break;

			case R_SEARCH_PG:
				stampa_dettagli(node_search_cod(tabella_pg.headPg,leggi_codice()));
				break;

			case R_SEARCH_OBJ:
				stampa_oggetto(inv_dic_search(ptr_inv,leggi_nome_equip(nome_oggetto),0,ptr_inv->nInv));
				break;

			case R_FINE:
				printf("\nChiusura...");
				break;

			default:
				printf("\nComando errato!");
				break;
		}
	} while (comando_letto != R_FINE);

	printf("\n");

	return(0);
}


/**Functions*/
boolean
decisione(){
	char risposta[__MAX_S__];
	scanf("%s",risposta);
	if (risposta[0] == 'S' || risposta[0] == 's')
		return TRUE;
	return FALSE;
}

char*
leggi_nome_file(char* nome_file) {
	printf("\nInserisci il nuovo nome del file: ");
	scanf("%s",nome_file);
	return nome_file;
}

char*
leggi_nome_equip(char* nome_oggetto) {
	printf("\nInserisci il nome dell'oggetto: ");
	scanf("%s",nome_oggetto);
	return nome_oggetto;
}

comando
leggi_comando(char menu[][30]) {
	comando r_tipo;
	char 	letto[__MAX_S__];
	printf("\nInserisci cosa vuoi fare: ");
	scanf("%s",letto);

	for ( int i = 0; i <=R_FINE; i++){
		if (strcmp(letto,menu[i]) == 0){
			return i;	//i corrisponde ad un valore della enum dei comandi
		}
	}
	return -1;			//altrimenti torna -1 per indicare il comando non valido
}

int
leggi_codice() {
	int codice;
	printf("\nInserisci il codice del personaggio: ");
	scanf("%d",&codice);
	return codice;
}

void
stampa_menu(const char menu_str[][30],int m){
    printf("\nMENU");
    for (int i = 0; i <=m; i++) {
        printf("\n>%s",menu_str[i]);
    }
}

/**Functions*/

/**Algorithm*/
/**
 *
 *
 *
 *
 *
 *
 *
 *
 *
/**Algorithm*/

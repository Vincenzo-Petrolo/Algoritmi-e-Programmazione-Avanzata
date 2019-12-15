#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**Constants*/
#define __MIN_LUNGHEZZA_COLLANA__	1
#define __N_TIPI_PIETRE__ 		4
/**Constants*/


/**Data structures*/

	/**Minor Data structures*/
	typedef enum{FALSE,TRUE} boolean;

	typedef enum{ZAFFIRO,
				SMERALDO,
				RUBINO,
				TOPAZIO} pietra_t;
	
	/**Minor Data structures*/


	/**Major Data structures*/
	typedef struct{
				int vet[__N_TIPI_PIETRE__]; //0 ZAFFIRI 1 SMERALDI 2 RUBINI 3 TOPAZI
				int vet_presi[__N_TIPI_PIETRE__];
				int *pietre;

	}collana_t;

	/**Major Data structures*/


	typedef struct{	
				int pos; 
				int n;
				int max_lunghezza;

				int *sol;
				int *best_sol; 
				
				collana_t *collana;}wrapper_t;

/**Data structures*/

/**Prototypes*/
void stampa_menu(char menu_str[][30],int m);
void leggi_comando(char *comando);

void aggiungi_pietre(char *decisione,
					collana_t *collana);

void collana_init(collana_t * collana);

void collana_destroy(collana_t* collana);

void collana_display(int* pietre,
					int n);

void disp_ripet(wrapper_t *db);

boolean check(		int *pietre,
					int n,
					collana_t *collana);

/**Prototypes*/

/**GLOBAL VARIABLES*/
/**GLOBAL VARIABLES*/

int 
main(int argc, char *argv[]){

	/**Variables declaration*/
	
	char decisione[200+1];
	char menu[][30] = {"smeraldi",
						"zaffiri",
						"rubini",
						"topazi",
						"calcola"};
	pietra_t tipo_pietra;
	wrapper_t db;
	int somma_pietre = 0;
	
	/**Variables declaration*/
	
	
	stampa_menu(menu,5);
	
	db.max_lunghezza = 0;
	db.collana = (collana_t*) malloc(sizeof(collana_t));
	
	collana_init(db.collana);
	
	do {
	
		leggi_comando(decisione);
		aggiungi_pietre(decisione,db.collana);
	
	}while(strcmp(decisione,"calcola") != 0);
	
	somma_pietre 		+= db.collana->vet[SMERALDO];
	somma_pietre 		+= db.collana->vet[ZAFFIRO];
	somma_pietre 		+= db.collana->vet[RUBINO];
	somma_pietre 		+= db.collana->vet[TOPAZIO];
	

	db.collana->pietre 	= (int*) malloc(somma_pietre*sizeof(int));
	db.sol 				= (int*) malloc(somma_pietre*sizeof(int));
	db.best_sol 		= (int*) malloc(somma_pietre*sizeof(int));
	db.pos 				= 0;
	
	
	disp_ripet(&db);
	collana_display(db.best_sol,db.max_lunghezza);
	free(db.sol);
	//free(db.best_sol);
	free(db.collana->pietre);
	free(db.collana);
	printf("\n");
	
	return(0);
}


/**Functions*/
void 
aggiungi_pietre(char *decisione,
				collana_t *collana){
	
	pietra_t tipo_pietra = -1;
	int n;
	
	if (strcmp("smeraldi",decisione) 	== 0)
			tipo_pietra 		= SMERALDO;
	else if (strcmp("zaffiri",decisione) 	== 0)
			tipo_pietra 		= ZAFFIRO;
	else if (strcmp("rubini",decisione) 	== 0)
			tipo_pietra 		= RUBINO;
	else if (strcmp("topazi",decisione) 	== 0)
			tipo_pietra 		= TOPAZIO;

	switch (tipo_pietra){
		case SMERALDO:
				printf("\nInserisci il numero di Smeraldi da aggiungere: ");
				scanf("%d",&n);
				collana->vet[SMERALDO]		+=n;
				break;
		case ZAFFIRO:
				printf("\nInserisci il numero di Zaffiri da aggiungere: ");
				scanf("%d",&n);
				collana->vet[ZAFFIRO]		+=n;
				break;
		case RUBINO:
				printf("\nInserisci il numero di Rubini da aggiungere: ");
				scanf("%d",&n);
				collana->vet[RUBINO] 		+=n;
				break;
		case TOPAZIO:
				printf("\nInserisci il numero di Topazi da aggiungere: ");
				scanf("%d",&n);
				collana->vet[TOPAZIO]		+=n;
				break;
		default:
			break;
		return;
	}
}

void 
collana_init(collana_t * collana){
	collana->pietre				=  0;
	for (int i = 0; i < __N_TIPI_PIETRE__; i++){
		collana->vet[i] 	  	=  0;
		collana->vet_presi[i] 	=  0;
	}
}

void 
collana_display(int* pietre,
				int n){

	printf("\nCOLLANA:");
	for (int i = 0; i < n; i++){
		switch (pietre[i]){
			case SMERALDO:
				printf(" S");
				break;
			case ZAFFIRO:
				printf(" Z");
				break;
			case RUBINO:
				printf(" R");
				break;
			case TOPAZIO:
				printf(" T");
				break;
			default:
				break;
		}
	}

	printf("\nLUNGHEZZA: %d",n+1);
}


void disp_ripet(wrapper_t *db) {
  	int i;
	
	if (db->pos > (db->max_lunghezza)){
		db->max_lunghezza 				= db->pos;
		for (i = 0; i <= db->pos; i++)
			db->best_sol[i] = db->sol[i];
	}
	if (db->pos > 0){
		for ( i = 0; i < __N_TIPI_PIETRE__; i++){
			if (db->sol[db->pos-1] == ZAFFIRO || db->sol[db->pos-1] == TOPAZIO) {
				if (i == ZAFFIRO || i == RUBINO) {
					if (db->collana->vet[i] -1 >= 0){
						db->sol[db->pos]	= 	i;
						db->pos				+=	1;
						db->collana->vet[i]	-=	1;
						db->collana->vet_presi[i] += 1;
						disp_ripet(db);
						db->pos				-=	1;
						db->collana->vet[i]	-=	1;
						db->collana->vet_presi[i] += 1;
					}
				}
			}
			else {
				if (i == SMERALDO || i == TOPAZIO) {
					if (db->collana->vet[i] -1 >= 0){
						db->sol[db->pos]	= 	i;
						db->pos				+=	1;
						db->collana->vet[i]	-=	1;
						db->collana->vet_presi[i] += 1;
						disp_ripet(db);
						db->pos				-=	1;
						db->collana->vet[i]	-=	1;
						db->collana->vet_presi[i] += 1;
					}
				}
			}
		}
	} 
	else {
		for ( i = 0; i < __N_TIPI_PIETRE__; i++) {
			if (db->collana->vet[i] -1 >= 0) { 
				db->sol[db->pos] 			= i;				 	//i corrisponde anche al tipo di pietra, dato dalla enum
				db->pos						+=1;					//incremento il valore di pos per scendere di livello alla prossima chiamata ricorsiva
				db->collana->vet_presi[i] 	+=1;					//aggiungo alla posizione i-esima del vettore delle gemme prese una unità in corrispondenza della gemma
				db->collana->vet[i]			-=1;					//rimuovo dalle pietre che ho a disposizione quella che ho preso
				disp_ripet(db);										//chiamata ricorsiva
				db->pos						-=1;					//risalgo di livello
				db->collana->vet_presi[i]	-=1;					//sposto la gemma corrispondente al valore di i dalla collana
				db->collana->vet[i]			+=1;
			}
		}
	}
}

void stampa_menu(char menu_str[][30],int m){
    printf("\nMENU");
    for (int i = 0; i < m; i++)
    {
        printf("\n>%s",menu_str[i]);   
    }
}

void leggi_comando(char *comando) {
    printf("\n> ");
    scanf("%s",comando);
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

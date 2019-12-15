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
	
	typedef struct{
				unsigned int val_z;
				unsigned int val_s;
				unsigned int val_r;
				unsigned int val_t;}valori_pietre_t;
	/**Minor Data structures*/


	/**Major Data structures*/
	typedef struct{
				int vet[__N_TIPI_PIETRE__]; //0 ZAFFIRI 1 SMERALDI 2 RUBINI 3 TOPAZI
				int vet_presi[__N_TIPI_PIETRE__];
				int *pietre;
				int max_rip;
				int ultima_pietra;
				int counter;

				valori_pietre_t valori;}collana_t;

	/**Major Data structures*/


	typedef struct{	
				int pos; 
				int n;
				int max_lunghezza;
				int max_valore;
				
				int *val; 
				int *sol;
				int *best_sol; 
				
				collana_t *collana;}wrapper_t;

/**Data structures*/

/**Prototypes*/
void stampa_menu(char menu_str[][30],int m);
void leggi_comando(char *comando);

void aggiungi_pietre(char *decisione,
					collana_t *collana);

void aggiungi_valori(char *decisione,
					collana_t *collana);

void collana_init(collana_t * collana);

void collana_destroy(collana_t* collana);

void collana_display(int* pietre,
					int n,
					int val);

void disp_ripet(wrapper_t *db);

boolean check(		int *pietre,
					int n,
					collana_t *collana);

int calcola_valore(collana_t *collana);

boolean verifica_ripetizioni(wrapper_t* db,
							pietra_t parametro);
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
						"val_s",
						"val_z",
						"val_r",
						"val_t",
						"max_rip",
						"calcola"};
	pietra_t tipo_pietra;
	wrapper_t db;
	int somma_pietre = 0;
	
	/**Variables declaration*/
	
	
	stampa_menu(menu,10);
	
	db.max_lunghezza = 0;
	db.max_valore = 0;
	db.collana = (collana_t*) malloc(sizeof(collana_t));
	
	collana_init(db.collana);
	
	do {
	
		leggi_comando(decisione);
		aggiungi_pietre(decisione,db.collana);
		aggiungi_valori(decisione,db.collana);
	
	}while(strcmp(decisione,"calcola") != 0);

	somma_pietre 		+= db.collana->vet[SMERALDO];
	somma_pietre 		+= db.collana->vet[ZAFFIRO];
	somma_pietre 		+= db.collana->vet[RUBINO];
	somma_pietre 		+= db.collana->vet[TOPAZIO];
	
	db.collana->pietre 	= (int*) malloc(somma_pietre*sizeof(int));
	db.sol 				= (int*) malloc(somma_pietre*sizeof(int));
	db.val 				= (int*) malloc(somma_pietre*sizeof(int));
	db.best_sol 		= (int*) malloc(somma_pietre*sizeof(int));
	db.pos 				= 0;
	
	
	disp_ripet(&db);
	collana_display(db.best_sol,db.max_lunghezza,db.max_valore);
	free(db.sol);free(db.val);free(db.best_sol);free(db.collana);
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
	collana->ultima_pietra    	= -1;
	collana->counter          	=  0;
	for (int i = 0; i < __N_TIPI_PIETRE__; i++){
		collana->vet[i] 	  	=  0;
		collana->vet_presi[i] 	=  0;
	}

}

void 
aggiungi_valori(char *decisione,
				collana_t *collana){

	if (strcmp("val_z",decisione) 			== 0){
			printf("\nInserisci il valore della pietra Zaffiro: ");
			scanf("%u",&(collana->valori.val_z));
	}
	else if (strcmp("val_s",decisione) 		== 0){
			printf("\nInserisci il valore della pietra Smeraldo: ");
			scanf("%u",&(collana->valori.val_s));
	}
	else if (strcmp("val_r",decisione) 		== 0){
			printf("\nInserisci il valore della pietra Rubino: ");
			scanf("%u",&(collana->valori.val_r));
	}
	else if (strcmp("val_t",decisione) 		== 0){
			printf("\nInserisci il valore della pietra Topazio: ");
			scanf("%u",&(collana->valori.val_t));
	}
	else if (strcmp("max_rip",decisione) 	== 0){
			printf("\nInserisci il numero massimo delle ripetizioni per ogni pezzo: ");
			scanf("%d",&(collana->max_rip));
	}
}

boolean 
check(	int *pietre,
		int n,
		collana_t *collana){
	
	for (int i = 0; i < n-1; i++){

		if (pietre[i] == ZAFFIRO){
				if (pietre[i+1] != ZAFFIRO && pietre[i+1] != RUBINO )
						return FALSE;
		}
		else if (pietre[i] == SMERALDO){
				if (pietre[i+1] != SMERALDO && pietre[i+1] != TOPAZIO )
						return FALSE;
		}
		else if (pietre[i] == RUBINO){
				if (pietre[i+1] != SMERALDO && pietre[i+1] != TOPAZIO )
						return FALSE;
		}
		else if (pietre[i] == TOPAZIO){
				if (pietre[i+1] != ZAFFIRO && pietre[i+1] != RUBINO )
						return FALSE;
		}
	}
	return TRUE;
}

void 
collana_display(int* pietre,
				int n,
				int val){

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

	printf("\nMAX VALORE: %d",val);
	printf("\nLUNGHEZZA: %d",n);
}

int 
calcola_valore(collana_t *collana){
	return (collana->vet_presi[ZAFFIRO]*collana->valori.val_z +
			collana->vet_presi[RUBINO]*collana->valori.val_r+
			collana->vet_presi[SMERALDO]*collana->valori.val_s+
			collana->vet_presi[TOPAZIO]*collana->valori.val_t);
}

void disp_ripet(wrapper_t *db) {
  	int i;
	int curr_val;
	curr_val = calcola_valore(db->collana);
	
	if (curr_val >= (db->max_valore) && db->pos >= (db->max_lunghezza)){
		
			if (check(db->sol,db->pos,db->collana)){
			
				if (db->collana->vet_presi[ZAFFIRO] <= db->collana->vet_presi[SMERALDO]){
			
						db->max_lunghezza 				= db->pos;
						db->max_valore 					= curr_val;
			
						for (int i = 0; i < db->pos; i++){
							db->best_sol[i] 			= db->sol[i];
						}
						collana_display(db->best_sol,db->pos,db->max_valore);
				}
			}else return;
	}
	if (db->pos>0){
		for (i = 0; i < __N_TIPI_PIETRE__; i++) {
			if ((db->sol[db->pos-1] == ZAFFIRO || db->sol[db->pos-1] == TOPAZIO)
				&& (i == ZAFFIRO || i == RUBINO)){

				if (verifica_ripetizioni(db,i)){
					db->sol[db->pos] 			= i;				 	//i corrisponde anche al tipo di pietra, dato dalla enum
					db->pos						+=1;					//incremento il valore di pos per scendere di livello alla prossima chiamata ricorsiva
					db->collana->vet_presi[i] 	+=1;					//aggiungo alla posizione i-esima del vettore delle gemme prese una unità in corrispondenza della gemma
					db->collana->vet[i]			-=1;					//rimuovo dalle pietre che ho a disposizione quella che ho preso
					disp_ripet(db);										//chiamata ricorsiva
					db->pos						-=1;					//risalgo di livello
					db->collana->vet_presi[i]	-=1;					//sposto la gemma corrispondente al valore di i dalla collana
					db->collana->vet[i]			+=1;					//nel contenitore in corrispondenza del suo valore
				}
			}
			else {
				if (verifica_ripetizioni(db,i)){
					db->sol[db->pos] 			= i;				 	//i corrisponde anche al tipo di pietra, dato dalla enum
					db->pos						+=1;					//incremento il valore di pos per scendere di livello alla prossima chiamata ricorsiva
					db->collana->vet_presi[i] 	+=1;					//aggiungo alla posizione i-esima del vettore delle gemme prese una unità in corrispondenza della gemma
					db->collana->vet[i]			-=1;					//rimuovo dalle pietre che ho a disposizione quella che ho preso
					disp_ripet(db);										//chiamata ricorsiva
					db->pos						-=1;					//risalgo di livello
					db->collana->vet_presi[i]	-=1;					//sposto la gemma corrispondente al valore di i dalla collana
					db->collana->vet[i]			+=1;					//nel contenitore in corrispondenza del suo valor
				}
			}
		}
	}
	else {
			for ( i = 0; i < __N_TIPI_PIETRE__; i++){
				if (db->collana->vet[i] -1 >= 0){
					db->sol[db->pos] 			= i;				 	//i corrisponde anche al tipo di pietra, dato dalla enum
					db->pos						+=1;					//incremento il valore di pos per scendere di livello alla prossima chiamata ricorsiva
					db->collana->vet_presi[i] 	+=1;					//aggiungo alla posizione i-esima del vettore delle gemme prese una unità in corrispondenza della gemma
					db->collana->vet[i]			-=1;					//rimuovo dalle pietre che ho a disposizione quella che ho preso
					disp_ripet(db);										//chiamata ricorsiva
					db->pos						-=1;					//risalgo di livello
					db->collana->vet_presi[i]	-=1;					//sposto la gemma corrispondente al valore di i dalla collana
					db->collana->vet[i]			+=1;					//nel contenitore in corrispondenza del suo valor
				}
			}
			
		}
}

		
boolean 
verifica_ripetizioni(wrapper_t* db,
					pietra_t parametro){

	if (db->collana->vet[parametro]-1>=0) {
			if (db->collana->ultima_pietra 			!= parametro){
					db->collana->counter			= 0;
					db->collana->ultima_pietra 		= parametro;
			}
			if (db->collana->counter+1				<= db->collana->max_rip){
					db->collana->counter			+=1;
					return TRUE;		
			}else
        return FALSE;
	}
  return FALSE;
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

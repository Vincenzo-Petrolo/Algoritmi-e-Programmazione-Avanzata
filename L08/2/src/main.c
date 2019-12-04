#include <stdio.h>
#include <stdlib.h>

/**Constants*/

#define __NF_TILES__ "tiles.txt"
#define __NF_BOARD__ "board.txt"

/**Constants*/


/**Data structures*/
	
	typedef enum{	ORIZZONTALE,
					VERTICALE
	} rotazione_t;
	
	typedef enum{	FALSE,
					TRUE
	} boolean;
	
	typedef char colori_t;

	typedef struct _sub_tile {
		int			val;

		colori_t	colore;
	
	}sub_tile_t;
	
	/**Major Data structures*/
	typedef struct _tile {
		rotazione_t 	rot;
		
		sub_tile_t 	tile[2];
		
		boolean 	usata;
			
	}tile_t;
	
	typedef struct _board {
		int 		id;

		boolean	 	vuoto;
	
	}board_t;
	

	/**Major Data structures*/

	/**Minor Data structures*/
	/**Minor Data structures*/


/**Data structures*/

/**Prototypes*/
void leggi_scacchiera(	board_t*** 	tiles_m,
						tile_t* 	pool_tasselli,
						int *		R,
						int *		C);


void leggi_pool(		tile_t**	tiles_pool,
						int* 		n);


void disp_sempl(		int 		pos,
						tile_t* 	sacco_tasselli,
						board_t** 	board,
						int* 		max_punteggio,
						board_t** 	best_sol,
						int 		n_tasselli,
						int 		R,
						int 		C);


void best_sol(			board_t** 	tiles_m,
						tile_t* 	tiles_pool);


void display_sol(		board_t** 	best_sol,
						int 		R,
						int 		C);


int valuta_punteggio(	board_t** 	board,
						tile_t* 	pool,
						int 		R,
						int 		C);

void rotate(			tile_t* tile,
						int k);

/**Prototypes*/

/**GLOBAL VARIABLES*/

/**GLOBAL VARIABLES*/


int main(int argc, char *argv[]) {

	/**Variables declaration*/
	board_t **tiles_m;
	tile_t	*tiles_pool;
	/**Variables declaration*/
	
	best_sol(tiles_m,tiles_pool);
	printf("\n");	
	
	return(0);
}


/**Functions*/

void
best_sol(board_t** tiles_m,tile_t* tiles_pool){
	
	int max_punteggio = 0;
	int R;
	int C;
	int n_tasselli;
	board_t** best_sol;
	
	leggi_pool(&tiles_pool,&n_tasselli);
	leggi_scacchiera(&tiles_m,tiles_pool,&R,&C);
	
	best_sol = (board_t**) malloc(R*sizeof(tile_t*));
	
	for (int i = 0; i < R; i++) {
		best_sol[i] = (board_t*) malloc(C*sizeof(tile_t));
	}
	
	disp_sempl(0,tiles_pool,tiles_m,&max_punteggio,best_sol,n_tasselli,R,C);
	display_sol(best_sol,R,C);
	printf("\nPUNTEGGIO: %d",max_punteggio);
}

void
display_sol(board_t** best_sol,int R,int C) {

	for (int i = 0; i < R; i++){
		
		printf("\n[ ");
		
		for (int j = 0; j < C; j++) {
			printf("%d ",best_sol[i][j].id);
		}

		printf("]");
	}
}

void
leggi_pool(tile_t **tiles_pool,int* n) {

	FILE* fp	= fopen(__NF_TILES__,"r");

	if (fp == NULL){
		printf("\nErrore durante l'apertura del file!");
		exit(EXIT_FAILURE);
	}

	fscanf(fp,"%d",n);
	*tiles_pool = (tile_t*) malloc(*n*sizeof(tile_t));
	fgetc(fp);
	for (int i = 0; i < *n; i++) {
	
		fscanf(fp,"%c %d %c %d",	&((*tiles_pool)[i].tile[ORIZZONTALE].colore),
									&((*tiles_pool)[i].tile[ORIZZONTALE].val),
									&((*tiles_pool)[i].tile[VERTICALE].colore),
									&((*tiles_pool)[i].tile[VERTICALE].val));
		fgetc(fp);
		(*tiles_pool)[i].usata	= FALSE;
	}
}

void 
leggi_scacchiera(board_t*** tiles_m,tile_t* pool_tasselli,int* R,int* C) {

	FILE* fp 					= fopen(__NF_BOARD__,"r");

	if (fp == NULL){
		exit(EXIT_FAILURE);
	}

	fscanf(fp,"%d%d",R,C);

	*tiles_m 					= (board_t**) malloc( (*R) * sizeof(*tiles_m));
	
	for (int i = 0; i < (*R); i++) {
		(*tiles_m)[i] 			= (board_t*) malloc((*C) * sizeof(board_t));
	}

	for (int i = 0; i < (*R); i++) {
		
		for (int j = 0; j < (*C); j++) {
		
			fscanf(fp,"%d/",&((*tiles_m)[i][j].id));
			
			if ( (*tiles_m)[i][j].id != -1) {

				(*tiles_m)[i][j].vuoto								= FALSE;
				fscanf(fp,"%d",&(pool_tasselli[ (*tiles_m)[i][j].id ].rot) );	//salvo nella posizione che ho appena letto se non era -1
	
				if ((pool_tasselli[ (*tiles_m)[i][j].id ].rot) == 1)
					rotate(pool_tasselli,(*tiles_m)[i][j].id);						//ruoto il tassello
	
				pool_tasselli[(*tiles_m)[i][j].id].usata			= TRUE;	
			
			}
			else {
			
				(*tiles_m)[i][j].vuoto								= TRUE;
				fscanf(fp,"%d",&((*tiles_m)[i][j].id));														//supero il valore numerico dopo lo /
			}
		}
	}
}

int
valuta_punteggio(board_t** board,tile_t* pool,int R,int C) {
	int risultato			= 0;
	int curr_ris 			= 0;
	int i,j;
	boolean col_eq;
	colori_t colore_iniziale;
	
	/**Calcolo il valore di tutte le righe*/
	
	for (i = 0; i < R; i++) {
		j = 0;
		colore_iniziale 	= pool[ board[i][j].id ].tile[ORIZZONTALE].colore;		//accesso mediante indice
		col_eq 				= TRUE;
		curr_ris 			= 0;
		for (j=0; j < C && col_eq; j++) {
			
			if (colore_iniziale == pool[ board[i][j].id ].tile[ORIZZONTALE].colore) {	
				
				curr_ris 	+= pool[ board[i][j].id ].tile[ORIZZONTALE].val;
			
			}
			else col_eq 	= FALSE;
		
		}
		
		if (col_eq)
			risultato 		+= curr_ris;	
	}

	/**Calcolo il valore di tutte le colonne*/
	for (j = 0; j < C; j++) {
		i = 0;
		colore_iniziale 	= pool[ board[i][j].id ].tile[VERTICALE].colore;
		col_eq 				= TRUE;
		curr_ris			= 0;
		for (i = 0; i < R && col_eq; i++) {
			
			if (colore_iniziale == pool[ board[i][j].id ].tile[VERTICALE].colore) {	
				curr_ris 	+= pool[ board[i][j].id ].tile[VERTICALE].val;
			}
			else col_eq 	= FALSE;
		}

		if (col_eq)
			risultato 		+= curr_ris;	
	}
	
	return risultato;
}

void
disp_sempl(int pos,tile_t* sacco_tasselli,board_t** board,int* max_punteggio,board_t** best_sol, int n_tasselli, int R,int C) {
	int i;
	int j;

	if (pos >= R*C) {	
		int curr_punteggio = valuta_punteggio(board,sacco_tasselli,R,C);
		if (curr_punteggio == 115 ) {
			printf("ciao");
		}
		if ( curr_punteggio > (*max_punteggio) ){
			
			*max_punteggio = curr_punteggio;
			
			for (i = 0; i < R; i++) {
			
				for (j = 0; j < C; j++) {
					best_sol[i][j]	= board[i][j];
				}
			
			}
		}
		return;
	}

	i						= pos/R;
	j						= pos%C;
	
	if (!board[i][j].vuoto){				//Se non vuoto => occupato => ricorro
		disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);
		return;
	}	

	for (int k=0; k<n_tasselli; k++) {
	
		if(sacco_tasselli[k].usata == FALSE){
	
			board[i][j].id				= k;

			board[i][j].vuoto			= FALSE;
			sacco_tasselli[k].usata		= TRUE;

			disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);
	
			rotate(sacco_tasselli,k);														//prima la inserisco normalmente, poi la ruoto

			disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);

			board[i][j].vuoto			= TRUE;
			sacco_tasselli[k].usata		= FALSE;
		}
	}
}

void rotate(tile_t* tile,int k) {
	sub_tile_t tmp;
	tmp 						= tile[k].tile[ORIZZONTALE];
	tile[k].tile[ORIZZONTALE] 	= tile[k].tile[VERTICALE];
	tile[k].tile[VERTICALE] 	= tmp;
}
/**Functions*/

/**Algorithm*/
/**Si tratta di un modello che si adatta al sudoku.
 * usare il modello di disposizioni semplici 
 * L'algoritmo si svolge sulle righe della matrice
 *
 *
/**Algorithm*/

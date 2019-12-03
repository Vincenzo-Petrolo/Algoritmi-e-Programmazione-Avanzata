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
		
		int 		id;
	
	}tile_t;
	
	typedef struct _board {
		tile_t 		tessera;
		
		int	 	vuoto;
	
	}board_t;
	

	/**Major Data structures*/

	/**Minor Data structures*/
	/**Minor Data structures*/


/**Data structures*/

/**Prototypes*/
void leggi_scacchiera(	board_t*** tiles_m,
						tile_t* pool_tasselli,
						int *R,
						int *C);


void leggi_pool(		tile_t **tiles_pool,
						int* n);


void disp_sempl(		int pos,
						tile_t* sacco_tasselli,
						board_t** board,
						int* max_punteggio,
						board_t** best_sol,
						int n_tasselli,
						int R,
						int C);


void best_sol(			board_t** tiles_m,
						tile_t* tiles_pool);


void display_sol(		board_t** best_sol,
						int R,
						int C);


int valuta_punteggio(	board_t** board,
						int R,
						int C);

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

void //it is  wrapper function
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
}

void
display_sol(board_t** best_sol,int R,int C) {

	for (int i = 0; i < R; i++){
		
		printf("\n[ ");
		
		for (int j = 0; j < C; j++) {
			printf("%d ",best_sol[i][j].tessera.id);
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

	for (int i = 0; i < *n; i++) {
	
		fscanf("%c%d%c%d",	&((*tiles_pool)[i].tile[ORIZZONTALE].colore),
							&((*tiles_pool)[i].tile[ORIZZONTALE].val),
							&((*tiles_pool)[i].tile[VERTICALE].colore),
							&((*tiles_pool)[i].tile[VERTICALE].val));
		
		(*tiles_pool)[i].id		= i;
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
		
			fscanf(fp,"%d/",&((*tiles_m)[i][j].tessera.id));
			
			if ( (*tiles_m)[i][j].tessera.id != -1) {

				fscanf(fp,"%d",&pool_tasselli[ (*tiles_m)[i][j].tessera.id ]);	//salvo nella posizione che ho appena letto se non era -1
				pool_tasselli[(*tiles_m)[i][j].tessera.id].usata	= TRUE;
			
			}
			else {
				fgetc(fp);														//supero il valore numerico dopo lo /
			}
		}
	}
}

int
valuta_punteggio(board_t** board,int R,int C) {
	int risultato			= 0;
	int curr_ris 			= 0;
	int i,j;
	boolean col_eq;
	colori_t colore_iniziale;
	
	/**Calcolo il valore di tutte le righe*/
	
	for (i = 0; i < R; i++) {
	
		colore_iniziale 	= board[i][j].tessera.tile[ORIZZONTALE].colore;
		col_eq 				= TRUE;
	
		for (; j < C && col_eq; j++) {
			
			if (colore_iniziale == board[i][j].tessera.tile[ORIZZONTALE].colore) {	
				
				curr_ris 	+= board[i][j].tessera.tile->val;
			
			}
			else col_eq 	= FALSE;
		
		}
		
		if (col_eq)
			risultato 		+= curr_ris;	
	}

	j 						= 0;
	i 						= 0;

	/**Calcolo il valore di tutte le colonne*/
	
	for (j = 0; j < C; j++) {
	
		colore_iniziale 	= board[i][j].tessera.tile[ORIZZONTALE].colore;
		
		col_eq 				= TRUE;
	
		for (; i < R && col_eq; i++) {
			
			if (colore_iniziale == board[i][j].tessera.tile[ORIZZONTALE].colore) {	
				curr_ris 	+= board[i][j].tessera.tile->val;
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
	int i,j;
	
	if (pos >= R*C) {	
		int curr_punteggio = valuta_punteggio(board,R,C);
		
		if ( curr_punteggio > (*max_punteggio) ){
			
			*max_punteggio = curr_punteggio;
			
			for (int i = 0; i < R; i++) {
			
				for (int j = 0; j < C; j++) {
					best_sol[i][j]	= board[i][j];
				}
			
			}
		
		}
		
	}

	i						= R/pos;
	j						= C%pos;
	
	if (board[i][j].vuoto	!= -1){
		disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);
		return;
	}	

	for (int k=0; k<n_tasselli; k++) {
	
		if(sacco_tasselli[k].usata == FALSE){
	
			sacco_tasselli[k].usata		= TRUE;
			board[i][j].tessera			= sacco_tasselli[k];
			board[i][j].vuoto			= k;
			board[i][j].tessera.rot		= ORIZZONTALE;
	
			disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);
	
			board[i][j].tessera.rot		= VERTICALE;
	
			disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);
	
			board[i][j].vuoto			= -1;
			sacco_tasselli[k].usata		= FALSE;
		}
	}
}
/**Functions*/

/**Algorithm*/
/**Si tratta di un modello che si adatta al sudoku.
 * usare il modello di disposizioni semplici 
 * L'algoritmo si svolge sulle righe della matrice
 *
 *
/**Algorithm*/

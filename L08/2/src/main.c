#include <stdio.h>
#include <stdlib.h>
#define __NF_TILES__ "tiles.txt"
#define __NF_BOARD__ "board.txt"

/**Constants*/
/**Constants*/


/**Data structures*/
	typedef enum{ORIZZONTALE,VERTICALE} rotazione_t;
	typedef enum{FALSE,TRUE} boolean;
	typedef enum{A,B,V,N,G,NC} colori_t;

	typedef struct _sub_tile {
		int		val;
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
void leggi_scacchiera(tile_t*** tiles_m,tile_t* pool_tasselli);
int valuta_punteggio(board_t** board,int R,int C);
void disp_sempl(int pos,tile_t* sacco_tasselli,board_t** board,int* max_punteggio,board_t** best_sol, int n_tasselli, int R,int C);
/**Prototypes*/

/**GLOBAL VARIABLES*/

/**GLOBAL VARIABLES*/


int main(int argc, char *argv[]) {

	/**Variables declaration*/
	tile_t **tiles_m;

	/**Variables declaration*/


	return(0);
}


/**Functions*/

void 
leggi_scacchiera(tile_t*** tiles_m,tile_t* pool_tasselli) {
	FILE* fp = fopen(__NF_BOARD__,"r");
	int R,C,tmp;
	if (fp == NULL){
		exit(EXIT_FAILURE);
	}
	fscanf(fp,"%d%d",&R,&C);

	*tiles_m = (tile_t**) malloc(R*sizeof(*tiles_m));
	
	for (int i = 0; i < R; i++) {
		(*tiles_m)[i] 	=  (tile_t*) malloc(C*sizeof(tile_t));
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			fscanf(fp,"%d/%d",&((*tiles_m)[i][j].id),&tmp);
			pool_tasselli[(*tiles_m)[i][j].id].rot	= tmp;
		}
		
	}
	
}

int
valuta_punteggio(board_t** board,int R,int C) {
	int risultato=0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			risultato += board[i][j].tessera.tile->val;
		}	
	}
	return risultato;
}
void
disp_sempl(int pos,tile_t* sacco_tasselli,board_t** board,int* max_punteggio,board_t** best_sol, int n_tasselli, int R,int C) {
	int i,j;
	if (pos >= R*C) {	
		int curr_punteggio = valuta_punteggio(board,R,C);
		if (curr_punteggio>*max_punteggio){
			*max_punteggio = curr_punteggio;
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					best_sol[i][j]	= board[i][j];
				}
			}
		}
		
	}

	i	= R/pos;
	j	= C%pos;
	if (board[i][j].vuoto	!= -1){
		disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);
		return;
	}	

	for (int k=0; k<n_tasselli; k++) {
		if(sacco_tasselli[k].usata == FALSE){
			sacco_tasselli[k].usata		= TRUE;
			board[i][j].tessera		= sacco_tasselli[k];
			board[i][j].vuoto		= k;
			board[i][j].tessera.tile->rot	= ORIZZONTALE;
			disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);
			board[i][j].tessera.tile->rot	= VERTICALE;
			disp_sempl(pos+1,sacco_tasselli,board,max_punteggio,best_sol,n_tasselli, R,C);
			board[i][j].vuoto		= -1;
			sacco_tasselli[k].usata		= FALSE;
		}
	}
}
/**Functions*/

/**Algorithm*/
/**Si tratta di un modello che si adatta al sudoku. Inoltre è necessario
 * usare il modello di disposizioni semplici 
 * L'algoritmo si svolge sulle righe della matrice
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

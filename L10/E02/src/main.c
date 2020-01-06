#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NOMEFILE "elementi.txt"
#define N_DIAGONALI 3
#define MAX_ELEMENTI 5

#define DBG 1

#if DBG
#include "../lib/elementi/include/elementi.h"
#include "../lib/f_ric/include/f_ric.h"
#endif

void disp_ripetute(diag_t *diagonali,diag_t *best_diagonali,elemento_t *vet_elementi,int n_elementi,float *best_val,int DD,int DP,int riga,int colonna);


int main(int argc, char *argv[]) {

	FILE* fp = fopen(NOMEFILE,"r");

	int n_elementi,DD,DP;

	elemento_t* vet_elementi;

	float best_val = 0.0;

	diag_t diagonali[N_DIAGONALI];
	diag_t best_diagonali[N_DIAGONALI];

	for (int i = 0; i < N_DIAGONALI; i++){
		diagonali[i] = diagonale_init();
		best_diagonali[i] = diagonale_init();
	}
	

	printf("Inserisci la DD e la DP: ");
	scanf("%d%d",&DD,&DP);



	fscanf(fp,"%d",&n_elementi);
	vet_elementi = (elemento_t*) malloc(n_elementi * sizeof(elemento_t));


	for (int i = 0; i < n_elementi; i++){
		fscanf(fp,"%s %d %d%d %d%d %f%d",vet_elementi[i].nome,&vet_elementi[i].tipo,&vet_elementi[i].direzione_ingr,&vet_elementi[i].direzione_usc,&vet_elementi[i].precedenza,&vet_elementi[i].successivo,&vet_elementi[i].valore,&vet_elementi[i].diffic);
	}

	disp_ripetute(diagonali,best_diagonali,vet_elementi,n_elementi,&best_val,DD,DP,0,0);

	for (int i = 0; i < N_DIAGONALI; i++){
		printf("\nDIAGONALE %d",i+1);
		diagonale_display(stdout,best_diagonali[i],vet_elementi);
		printf("\nVALORE: %2f",calcola_valore(best_diagonali[i],vet_elementi));
	}
	
	free(vet_elementi);
	printf("\n");
	return(0);
}


void disp_ripetute(diag_t *diagonali,diag_t *best_diagonali,elemento_t *vet_elementi,int n_elementi,float *best_val,int DD,int DP,int riga,int colonna){
	int i = 0;
	int curr_diff;

	if (verifica_condizioni_accettabili(diagonali,N_DIAGONALI,vet_elementi)) {
		float curr_val[N_DIAGONALI] = {0};
		float tot_val = 0;
		int k,j;
	
		for ( j = 0; j < N_DIAGONALI; j++){
			curr_val[j] += calcola_valore(diagonali[j],vet_elementi);
			if (j == N_DIAGONALI - 1){
				if (estrai_difficolta(vet_elementi[diagonali[j].diagonale[diagonali[j].cnt_elementi-1]]) > DIFF_BONUS)
					curr_val[j] *= BONUS;
			}
		}
	
		for ( j = 0; j < N_DIAGONALI; j++){
			tot_val += curr_val[j];
		}

		if (tot_val > *best_val){
			printf("\nbest val: %f",tot_val);
			*best_val = tot_val;
			for ( k = 0; k < N_DIAGONALI; k++){
				best_diagonali[k] = diagonali[k];
				for ( j = 0; j < diagonali[k].cnt_elementi; j++){
					best_diagonali[k].diagonale[j] = diagonali[k].diagonale[j];
				}
			}
		}
	}
	
	for ( i = 0; i < n_elementi; i++){
		if (colonna == 0) {
			if (entrata_frontale(vet_elementi[i])){
		
				diagonali[riga].diagonale[colonna] = i;
				curr_diff = calcola_diffclt(diagonali[riga],vet_elementi); 
				
				if ( curr_diff + estrai_difficolta(vet_elementi[diagonali[riga].diagonale[colonna]]) <= DD && estrai_difficolta(vet_elementi[diagonali[riga].diagonale[colonna]]) <= DP){
					diagonali[riga].cnt_elementi++;
					disp_ripetute(diagonali,best_diagonali,vet_elementi,n_elementi,best_val,DD,DP-estrai_difficolta(vet_elementi[diagonali[riga].diagonale[colonna]]),riga,colonna+1);
					diagonali[riga].cnt_elementi--;
				}else {	//se sono costretto a terminare la diagonale
					if (riga +1 < N_DIAGONALI){
						disp_ripetute(diagonali,best_diagonali,vet_elementi,n_elementi,best_val,DD,DP,riga+1,0);
					}						
				}
			}	
		}
		else {
			diagonali[riga].diagonale[colonna] = i;
			curr_diff = calcola_diffclt(diagonali[riga],vet_elementi); 
		
			if ( curr_diff + estrai_difficolta(vet_elementi[diagonali[riga].diagonale[colonna]]) <= DD && estrai_difficolta(vet_elementi[diagonali[riga].diagonale[colonna]]) <= DP && diagonali[riga].cnt_elementi+1 < MAX_ELEMENTI){
				diagonali[riga].cnt_elementi++;
				disp_ripetute(diagonali,best_diagonali,vet_elementi,n_elementi,best_val,DD,DP-estrai_difficolta(vet_elementi[diagonali[riga].diagonale[colonna]]),riga,colonna+1);
				diagonali[riga].cnt_elementi--;

			}else {
				if (riga +1 < N_DIAGONALI){
					disp_ripetute(diagonali,best_diagonali,vet_elementi,n_elementi,best_val,DD,DP,riga+1,0);
				}	
			}
		}		
	}
}
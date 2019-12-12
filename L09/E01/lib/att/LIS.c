#include <stdio.h>
#include <stdlib.h>
#include "LIS.h"
#define __NOME_FILE__ "att.txt"



void leggi_att(att_wrapper* att_w,att_wrapper* sol){ 
	
	FILE* fp;
	
	if ((fp = fopen(__NOME_FILE__,"r")) == NULL){
		printf("\nErrore in apertura!\n");
		exit(EXIT_SUCCESS);
	}
	
	fscanf(fp,"%d",&(att_w->n));
	att_w->att_ptr = (att_t*) malloc( att_w->n * sizeof *(att_w->att_ptr) );

	for (int i = 0; i < att_w->n; i++) {
		fscanf(fp,"%d%d",&((att_w->att_ptr)[i].inizio),&((att_w->att_ptr)[i].fine));
	}
	fclose(fp);
}



void ordina_att(att_wrapper* att_w) { //algoritmo di ordinamento per ordinarli tutti in base all'inizio
	int i,j,k;
	att_t tmp,min;
	for (i = 0; i < att_w->n; i++) {
		
		min	= att_w->att_ptr[i];
		k = i;

		for (j = i; j < att_w->n; j++) {
			
			if (att_w->att_ptr[j].inizio < min.inizio){
				min = att_w->att_ptr[j];
				k	= j;
			}			
		}
		
		if (k != i){
			tmp = att_w->att_ptr[i];
			att_w->att_ptr[i] = att_w->att_ptr[k];
			att_w->att_ptr[k] = tmp;
		}
	}
	

}

boolean check(att_t att1,att_t att2) {
	/*Date due attività dice se sono compatibili o no*/
	boolean compatibili = TRUE;
	if (att1.inizio < att2.fine && att2.inizio < att1.fine)
		return FALSE;
	return TRUE;
}

int calcola_diff(att_t att){
	return (att.fine - att.inizio);
}

void  LIA_calc(att_wrapper* att){
	int i, j, ris=1, V[att->n], P[att->n], last=1;
	V[0] = calcola_diff(att->att_ptr[0]); P[0] = -1;
	
	for (i=1; i< (att->n); i++) {
		V[i] = calcola_diff(att->att_ptr[i]); P[i] = -1;
		for (j=0; j<i; j++)
			if (check(att->att_ptr[i],att->att_ptr[j]) && (V[i] < V[i] + V[j])) {
				V[i] += V[j];
				P[i] = j;
			}
		if (ris < V[i]) {
			ris = V[i];
			last = i;
		}
	}
	LIA_display(att,P,last);
}

void LIA_display(att_wrapper* att,int* P,int i) {
	if (P[i] == -1) {
		printf("(%d,%d) ",att->att_ptr[i].inizio,att->att_ptr[i].fine);
		return;
	}
	LIA_display(att,P,P[i]);
	printf("(%d,%d) ",att->att_ptr[i].inizio,att->att_ptr[i].fine);
}

void LIA_Calcwr() {
	att_wrapper* att_w;
	leggi_att(att_w);
	ordina_att(att_w);
	LIA_calc(att_w);
	att_wr_destroy(att_w);
}

void att_wr_destroy(att_wrapper* att_w) {
	free(att_w->att_ptr);
}
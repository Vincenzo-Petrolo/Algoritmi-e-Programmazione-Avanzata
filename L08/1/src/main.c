#include <stdio.h>
#include <stdlib.h>
#define __NOME_FILE__ "att.txt"

/**Constants*/
/**Constants*/


/**Data structures*/

	/**Major Data structures*/
	typedef struct _att {
		int s;
		int f;
	}att;
	
	/**Major Data structures*/

	/**Minor Data structures*/
	typedef enum{FALSE,TRUE} boolean;
	/**Minor Data structures*/


/**Data structures*/

/**Prototypes*/
void attSel(int N, att *v);
void powerset_disp_rip(int pos, int *sol, int n,att* vet,int* max_diff,int* best_sol);
boolean check(int* sol,att* vet,int N);
int calcola_diff(att* vet,int N,int* sol);
att* leggi_att(int* N);
void att_display(int* best_sol,att* vet,int N);
/**Prototypes*/

/**GLOBAL VARIABLES*/

/**GLOBAL VARIABLES*/


int main(int argc, char *argv[]) {

	/**Variables declaration*/
	int 	N;
	att* 	vet	= leggi_att(&N);
	/**Variables declaration*/
	attSel(N,vet);

	return(0);
}


/**Functions*/

att* leggi_att(int* N){
	
	FILE* fp;
	att* v;
	
	if ((fp = fopen(__NOME_FILE__,"r")) == NULL){
		printf("\nErrore in apertura!");
		exit(EXIT_SUCCESS);
	}
	
	fscanf(fp,"%d",N);
	
	v = (att*) malloc( *N * sizeof *v );
	
	for (int i = 0; i < *N; i++) {
		fscanf(fp,"%d%d",&(v[i].s),&(v[i].f));
	}
}

void attSel(int N, att *v){
	int sol[N];
	int best_sol[N];
	int max_diff = -1;
	powerset_disp_rip(0,sol,N,v,&max_diff,best_sol);
	att_display(best_sol,v,N);
	printf("\nDIFFERENZA MASSIMA: %d",max_diff);
}

void att_display(int* best_sol,att* vet,int N) {
	printf("\n{ ");
	for (int i = 0; i < N; i++) {
		if (best_sol[i]) {
			printf("{%d,%d} ",vet[i].s,vet[i].f);
		}
	}
	
}

void 
powerset_disp_rip(int pos, int *sol, int n,att* vet,int* max_diff,int* best_sol) {
	int i;
	int curr_diff;
	if (pos >= n) {
		if (check(sol,vet,n)){
			if ((curr_diff = calcola_diff(vet,n,sol)) > *max_diff){
				*max_diff 	= curr_diff;
				for (int i = 0; i < n; i++) {
					best_sol[i] 	= sol[i];
				}
				
			}
		}
		return;
	}

	sol[pos] = 0;
	powerset_disp_rip(pos+1, sol, n,vet,max_diff,best_sol);
	sol[pos] = 1;
	powerset_disp_rip(pos+1, sol, n,vet,max_diff,best_sol);
}

boolean
check(int* sol,att* vet,int N) {
	for (int i = 0; i < N; i++) {

		if (sol[i] 	== 1) {
		
			for (int j = i; j < N; j++) {
		
				if (sol[j] 	== 1){
		
					if (vet[i].s < vet[j].f && vet[j].s < vet[i].f){
		
						return FALSE;
		
					}
				}
			}
		}
	}
	return TRUE;
}

int
calcola_diff(att* vet,int N,int* sol){
	int diff=0;
	for (int i = 0; i < N; i++) {
		if (sol[i] == 1){
			diff		+= (vet[i].f - vet[i].s);
		}
	}
	return diff;
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

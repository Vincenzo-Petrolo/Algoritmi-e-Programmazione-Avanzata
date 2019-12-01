#include <stdio.h>
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
/**Prototypes*/

/**GLOBAL VARIABLES*/

/**GLOBAL VARIABLES*/


int main(int argc, char *argv[]) {

	/**Variables declaration*/

	/**Variables declaration*/


	return(0);
}


/**Functions*/

void 
powerset_disp_rip(int pos, int *val, int *sol, int n, int count,att* vet,int* max_diff) {
	int i;
	int curr_diff;
	if (pos >= n) {
		if (check(sol,vet,n)){
			if ((curr_diff = calcola_diff(vet,n,sol)) > *max_diff){
				*max_diff 	= curr_diff;
			}
		}
		return;
	}

	sol[pos] = 0;
	powerset_disp_rip(pos+1, val, sol, n, count,vet,max_diff);
	sol[pos] = 1;
	powerset_disp_rip(pos+1, val, sol, n, count,vet,max_diff);
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

void attSel(int N, att *v){

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

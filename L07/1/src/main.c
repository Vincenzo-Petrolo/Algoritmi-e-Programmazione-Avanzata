#include <mylibs/menu.h>

/**Constants*/
#define __MIN_LUNGHEZZA_COLLANA__ 1
/**Constants*/


/**Data structures*/

	/**Minor Data structures*/
	typedef enum{ZAFFIRO,SMERALDO,RUBINO,TOPAZIO} pietra_t;
	/**Minor Data structures*/


	/**Major Data structures*/
	typedef struct
	{
		int zaffiri;
		int smeraldi;
		int rubini;
		int topazi;
		int *pietre;
	}collana_t;

	/**Major Data structures*/



/**Data structures*/

/**Prototypes*/
void aggiungi_pietre(char *decisione,collana_t *collana);
void collana_init(collana_t * collana);
void collana_destroy(collana_t* collana);
void collana_display(int* pietre,int n);
void powerset_disp_rip(int pos, int *val, int *sol,int *best_sol, int n,int* max_lunghezza,collana_t *collana);
boolean check(int *pietre,int n);
/**Prototypes*/

/**GLOBAL VARIABLES*/

/**GLOBAL VARIABLES*/


int main(int argc, char *argv[]) {

	/**Variables declaration*/
	char decisione[200+1];
	char menu[][30] = {"smeraldi", "zaffiri","rubini","topazi","calcola"};
	pietra_t tipo_pietra;
	collana_t collana_1;
	int *sol,*val,*best_sol;
	int somma_pietre=0,max_lunghezza=0;
	/**Variables declaration*/
	collana_init(&collana_1);
	stampa_menu(menu,5);
	do {
		leggi_comando(decisione);
		aggiungi_pietre(decisione,&collana_1);
	}while(strcmp(decisione,"calcola") != 0);
	somma_pietre += collana_1.smeraldi;
	somma_pietre += collana_1.zaffiri;
	somma_pietre += collana_1.rubini;
	somma_pietre += collana_1.topazi;
	collana_1.pietre = (int *) malloc(somma_pietre*sizeof(int)); //creo una collana di pietre
	sol = (int*) malloc(somma_pietre*sizeof(int));
	val = (int*) malloc(somma_pietre*sizeof(int));
	best_sol = (int*) malloc(somma_pietre*sizeof(int));
	powerset_disp_rip(0,val,sol,best_sol,somma_pietre,&max_lunghezza,&collana_1);
	collana_display(best_sol,max_lunghezza);
	free(sol);free(val);
	printf("\n");
	return(0);
}


/**Functions*/
void aggiungi_pietre(char *decisione,collana_t *collana){
	pietra_t tipo_pietra = -1;
	int n;
	if (strcmp("smeraldi",decisione) == 0){
		tipo_pietra = SMERALDO;
	}
	else if (strcmp("zaffiri",decisione) == 0){
		tipo_pietra = ZAFFIRO;
	}
	else if (strcmp("rubini",decisione) == 0){
		tipo_pietra = RUBINO;
	}
	else if (strcmp("topazi",decisione) == 0){
		tipo_pietra = TOPAZIO;
	}
	switch (tipo_pietra){
	case SMERALDO:
		printf("\nInserisci il numero di Smeraldi da aggiungere: ");
		scanf("%d",&n);
		collana->smeraldi+=n;
		break;
	case ZAFFIRO:
		printf("\nInserisci il numero di Zaffiri da aggiungere: ");
		scanf("%d",&n);
		collana->zaffiri+=n;
		break;
	case RUBINO:
		printf("\nInserisci il numero di Rubini da aggiungere: ");
		scanf("%d",&n);
		collana->rubini+=n;
		break;
	case TOPAZIO:
		printf("\nInserisci il numero di Topazi da aggiungere: ");
		scanf("%d",&n);
		collana->topazi+=n;
		break;
	default:
		return;
	}
}
void collana_init(collana_t * collana){
	collana->pietre = 0;
	collana->rubini = 0;
	collana->zaffiri = 0;
	collana->smeraldi = 0;
	collana->topazi = 0;
}
void collana_destroy(collana_t* collana){
	free(collana);
}
boolean check(int *pietre,int n){
	for (int i = 0; i < n-1; i++)
	{
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

void collana_display(int* pietre,int n){
	printf("\nCOLLANA:");
	for (int i = 0; i < n; i++)
	{
		switch (pietre[i])
		{
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
	printf("\nMAX LUNGHEZZA: %d",n);
}

void powerset_disp_rip(int pos, int *val, int *sol,int *best_sol, int n,int* max_lunghezza,collana_t *collana) {
  int i;

  if (pos > *max_lunghezza) { //la ricorsione si blocca
	  if (check(sol,pos))
			  *max_lunghezza = pos;
			  for (int i = 0; i < *max_lunghezza; i++)
			  {
				  best_sol[i] = sol[i];
			  }
  	}
  if (pos>0) {
	  switch (sol[pos-1])
	  {
	  case ZAFFIRO:{
		if (collana->zaffiri-1>=0){
		sol[pos] = ZAFFIRO;
		collana->zaffiri-=1; //tolgo uno zaffiro dalla pool
		powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
		collana->zaffiri++; //lo riaggiungio (backtrack)
		}

		if (collana->rubini-1>=0){
			sol[pos] = RUBINO;
			collana->rubini-=1;
			powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
			collana->rubini++;
		}
	  }
		  break;
	  case SMERALDO:{
		if (collana->smeraldi-1>=0){
			sol[pos] = SMERALDO;
			collana->smeraldi-=1;
			powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
			collana->smeraldi++;
		}
		if (collana->topazi-1>=0){
			sol[pos] = TOPAZIO;
			collana->topazi-=1;
			powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
			collana->topazi++;
		}
	  }
		  break;
	  case RUBINO:{
		if (collana->smeraldi-1>=0){
			sol[pos] = SMERALDO;
			collana->smeraldi-=1;
			powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
			collana->smeraldi++;
		}
		if (collana->topazi-1>=0){
			sol[pos] = TOPAZIO;
			collana->topazi-=1;
			powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
			collana->topazi++;
		}
	  }
		  break;
	  case TOPAZIO:{
		if (collana->zaffiri-1>=0){
		sol[pos] = ZAFFIRO;
		collana->zaffiri-=1; //tolgo uno zaffiro dalla pool
		powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
		collana->zaffiri++; //lo riaggiungio (backtrack)
		}

		if (collana->rubini-1>=0){
			sol[pos] = RUBINO;
			collana->rubini-=1;
			powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
			collana->rubini++;
		}
	  }
		  break;
	  
	  default:
		  break;
	  }
  }

  else {
	if (collana->zaffiri-1>=0){
	sol[pos] = ZAFFIRO;
	collana->zaffiri-=1; //tolgo uno zaffiro dalla pool
	powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
	collana->zaffiri++; //lo riaggiungio (backtrack)
	}
	
	if (collana->smeraldi-1>=0){
		sol[pos] = SMERALDO;
		collana->smeraldi-=1;
		powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
		collana->smeraldi++;
	}
	if (collana->rubini-1>=0){
		sol[pos] = RUBINO;
		collana->rubini-=1;
		powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
		collana->rubini++;
	}
	
	if (collana->topazi-1>=0){
		sol[pos] = TOPAZIO;
		collana->topazi-=1;
		powerset_disp_rip(pos+1, val, sol,best_sol, n,max_lunghezza,collana);
		collana->topazi++;
	}
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

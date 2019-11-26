#include <mylibs/includes.h>

/**Constants*/
#define __MAX_S__ 	50+1
#define __MAX_EQUIP__ 	8
/**Constants*/


/**Data structures*/

	/**Major Data structures*/

			
	typedef struct{
		
		unsigned int hp;
		unsigned int mp;
		unsigned int atk;
		unsigned int def;
		unsigned int mag;
		unsigned int spr; }stats_t;
	
	typedef struct{
		int	codice;

		char 	nome	[__MAX_S__];
		char 	classe	[__MAX_S__];

		stats_t stats; }pg_t;
	
	typedef struct nodoPg_t *link;

	struct nodoPg_t{
		
		pg_t	personaggio;
		
		link 	next; };



	typedef struct{
		
		link	headPg;
		link	tailPg;

		int 	nPg; }tabPg;

	

	typedef tabPg* 	tabPg_t;

	typedef struct inv_t{
		char	nome[__MAX_S__];
		char	tipo[__MAX_S__];
		
		stats_t buff;};
	
	
	typedef struct{
		int 	inUso;
		
		struct inv_t*	vettEq; }tabEquip_t;			//puntatore ad un elemento dell'inventario
	


	typedef 	struct{
		struct inv_t 	*vettInv;			//puntatore all'inizio dell'inventario
		
		int 	nInv;
		int 	maxInv; }tabInv;

	typedef tabInv* tabInv_t;
	
	/**Major Data structures*/
	
	/**Minor Data structures*/
	
	/**Minor Data structures*/


/**Data structures*/

/**Prototypes*/
/**Prototypes*/

/**GLOBAL VARIABLES*/

/**GLOBAL VARIABLES*/

//commento
int main(int argc, char *argv[]) {

	/**Variables declaration*/
	char  menu[][30]	=  {"list_up","objs_up","pg_add","pg_del","equip_obj","unequip_obj","stats_calc"};
	tabPg_t tabella_pg;
	tabella_pg->tailPg	= NULL;
	tabella_pg->headPg	= tabella_pg->tailPg;		//la testa punta alla coda in fase di inizializzazione
	tabInv_t ptr_inv	= NULL;
	/**Variables declaration*/
	do
	{
		stampa_menu(menu,7);
	} while (1);
	
	

	printf("\n");
	return(0);
}


/**Functions*/
void 
carica_pg(tabPg_t tab_pg_ptr,char *nome_file){
	FILE* fp 	= fopen(nome_file,"r");
	pg_t  pg_temp;

	while (fscanf(fp,"PG%d%s%s%d%d%d%d%d%d%d",
		pg_temp.codice,
		pg_temp.nome,
		pg_temp.classe,
		pg_temp.stats.hp,
		pg_temp.stats.mp,
		pg_temp.stats.atk,
		pg_temp.stats.def,
		pg_temp.stats.mag,
		pg_temp.stats.spr) != EOF){
		
		newNode(&(tab_pg_ptr->headPg),
			pg_temp,
			&(tab_pg_ptr->headPg->next));	
	
	}
	fclose(fp);
}

void
carica_inventario(tabInv_t ptr_inv,char *nome_file){
	FILE *fp	= fopen(nome_file,"r");
	int    n;
	struct inv_t  inv_tmp;

	fscanf(fp,"%d",&n);		//leggo la dimensione
	
	ptr_inv->vettInv 	= (struct inv_t*) malloc(n * sizeof (struct inv_t));
	ptr_inv->nInv 		= n;
	ptr_inv->maxInv; 		//???????????????????

	for (int i = 0; i < n; i++){
		fscanf(fp,"%s%s%d%d%d%d%d%d",
		inv_tmp.nome,
		inv_tmp.tipo,
		inv_tmp.buff.hp,
		inv_tmp.buff.mp,
		inv_tmp.buff.atk,
		inv_tmp.buff.def,
		inv_tmp.buff.mag,
		inv_tmp.buff.spr);
		
		ptr_inv->vettInv[i] 	= inv_tmp; 
	}
	fclose(fp);
}

void 
newPg (link *head,pg_t val, link next) {
	link x		 = (link) malloc(sizeof *x);
	
	if (x == NULL)
		return;
	
	x->personaggio 	= val;
	x->next 	= next;
	*head		= x;
}

void
delPg (pg_t key_pg, char *nome_pg,tabPg_t tab_pg_ptr) {
	link x		= tab_pg_ptr->headPg;
	link p		= NULL;
	
	if (x == NULL)
		return;
	printf("\nEliminazione...");
	
	for (; x != NULL;p 	= x,
			 x	= x->next){
		if (strncmp(x,nome_pg,strlen(nome_pg)) == 0){
			if (x == tab_pg_ptr->headPg){
				tab_pg_ptr->headPg->next = x->next;
			}
			else {
				p->next		= x->next;
			}
			free(x);
			printf("\nEliminato con successo");
			break;
		}
	}
	if (x == NULL)
		printf("\nPersonaggio non trovato");
}
/**Functions*/

/**Algorithm*/
/**GRUPPI DI STRUTTURE DATI:	> Lista che si occupa di collegare i personaggi
 *				> Vettore di oggetti che rappresenta un inventario
 *
 *
 *
 *
 *
 *
 *
 *
/**Algorithm*/

#include <mylibs/includes.h>

/**Constants*/
#define __MAX_S__ 	50+1
#define __MAX_EQUIP__ 	8
/**Constants*/


/**Data structures*/

	/**Major Data structures*/
	typedef enum{	R_LIST_UP,
			R_OBJS_UP,
			R_PG_ADD,
			R_EQUIP_OBJ,
			R_UNEQUIP_OBJ,
			R_STATS_CAL,
			R_FINE
			} comando;

			
	typedef struct{
		
		unsigned int hp;
		unsigned int mp;
		unsigned int atk;
		unsigned int def;
		unsigned int mag;
		unsigned int spr; }stats_t;
	
	
	typedef struct{
		int 	inUso;
		
		struct inv_t**	vettEq; }tabEquip_t;			//puntatore ad un elemento dell'inventario
	
	typedef struct{
		int	codice;

		char 	nome	[__MAX_S__];
		char 	classe	[__MAX_S__];
		
		tabEquip_t equip[__MAX_EQUIP__];
		
		stats_t stats; }pg_t;
	
	typedef struct nodoPg_t *link;

	struct nodoPg_t{
		
		pg_t	personaggio;
		
		link 	next; };



	typedef struct{
		
		link	headPg;
		link	tailPg;

		int 	nPg; }tabPg;

	

	typedef struct inv_t{
		char	nome[__MAX_S__];
		char	tipo[__MAX_S__];
		
		tabEquip_t* equip;
		
		stats_t	 buff;};
	
	


	typedef 	struct{
		struct inv_t 	*vettInv;			//puntatore all'inizio dell'inventario
		
		int 	nInv;
		int 	maxInv; }tabInv_t;

	
	/**Major Data structures*/
	
	/**Minor Data structures*/
	
	/**Minor Data structures*/


/**Data structures*/

/**Prototypes*/
/**Prototypes*/

/**GLOBAL VARIABLES*/

/**GLOBAL VARIABLES*/


int main(int argc, char *argv[]) {

	/**Variables declaration*/
	const char  menu[][30]	=  {"list_up","objs_up","pg_add","pg_del","equip_obj","unequip_obj","stats_calc"};
	tabPg* tabella_pg 	= tabPg_init();
	tabInv_t* ptr_inv	= tabInv_init();
	comando comando_letto;
	/**Variables declaration*/

	do {
		stampa_menu(menu,7);
		comando_letto	= leggi_comando(menu);
		switch (comando_letto)
		{
		case R_LIST_UP:
			carica_pg_file(&tabella_pg,leggi_nome_file());		
			break;
		case R_OBJS_UP:
			carica_inventario(ptr_inv,leggi_nome_file());
			break;
		case R_PG_ADD:
			carica_pg_stdin(&tabella_pg);
			break;	
		case R_EQUIP_OBJ:
			add_equip(leggi_codice(),tabella_pg,ptr_inv,leggi_nome_equip());
			break;	
		case R_UNEQUIP_OBJ:
			rm_equip(leggi_codice(),tabella_pg,ptr_inv,leggi_nome_equip());
			break;	
		case R_STATS_CAL:
			break;
		case R_FINE:
			printf("\nChiusura...");
			break;
		default:
			printf("\nComando errato!");
			break;
		}
	} while (comando_letto != R_FINE);
	
	printf("\n");
	return(0);
}


/**Functions*/
char* leggi_nome_equip() {
	char nome_oggetto[__MAX_S__];
	printf("\nInserisci il nome dell'oggetto: ");
	scanf("%s",nome_oggetto);
	return nome_oggetto;
}
int
leggi_codice() {
	int codice;
	printf("\nInserisci il codice del personaggio: ");
	scanf("%d",&codice);
	return codice;
}


void carica_pg_stdin(tabPg** tab_pg_ptr) {
	pg_t pg_temp;

	scanf("PG%d%s%s%d%d%d%d%d%d%d",
		pg_temp.codice,
		pg_temp.nome,
		pg_temp.classe,
		pg_temp.stats.hp,
		pg_temp.stats.mp,
		pg_temp.stats.atk,
		pg_temp.stats.def,
		pg_temp.stats.mag,
		pg_temp.stats.spr);

		newNode((*tab_pg_ptr)->headPg,
			pg_temp,
			(*tab_pg_ptr)->headPg->next);
}
void 
carica_pg_file(tabPg** tab_pg_ptr,char *nome_file){
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
		
		newNode((*tab_pg_ptr)->headPg,
			pg_temp,
			(*tab_pg_ptr)->headPg->next);	
	}
	fclose(fp);
}

link 
newNode (link head,pg_t val, link next) {
	link x 		= (link) malloc(sizeof *x);
	if (x == NULL)
		return NULL;
	x->personaggio	= val;
	x->next 	= next;
	return x;
}

tabPg*
tabPg_init() {
	tabPg* tabella_pg;
	tabella_pg->tailPg 	= NULL;
	tabella_pg->headPg 	= tabella_pg->tailPg;
	return tabella_pg;
}

tabInv_t*
tabInv_init() {
	tabInv_t* tab_inv;
	tab_inv 	= NULL;
	return tab_inv;
}

void
carica_inventario(tabInv_t* ptr_inv,char *nome_file){
	FILE *fp	= fopen(nome_file,"r");
	int    n;
	struct inv_t  inv_tmp;

	fscanf(fp,"%d",&n);		//leggo la dimensione
	
	ptr_inv->vettInv 	= (struct inv_t*) malloc(n * sizeof (struct inv_t));
	ptr_inv->nInv 		= n;

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
	sortInv_byname(ptr_inv);	//ordino l'inventario per nome
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
delPg (pg_t key_pg,int codice_pg,tabPg* tab_pg_ptr) {
	link x		= tab_pg_ptr->headPg;
	link p		= NULL;
	
	if (x == NULL)
		return;
	printf("\nEliminazione...");
	
	for (; x != NULL;p 	= x,
			 x	= x->next){
		if (codice_pg == x->personaggio.codice){
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

link
node_search_cod(link head,int codice_pg) {
	link x;
	for (	x = head;
		x != NULL
		&& x->personaggio.codice != codice_pg;
		x = x->next);
	return x;
}

struct inv_t*
inv_dic_search(tabInv_t* tabInv,char *nome_oggetto,int l,int r) {
	int m		= (r-l)/2;
	int risultato = strncmp(nome_oggetto,
				tabInv->vettInv[m].nome,
				strlen(tabInv->vettInv[m].nome));

	if (m < 0)
		return;
	if 	( risultato > 0)
		inv_dic_search(tabInv,nome_oggetto,m+1,r);
	else if (risultato < 0)
		inv_dic_search(tabInv,nome_oggetto,l,m-1);
	else if (risultato == 0) {
		return &(tabInv->vettInv[m]);
	}
}

void
sortInv_byname(tabInv_t* tabInv) {
	int i, j, l 		= 0; 
	int r 			= tabInv->nInv - 1;
	struct inv_t x;		
	for (i = l + 1; i <= r; i++) {
		x 		= tabInv->vettInv[i];
		j 		= i - 1;
		while (j >= l && strcmp(x.nome,tabInv->vettInv[j].nome) < 0) {
			
			tabInv->vettInv[j + 1] = tabInv->vettInv[j];
			j	-=1;
		
		}
		tabInv->vettInv[j + 1] 		= x;
	}
}

void
add_equip(int codice_pg,link head,tabInv_t* inventario,char *nome_equip) {
	link nodo_pg		= node_search_cod(head,codice_pg);
	if (nodo_pg->personaggio.equip->inUso <__MAX_EQUIP__) { 
		struct inv_t* oggetto	= inv_dic_search(inventario,
							nome_equip,
							0,
							inventario->nInv);
		nodo_pg->personaggio.equip->inUso	+= 1;
		nodo_pg->personaggio.equip->vettEq[nodo_pg->personaggio.equip->inUso] = oggetto; 
	}
}

void
rm_equip(int codice_pg,link head,tabInv_t* inventario,char *nome_equip) {
	link nodo_pg		= node_search_cod(head,codice_pg);
	for (int i = 0;i < nodo_pg->personaggio.equip->inUso && 
			strcmp(nodo_pg->personaggio.equip->vettEq[i]->nome,nome_equip) != 0; i++){
				nodo_pg->personaggio.equip->vettEq[i] = NULL;
	}
}

comando
leggi_comando(char menu[][30]) {
	comando r_tipo;
	char 	letto[__MAX_S__];
	
	printf("\nInserisci cosa vuoi fare: ");
	scanf("%s",letto);
	
	for ( int i = 0; i < R_FINE; i++){
		if (strcmp(letto,menu[i]) == 0){
			return i;	//i corrisponde ad un valore della enum dei comandi
		}
	}
	return -1;			//altrimenti torna -1 per indicare il comando non valido
	

}

char* leggi_nome_file() {
	char nome_file[__MAX_S__];
	printf("\nInserisci il nuovo nome del file: ");
	scanf("%s",nome_file);
	return nome_file;
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

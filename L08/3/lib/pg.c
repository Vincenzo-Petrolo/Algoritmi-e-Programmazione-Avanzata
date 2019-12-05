#include "pg.h"


tabPg*
tabPg_init(tabPg* tabella_pg_ptr) {
	tabella_pg_ptr->tailPg 		= NULL;
	tabella_pg_ptr->nPg		= 0;
	tabella_pg_ptr->headPg 		= tabella_pg_ptr->tailPg;
	return tabella_pg_ptr;
}

void
tabPg_destroy(tabPg *tabella_pg) {
	link x,p;
	if (tabella_pg->headPg == NULL)
		return;
	for (x = tabella_pg->headPg->next,p=tabella_pg->headPg;x != NULL;p=x,x = x->next) {
		free(p->personaggio.equip);
		free(p);
	}
	
}

link
newNode (pg_t val, link next) {
	link x 		= (link) malloc(sizeof *x);
	if (x == NULL)
		return NULL;
	x->personaggio	= val;
	x->next 	= next;
	return x;
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

link 
insHead(link head,pg_t val) {
	head = newNode(val,head);
}

void
stampa_pg(pg_t pg){
	printf("PG%d %s %s %d %d %d %d %d %d\n",
						pg.codice,
						pg.nome,
						pg.classe,
						pg.stats.hp,
						pg.stats.mp,
						pg.stats.atk,
						pg.stats.def,
						pg.stats.mag,
						pg.stats.spr);
}


void
carica_pg_file(tabPg* tab_pg_ptr,char *nome_file){
	FILE* fp = fopen(nome_file,"r");
	pg_t  pg_temp;

	while (fscanf(fp,"PG%d%s%s%d%d%d%d%d%d",&(pg_temp.codice),
						pg_temp.nome,
						pg_temp.classe,
						&(pg_temp.stats.hp),
						&(pg_temp.stats.mp),
						&(pg_temp.stats.atk),
						&(pg_temp.stats.def),
						&(pg_temp.stats.mag),
						&(pg_temp.stats.spr)) != EOF){
		fgetc(fp);
		pg_temp.equip		= (tabEquip_t*) malloc(sizeof(tabEquip_t));
		pg_temp.equip->inUso 	= 0;																																	//to trigger the '\n' character
		tab_pg_ptr->headPg 	= insHead(tab_pg_ptr->headPg,pg_temp);
		stampa_pg(pg_temp);
		tab_pg_ptr->nPg		+= 1;
	}
	fclose(fp);
}

void
carica_pg_stdin(tabPg* tab_pg_ptr) {
	pg_t pg_temp;
	printf("\nInserisci il personaggio a mano: ");
	scanf(" PG%d%s%s%d%d%d%d%d%d",
		&(pg_temp.codice),
		pg_temp.nome,
		pg_temp.classe,
		&(pg_temp.stats.hp),
		&(pg_temp.stats.mp),
		&(pg_temp.stats.atk),
		&(pg_temp.stats.def),
		&(pg_temp.stats.mag),
		&(pg_temp.stats.spr));
		pg_temp.equip		= (tabEquip_t*) malloc(sizeof(tabEquip_t));
		pg_temp.equip->inUso	= 0;
		tab_pg_ptr->headPg 	= insHead(tab_pg_ptr->headPg,pg_temp);
		tab_pg_ptr->nPg		+= 1;
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
delPg (int codice_pg,tabPg* tab_pg_ptr) {
	link x		= tab_pg_ptr->headPg;
	link p		= NULL;

	if (x == NULL)
		return;
	printf("\nEliminazione...");
	for (;x != NULL;p=x,x = x->next) {
		if (codice_pg == x->personaggio.codice){
			if (x == tab_pg_ptr->headPg){
				tab_pg_ptr->headPg->next = x->next;
			}
			else {
				p->next			= x->next;
			}
			printf("\nEliminato con successo\n");
			tab_pg_ptr->nPg			-= 1;
			free(x->personaggio.equip);
			free(x);
			break;
		}
	}
}

void
add_equip(int codice_pg,link head,tabInv_t* inventario,char *nome_equip) {
	link nodo_pg		= node_search_cod(head,codice_pg);
	
	if (nodo_pg 		== NULL) return;

	if (nodo_pg->personaggio.equip->inUso <__MAX_EQUIP__) {
		struct inv_t* oggetto	= inv_dic_search(inventario,
							nome_equip,
							0,
							inventario->nInv);
		nodo_pg->personaggio.equip->vettEq[nodo_pg->personaggio.equip->inUso] = oggetto;
		nodo_pg->personaggio.equip->inUso				      += 1;

		if (nodo_pg->personaggio.stats.hp + oggetto->buff.hp  < 1) {
			nodo_pg->personaggio.stats.hp 		= 1;
		} else nodo_pg->personaggio.stats.hp 		+= oggetto->buff.hp;
		
		if (nodo_pg->personaggio.stats.mp + oggetto->buff.mp  < 1) {
			nodo_pg->personaggio.stats.mp 		= 1;
		} else nodo_pg->personaggio.stats.mp 		+= oggetto->buff.mp;
		
		if (nodo_pg->personaggio.stats.atk + oggetto->buff.atk  < 1) {
			nodo_pg->personaggio.stats.atk 		= 1;
		} else nodo_pg->personaggio.stats.atk 		+= oggetto->buff.atk;
		
		if (nodo_pg->personaggio.stats.def + oggetto->buff.def  < 1) {
			nodo_pg->personaggio.stats.def 		= 1;
		} else nodo_pg->personaggio.stats.def 		+= oggetto->buff.def;
		
		if (nodo_pg->personaggio.stats.mag + oggetto->buff.mag  < 1) {
			nodo_pg->personaggio.stats.mag 		= 1;
		} else nodo_pg->personaggio.stats.mag 		+= oggetto->buff.mag;
		
		if (nodo_pg->personaggio.stats.spr + oggetto->buff.spr  < 1) {
			nodo_pg->personaggio.stats.spr 		= 1;
		} else nodo_pg->personaggio.stats.spr 		+= oggetto->buff.spr;
	}
}

void
rm_equip(int codice_pg,link head,tabInv_t* inventario,char *nome_equip) {
	link nodo_pg		= node_search_cod(head,codice_pg);
	if (nodo_pg 		== NULL) return;

	for (	int i = 0; i < nodo_pg->personaggio.equip->inUso; i++){

			if (strcmp(nodo_pg->personaggio.equip->vettEq[i]->nome,nome_equip) == 0){
		
				struct inv_t* oggetto = nodo_pg->personaggio.equip->vettEq[i];		
		
				if (nodo_pg->personaggio.stats.hp - oggetto->buff.hp  < 1) {
					nodo_pg->personaggio.stats.hp 		= 1;
				} else nodo_pg->personaggio.stats.hp 		-= oggetto->buff.hp;
				
				if (nodo_pg->personaggio.stats.mp - oggetto->buff.mp  < 1) {
					nodo_pg->personaggio.stats.mp 		= 1;
				} else nodo_pg->personaggio.stats.mp 		-= oggetto->buff.mp;
				
				if (nodo_pg->personaggio.stats.atk - oggetto->buff.atk  < 1) {
					nodo_pg->personaggio.stats.atk 		= 1;
				} else nodo_pg->personaggio.stats.atk 		-= oggetto->buff.atk;
				
				if (nodo_pg->personaggio.stats.def - oggetto->buff.def  < 1) {
					nodo_pg->personaggio.stats.def 		= 1;
				} else nodo_pg->personaggio.stats.def 		-= oggetto->buff.def;
				
				if (nodo_pg->personaggio.stats.mag - oggetto->buff.mag  < 1) {
					nodo_pg->personaggio.stats.mag 		= 1;
				} else nodo_pg->personaggio.stats.mag 		-= oggetto->buff.mag;
				
				if (nodo_pg->personaggio.stats.spr - oggetto->buff.spr  < 1) {
					nodo_pg->personaggio.stats.spr 		= 1;
				} else nodo_pg->personaggio.stats.spr 		-= oggetto->buff.spr;


				shift_vet(nodo_pg->personaggio.equip->vettEq,i); 			//shift per evitare buchi nel vettore
				nodo_pg->personaggio.equip->inUso		-= 1;
				break;
			}
	}

}



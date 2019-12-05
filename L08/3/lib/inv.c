#include "inv.h"

tabInv_t*
tabInv_init(tabInv_t* tab_inv) {
	tab_inv->vettInv 	= NULL;
	tab_inv->nInv		= 0;
	return tab_inv;
}


void
inv_destroy(struct inv_t* vett_inventario) {
	if (vett_inventario == NULL){
		printf("\nInventario vuoto!");
		return;
	}
	free(vett_inventario);
}

void shift_vet(struct inv_t** vet,int n) {
	for (int i = n; i < __MAX_EQUIP__-1; i++) {
		vet[i] = vet[i+1];
	}	
}

void
carica_inventario(tabInv_t* ptr_inv,char *nome_file){
	FILE *fp		= fopen(nome_file,"r");
	int    n;
	struct inv_t  inv_tmp;

	fscanf(fp,"%d",&n);		//leggo la dimensione

	ptr_inv->vettInv 	= (struct inv_t*) malloc(n * sizeof (struct inv_t));
	ptr_inv->nInv 		= n;

	for (int i = 0; i < n; i++){
		fscanf(fp,"%s%s%d%d%d%d%d%d",
		inv_tmp.nome,
		inv_tmp.tipo,
		&(inv_tmp.buff.hp),
		&(inv_tmp.buff.mp),
		&(inv_tmp.buff.atk),
		&(inv_tmp.buff.def),
		&(inv_tmp.buff.mag),
		&(inv_tmp.buff.spr));

		ptr_inv->vettInv[i] 	= inv_tmp;
	}
	fclose(fp);
	sortInv_byname(ptr_inv);	//ordino l'inventario per nome
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

			tabInv->vettInv[j + 1]	= tabInv->vettInv[j];
			j	-=1;

		}
		tabInv->vettInv[j + 1] 		= x;
	}
}

struct inv_t*
inv_dic_search(tabInv_t* tabInv,char *nome_oggetto,int l,int r) {
	if (l>r)
		return NULL;
	int m		= (r+l)/2;
	int risultato 	= strncmp(nome_oggetto,
				tabInv->vettInv[m].nome,
				strlen(tabInv->vettInv[m].nome));

	if 	( risultato 	> 0)
		inv_dic_search(tabInv,nome_oggetto,m+1,r);
	else if (risultato 	< 0)
		inv_dic_search(tabInv,nome_oggetto,l,m-1);
	else if (risultato 	== 0) {
		return &(tabInv->vettInv[m]);
	}
}

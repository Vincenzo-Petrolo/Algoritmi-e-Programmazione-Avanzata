#ifndef __PG_H__
#define __PG_H__
#include "inv.h"

	typedef struct{
		int	        codice;

		char 	    nome	[__MAX_S__];
		char 	    classe	[__MAX_S__];

		tabEquip_t* equip;

		stats_t     stats; 
    }pg_t;

	typedef struct nodoPg_t *link;

    struct nodoPg_t{

		pg_t	personaggio;

		link 	next; 
    };

    typedef struct{

		link	headPg;
		link	tailPg;

		int 	nPg; 
    
    }tabPg;


/**Prototypes*/
tabPg*  tabPg_init(tabPg* tabella_pg);
void    tabPg_destroy(tabPg* tabella_pg);


link    newNode (       pg_t val,
                        link next);

link    node_search_cod(link head,
                        int codice_pg);

link    insHead(        link head,
                        pg_t val);

void stampa_pg(         pg_t pg);

void carica_pg_file(    tabPg* tab_pg_ptr,
                        char *nome_file);

void carica_pg_stdin(   tabPg* tab_pg_ptr);

void  newPg (           link *head,
                        pg_t val,
                        link next);

void delPg (            int codice_pg,
                        tabPg* tab_pg_ptr);

void add_equip(         int codice_pg,
                        link head,
                        tabInv_t* inventario,
                        char *nome_equip);

void rm_equip(          int codice_pg,
                        link head,
                        tabInv_t* inventario,
                        char *nome_equip);

void stampa_dettagli(   link node_pg);
/**Prototypes*/


#endif
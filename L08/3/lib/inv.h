#ifndef INVENTARIO_H
#define INVENTARIO_H
#define __MAX_S__ 50+1
#define __MAX_EQUIP__ 8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct{

      int hp;
      int mp;
      int atk;
      int def;
      int mag;
      int spr;

    }stats_t;						        //statistiche di un pg o un oggetto

	typedef struct{

  		int 	inUso;

		  struct inv_t*	vettEq[__MAX_EQUIP__]; 
 
    }tabEquip_t;			                //puntatore ad un elemento dell'inventario

    typedef struct inv_t{

      char	nome[__MAX_S__];
      char	tipo[__MAX_S__];

      stats_t		buff;

    }inv_p;

    typedef 	struct{
		
      struct inv_t 	*vettInv;			//puntatore all'inizio dell'inventario

      int 	        nInv;
      int 	        maxInv; 

    }tabInv_t;

    /*Prototypes*/
    /*Costruttore && Distruttore*/    
    tabInv_t*       tabInv_init(        tabInv_t* tabella_inventario);
    void            inv_destroy(        struct inv_t * vett_inventario);
    /*Costruttore && Distruttore*/    
    
    void            shift_vet(          struct inv_t** vet,
                                        int n);

    void            carica_inventario(  tabInv_t* ptr_inv,
                                        char *nome_file);

    void            sortInv_byname(     tabInv_t* tabInv);

    struct inv_t*   inv_dic_search(     tabInv_t* tabInv,
                                        char *nome_oggetto,
                                        int l,
                                        int r);

    /*Prototypes*/



#endif
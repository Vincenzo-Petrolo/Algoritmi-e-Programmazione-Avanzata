#include "../include/pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    pgp->equip  = equipArray_init();
    return fscanf(fp,"%s%s%s%d%d%d%d%d%d",  pgp->cod,
                                            pgp->nome,
                                            pgp->classe,
                                            &(pgp->b_stat.hp),
                                            &(pgp->b_stat.mp),
                                            &(pgp->b_stat.atk),
                                            &(pgp->b_stat.def),
                                            &(pgp->b_stat.mag),
                                            &(pgp->b_stat.spr));
}

void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    stat_t tmp;
    inv_t* tmp1;
    tmp.hp  = pgp->b_stat.hp;
    tmp.mp  = pgp->b_stat.mp;
    tmp.atk  = pgp->b_stat.atk;
    tmp.def  = pgp->b_stat.def;
    tmp.mag  = pgp->b_stat.mag;
    tmp.spr  = pgp->b_stat.spr;

    for (int i = 0; i < EQUIP_SLOT; i++) {
        if ((tmp1 = invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip,i))) != NULL){
            tmp.hp += tmp1->stat.hp;
            tmp.mp += tmp1->stat.mp;
            tmp.atk += tmp1->stat.atk;
            tmp.def += tmp1->stat.def;
            tmp.mag += tmp1->stat.mag;
            tmp.spr += tmp1->stat.spr;
        }
    }
    
    fprintf(fp,"\nCODICE: %s NOME: %s CLASSE: %s",  pgp->cod,
                                                    pgp->nome,
                                                    pgp->classe);
    stat_print(fp,&tmp,1);
    fprintf(fp,"\nEQUIPAGGIAMENTO: ");
    equipArray_print(fp,pgp->equip,invArray);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip,invArray);
}
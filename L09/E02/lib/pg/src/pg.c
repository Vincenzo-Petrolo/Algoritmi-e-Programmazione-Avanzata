#include "../include/pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    pgp->equip  = equipArray_init();
    return fscanf(fp,"%s%s%s%d%d%d%d%d%d",  pgp->cod,
                                            pgp->nome,
                                            pgp->classe,
                                            pgp->b_stat.hp,
                                            pgp->b_stat.mp,
                                            pgp->b_stat.atk,
                                            pgp->b_stat.def,
                                            pgp->b_stat.mag,
                                            pgp->b_stat.spr);
}

void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){//da fare!!
    fprintf(fp,"\nCODICE: %s\nNOME: %s\nCLASSE: %s",    pgp->cod,
                                                        pgp->nome,
                                                        pgp->classe);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip,invArray);
}
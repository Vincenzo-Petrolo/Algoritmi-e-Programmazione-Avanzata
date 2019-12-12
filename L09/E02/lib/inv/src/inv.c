#include "../include/inv.h"


void stat_read(FILE *fp, stat_t *statp) {
    fscanf(fp,"%d%d%d%d%d%d",   &(statp->hp),
                                &(statp->mp),
                                &(statp->atk),
                                &(statp->def),
                                &(statp->mag),
                                &(statp->spr));
}

void stat_print(FILE *fp, stat_t *statp, int soglia) {
    if (statp->hp < soglia )
        printf("\n\tHP: %d",soglia);
    else
        printf("\n\tHP: %d",statp->hp);

    if (statp->mp < soglia )
        printf("\n\tMP: %d",soglia);
    else
        printf("\n\tMP: %d",statp->mp);

    if (statp->atk < soglia )
        printf("\n\tATK: %d",soglia);
    else
        printf("\n\tATK: %d",statp->atk);
    
    if (statp->def < soglia )
        printf("\n\tDEF: %d",soglia);
    else
        printf("\n\tDEF: %d",statp->def);
    
    if (statp->mag < soglia )
        printf("\n\tMAG: %d",soglia);
    else
        printf("\n\tMAG: %d",statp->mag);

    if (statp->spr < soglia )
        printf("\n\tSPR: %d",soglia);
    else
        printf("\n\tSPR: %d",statp->spr);
}

void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp,"%s%s%d%d%d%d%d%d",   invp->nome,
                                    invp->tipo,
                                    &(invp->stat.hp),
                                    &(invp->stat.mp),
                                    &(invp->stat.atk),
                                    &(invp->stat.def),
                                    &(invp->stat.mag),
                                    &(invp->stat.spr));
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp,"\n\tNOME:%s\n\tTIPO:%s\n\tHP:%d\n\tMP:%d\n\tATK:%d\n\tDEF:%d\n\tMAG:%d\n\tSPR:%d",  invp->nome,
                                                                                                    invp->tipo,
                                                                                                    invp->stat.hp,
                                                                                                    invp->stat.mp,
                                                                                                    invp->stat.atk,
                                                                                                    invp->stat.def,
                                                                                                    invp->stat.mag,
                                                                                                    invp->stat.spr);
}

stat_t inv_getStat(inv_t *invp) {
    return invp->stat;
}

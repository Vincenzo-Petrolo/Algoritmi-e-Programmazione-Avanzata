#include "../include/f_ric.h"

int fZ(struct pietre_bag* pietre,struct pietre_bag* prese,matrice_p matrice_ptr){ //prova
    if (pietre->zaffiri <= 0) {
        return 0;
    }
    
    if (estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi)) == -1){
        pietre->zaffiri--;
        prese->zaffiri++;
    
        inserisci_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi),max(fZ(pietre,prese,matrice_ptr),fR(pietre,prese,matrice_ptr)));
        
        pietre->zaffiri++;
        return 1 + estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri--,prese->rubini,prese->topazi,prese->smeraldi));
    }

    return estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi));
}

int fT(struct pietre_bag* pietre,struct pietre_bag* prese,matrice_p matrice_ptr){ //prova
    if (pietre->topazi <= 0 ) {
        return 0;
    }
    if (estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi)) == -1){
        pietre->topazi--;
        prese->topazi++;

        inserisci_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi),max(fZ(pietre,prese,matrice_ptr),fR(pietre,prese,matrice_ptr)));
        pietre->topazi++;
        return 1 + estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi--,prese->smeraldi));
    }

    return estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi));
}

int fR(struct pietre_bag* pietre,struct pietre_bag* prese,matrice_p matrice_ptr){ //prova
    if (pietre->rubini <= 0 ) {
        return 0;
    }
    if (estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi)) == -1){
        pietre->rubini--;
        prese->rubini++;

        inserisci_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi),max(fS(pietre,prese,matrice_ptr),fT(pietre,prese,matrice_ptr)));
        pietre->rubini++;

        return 1 + estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini--,prese->topazi,prese->smeraldi));
    }

    return estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi));
}

int fS(struct pietre_bag* pietre,struct pietre_bag* prese,matrice_p matrice_ptr){ //prova
    if (pietre->smeraldi == 0 ) {
        return 0;
    }
    if (estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi)) == -1){
        pietre->smeraldi--;
        prese->smeraldi++;

        inserisci_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi),max(fS(pietre,prese,matrice_ptr),fT(pietre,prese,matrice_ptr)));
        pietre->smeraldi++;

        return 1 + estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi--));
    }

    return estrai_matr4dp(matrice_ptr,quaternioni_init(prese->zaffiri,prese->rubini,prese->topazi,prese->smeraldi));
}



int max(int val_1,int val_2) {
    if (val_1 >= val_2)
        return val_1;
    else
        return val_2;
}

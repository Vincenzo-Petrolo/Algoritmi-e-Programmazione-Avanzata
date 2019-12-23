#ifndef __F_RIC__H__
#define __F_RIC__H__

#include "../../pietre/include/pietre.h"
#include "../../matr4dp/include/matr4dp.h"

int fZ(struct pietre_bag* pietre,struct pietre_bag* prese,matrice_p matrice_ptr);
int fS(struct pietre_bag* pietre,struct pietre_bag* prese,matrice_p matrice_ptr);
int fT(struct pietre_bag* pietre,struct pietre_bag* prese,matrice_p matrice_ptr);
int fR(struct pietre_bag* pietre,struct pietre_bag* prese,matrice_p matrice_ptr);

int max(int val_1,int val_2);

#endif
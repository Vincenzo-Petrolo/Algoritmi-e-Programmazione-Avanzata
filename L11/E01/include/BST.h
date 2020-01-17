#ifndef __BST__H__
#define __BST__H__

#include "../include/quotazioni.h"

#include <limits.h>
#include <stdlib.h>


typedef struct binarysearchtree *BST;

BST  BSTinit() ;
void BSTfree(BST bst);

int  BSTcount(BST bst);
int  BSTempty(BST bst);

quotazioni_t *BSTsearch(BST bst, data_t data);

void BSTinsert_leafR(BST bst, quotazioni_t quotazione);
void BSTinsert_root(BST bst, quotazioni_t quotazione);

data_t BSTminData(BST bst);
data_t BSTmaxData(BST bst);

void BSTsearchMaxMinR(BST bst,data_t data1,data_t data2,float *max,float *min);


void BSTminmax(BST bst,int *min,int *max);

void BSTbalance(BST bst,float soglia);


#endif
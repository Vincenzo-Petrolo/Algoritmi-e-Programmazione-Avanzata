#ifndef __BST__H__
#define __BST__H__

#include "../include/quotazioni.h"

#include <stdlib.h>


typedef struct binarysearchtree *BST;

BST  BSTinit() ;
void BSTfree(BST bst);
int  BSTcount(BST bst);
int  BSTempty(BST bst);
quotazioni_t *BSTsearch(BST bst, data_t data);
void BSTinsert_leafR(BST bst, quotazioni_t quotazione);
void BSTinsert_root(BST bst, quotazioni_t quotazione);
quotazioni_t BSTmin(BST bst);
quotazioni_t BSTmax(BST bst);
void BSTvisit(BST bst, int strategy);


#endif
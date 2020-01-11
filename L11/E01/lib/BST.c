#include "../include/BST.h"

typedef struct BSTnode* link;

struct BSTnode {quotazioni_t quotazione; link l; link r;} ;

struct binarysearchtree { link root; link z; };

static link NEW( quotazioni_t quotazione, link l, link r) {
    link x = malloc(sizeof *x);
    x->quotazione = quotazione; x->l = l; x->r = r;
    return x;
}

BST BSTinit( ) {
    BST bst = malloc(sizeof *bst) ;
    bst->root= ( bst->z = NEW(quotSetNull(), NULL, NULL));
    return bst;
}

static void treeFree(link h, link z) {
    if (h == z) return;
    treeFree(h->l, z); treeFree(h->r, z);
    free(h);
}

void BSTfree(BST bst) {
    if (bst == NULL) return;
    treeFree(bst->root, bst->z);
    free(bst->z); free(bst);
}

static int countR(link h, link z) {
    if (h == z) return 0;
    return countR(h->l, z) + countR(h->r, z) +1;
}

int BSTcount(BST bst) {
    return countR(bst->root, bst->z);
}

int BSTempty(BST bst) {
    if (BSTcount(bst) == 0) return 1;
    return 0;
}

quotazioni_t *searchR(link h, data_t giorno, link z) {
    int cmp;
    if (h == z)
        return NULL;
    cmp = dataCmp(giorno, h->quotazione.giorno);
    if (cmp == 0)
        return &(h->quotazione);
    if (cmp == -1)
        return searchR(h->l, giorno, z);
    return searchR(h->r, giorno, z);
}

quotazioni_t* BSTsearch(BST bst, data_t giorno) {
    return searchR(bst->root, giorno, bst->z);
}

static link insertR(link h, quotazioni_t x, link z) {
    if (h == z)
        return NEW(x, z, z);
    if (dataCmp(x.giorno, h->quotazione.giorno) ==-1)
        h->l = insertR(h->l, x, z);
    else
        h->r = insertR(h->r, x, z);
    return h;
}

void BSTinsert_leafR(BST bst, quotazioni_t x) {
    bst->root = insertR(bst->root, x, bst->z);
}


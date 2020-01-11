#include "../include/LIST.h"


#include <string.h>

struct nodo{
    Titolo titolo;
    link next;
};


static link new_node(link h,Titolo titolo){
    link x = malloc(sizeof(*x));
    x->titolo   = titolo;
    x->next     = h;
    return x;
}

link list_init(){
    return NULL;
}
link list_free(link x){
    free(x);
}

static link sortInsList(link h,Titolo titolo){ //ordine alfanumerico crescente a1,a2,b1...

    link x,p;
    if (h == NULL || strcmp(getCodice(h->titolo),getCodice(titolo)) > 0){
        return new_node(h,titolo);
    }

    for (x = h->next,p = h; x != NULL && strcmp(getCodice(x->titolo),getCodice(titolo)) < 0; p = x,x = x->next);
    p->next = new_node(x,titolo);
    return h;
}

link crea_lista_titoli(FILE *fin){
    int n_titoli;
    int i;

    link head = list_init();

    fscanf(fin,"%d",&n_titoli);
    Titolo tmp;
    for ( i = 0; i < n_titoli; i++){
        tmp = titInit();
        tmp = titCarica(tmp,fin);
        head = sortInsList(head,tmp);
    }

    return head;
}

link cerca_titolo(link h,char *codice){
    for (link x = h; x != NULL; x = x->next){
        if (strcmp(getCodice(x->titolo),codice) == 0){
            return x;
        }
    }
    return NULL;
}

BST getBST(link x){
    return getBinSearchTree(x->titolo);
}

#include <stdio.h>
#include <stdlib.h>
#define __MAX_CHARS__ 50+1
#define  __FILE_NAME__ "anagrafica.txt"

typedef char KEY;
typedef enum {r_acquisizione,r_codice,r_cancella,r_stampa,r_fine} decisioni;
typedef enum {FALSE,TRUE} boolean;
typedef enum {FILE_TESTO,STDIN} sorgente_lettura;
typedef struct {
    int gg;
    int mm;
    int aaaa;
}data_t;

typedef struct {
    KEY codice[5+1];
    char nome[__MAX_CHARS__];
    char cognome[__MAX_CHARS__];
    data_t data;
    char via[__MAX_CHARS__];
    char citta[__MAX_CHARS__];
    int cap;
}Item;

typedef  struct nodo* link;

struct nodo {
    Item val;
    link next;
};
link newNode (Item val, link next);

void ricerca_per_codice();
void cancellazione(); //se con cancellazione dopo ricerca, o in un intervallo in base a un paramentro
void stampa_lista();
boolean data_gt(data_t data1,data_t data2);
void acquisisci_Item(link *head,sorgente_lettura tipo);
link SortInsList(link h,Item val);

decisioni acquisisci_menu();
int main() {
decisioni menu;
    link head = NULL;

    acquisisci_Item(&head,FILE_TESTO);
    for (link i = head; i != NULL; i = i->next) {
        printf("\n%s %s %s %d/%d/%d %s %s %d",i->val.codice,i->val.nome,i->val.cognome,
                i->val.data.gg,i->val.data.mm,i->val.data.aaaa,i->val.via,i->val.citta,i->val.cap);
    }

    return 0;
}

boolean data_gt(data_t data1,data_t data2) {
    if (data1.aaaa > data2.aaaa)
        return TRUE;
    else if (data1.aaaa < data2.aaaa)
        return FALSE;
    else if (data1.aaaa == data2.aaaa)
        if (data1.mm > data2.mm)
            return TRUE;
        else if (data1.mm < data2.mm)
            return FALSE;
        else if ( data1.mm == data2.mm)
            if (data1.gg > data2.gg)
                return TRUE;
            else if (data1.gg < data2.gg)
                return FALSE;
            else if (data1.gg == data2.gg)
                return FALSE;
}

void acquisisci_Item(link *head, sorgente_lettura tipo) { //inserire o in coda o in testa!!
    /* Dichiarazione variabili*/
    FILE *fp;
    Item read;
    /*Fine dichiarazione*/
    if (tipo == FILE_TESTO) {
        fp = fopen(__FILE_NAME__,"r");
        if (fp == NULL){
            printf("\n**********ERRORE DURANTE L'APERTURA DEL FILE********\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        fp = stdin;
    }


    while (fscanf(fp,"%s%s%s%d/%d/%d%s%s%d",read.codice,read.nome,read.cognome,&read.data.gg,&read.data.mm,&read.data.aaaa,
                  read.via,read.citta,&read.cap) != EOF){
        *head = SortInsList(*head,read);
    }

}


link newNode (Item val, link next) {
    link x = (link) malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}

link SortInsList(link h,Item val) {
    link x,p;

    if (h == NULL || !data_gt(h->val.data,val.data))
        return newNode(val,h);

    for (x = h->next,p=h; x!=NULL && data_gt(x->val.data,val.data); p = x,x = x->next)
    {

    }
    p->next = newNode(val,x);
    return h;
}

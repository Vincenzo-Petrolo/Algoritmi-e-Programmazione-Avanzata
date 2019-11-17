#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __MAX_CHARS__ 50+1
#define  __FILE_NAME__ "anagrafica.txt"
#define __NUM_INFO__ 9
#define __NUM_COMANDI__ 5

/**Minor data structures*/
typedef enum {r_acquisizione,r_codice,r_cancella,r_stampa,r_fine} decisioni;
typedef enum {FALSE,TRUE} boolean;
typedef enum {FILE_TESTO,STDIN} sorgente_lettura;
/**Minor data structures*/

/**Date type*/
typedef struct {
    int gg;
    int mm;
    int aaaa;
}data_t;
typedef data_t KEY_1;
/**Date prototypes*/
boolean data_gt(data_t data1,data_t data2);
boolean KEY_1eq(KEY_1 data_1,KEY_1 data_2);
/**Date prototypes*/
/**Date type*/


/**Nodo*/
/**VAL*/
typedef char KEY;
typedef struct {
    KEY codice;
    char nome[__MAX_CHARS__];
    char cognome[__MAX_CHARS__];
    data_t data;
    char via[__MAX_CHARS__];
    char citta[__MAX_CHARS__];
    int cap;
}Item;
/**VAL*/

typedef  struct nodo* link;

struct nodo {
    Item val;
    link next;
};
/**Nodo prototypes*/
link newNode (Item val, link next);
link SortInsList(link h,Item val);
link getKEY_1(link head,KEY_1 data_2);
link KEY_listSearch(link *head,KEY k);
link getKEY(link head,KEY codice);
void node_display(link node);
void node_delete(link* head,link node);
void node_extract(link* head,link node);
void acquisisci_Item(link *head);
decisioni acquisisci_menu(link *head);
boolean KEY_eq(KEY *k1,KEY *k2);
/**Nodo prototypes*/
/**Nodo*/


int main() {
decisioni menu;
    link head = NULL;

    acquisisci_Item(&head);
    while (acquisisci_menu(&head) != r_fine);
    return 0;
}

/**Chiamante*/
decisioni acquisisci_menu(link *head) {

    char menu[__NUM_COMANDI__][30] = {{"inserisci"},{"ricerca(codice)"},{"cancella"},{"stampa"},{"fine"}};
    char decisione[30];
    decisioni scelta;
    KEY_1 data_1,data_2;
    link occorrenza1,occorrenza2;
    KEY k;

    printf("\nMENÙ");
    for (int i = 0; i < __NUM_COMANDI__; i++) {
        printf("\n>");
        printf("%s",menu[i]);
    }
    printf("\nScrivi cosa vuoi fare: ");
    scanf("%s",decisione);

    for (int j = 0; j < __NUM_COMANDI__; j++) {
        if (strstr(menu[j],decisione) != NULL){
            scelta = j;
            break;
        }
    }

    switch (scelta){

        case r_acquisizione:
            acquisisci_Item(head);
            break;
        case r_codice:
            scanf("%s",k);
            occorrenza1=getKEY(head,k);
            node_extract(head,occorrenza1);
            break;
        case r_cancella:
            scanf("%d/%d/%d",&data_1.gg,&data_1.mm,&data_1.aaaa);
            scanf("%d/%d/%d",&data_2.gg,&data_2.mm,&data_2.aaaa);
            occorrenza1 = getKEY_1(*head,data_2);
            occorrenza2 = getKEY_1(*head,data_1);
            for (link x = occorrenza1; x != NULL && x != occorrenza2 ;x = x->next) {
                node_extract(head,x); //elimina ogni x finchè non li ha eliminati tutti
            }
            break;
        case r_stampa:
            for (link x = *head; x != NULL ;x = x->next) {
                node_display(x);
            }
            break;
        case r_fine:
            return r_fine;
        default:
            break;
    }

}
/**Chiamante*/


/**Date functions*/
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
link getKEY_1(link head,KEY_1 data_2) {
    for (link x = head->next; x != NULL ; x = x->next) {
        if (KEY_1eq(x->val.data,data_2))
            return x; //ritorno al chiamante l'inizio della seconda data che sarà quella più grande, e quindi quella di inizio
    }
    printf("\nNessun elemento trovato in questo intervallo di date!");
    return NULL;
}
boolean KEY_1eq(KEY_1 data_1,KEY_1 data_2){
    if (data_1.aaaa == data_2.aaaa && data_1.mm == data_2.mm && data_1.gg == data_2.gg)
        return TRUE;
    return FALSE;
}
/**Date functions*/

/**Node functions*/
/**VAL functions*/
void acquisisci_Item(link *head) { //inserire o in coda o in testa!!
    /* Dichiarazione variabili*/
    FILE *fp;
    Item read;
    int terminazione;
    char decisione[30];
    sorgente_lettura tipo = STDIN;
    /*Fine dichiarazione*/
    printf("\nCome vuoi che acquisisca i dati? (File/Standard Input)\n>");
    scanf("%s",decisione);

    if (strstr("File",decisione)){
        tipo = FILE_TESTO;
    }


    if (tipo == FILE_TESTO) {
        fp = fopen(__FILE_NAME__,"r");
        if (fp == NULL){
            printf("\n**********ERRORE DURANTE L'APERTURA DEL FILE********\n");
            exit(EXIT_FAILURE);
        }
        terminazione = EOF;
    }
    else {
        fp = stdin;
        terminazione = __NUM_INFO__;
        printf("\n Digita le informazioni, attenzione nel caso il numero di campi fosse errato il processo di acquisizione terminerà!");
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
boolean richiedi_cancellazione() {
    char c;
    printf("Vuoi eliminare l'elemento cercato?[S/n]:");
    scanf("%c",&c);

    if (c == 'S' || c == 's'){
        return TRUE;
    }
    else return FALSE;
}
link getKEY(link head,KEY codice) {

    for (link x = head->next; x != NULL ; x = x->next) {
        if (strncmp(x->val.codice,codice,strlen(codice)) == 0){
            return x;
        }
    }
    printf("\nCodice non trovato!");
    return NULL;
}
void node_display(link node) {
    printf("\n%s %s %s %d/%d/%d %s %s %d",node->val.codice,
           node->val.nome,
           node->val.cognome,
           node->val.data.gg,
           node->val.data.mm,
           node->val.data.aaaa,
           node->val.via,
           node->val.citta,
           node->val.cap);
}
void node_delete(link *head, link node) {
    link x,p;
    for (x = (*head)->next, p = *head ; x != NULL && x!= node; x = x->next,p = x);
    p = x->next;
    free(node);
}
void node_extract(link* head,link node) {
    printf("\nEliminazione di:");
    node_display(node);
    node_delete(head,node);
}
boolean KEY_eq(KEY *k1,KEY *k2) {
    if (strcmp(k1,k2) == 0)
        return TRUE;
    return FALSE;
}
/**VAL functions*/
/**Node functions*/
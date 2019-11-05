#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define __MAX_DIM__ 200
#define  FILENAME "sorgente.txt"

typedef enum {FALSE,TRUE} boolean;


typedef enum {PUNTO,PARENTESI,NEGAZIONE_PARENTESI,MINUSCOLO,MAIUSCOLO} tipo_metacarattere;
typedef struct {
    char regexp_a_cui_si_riferisce[__MAX_DIM__];
    int posizione;
    tipo_metacarattere metacarattere;
    char contenuto_parentesi[__MAX_DIM__];
    int lunghezza_shift;
}vincoli_al_carattere;

void leggi_regularexp(char regexp[__MAX_DIM__]);
void compila_vincoli(char regexp[__MAX_DIM__],vincoli_al_carattere *caratteri,int *lunghezza_vettore_caratteri);
void pulizia_regexp(char regexp[__MAX_DIM__],int lunghezza_vettore_caratteri,vincoli_al_carattere *metacaratteri,char pulita[strlen(regexp)]);
char* cercaRegexp(char* src,char* regexp);


int main() {
    int lunghezza_vettore_caratteri;
    char regexp[__MAX_DIM__];
    char parola[__MAX_DIM__];
    FILE *fp;
    char *pointer;
    int i=0;

    fp = fopen(FILENAME,"r");
    if (fp == NULL) {
        printf("\nFile inesistente!");
        return 1;
    }

    /*Modalità di ricerca riga per riga*/
    leggi_regularexp(regexp);

    while (fscanf(fp,"%s",parola) != EOF) {
        i=0;
        while (i<=strlen(parola)) {
            pointer=cercaRegexp(&parola[i++],regexp);
            if (pointer != NULL)
                printf("\n%s", pointer);
        }
    }



    return 0;
}//ricordarsi di inserire il/0 alla fine quando salvo le parole da negare,o da accettare

char* cercaRegexp(char* src,char* regexp){
/*Confronto parola per parola*/
/**Algoritmo
 * STEP 1: Pulire la regexp per capire cosa si vuol cercare
 *      >STEP 1.1 Scorre la regexp e per ogni metacarattere trovato
 *      ne salva la posizione,se è un punto,minuscolo,maiuscolo,
 *      se si tratta di una parentesi, controlla che tipo di parentesi
 *      è, e poi salva i caratteri. Tutte queste informazioni sono contenute
 *      in una apposita struttura dati.(compila vincoli)
 *      >STEP 1.2 Pulisce la regexp togliendo tutti i metacaratteri, in modo
 *      da agevolare l'utilizzo della strstr, per trovare facilmente l'occorrenza
 *      La pulizia della regexp è effettuata dopo ogni metacarattere incontrato,
 *      Dato che si suppone che i caratteri della regexp siano alfabetici,allora
 *      in una sottostringa verrà copiato uno 0 per ogni metacarattere
 *      e il carattere stesso della regexp
 * STEP 2: Cercare l'occorrenza nella stringa src
 *     >STEP 2.1 L'occorrenza verrà cercata parola per parola, in particolare
 *     si cercherà l'occorrenza del primo carattere nella regexp, e poi si
 *     verificherà che esistono in quella parola(quindi non ci sono spazi in mezzo)
 *     alle posizioni esatte anche gli altri caratteri. Dopodichè per ogni
 *     metacarattere (rappresentato da un vettore di vincoli_al_carattere)
 *     se vale ciò che è stato trovato
 * STEP 3: Verifiare che rispetti i vincoli posti dalla regexp*/

    char* pointer=NULL;
    int lunghezza_vettore_metacaratteri = strlen(regexp);
    char pulita[strlen(regexp)+1];
    pulita[strlen(regexp)] = '\0'; //metto il terminatore che poi mi trascinerò durante gli shift

    vincoli_al_carattere metacaratteri[strlen(regexp)];
    compila_vincoli(regexp,metacaratteri,&lunghezza_vettore_metacaratteri);
    pulizia_regexp(regexp,lunghezza_vettore_metacaratteri,metacaratteri,pulita);
    boolean meta_accettabile = FALSE,carat_accettabile=FALSE;
    /*Per comparare la presenza della stringa posso spostare la regexp, sulla src per confrontarle, partendo da 0*/
    int limite = strlen(src) -strlen(pulita);
    if (limite >= 0){
        meta_accettabile =TRUE;
        for (int l = 0; l < lunghezza_vettore_metacaratteri && meta_accettabile == TRUE; l++) {
            if (metacaratteri[l].metacarattere == PARENTESI) {
                for (int j = 0; j <= metacaratteri[l].lunghezza_shift-2; j++) { //se la lettera di src che sto considerando in posizione i è uguale al contenuto tra parentesi, allora meta_accettabile TRUE
                    if (metacaratteri[l].contenuto_parentesi[j+1] != src[metacaratteri[l].posizione]) {//controllo che nella posizione della src ci sia il carattere che cerco
                        meta_accettabile = FALSE;
                    }
                }
            }
            else if (metacaratteri[l].metacarattere == NEGAZIONE_PARENTESI) {
                for (int j = 0; j < metacaratteri[l].lunghezza_shift-3; j++) { //se la lettera di src che sto considerando in posizione i è uguale al contenuto tra parentesi, allora meta_accettabile TRUE
                    if (metacaratteri[l].contenuto_parentesi[j+2] == src[metacaratteri[l].posizione]) { //controllo che nella posizione della src ci sia il carattere che cerco
                        meta_accettabile = FALSE;
                    }
                }
            }
            else if (metacaratteri[l].metacarattere == MINUSCOLO){
                if (!islower(src[metacaratteri[l].posizione]))
                    meta_accettabile=FALSE;
            }
            else if (metacaratteri[l].metacarattere == MAIUSCOLO){
                if (!isupper(src[metacaratteri[l].posizione]))
                    meta_accettabile=FALSE;
            }
        }
        carat_accettabile = TRUE;
        for (int k = 0; k < strlen(pulita) && carat_accettabile == TRUE; k++) {
            if (pulita[k] != '\n')
                if (src[k] != pulita[k])
                    carat_accettabile = FALSE;
        }
    }

    if (meta_accettabile && carat_accettabile){ //se i caratteri combaciano, e i metacaratteri rispettano i vincoli allora è una valida regexp
        pointer = src; //distanza è la distanza dall'inizio
    }

    return pointer;
}

void leggi_regularexp(char regexp[__MAX_DIM__]){
    printf("\nInserisci l'espressione regolare: ");
    scanf("%s",regexp);
}

void compila_vincoli(char regexp[__MAX_DIM__],vincoli_al_carattere *caratteri,int *lunghezza_vettore_caratteri){
    /**Casi di ricerca*/
    char *ptr;
    ptr = regexp;
    int j;

    /**Cerco se nella stringa ci sono '\a'*/
    j = 0;
    while ((ptr=strstr(ptr,"\\a")) != NULL) {
        caratteri[j].metacarattere = MINUSCOLO;
        caratteri[j].posizione = ptr - &regexp[0]; //differenza per capire la posizione

        strcpy(caratteri[j].regexp_a_cui_si_riferisce,regexp);
        caratteri[j].lunghezza_shift = 1;
        j++;
        ptr+=2;
    }
    ptr = regexp;

    /**Cerco se nella stringa ci sono '\A'*/

    while ((ptr=strstr(ptr,"\\A")) != NULL) {
        caratteri[j].metacarattere = MAIUSCOLO;
        caratteri[j].posizione = ptr - &regexp[0]; //differenza per capire la posizione
        strcpy(caratteri[j].regexp_a_cui_si_riferisce,regexp);
        caratteri[j].lunghezza_shift = 1;
        j++;
        ptr+=2;
    }
    ptr = regexp;

    /**Cerco se nella stringa ci sono '.'*/
    while ((ptr=strstr(ptr,".")) != NULL) {
        caratteri[j].metacarattere = PUNTO;
        caratteri[j].posizione = ptr - &regexp[0]; //differenza per capire la posizione
        strcpy(caratteri[j].regexp_a_cui_si_riferisce,regexp);
        caratteri[j].lunghezza_shift = 0;
        j++;
        ptr++;

    }
    ptr = regexp;

    /**Cerco se nella stringa ci sono '['*/

    while ((ptr=strstr(ptr,"[")) != NULL) {
        int i=1;
        if (*(ptr+1) == '^'){
            caratteri[j].metacarattere = NEGAZIONE_PARENTESI;
            i=2;
        }
        else caratteri[j].metacarattere = PARENTESI;

        while (*(ptr+i) != ']'){
            caratteri[j].contenuto_parentesi[i] = *(ptr+i);
            i++;
        }
        caratteri[j].posizione = ptr - &regexp[0]; //differenza per capire la posizione,non è corretta, in quanto ottengo la posi
        strcpy(caratteri[j].regexp_a_cui_si_riferisce,regexp);
        ptr+=i; //riparto dalla fine delle parentesi
        caratteri[j].lunghezza_shift = i;
        j++;

    }

    //Alla fine avrò compilato un vettore lungo al più la lunghezza della regexp
    *lunghezza_vettore_caratteri=j;
}

void pulizia_regexp(char regexp[__MAX_DIM__],int lunghezza_vettore_caratteri,vincoli_al_carattere *metacaratteri,char pulita[strlen(regexp)]) {


    /**Riempio di 0 tutte le celle con metacaratteri*/
    for (int i = 0; i < lunghezza_vettore_caratteri; i++) {
        if (strcmp(regexp,metacaratteri[i].regexp_a_cui_si_riferisce) == 0) {
            pulita[metacaratteri[i].posizione] = '\n';
        }
    }
    /**Riempio con le lettere la stringa pulita*/
    for (int j = 0; j < strlen(regexp); j++) {
        if (pulita[j] != '\n'){
            pulita[j] = *(&regexp[0] + j);
        }
    }
    int k;
    int i;

    for (k = 0; k < lunghezza_vettore_caratteri; k++) {
        for (i = metacaratteri[k].posizione+1; i <=strlen(regexp)-metacaratteri[k].lunghezza_shift; i++) {
            pulita[i] = pulita[i+metacaratteri[k].lunghezza_shift];
        }
        for (int j = k+1; j < lunghezza_vettore_caratteri; j++) {
            if (metacaratteri[j].posizione >= metacaratteri[k].lunghezza_shift) //aggiorno la pos del metacarattere se non è 0, che è stato spostato
                metacaratteri[j].posizione -= metacaratteri[k].lunghezza_shift;

        }
    }


}
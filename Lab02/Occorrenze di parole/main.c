/**Vincenzo Petrolo s256499*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define __MAX_LUNGHEZZA_FILE__ 20
#define __MAX_CHAR__ 5+1
#define __MAX_WORD__ 25+1
#define __SEQUENZE__ "sequenze.txt"
#define __TESTO__ "testo.txt"


typedef enum {FALSE,TRUE} boolean;

typedef struct {
    char sottostringa[__MAX_CHAR__+1];
}agg_type0;

boolean salva_sequenza(agg_type0 sequenza[__MAX_LUNGHEZZA_FILE__],int *lunghezza);
void ricerca_e_stampa(agg_type0 sequenze[__MAX_LUNGHEZZA_FILE__],int lunghezza,char parola[__MAX_WORD__],int n_parola);
void acquisisci_parola(agg_type0 sequenza[__MAX_LUNGHEZZA_FILE__],int lunghezza);

int main() {

    agg_type0 sequenze[__MAX_LUNGHEZZA_FILE__];
    int lunghezza;

    salva_sequenza(sequenze,&lunghezza);
    acquisisci_parola(sequenze,lunghezza);

    return 0;
}

boolean salva_sequenza(agg_type0 sequenza[__MAX_LUNGHEZZA_FILE__],int *lunghezza){
    FILE* fp;
    boolean result=TRUE;
    int i;

    fp = fopen(__SEQUENZE__,"r");
    if (fp==NULL){
        printf("\nErrore durante l'apertura del file %s",__SEQUENZE__);
        result = FALSE;
    }
    fscanf(fp,"%d",lunghezza);
    for (i = 0;i < *lunghezza; i++) {
        fscanf(fp,"%s",sequenza[i].sottostringa);
    }
    fclose(fp);

    return result;
}

void acquisisci_parola(agg_type0 sequenza[__MAX_LUNGHEZZA_FILE__],int lunghezza){
    /**Questa funzione legge una parola priva di punteggiatura e spazi, in modo da poterla processare direttamente**/
    FILE * fp;
    char parola[__MAX_WORD__+1];
    char c;
    int k;
    int n_parole=0;
    boolean word_in=FALSE,fine_parola = FALSE;

    fp = fopen(__TESTO__,"r");

    if (fp == NULL){
        printf("\nErrore durante l'apertura del file %s",__TESTO__);
        exit(EXIT_FAILURE);
    }
    k=0;
    while ((c=tolower(fgetc(fp))) != EOF || word_in==TRUE) {

        if (isalnum(c)){
            parola[k] = c;
            k++;
            word_in = TRUE;
        }
        if ((c==EOF || !isalnum(c)) && word_in==TRUE) {
            fine_parola =TRUE; // mi dice che incontro uno spazio o un segno di punteggiatura e prima ero dentro una parola
            //allora significa che la parola si è finita, e quindi posso uscire dal while mettendo il terminatore alla parola
            parola[k] = '\0'; // metto il terminatore perchè ho incontrato la fine della parola
        }
        //chiamo la funzione di ricerca
        if (fine_parola == TRUE || c==EOF){
            n_parole++; //ogni volta che finisco una parola, incremento il contatore
            ricerca_e_stampa(sequenza,lunghezza,parola,n_parole);
            fine_parola =FALSE;
            word_in = FALSE;
            k=0;
        }
    }
    fclose(fp);
}

void ricerca_e_stampa(agg_type0 sequenze[__MAX_LUNGHEZZA_FILE__],int lunghezza,char parola[__MAX_WORD__],int n_parola){
    /**Obiettivo della funzione è quello di cercare nella parola sfoltendola sempre di più mediante l'uso di un puntatore
     * e della funzione strstr**/
     char *ptr;
     int l,i=0;

    for (i = 0; i < lunghezza; i++) {
        l=0;
        while (sequenze[i].sottostringa[l]){ //serve per ridurre al minimo tutti i caratteri della parola da cercare
            sequenze[i].sottostringa[l] = tolower(sequenze[i].sottostringa[l]);
            l++;
        }
        ptr = parola;
        while ((ptr=strstr(ptr,sequenze[i].sottostringa)) != NULL) {
            ptr += strlen(sequenze[i].sottostringa); //incremento il puntatore per sfoltire la parola e vedere se ci sono ancora occorrenze
            printf("\nLa sequenza \"%s\" è contenuta in \"%s\" (parola in posizione %d nel testo)",
                   sequenze[i].sottostringa, parola, n_parola);
        }
    }

}
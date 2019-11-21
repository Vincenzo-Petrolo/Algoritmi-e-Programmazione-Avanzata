/**Vincenzo Petrolo s256499*/
#include <stdio.h>
#include <string.h>
#define  MAX_NOME_FILE 20+1
#define  MAX_DIM 30
#define MAX_STR 100+1
#define SELETTORE_FINE "fine"
#define SELETTORE_COLONNA "colonna"
#define SELETTORE_RIGA "riga"
#define SELETTORE_SU "su"
#define SELETTORE_GIU "giu"
#define SELETTORE_DX "destra"
#define SELETTORE_SX "sinistra"

typedef enum{FALSO,VERO} boolean;

typedef struct {
    char selettore[MAX_STR];
    int indice;
    char direzione[MAX_STR];
    int posizioni;
}agg_type0;

typedef struct {
    int numero_colonne;
    int numero_righe;
}agg_type2;

void lettura_file(int *ptrnr,int *ptrnc,int matrice[MAX_DIM][MAX_DIM]);
int acquisizione_istruzioni(char selettore[MAX_STR],int* indice,char direzione[MAX_STR],int* posizioni);
void ruota_vettore(agg_type0 istruzione,int matrice[MAX_DIM][MAX_DIM],agg_type2 dati_matrice);
void stampa_matrice(int matrice[][MAX_DIM],int nc,int nr);

int main() {
    agg_type0 istruzione;
    agg_type2 dati_matrice;
    int res;
    int matrice[MAX_DIM][MAX_DIM],sub_vettore[MAX_DIM];

    lettura_file(&dati_matrice.numero_righe,&dati_matrice.numero_colonne,matrice);
    do {
        stampa_matrice(matrice,dati_matrice.numero_colonne,dati_matrice.numero_righe);
        res=acquisizione_istruzioni(istruzione.selettore,&istruzione.indice,istruzione.direzione,&istruzione.posizioni);
        if (res == VERO ) {
            ruota_vettore(istruzione,matrice,dati_matrice);
        }
    }while (res!=2);

    return 0;
}


void lettura_file(int *ptrnr,int *ptrnc,int matrice[MAX_DIM][MAX_DIM]){
    char nome_file[MAX_NOME_FILE];
    FILE *fp;
    int i=0,j=0;

    do {
        printf("\nInserire il nome del file(MAX 20 CARATTERI): ");
        scanf("%s",nome_file);
        fp = fopen(nome_file,"r");
    } while (fp == NULL);

    if (fscanf(fp,"%d%d",ptrnr,ptrnc) != 2) printf("\nErrore di lettura,dati mancanti nel file!");


    for ( i = 0; i < *ptrnr ; i++) {
        for (j = 0; j < *ptrnc; j++) {
            fscanf(fp,"%d",&matrice[i][j]);
        }
    }

}

int acquisizione_istruzioni(char selettore[MAX_STR],int* indice,char direzione[MAX_STR],int* posizioni){
    /*Manda il segnale di terminazione ritornando 2, anziche FALSO*/
    int risultato=VERO;

    printf("\nInserire l'istruzione nel formato <selettore> <indice> <direzione> <posizioni>: ");
    if (scanf("%s%d%s%d",selettore,indice,direzione,posizioni) != 4){
        printf("\nErrore nella lettura delle istruzioni!");
        risultato = FALSO;
    }
    if (strcmp(selettore,SELETTORE_FINE)==0)
        risultato = 2;
    if (strcmp(selettore,SELETTORE_RIGA) == 0 && (strcmp(direzione,SELETTORE_GIU) == 0 || strcmp(direzione,SELETTORE_SU) == 0))
    {
        printf("\nDirezione non compatibile con il selettore scelto!\n");
        risultato = FALSO;
    }
    if (strcmp(selettore,SELETTORE_COLONNA) == 0 && (strcmp(direzione,SELETTORE_DX) == 0 || strcmp(direzione,SELETTORE_SX) == 0))
    {
        printf("\nDirezione non compatibile con il selettore scelto!\n");
        risultato = FALSO;
    }
    return risultato;
}

void stampa_matrice(int matrice[MAX_DIM][MAX_DIM],int nc,int nr) {
    int i,j;
    for (i = 0; i < nr; i++) {
        printf("\n");
        for (j = 0; j < nc; j++) {
            printf("%d ",matrice[i][j]);
        }
    }
}

void ruota_vettore(agg_type0 istruzione,int matrice[MAX_DIM][MAX_DIM],agg_type2 dati_matrice) {
/*La funzione mediante un if capisce se mi muovo su una riga o su una colonna,se VERO entra nell'if e
 * salva dei coefficienti che sono situazionali e ognuno diverso per ogni if.
 * nel primo ciclo for si salvano i dati che verrebbero sovrascritti in un vettore di supporto ,dimensionato al massimo a MAX_DIM
 * nel secondo ciclo for si ha uno shift a destra o sinistra a seconda dei casi
 * nel terzo ciclo for si inseriscono di nuovo i dati salvati nel vettore di supporto*/
    int i;
    int vett_supp[MAX_DIM];

    if (strcmp(istruzione.direzione,SELETTORE_DX)==0)
    {/*Caso riga dx*/
        istruzione.posizioni = istruzione.posizioni%dati_matrice.numero_colonne; //modulo di P per evitare di ciclare inutilmente

        for (i = 0; i <istruzione.posizioni; i++) { //salvo il sotto-vettore che verrebbe sovrascritto
            vett_supp[i]=matrice[istruzione.indice-1][dati_matrice.numero_colonne-istruzione.posizioni+i];
        }
        for (i = dati_matrice.numero_colonne-istruzione.posizioni; i > 0;i--) { //shift a destra
            matrice[istruzione.indice-1][istruzione.posizioni + i-1] = matrice[istruzione.indice-1][i-1];
        }
        for (i=0;i<istruzione.posizioni;i++) { //inserisco il sottovettore
            matrice[istruzione.indice-1][i]=vett_supp[i];
        }
    }
    /*Caso riga sx*/
    if (strcmp(istruzione.direzione,SELETTORE_SX)==0)
    {
        istruzione.posizioni = istruzione.posizioni%dati_matrice.numero_colonne;

        for (i =0; i < istruzione.posizioni; i++) {
            vett_supp[i]=matrice[istruzione.indice-1][i];
        }
        for (i = 0; i < dati_matrice.numero_colonne-istruzione.posizioni;i++) { //shift a sx
            matrice[istruzione.indice-1][i] = matrice[istruzione.indice-1][i+istruzione.posizioni];
        }
        for (i=0;i<istruzione.posizioni;i++) { //assegnazione delle variabili salvate nel vettore
            matrice[istruzione.indice-1][i+dati_matrice.numero_colonne-istruzione.posizioni]=vett_supp[i];
        }
    }

    if (strcmp(istruzione.direzione,SELETTORE_SU)==0)
    {/*Caso colonna su*/
        istruzione.posizioni = istruzione.posizioni%dati_matrice.numero_righe; //modulo

        for (i = 0; i < istruzione.posizioni; i++) {
            vett_supp[i]=matrice[i][istruzione.indice-1];
        }
        for (i = 0; i < dati_matrice.numero_righe-istruzione.posizioni;i++) { //shift a sx
            matrice[i][istruzione.indice-1] = matrice[istruzione.posizioni+i][istruzione.indice-1];
        }
        for (i=0;i<istruzione.posizioni;i++) { //assegnazione delle variabili salvate nel vettore
            matrice[i+dati_matrice.numero_righe-istruzione.posizioni][istruzione.indice-1]=vett_supp[i];
        }
    }

    if (strcmp(istruzione.direzione,SELETTORE_GIU)==0) //salvo gli ultimi P numeri del vettore in un vettore di supporto
    {/*Caso colonna giu*/
        istruzione.posizioni = istruzione.posizioni%dati_matrice.numero_righe; //modulo

        for (i = 0; i < istruzione.posizioni; i++) {
            vett_supp[i]=matrice[dati_matrice.numero_righe-istruzione.posizioni+i][istruzione.indice-1];
        }
        for (i=dati_matrice.numero_righe-istruzione.posizioni-1; i >= 0;i--) { //shift a destra
            matrice[istruzione.posizioni+i][istruzione.indice-1] = matrice[i][istruzione.indice-1];
        }
        for (i=0;i<istruzione.posizioni;i++) { //assegnazione delle variabili salvate nel vettore
            matrice[i][istruzione.indice-1]=vett_supp[i];
        }

    }
}
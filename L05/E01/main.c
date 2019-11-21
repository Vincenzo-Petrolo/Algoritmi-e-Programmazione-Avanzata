#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __MAX_NAME__ 255+1
#define __FILENAME__ "brani.txt"
#define __MAX_SONGS__ 5


typedef struct {
    char *pointer[__MAX_SONGS__];
    int n_scelte;
}brani_persone;
void leggi_file(FILE *fp ,brani_persone *playlist,int n);
void principio_moltiplicazione(brani_persone playlist[],int livello, char **sol,int altezza);
int main() {
    FILE *fp;
    int n_persone;

    fp = fopen(__FILENAME__,"r");
    fscanf(fp,"%d",&n_persone);

    brani_persone playlist[n_persone];
    char *sol[n_persone];

    for (int i = 0; i < n_persone; i++) {
        leggi_file(fp,playlist,i); //inizializzo playlist con i valori
    }
    principio_moltiplicazione(playlist,0,sol,n_persone);

    return 0;
}

void leggi_file(FILE *fp ,brani_persone *playlist,int n) {
    char letta[__MAX_NAME__];
    char *ptr;
    int lunghezza_per_corrente;

    fscanf(fp,"%d",&lunghezza_per_corrente);

    playlist[n].n_scelte = lunghezza_per_corrente; //salvo il numero di scelte per ogni persona

    for (int i=0; i<lunghezza_per_corrente;i++){
        ptr = (char *) malloc(strlen(letta));
        fscanf(fp,"%s",ptr);
        (playlist+n)->pointer[i] = ptr;
    }
}

void principio_moltiplicazione(brani_persone playlist[],int livello, char **sol,int altezza) {

    if (livello >= altezza){
        for (int i = 0; i < altezza; i++) {
            printf("\n%s",sol[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < playlist[livello].n_scelte; i++) {
        sol[livello] = playlist[livello].pointer[i];
        principio_moltiplicazione(playlist,livello+1,sol,altezza);
    }
}

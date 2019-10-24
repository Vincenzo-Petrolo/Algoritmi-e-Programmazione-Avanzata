/**Vincenzo Petrolo s256499*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_S 200
#define _DIZIONARIO_ "dizionario.txt"
#define _SORGENTE_ "sorgente.txt"
#define _RICODIFICA_ "ricodifica.txt"
/*MAX INT è lungo 10 cifre, perciò nella notazione $<intero>$ la lunghezza massima del vettore sarà 10 + 2*/

typedef enum {FALSE,TRUE} boolean;

typedef struct {
    char ricodifica[10+2];
    char sottostringa[MAX_S];
}agg_type0;

int lettura_lunghezza_file(FILE *fp_dict);
void ricodifica(int lunghezza,agg_type0 dizionario[]);

int main() {
    int lunghezza=0,i;
    FILE *fp_dict;

/**INIZIO LETTURA DIZIONARIO**/

    fp_dict = fopen(_DIZIONARIO_,"r");

    lunghezza=lettura_lunghezza_file(fp_dict);

    //ora posso definire la lunghezza del vettore
    agg_type0 dizionario[lunghezza];

    for (i=0;i<lunghezza;i++) {
        fscanf(fp_dict,"%s%s",dizionario[i].ricodifica,dizionario[i].sottostringa);

    }
    fclose(fp_dict);

/*********FINE LETTURA DIZIONARIO***********/

/**INIZIO RICODIFICA**/
    ricodifica(lunghezza,dizionario);
/**FINE RICODIFICA**/

    return 0;
}

int lettura_lunghezza_file(FILE *fp_dict) {
    int lunghezza;
    if (fp_dict == NULL) {
        printf("\nErrore file mancante!");
        exit(EXIT_FAILURE);
    }
    else {
        fscanf(fp_dict, "%d", &lunghezza);
    }
    /*+Fine Lettura lunghezza file+*/
    return lunghezza;
}

void ricodifica(int lunghezza,agg_type0 dizionario[]){
    FILE *fp_sorgente,*fp_ricodifica;
    int result = TRUE;
    int i,j,k;
    int shift_dx,shift_sx;
    char stringa[MAX_S];
    char *pointer;
    char stringa_mod[MAX_S*12];  //questa dimensione poichè così se avessi 200 caratteri da ricodificare, li devo ricodificare
    //in massimo 12 caratteri,allora avrò200*12

    /**Inizio lettura file**/
    fp_sorgente = fopen(_SORGENTE_,"r");
    fp_ricodifica = fopen(_RICODIFICA_,"w");
    if (fp_sorgente==NULL || fp_ricodifica==NULL){
        printf("\nErrore durante l'apertura del file sorgente o del file di ricodifica!");
        result=FALSE;
    }
    int differenza;
    /**Inizio processazione, stringa per stringa**/
    if (result) {
        /***Fase di acquisizione puntatori alle codifiche****/
        while (fgets(stringa,MAX_S,fp_sorgente) != NULL) {
            strcpy(stringa_mod,stringa);
            for ( i = 0; i < lunghezza; i++) {
                if ((pointer=strstr(stringa_mod,dizionario[i].sottostringa)) != NULL) {
                    differenza=pointer- stringa_mod; //non c'è bisogno di salvare il puntatore
                    /**Shift a destra,di n, se la ricodifica è più grande della codifica**/
                    if (strlen(dizionario[i].sottostringa) < strlen(dizionario[i].ricodifica)){
                         k=differenza + strlen(dizionario[i].sottostringa);
                         shift_dx=abs(strlen(dizionario[i].sottostringa)-strlen(dizionario[i].ricodifica));
                        for ( j = strlen(stringa); j >= k; j--) {
                            stringa_mod[j+shift_dx] = stringa_mod[j];
                        }
                    }
                        /**Shift a sx,di n, se la ricodifica è più piccola della codifica**/
                        /*Altrimenti nulla*/
                    else if (strlen(dizionario[i].sottostringa) > strlen(dizionario[i].ricodifica)) {
                        j=differenza+strlen(dizionario[i].sottostringa);
                        shift_sx=abs(strlen(dizionario[i].sottostringa)-strlen(dizionario[i].ricodifica));
                        for ( ; j <strlen(stringa_mod); j++) {
                            stringa_mod[j-shift_sx] = stringa_mod[j];
                        }
                        k = strlen(stringa_mod)-shift_sx;
                        stringa_mod[k] = '\0';
                    }
                    strncpy(&stringa_mod[differenza],dizionario[i].ricodifica,strlen(dizionario[i].ricodifica));
                }
            }
            /*Stampo la stringa modificata nel file di output*/
            fprintf(fp_ricodifica,"%s",stringa_mod);
        }
        /*Metto qui gli fclose poichè in caso di errore, non verrebbero inizializzati a puntatori non NULL*/
        fclose(fp_sorgente);
        fclose(fp_ricodifica);
    }
}
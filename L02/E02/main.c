/**Vincenzo Petrolo s256499*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __NOMEFILE__ "corse.txt"
#define __N_COMANDI__ 5
#define  __MAX_S__ 31
#define  __MAX_DATI__ 1000

typedef enum{r_date,r_partenza,r_capolinea,r_ritardo,r_fine}comando;

typedef struct {
    char codice_tratta[__MAX_S__];
    char partenza[__MAX_S__];
    char data_part[__MAX_S__];
    char destinazione[__MAX_S__];
    char orario_partenza[__MAX_S__];
    char orario_arrivo[__MAX_S__];
    int ritardo;
}dati;

typedef struct {
    int giorno;
    int mese;
    int anno;
}data;

int leggiFile(dati tabella[]);
int leggiComando();
void selezionaDati(dati tabella[],int lunghezza_tabella,int comando);
int compara_date(char data_l[__MAX_S__],char data_m[__MAX_S__],char data_r[__MAX_S__]);
void string2low(char stringa[__MAX_S__]);

int main() {
    int comando,lunghezza_effettiva;
    dati tabella[__MAX_DATI__];

    lunghezza_effettiva=leggiFile(tabella);
    while ((comando=leggiComando())!= r_fine){
        selezionaDati(tabella,lunghezza_effettiva,comando);
    }
    return 0;
}


int leggiComando(){
    char comandi[][20] = {"date","partenza","capolinea","ritardo","fine"};
    char comando_utente[20];
    int result = -1;

    for (int i = 0; i <__N_COMANDI__ ; i++) {
        printf("\n>");
        printf("%s",comandi[i]);
    }
    printf("\nInserire il comando:\n> ");
    scanf("%s",comando_utente);
    for (int j = 0; j < __N_COMANDI__; j++) {
        if (strcmp(comandi[j],comando_utente) == 0)
            result = j;
    }
    return result;
}

int leggiFile(dati tabella[]) {
    int righe;
    FILE* fp;
    char data_part[__MAX_S__];
    char ora_part[__MAX_S__];
    char ora_arr[__MAX_S__];

    fp = fopen(__NOMEFILE__,"r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"%d",&righe);
    for (int i = 0; i < righe; i++) {
        fscanf(fp,"%s%s%s%s%s%s%d",tabella[i].codice_tratta,tabella[i].partenza,tabella[i].destinazione,tabella[i].data_part,
               tabella[i].orario_partenza,tabella[i].orario_arrivo,&tabella[i].ritardo);
        string2low(tabella[i].codice_tratta);
        string2low(tabella[i].partenza);
        string2low(tabella[i].destinazione); // ho normalizzato la stringa tutto al minimo
    }

    return righe;
}

void selezionaDati(dati tabella[],int lunghezza_tabella,int comando){

    char stringa1[__MAX_S__],stringa2[__MAX_S__];

    switch (comando) {
                                    /**0 intervallo di date, stringhe da acquisire 2**/
        case r_date: {
            scanf("%s%s", stringa1, stringa2);
            string2low(stringa1);
            string2low(stringa2);
            for (int i = 0; i < lunghezza_tabella; i++) {
                if (compara_date(stringa1,tabella[i].data_part,stringa2)) {
                    printf("\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                           "Ora arrivo: %s || Ritardo: %d", tabella[i].codice_tratta, tabella[i].partenza,
                           tabella[i].destinazione,
                           tabella[i].data_part, tabella[i].orario_partenza, tabella[i].orario_arrivo,
                           tabella[i].ritardo);
                }
            }
        }
            break;
        case r_partenza:{            /**1 Corse partite da una fermata, stringhe da acquisire: 1*/
            scanf("%s",stringa1);
            string2low(stringa1);
            for (int i = 0; i < lunghezza_tabella; i++) {
                if (strcmp(tabella[i].partenza,stringa1) == 0){
                    printf("\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                           "Ora arrivo: %s || Ritardo: %d", tabella[i].codice_tratta, tabella[i].partenza,
                           tabella[i].destinazione,
                           tabella[i].data_part, tabella[i].orario_partenza, tabella[i].orario_arrivo,
                           tabella[i].ritardo);
                }
            }
            break;
        }
        case r_capolinea:{            /**2 Corse che fanno capolinea a una certa fermata, stringhe da acquisire: 1*/
            scanf("%s",stringa1);
            string2low(stringa1);
            for (int i = 0; i < lunghezza_tabella; i++) {
                if (strcmp(tabella[i].destinazione,stringa1) == 0){
                    printf("\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                           "Ora arrivo: %s || Ritardo: %d", tabella[i].codice_tratta, tabella[i].partenza,
                           tabella[i].destinazione,
                           tabella[i].data_part, tabella[i].orario_partenza, tabella[i].orario_arrivo,
                           tabella[i].ritardo);
                }
            }
            break;
        }
        case r_ritardo:{            /**3 Corse che hanno ritardato(ritardo != 0) in un certo intervallo di date, stringhe da acquisire: 2*/
            scanf("%s",stringa1); //cerco nelle posizioni di dove dovrebbero essere gli slash
            string2low(stringa1);
            if (stringa1[2] == '/' && stringa1[5] == '/')
            {
                scanf("%s",stringa2); //continuo a leggere
                for (int i = 0; i < lunghezza_tabella; i++) {
                if (compara_date(stringa1,tabella[i].data_part,stringa2) && tabella[i].ritardo !=0) {
                    printf("\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                           "Ora arrivo: %s || Ritardo: %d", tabella[i].codice_tratta, tabella[i].partenza,
                           tabella[i].destinazione,
                           tabella[i].data_part, tabella[i].orario_partenza, tabella[i].orario_arrivo,
                           tabella[i].ritardo);
                    }
                }
            }
            else {
                int ritardo_complessivo = 0;
                for (int i = 0; i < lunghezza_tabella; i++) {
                    if (strcmp(stringa1, tabella[i].codice_tratta) == 0 && tabella[i].ritardo != 0) {
                        ritardo_complessivo += tabella[i].ritardo;
                    }
                }
                printf("\nRitardo complessivo per il codice tratta: %s pari a: %d", stringa1, ritardo_complessivo);
            }
            break;
        }
        default:
            printf("\nCodice comando errato");
    }
    }

int compara_date(char data_l[__MAX_S__],char data_m[__MAX_S__],char data_r[__MAX_S__]){
    /**Comparo anni mesi e giorni trasformandoli in intero*/
    char giorno[3];
    char mese[3];
    char anno[5];
    data date_da_comparare[3]; //0 data_l 1 data_m 2 data_r
    int risultato=0;
/**Salvo i giorni*/
    strncpy(giorno,data_l,2);
    date_da_comparare[0].giorno = atoi(giorno);
    strncpy(giorno,data_m,2);
    date_da_comparare[1].giorno = atoi(giorno);
    strncpy(giorno,data_r,2);
    date_da_comparare[2].giorno = atoi(giorno);
/**Salvo i mesi*/
    strncpy(mese,data_l+3,2); //sposto il puntatore di 3 poichè ricevo i dati in forma gg/mm/aaaa allora mi muovo di 3 posizioni fino all'inizio del mese
    date_da_comparare[0].mese = atoi(mese);
    strncpy(mese,data_m+3,2);
    date_da_comparare[1].mese = atoi(mese);
    strncpy(mese,data_r+3,2);
    date_da_comparare[2].mese = atoi(mese);
/**Salvo gli anni*/
    strncpy(anno,data_l+6,4); //sposto il puntatore di 6 poichè ricevo i dati in forma gg/mm/aaaa allora mi muovo di 6 posizioni fino all'inizio del mese
    date_da_comparare[0].anno = atoi(anno);
    strncpy(anno,data_m+6,4);
    date_da_comparare[1].anno = atoi(anno);
    strncpy(anno,data_r+6,4);
    date_da_comparare[2].anno= atoi(anno);

    /**Albero di decisione*/
    if (date_da_comparare[0].anno <= date_da_comparare[1].anno &&  date_da_comparare[1].anno <= date_da_comparare[2].anno ){
        if (date_da_comparare[0].anno == date_da_comparare[1].anno &&  date_da_comparare[1].anno == date_da_comparare[2].anno ){
            if (date_da_comparare[0].mese == date_da_comparare[1].mese &&  date_da_comparare[1].mese == date_da_comparare[2].mese ){
                if (date_da_comparare[0].giorno == date_da_comparare[1].giorno &&  date_da_comparare[1].giorno == date_da_comparare[2].giorno ){
                    risultato = 1;
                }
            }
        }
        else {
            if (date_da_comparare[0].anno == date_da_comparare[1].anno){
            if (date_da_comparare[0].mese < date_da_comparare[1].mese){
                risultato = 1;
            }
            else if (date_da_comparare[0].mese == date_da_comparare[1].mese){
                if (date_da_comparare[0].giorno <= date_da_comparare[1].giorno){
                        risultato = 1;
                }
            }
        }
        if (date_da_comparare[1].anno == date_da_comparare[2].anno){
            if (date_da_comparare[1].mese < date_da_comparare[2].mese){
                risultato = 1;
            }
            else if (date_da_comparare[1].mese == date_da_comparare[2].mese) {
                if (date_da_comparare[1].giorno <= date_da_comparare[2].giorno){
                    risultato = 1;
                }
            }
        }
        if (date_da_comparare[0].anno <= date_da_comparare[1].anno &&  date_da_comparare[1].anno <= date_da_comparare[2].anno ){
            risultato = 1;
        }
        }
    }
    return risultato;
}

void string2low(char stringa[__MAX_S__]){

    for (int i = 0; i < strlen(stringa); i++) {
        stringa[i]=tolower(stringa[i]);
    }
}
/**Vincenzo Petrolo s256499*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __NOMEFILE__ "corse.txt"
#define __LOGFILE__ "log.txt"
#define __N_COMANDI__ 7
#define  __MAX_S__ 31
#define  __MAX_DATI__ 1000

typedef enum{r_date,r_tratte,r_partenza,r_capolinea,r_ricerca,r_stampa,r_fine}comando;

typedef struct {
    char codice_tratta[__MAX_S__];
    char partenza[__MAX_S__];
    char data_part[__MAX_S__];
    char destinazione[__MAX_S__];
    char orario_partenza[__MAX_S__];
    char orario_arrivo[__MAX_S__];
    int ritardo;
}dati;

typedef enum{VIDEO,FILE_TESTO} stampa;
typedef enum{FALSE,TRUE} boolean;

typedef struct {
    int giorno;
    int mese;
    int anno;
}data;

typedef struct {
    dati *ord_date[__MAX_DATI__];
    boolean date_ordinate;
    dati *ord_codice[__MAX_DATI__];
    boolean codice_ordinato;
    dati *ord_partenza[__MAX_DATI__];
    boolean partenza_ordinato;
    dati *ord_arrivo[__MAX_DATI__];
    boolean arrivo_ordinato;
}set_vettori;


int leggiFile(dati tabella[]);
int leggiComando(stampa tipo_stampa);
void esegui_comandi(dati tabella[],int lunghezza_tabella,set_vettori *vettori,int comando);
void ordinamento(dati tabella[],set_vettori *vettori,int lunghezza,comando richiesta_campo_ordinamento);
void stampa_log(stampa tipo,comando comando,set_vettori vettori,int lunghezza);
void string2low(char stringa[__MAX_S__]);
stampa leggi_tipo_stampa();
void ricerca_dicotomica(set_vettori vettori,int lunghezza,char chiave[__MAX_S__],int l,int r);
void ricerca_lineare(set_vettori vettori,int lunghezza);

int main() {
    int comando,lunghezza_effettiva;
    dati tabella[__MAX_DATI__];
    set_vettori vettori;
    vettori.arrivo_ordinato=FALSE;
    vettori.partenza_ordinato=FALSE;
    vettori.codice_ordinato = FALSE;
    vettori.date_ordinate = FALSE;
    stampa tipo_stampa;

    lunghezza_effettiva=leggiFile(tabella);
    tipo_stampa = leggi_tipo_stampa();
    while ((comando=leggiComando(tipo_stampa)) != r_fine) {
        esegui_comandi(tabella, lunghezza_effettiva,&vettori, comando);
        stampa_log(tipo_stampa,comando,vettori,lunghezza_effettiva);
        tipo_stampa = leggi_tipo_stampa();
    }
    return 0;
}


stampa leggi_tipo_stampa() {

    stampa decisione=VIDEO;
    char stringa[__MAX_S__];
    printf("\nVuoi stampare su file anzichè video?[S/n]");
    scanf("%s",stringa);
    string2low(stringa);
    if (strstr(stringa,"s") != NULL) {
        decisione = FILE_TESTO;
    }

    return decisione;

}

int leggiComando(stampa tipo_stampa){
    char comandi[][50] = {"data","codice","partenza",
                          "arrivo","ricerca","Stampa attuale: ","fine"};
    char comando_utente[20];
    int result = -1;

    for (int i = 0; i <__N_COMANDI__ ; i++) {
        printf("\n>");
        printf("%s",comandi[i]);
        if (i == __N_COMANDI__ -2) {
            if (tipo_stampa == FILE_TESTO)
                printf(" File di testo");
            else
                printf(" Video");
        }
    }
    printf("\nInserire il comando:\n> ");
    scanf("%s",comando_utente);
    string2low(comando_utente);
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

void esegui_comandi(dati tabella[],int lunghezza_tabella,set_vettori *vettori,int comando){

    char stringa1[__MAX_S__],stringa2[__MAX_S__];

    switch (comando) {
        case r_date: {         /**0 Ordinamento per date**/
            ordinamento(tabella,vettori,lunghezza_tabella,comando);
            break;
        }
        case r_tratte:{            /**1 Ordinamento per codice tratta*/
            ordinamento(tabella,vettori,lunghezza_tabella,comando);
            break;
        }

        case r_partenza:{            /**2 Ordinamento per stazione di partenza*/
            ordinamento(tabella,vettori,lunghezza_tabella,comando);
            break;
        }

        case r_capolinea:{            /**3 Ordinamento per stazione di arrivo*/
            ordinamento(tabella,vettori,lunghezza_tabella,comando);
            break;
        }
        case r_ricerca: {
            if (vettori->partenza_ordinato == TRUE) {
                char chiave[__MAX_S__];
                scanf("%s",chiave);
                ricerca_dicotomica(*vettori, lunghezza_tabella,chiave, 0, lunghezza_tabella);
            }
            else{
                for (int k = 0; k < lunghezza_tabella; k++) {
                    vettori->ord_partenza[k] = &tabella[k];
                } //sposto i puntatori nel vettore da ordinare
                ricerca_lineare(*vettori,lunghezza_tabella);}

            break;
        }
        default:
            printf("\nComando errato!");
    }
}

int compara_date(char data_l[__MAX_S__],char data_m[__MAX_S__],char orario1[__MAX_S__],char orario2[__MAX_S__]){
    /**Ritorna 1 se il primo argomento è maggiore del secondo
     * Ritorna -1 se il primo argomento è minore del secondo
     * Ritorna 0 se entrambi gli argomenti sono uguali*/

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
/**Salvo i mesi*/
    strncpy(mese,data_l+3,2); //sposto il puntatore di 3 poichè ricevo i dati in forma gg/mm/aaaa allora mi muovo di 3 posizioni fino all'inizio del mese
    date_da_comparare[0].mese = atoi(mese);
    strncpy(mese,data_m+3,2);
    date_da_comparare[1].mese = atoi(mese);
/**Salvo gli anni*/
    strncpy(anno,data_l+6,4); //sposto il puntatore di 6 poichè ricevo i dati in forma gg/mm/aaaa allora mi muovo di 6 posizioni fino all'inizio del mese
    date_da_comparare[0].anno = atoi(anno);
    strncpy(anno,data_m+6,4);
    date_da_comparare[1].anno = atoi(anno);

    if (date_da_comparare[0].anno > date_da_comparare[1].anno)
        risultato= 1;
    else if (date_da_comparare[0].anno < date_da_comparare[1].anno)
        risultato= -1;
    else if (date_da_comparare[0].anno == date_da_comparare[1].anno)
        if (date_da_comparare[0].mese > date_da_comparare[1].mese)
            risultato= 1;
        else if (date_da_comparare[0].mese < date_da_comparare[1].mese)
            risultato= -1;
        else if (date_da_comparare[0].mese == date_da_comparare[1].mese)
            if (date_da_comparare[0].giorno > date_da_comparare[1].giorno)
                risultato= 1;
            else if (date_da_comparare[0].giorno < date_da_comparare[1].giorno)
                risultato= -1;
            else if (date_da_comparare[0].giorno == date_da_comparare[1].giorno)
                if (strcmp(orario1,orario2) > 0)
                    risultato= 1;
                else if (strcmp(orario1,orario2) < 0)
                    risultato= -1;
                else
                    risultato= 0;
    return risultato;
}


void string2low(char stringa[__MAX_S__]){

    for (int i = 0; i < strlen(stringa); i++) {
        stringa[i]=tolower(stringa[i]);
    }
}

void ordinamento(dati tabella[],set_vettori *vettori,int lunghezza,comando richiesta_campo_ordinamento) {

    /*Applico il Selection Sort*/
    switch (richiesta_campo_ordinamento) {
        case r_date: {         /**0 Ordinamento per date**/
             if (vettori->date_ordinate != TRUE){
                    for (int k = 0; k < lunghezza; k++) {
                        vettori->ord_date[k] = &tabella[k];
                    } //sposto i puntatori nel vettore da ordinare

                    //siccome lo sto ordinando setto la variabile che si riferisce al fatto se ha ordinato o meno gia il vettore
                    vettori->date_ordinate = TRUE;

                    /*Selection sort ha inizio*/
                    int i, j, l = 0, r = lunghezza - 1;
                    int posizione;
                    int minimo;
                    dati *tmp;
                    for (i = l; i < r; i++) {
                        //associo il minimo all'elemento i-esimo della struttura
                        minimo = i;
                        for (j = i + 1; j <= r; j++)
                            if (compara_date((vettori->ord_date[j])->data_part,(vettori->ord_date[minimo])->data_part,(vettori->ord_date[j])->orario_partenza,(vettori->ord_date[minimo])->data_part) == -1) //se è minore del minimo
                            {minimo = j;}
                        //ordino il vettore di puntatori anzichè quello effettivo
                        if (minimo != i) {
                            tmp = vettori->ord_date[i];
                            vettori->ord_date[i] = vettori->ord_date[minimo];
                            vettori->ord_date[minimo] = tmp;
                        }
                }
            }
            break;
        }
        case r_tratte: {            /**1 Ordinamento per codice tratta*/
            if (vettori->codice_ordinato != TRUE) {
                for (int k = 0; k < lunghezza ; k++) {
                    vettori->ord_codice[k] = &tabella[k];
                } //sposto i puntatori nel vettore da ordinare
                //siccome lo sto ordinando setto la variabile che si riferisce al fatto se ha ordinato o meno gia il vettore
                vettori->codice_ordinato = TRUE;
                /**Per questo tipo di dato preferisco usare l'insertion sort, sempre stabile,in loco*/
                int i, j, l=0, r=lunghezza-1;
                dati *x;
                for(i = l+1; i <= r; i++) {
                    x = vettori->ord_codice[i];
                    j = i - 1;
                    while (j >= l && strcmp(x->codice_tratta,(vettori->ord_codice[j])->codice_tratta) < 0) {
                        vettori->ord_codice[j+1] = vettori->ord_codice[j];
                        j--;
                    }
                    vettori->ord_codice[j+1] = x;
                }
            }
            break;
        }

        case r_partenza: {            /**2 Ordinamento per stazione di partenza*/
            if (vettori->partenza_ordinato != TRUE) {

                for (int k = 0; k < lunghezza; k++) {
                    vettori->ord_partenza[k] = &tabella[k];
                } //sposto i puntatori nel vettore da ordinare
                //siccome lo sto ordinando setto la variabile che si riferisce al fatto se ha ordinato o meno gia il vettore
                vettori->partenza_ordinato = TRUE;
                /**Per questo tipo di dato preferisco usare l'insertion sort, sempre stabile,in loco*/
                int i, j, l = 0, r = lunghezza - 1;
                dati *x;
                for (i = l + 1; i <= r; i++) {
                    x = vettori->ord_partenza[i];
                    j = i - 1;
                    while (j >= l && strcmp(x->partenza, (vettori->ord_partenza[j])->partenza) < 0) {
                        vettori->ord_partenza[j + 1] = vettori->ord_partenza[j];
                        j--;
                    }
                    vettori->ord_partenza[j + 1] = x;
                }
            }
            break;
        }

        case r_capolinea: {            /**3 Ordinamento per stazione di arrivo*/
            if (vettori->arrivo_ordinato != TRUE ) {
                for (int k = 0; k < lunghezza; k++) {
                    vettori->ord_arrivo[k] = &tabella[k];
                } //sposto i puntatori nel vettore da ordinare
                //siccome lo sto ordinando setto la variabile che si riferisce al fatto se ha ordinato o meno gia il vettore
                vettori->arrivo_ordinato = TRUE;
                /**Per questo tipo di dato preferisco usare l'insertion sort, sempre stabile,in loco*/
                int i, j, l = 0, r = lunghezza - 1;
                dati *x;
                for (i = l + 1; i <= r; i++) {
                    x = vettori->ord_arrivo[i];
                    j = i - 1;
                    while (j >= l && strcmp(x->destinazione, (vettori->ord_arrivo[j])->destinazione) < 0) {
                        vettori->ord_arrivo[j + 1] = vettori->ord_arrivo[j];
                        j--;
                    }
                    vettori->ord_arrivo[j + 1] = x;
                }
            }
            break;
        }
        default:
            break;
    }

}

void stampa_log(stampa tipo,comando comando,set_vettori vettori,int lunghezza) {

    FILE * fp;
    if (tipo == FILE_TESTO) {
        fp = fopen(__LOGFILE__, "a");
    }
    else {
        fp = stdout;
    }
    switch (comando) {
        case r_date:
        {
            fprintf(fp,"ORDINAMENTO DATE");
            for (int i = 0; i < lunghezza; i++) {
                fprintf(fp,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                       "Ora arrivo: %s ", (*(vettori.ord_date[i])).codice_tratta, (*(vettori.ord_date[i])).partenza,
                       (*(vettori.ord_date[i])).destinazione,
                       (*(vettori.ord_date[i])).data_part,(*(vettori.ord_date[i])).orario_partenza, (*(vettori.ord_date[i])).orario_arrivo);
            }
            break;
        }
        case r_tratte:
        {
            fprintf(fp,"\nORDINAMENTO CODICI");
            for (int i = 0; i < lunghezza; i++) {
                fprintf(fp,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                       "Ora arrivo: %s ", (*(vettori.ord_codice[i])).codice_tratta, (*(vettori.ord_codice[i])).partenza,
                       (*(vettori.ord_codice[i])).destinazione,
                       (*(vettori.ord_codice[i])).data_part,(*(vettori.ord_codice[i])).orario_partenza, (*(vettori.ord_codice[i])).orario_arrivo);
            }

            break;
        }
        case r_partenza:
        {
            fprintf(fp,"\nORDINAMENTO PER STAZIONI DI PARTENZA");
            for (int i = 0; i < lunghezza; i++) {
                fprintf(fp,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                       "Ora arrivo: %s ", (*(vettori.ord_partenza[i])).codice_tratta, (*(vettori.ord_partenza[i])).partenza,
                       (*(vettori.ord_partenza[i])).destinazione,
                       (*(vettori.ord_partenza[i])).data_part,(*(vettori.ord_partenza[i])).orario_partenza, (*(vettori.ord_partenza[i])).orario_arrivo);
            }
            break;
        }
        case r_capolinea:
        {
            fprintf(fp,"ORDINAMENTO PER STAZIONI DI ARRIVO");
            for (int i = 0; i < lunghezza; i++) {
                fprintf(fp,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                       "Ora arrivo: %s ", (*(vettori.ord_arrivo[i])).codice_tratta, (*(vettori.ord_arrivo[i])).partenza,
                       (*(vettori.ord_arrivo[i])).destinazione,
                       (*(vettori.ord_arrivo[i])).data_part,(*(vettori.ord_arrivo[i])).orario_partenza, (*(vettori.ord_arrivo[i])).orario_arrivo);
            }
            break;
        }
        default:
            break;

    }
    if (fp != stdout)
        fclose(fp);
}

void ricerca_lineare(set_vettori vettori,int lunghezza) {
    char chiave[__MAX_S__];
    scanf("%s",chiave);

    printf("\nRISULTATI RICERCA: ");
    for (int i = 0; i < lunghezza; i++) {
        if (strncmp(vettori.ord_partenza[i]->partenza,chiave,2) == 0)
            fprintf(stdout,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                       "Ora arrivo: %s ", (*(vettori.ord_partenza[i])).codice_tratta, (*(vettori.ord_partenza[i])).partenza,
                    (*(vettori.ord_partenza[i])).destinazione,
                    (*(vettori.ord_partenza[i])).data_part,(*(vettori.ord_partenza[i])).orario_partenza, (*(vettori.ord_partenza[i])).orario_arrivo);
    }
}

void ricerca_dicotomica(set_vettori vettori,int lunghezza,char chiave[__MAX_S__],int l,int r) {
    if (l>r)
        return;
    int m = (r+l)/2;
    int risultato = strncmp(chiave,vettori.ord_partenza[m]->partenza,strlen(chiave));

    if ( risultato > 0)
        return ricerca_dicotomica(vettori,lunghezza,chiave,m+1,r);
    else if (risultato < 0)
        return ricerca_dicotomica(vettori,lunghezza,chiave,l,m-1);
    else if (risultato == 0) {
        printf("\nRISULTATI RICERCA: ");
        fprintf(stdout, "\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                        "Ora arrivo: %s ", (*(vettori.ord_partenza[m])).codice_tratta,
                (*(vettori.ord_partenza[m])).partenza,
                (*(vettori.ord_partenza[m])).destinazione,
                (*(vettori.ord_partenza[m])).data_part, (*(vettori.ord_partenza[m])).orario_partenza,
                (*(vettori.ord_partenza[m])).orario_arrivo);
        int tmp = m;
        while ( ++m<lunghezza && strncmp(chiave, vettori.ord_partenza[m]->partenza, strlen(chiave)) == 0 && m<lunghezza)
        {    fprintf(stdout, "\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                            "Ora arrivo: %s ", (*(vettori.ord_partenza[m])).codice_tratta,
                    (*(vettori.ord_partenza[m])).partenza,
                    (*(vettori.ord_partenza[m])).destinazione,
                    (*(vettori.ord_partenza[m])).data_part, (*(vettori.ord_partenza[m])).orario_partenza,
                    (*(vettori.ord_partenza[m])).orario_arrivo);
        }
        m = tmp;
        while ( --m>=0 && strncmp(chiave, vettori.ord_partenza[m]->partenza, strlen(chiave)) == 0 )
        {    fprintf(stdout, "\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                             "Ora arrivo: %s ", (*(vettori.ord_partenza[m])).codice_tratta,
                     (*(vettori.ord_partenza[m])).partenza,
                     (*(vettori.ord_partenza[m])).destinazione,
                     (*(vettori.ord_partenza[m])).data_part, (*(vettori.ord_partenza[m])).orario_partenza,
                     (*(vettori.ord_partenza[m])).orario_arrivo);
        }
        return;
    }
}
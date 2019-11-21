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

/**Minor data structs*/
typedef enum{r_date,r_tratte,r_partenza,r_capolinea,r_ricerca,r_stampa,r_fine}comando;
typedef enum{VIDEO,FILE_TESTO} stampa;
typedef enum{FALSE,TRUE} boolean;
/**Minor data structs*/

/**Major data struct*/
typedef struct {
    char codice_tratta[__MAX_S__];
    char partenza[__MAX_S__];
    char data_part[__MAX_S__];
    char destinazione[__MAX_S__];
    char orario_partenza[__MAX_S__];
    char orario_arrivo[__MAX_S__];
    int ritardo;
}dati;
	/**Prototypes*/
	void ricerca_dicotomica(dati tabella[],int lunghezza,char chiave[__MAX_S__],int l,int r);
	void ricerca_lineare(dati tabella[],int lunghezza);
	void esegui_comandi(dati tabella[],int *ultimo_ordinamento,int lunghezza_tabella,int comando);
	void ordinamento(dati tabella[],int lunghezza,comando richiesta_campo_ordinamento);
	void stampa_log(dati tabella[],stampa tipo,comando comando,int lunghezza);
	/**Prototypes*/	
/**Major data struct*/

/**Date struct*/
typedef struct {
    int giorno;
    int mese;
    int anno;
}data;
/**Date struct*/

/**File interactive prototypes*/
int leggiFile(dati tabella[]);
/**File interactive prototypes*/

/**Menu prototypes*/
int leggiComando(stampa tipo_stampa);
stampa leggi_tipo_stampa();
/**Menu prototypes*/

/**Other prototypes*/
void string2low(char stringa[__MAX_S__]);
/**Other prototypes*/

int main() {
    int comando,lunghezza_effettiva,ultimo_ordinamento;
    dati tabella[__MAX_DATI__];
    char selezione_stampa[__MAX_S__];
    stampa tipo_stampa;
    int chiave_ordinamento;

    lunghezza_effettiva=leggiFile(tabella);
    tipo_stampa = leggi_tipo_stampa();
    while ((comando=leggiComando(tipo_stampa)) != r_fine) {
        esegui_comandi(tabella,&chiave_ordinamento, lunghezza_effettiva, comando);
        stampa_log(tabella,tipo_stampa,comando,lunghezza_effettiva);
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

void esegui_comandi(dati tabella[],int *ultimo_ordinamento,int lunghezza_tabella,int comando){

    char stringa1[__MAX_S__],stringa2[__MAX_S__];

    switch (comando) {
        case r_date: {         /**0 Ordinamento per date**/
			if (*ultimo_ordinamento != r_date){
                ordinamento(tabella,lunghezza_tabella,comando);
                *ultimo_ordinamento = r_date;
            }
            break;
        }
        case r_tratte:{            /**1 Ordinamento per codice tratta*/
            if (*ultimo_ordinamento != r_tratte){
                ordinamento(tabella,lunghezza_tabella,comando);
                *ultimo_ordinamento = r_tratte;
            }
            break;
        }

        case r_partenza:{            /**2 Ordinamento per stazione di partenza*/
            if (*ultimo_ordinamento != r_partenza){
                ordinamento(tabella,lunghezza_tabella,comando);
                *ultimo_ordinamento = r_partenza;
            }
            break;
        }

        case r_capolinea:{            /**3 Ordinamento per stazione di arrivo*/
            if (*ultimo_ordinamento != r_capolinea){
                ordinamento(tabella,lunghezza_tabella,comando);
                *ultimo_ordinamento = r_capolinea;
            }

            break;
        }
        case r_ricerca: {
            if (*ultimo_ordinamento == r_partenza) {
                char chiave[__MAX_S__];
                scanf("%s",chiave);
                ricerca_dicotomica(tabella,lunghezza_tabella,chiave, 0, lunghezza_tabella);
            }
            else{
                ricerca_lineare(tabella,lunghezza_tabella);}

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

void ordinamento(dati tabella[],int lunghezza,comando richiesta_campo_ordinamento) {

    /*Applico il Selection Sort che è stabile e in loco*/
    switch (richiesta_campo_ordinamento) {
        case r_date: {         /**0 Ordinamento per date**/
            //siccome lo sto ordinando setto la variabile che si riferisce al fatto se ha ordinato o meno gia il vettore
            /*Selection sort ha inizio*/

            int i, j, l = 0, r = lunghezza - 1;
            int posizione;
            int minimo;
            dati tmp;
            for (i = l; i < r; i++) {
                //associo il minimo all'elemento i-esimo della struttura
                minimo = i;
                for (j = i + 1; j <= r; j++)
                    if (compara_date(tabella[j].data_part,tabella[minimo].data_part,tabella[j].orario_partenza,tabella[minimo].orario_partenza) == -1) //se è minore del minimo
                    {minimo = j;}
                //ordino il vettore di puntatori anzichè quello effettivo
                if (minimo != i) {
                    tmp = tabella[i];
                    tabella[i] = tabella[minimo];
                    tabella[minimo] = tmp;
                }
        }
            break;
        }
        case r_tratte: {            /**1 Ordinamento per codice tratta*/
                /**Per questo tipo di dato preferisco usare l'insertion sort, sempre stabile,in loco*/
                int i, j, l=0, r=lunghezza-1;
                dati x;
                for(i = l+1; i <= r; i++) {
                    x = tabella[i];
                    j = i - 1;
                    while (j >= l && strcmp(x.codice_tratta,tabella[j].codice_tratta) < 0) {
                        tabella[j+1] = tabella[j];
                        j--;
                    }
                    tabella[j+1] = x;
                }
            break;
        }

        case r_partenza: {            /**2 Ordinamento per stazione di partenza*/
            int i, j, l=0, r=lunghezza-1;
            dati x;
            for(i = l+1; i <= r; i++) {
                x = tabella[i];
                j = i - 1;
                while (j >= l && strcmp(x.partenza,tabella[j].partenza) < 0) {
                    tabella[j+1] = tabella[j];
                    j--;
                }
                tabella[j+1] = x;
            }
            break;
        }

        case r_capolinea: {            /**3 Ordinamento per stazione di arrivo*/
            int i, j, l=0, r=lunghezza-1;
            dati x;
            for(i = l+1; i <= r; i++) {
                x = tabella[i];
                j = i - 1;
                while (j >= l && strcmp(x.destinazione,tabella[j].destinazione) < 0) {
                    tabella[j+1] = tabella[j];
                    j--;
                }
                tabella[j+1] = x;
            }
            break;
        }
        default:
            break;
    }

}

void stampa_log(dati tabella[],stampa tipo,comando comando,int lunghezza) {

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
                       "Ora arrivo: %s ", tabella[i].codice_tratta, tabella[i].partenza,
                        tabella[i].destinazione,
                        tabella[i].data_part,tabella[i].orario_partenza,tabella[i].orario_arrivo);
            }
            break;
        }
        case r_tratte:
        {
            fprintf(fp,"\nORDINAMENTO CODICI");
            for (int i = 0; i < lunghezza; i++) {
                fprintf(fp,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                           "Ora arrivo: %s ", tabella[i].codice_tratta, tabella[i].partenza,
                        tabella[i].destinazione,
                        tabella[i].data_part,tabella[i].orario_partenza,tabella[i].orario_arrivo);
            }

            break;
        }
        case r_partenza:
        {
            fprintf(fp,"\nORDINAMENTO PER STAZIONI DI PARTENZA");
            for (int i = 0; i < lunghezza; i++) {
                fprintf(fp,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                           "Ora arrivo: %s ", tabella[i].codice_tratta, tabella[i].partenza,
                        tabella[i].destinazione,
                        tabella[i].data_part,tabella[i].orario_partenza,tabella[i].orario_arrivo);
            }
            break;
        }
        case r_capolinea:
        {
            fprintf(fp,"ORDINAMENTO PER STAZIONI DI ARRIVO");
            for (int i = 0; i < lunghezza; i++) {
                fprintf(fp,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                           "Ora arrivo: %s ", tabella[i].codice_tratta, tabella[i].partenza,
                        tabella[i].destinazione,
                        tabella[i].data_part,tabella[i].orario_partenza,tabella[i].orario_arrivo);
            }
            break;
        }
        default:
            break;

    }
    if (fp != stdout)
        fclose(fp);
}

void ricerca_lineare(dati tabella[],int lunghezza) {
    char chiave[__MAX_S__];
    scanf("%s",chiave);

    printf("\nRISULTATI RICERCA: ");
    for (int i = 0; i < lunghezza; i++) {
        if (strncmp(tabella[i].partenza,chiave,2) == 0)
            fprintf(stdout,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                       "Ora arrivo: %s ", tabella[i].codice_tratta, tabella[i].partenza,
                    tabella[i].destinazione,
                    tabella[i].data_part,tabella[i].orario_partenza,tabella[i].orario_arrivo);
    }
}

void ricerca_dicotomica(dati tabella[],int lunghezza,char chiave[__MAX_S__],int l,int r) {
    
    if (l>r)
        return;

    int m = (r+l)/2;
    int risultato = strncmp(chiave,tabella[m].partenza,strlen(chiave));

    if ( risultato > 0)
        return ricerca_dicotomica(tabella,lunghezza,chiave,m+1,r);
    else if (risultato < 0)
        return ricerca_dicotomica(tabella,lunghezza,chiave,l,m-1);
    else if (risultato == 0) {
        printf("\nRISULTATI RICERCA: ");
        fprintf(stdout,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                   "Ora arrivo: %s ", tabella[m].codice_tratta, tabella[m].partenza,
                tabella[m].destinazione,
                tabella[m].data_part,tabella[m].orario_partenza,tabella[m].orario_arrivo);
        int tmp = m;
        while ( ++m <lunghezza && strncmp(chiave, tabella[m].partenza, strlen(chiave)) == 0)
        {    fprintf(stdout,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                            "Ora arrivo: %s ", tabella[m].codice_tratta, tabella[m].partenza,
                     tabella[m].destinazione,
                     tabella[m].data_part,tabella[m].orario_partenza,tabella[m].orario_arrivo);
        }
        m = tmp;
        while ( --m>=0 &&strncmp(chiave, tabella[m].partenza, strlen(chiave)) == 0)
        {    fprintf(stdout,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                            "Ora arrivo: %s ", tabella[m].codice_tratta, tabella[m].partenza,
                     tabella[m].destinazione,
                     tabella[m].data_part,tabella[m].orario_partenza,tabella[m].orario_arrivo);
        }
        return;
    }
}

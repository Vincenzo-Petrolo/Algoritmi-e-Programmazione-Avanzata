/**Vincenzo Petrolo s256499*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __MAX_NOME_FILE__ 30 //potrei voler leggere un file di log che scritto come log_gg/mm/aaa.txt
#define __LOGFILE__ "log.txt"
#define __N_COMANDI__ 8
#define  __MAX_S__ 31
#define  __N_ORDINAMENTI__ 4

typedef enum{r_date,r_tratte,r_partenza,r_capolinea,r_ricerca,r_stampa,r_nomefile,r_fine}comando;

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
    dati* *v_ordinamenti[__N_ORDINAMENTI__];//matrice di puntatori degli ordinamenti, 0 date,1 codice,2 partenza,3 arrivo
    boolean date_ordinate;
    boolean codice_ordinato;
    boolean partenza_ordinato;
    boolean arrivo_ordinato;
}set_vettori;


int leggiFile(dati **tabella,set_vettori *vettori, int * n,char *nome_file);
int leggiComando(stampa tipo_stampa);
void esegui_comandi(dati tabella[],int lunghezza_tabella,set_vettori *vettori,int comando);
void ordinamento(dati tabella[],set_vettori *vettori,int lunghezza,comando richiesta_campo_ordinamento);
void stampa_log(stampa tipo,comando comando,set_vettori vettori,int lunghezza);
void string2low(char stringa[__MAX_S__]);
void string2upper(char stringa[__MAX_S__]);
stampa leggi_tipo_stampa();
void ricerca_dicotomica(set_vettori vettori,int lunghezza,char chiave[__MAX_S__],int l,int r);
void ricerca_lineare(set_vettori vettori,int lunghezza);
void leggi_nome_file(char *nomefile);

int main() {
    int comando,lunghezza_effettiva,n;
    dati *tabella;
    char nomefile[__MAX_NOME_FILE__];
    stampa tipo_stampa;
    set_vettori vettori;

        //Inizializzo i vettori
    vettori.partenza_ordinato = FALSE;
    vettori.date_ordinate = FALSE;
    vettori.codice_ordinato  = FALSE;
    vettori.arrivo_ordinato = FALSE;

    leggi_nome_file(nomefile);

    lunghezza_effettiva=leggiFile(&tabella,&vettori,&n,nomefile);

    tipo_stampa = leggi_tipo_stampa();
    while ((comando = leggiComando(tipo_stampa)) != r_fine) {

        if (comando == r_nomefile) {

            free(tabella);

            for (int i = 0; i < __N_ORDINAMENTI__; i++) {
                free(vettori.v_ordinamenti[i]);
            }
            leggi_nome_file(nomefile);
            lunghezza_effettiva = leggiFile(&tabella, &vettori, &n, nomefile);
            vettori.partenza_ordinato = FALSE;
            vettori.date_ordinate = FALSE;
            vettori.codice_ordinato = FALSE;
            vettori.arrivo_ordinato = FALSE;
        }
            esegui_comandi(tabella, lunghezza_effettiva, &vettori, comando);
            stampa_log(tipo_stampa, comando, vettori, lunghezza_effettiva);
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
                          "arrivo","ricerca","Stampa attuale: ","nome_file","fine"};
    char comando_utente[20];
    int result = -1;

    for (int i = 0; i <__N_COMANDI__ ; i++) {
        printf("\n>");
        printf("%s",comandi[i]);
        if (i == __N_COMANDI__ -3) {
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

int leggiFile(dati **tabella,set_vettori *vettori, int * n,char *nome_file){ //rendere dinamica
    FILE* fp;
    int righe;
    dati tabella_supporto;
    dati *tmp;
    dati **temp1;
    int i;

    fp = fopen(nome_file,"r");

    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"%d",&righe);
    if ((tmp = (dati *) malloc (righe * sizeof(dati))) != NULL) {
        *tabella = tmp;
    }
    else{
        printf("\nMemoria insufficiente!");
        exit(EXIT_FAILURE);
    }

    for (int j = 0; j < righe; j++) {
        fscanf(fp,"%s%s%s%s%s%s%d",tabella_supporto.codice_tratta,tabella_supporto.partenza,
               tabella_supporto.destinazione,tabella_supporto.data_part,tabella_supporto.orario_partenza,
               tabella_supporto.orario_arrivo,&tabella_supporto.ritardo);
        (*tabella)[j] = tabella_supporto;
    }
    fclose(fp);


    for (i = 0; i < __N_ORDINAMENTI__ ; i++) { //dopo aver scandito il file, creo nell'HEAP i vettori di ordinamento
        //se l'operazione fallisce allora verifico di averne almeno creato 1, e laovoro solo su quello
        //lo comunico alle altre funzioni tramite una variabile globale
        if ((temp1 = (dati **) malloc(righe * sizeof(dati *))) != NULL){ //verifico che non sia null

            (vettori->v_ordinamenti[i]) = temp1;  // dal puntatore alla struct

        //arrivo al campo della struct che è un puntatore a un vettore di puntatori
        //dereferenzio all'i-esimo elemento e in quell'i-esimo salvo il puntatore
        //alla memoria allocata
        }
    }
    *n = i; //salvo il numero di iterazioni per vedere se almeno ho salvato un vettore
    //su cui posso fare gli ordinamenti

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
                    scanf("%s", chiave);
                    string2upper(chiave);
                    ricerca_dicotomica(*vettori, lunghezza_tabella, chiave, 0, lunghezza_tabella);
                } else {
                    for (int k = 0; k < lunghezza_tabella; k++) {
                        vettori->v_ordinamenti[r_partenza][k] = &tabella[k];
                    } //sposto i puntatori nel vettore da ordinare
                    ricerca_lineare(*vettori, lunghezza_tabella);
                }
            }
        case r_nomefile:
            break;
        default:
            printf("\nComando errato!");
            break;
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

void string2upper(char stringa[__MAX_S__]) {
    for (int i = 0; i < strlen(stringa); i++) {
        stringa[i]=toupper(stringa[i]);
    }
}

void ordinamento(dati tabella[],set_vettori *vettori,int lunghezza,comando richiesta_campo_ordinamento){

    switch (richiesta_campo_ordinamento) {
        case r_date: {         /**0 Ordinamento per date**/
            if (vettori->date_ordinate != TRUE) {
                for (int k = 0; k < lunghezza; k++) {
                    vettori->v_ordinamenti[r_date][k] = &tabella[k];
                } //sposto i puntatori nel vettore da ordinare
                vettori->date_ordinate = TRUE;

                //siccome lo sto ordinando setto la variabile che si riferisce al fatto se ha ordinato o meno gia il vettore

                /*Selection sort ha inizio*/
                int i, j, l = 0, r = lunghezza - 1;
                int posizione;
                int minimo;
                dati *tmp;
                for (i = l; i < r; i++) {
                    //associo il minimo all'elemento i-esimo della struttura
                    minimo = i;
                    for (j = i + 1; j <= r; j++)
                        if (compara_date((vettori->v_ordinamenti[r_date][j])->data_part,
                                         (vettori->v_ordinamenti[r_date][minimo])->data_part,
                                         (vettori->v_ordinamenti[r_date][j])->orario_partenza,
                                         (vettori->v_ordinamenti[r_date][minimo])->data_part) ==
                            -1) //se è minore del minimo
                        { minimo = j; }
                    //ordino il vettore di puntatori anzichè quello effettivo
                    if (minimo != i) {
                        tmp = vettori->v_ordinamenti[r_date][i];
                        vettori->v_ordinamenti[r_date][i] = vettori->v_ordinamenti[r_date][minimo];
                        vettori->v_ordinamenti[r_date][minimo] = tmp;
                    }
                }
            }
            break;
        }
        case r_tratte: {            /**1 Ordinamento per codice tratta*/
            if (vettori->codice_ordinato != TRUE) {
                for (int k = 0; k < lunghezza; k++) {
                    vettori->v_ordinamenti[r_tratte][k] = &tabella[k];
                } //sposto i puntatori nel vettore da ordinare
                //siccome lo sto ordinando setto la variabile che si riferisce al fatto se ha ordinato o meno gia il vettore
                vettori->codice_ordinato = TRUE;
                /**Per questo tipo di dato preferisco usare l'insertion sort, sempre stabile,in loco*/
                int i, j, l = 0, r = lunghezza - 1;
                dati *x;
                for (i = l + 1; i <= r; i++) {
                    x = vettori->v_ordinamenti[r_tratte][i];
                    j = i - 1;
                    while (j >= l &&
                           strcmp(x->codice_tratta, (vettori->v_ordinamenti[r_tratte][j])->codice_tratta) < 0) {
                        vettori->v_ordinamenti[r_tratte][j + 1] = vettori->v_ordinamenti[r_tratte][j];
                        j--;
                    }
                    vettori->v_ordinamenti[r_tratte][j + 1] = x;
                }
            }
            break;
        }

        case r_partenza: {            /**2 Ordinamento per stazione di partenza*/
            if (vettori->partenza_ordinato != TRUE) {

                for (int k = 0; k < lunghezza; k++) {
                    vettori->v_ordinamenti[r_partenza][k] = &tabella[k];
                } //sposto i puntatori nel vettore da ordinare
                //siccome lo sto ordinando setto la variabile che si riferisce al fatto se ha ordinato o meno gia il vettore
                vettori->partenza_ordinato = TRUE;
                /**Per questo tipo di dato preferisco usare l'insertion sort, sempre stabile,in loco*/
                int i, j, l = 0, r = lunghezza - 1;
                dati *x;
                for (i = l + 1; i <= r; i++) {
                    x = vettori->v_ordinamenti[r_partenza][i];
                    j = i - 1;
                    while (j >= l && strcmp(x->partenza, (vettori->v_ordinamenti[r_partenza][j])->partenza) < 0) {
                        vettori->v_ordinamenti[r_partenza][j + 1] = vettori->v_ordinamenti[r_partenza][j];
                        j--;
                    }
                    vettori->v_ordinamenti[r_partenza][j + 1] = x;
                }
            }
            break;
        }

        case r_capolinea: {            /**3 Ordinamento per stazione di arrivo*/
            if (vettori->arrivo_ordinato != TRUE) {
                for (int k = 0; k < lunghezza; k++) {
                    vettori->v_ordinamenti[r_capolinea][k] = &tabella[k];
                } //sposto i puntatori nel vettore da ordinare
                //siccome lo sto ordinando setto la variabile che si riferisce al fatto se ha ordinato o meno gia il vettore
                vettori->arrivo_ordinato = TRUE;
                /**Per questo tipo di dato preferisco usare l'insertion sort, sempre stabile,in loco*/
                int i, j, l = 0, r = lunghezza - 1;
                dati *x;
                for (i = l + 1; i <= r; i++) {
                    x = vettori->v_ordinamenti[r_capolinea][i];
                    j = i - 1;
                    while (j >= l &&
                           strcmp(x->destinazione, (vettori->v_ordinamenti[r_capolinea][j])->destinazione) < 0) {
                        vettori->v_ordinamenti[r_capolinea][j + 1] = vettori->v_ordinamenti[r_capolinea][j];
                        j--;
                    }
                    vettori->v_ordinamenti[r_capolinea][j + 1] = x;
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
        case r_date: {
            fprintf(fp, "ORDINAMENTO DATE");
            for (int i = 0; i < lunghezza; i++) {
                fprintf(fp,
                        "\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                        "Ora arrivo: %s ", (*(vettori.v_ordinamenti[r_date][i])).codice_tratta,
                        (*(vettori.v_ordinamenti[r_date][i])).partenza,
                        (*(vettori.v_ordinamenti[r_date][i])).destinazione,
                        (*(vettori.v_ordinamenti[r_date][i])).data_part,
                        (*(vettori.v_ordinamenti[r_date][i])).orario_partenza,
                        (*(vettori.v_ordinamenti[r_date][i])).orario_arrivo);
            }
            break;
        }
        case r_tratte: {
            fprintf(fp, "\nORDINAMENTO CODICI");
            for (int i = 0; i < lunghezza; i++) {
                fprintf(fp,
                        "\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                        "Ora arrivo: %s ", (*(vettori.v_ordinamenti[r_tratte][i])).codice_tratta,
                        (*(vettori.v_ordinamenti[r_tratte][i])).partenza,
                        (*(vettori.v_ordinamenti[r_tratte][i])).destinazione,
                        (*(vettori.v_ordinamenti[r_tratte][i])).data_part,
                        (*(vettori.v_ordinamenti[r_tratte][i])).orario_partenza,
                        (*(vettori.v_ordinamenti[r_tratte][i])).orario_arrivo);
            }

            break;
        }
        case r_partenza: {
            fprintf(fp, "\nORDINAMENTO PER STAZIONI DI PARTENZA");
            for (int i = 0; i < lunghezza; i++) {
                fprintf(fp,
                        "\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                        "Ora arrivo: %s ", (*(vettori.v_ordinamenti[r_partenza][i])).codice_tratta,
                        (*(vettori.v_ordinamenti[r_partenza][i])).partenza,
                        (*(vettori.v_ordinamenti[r_partenza][i])).destinazione,
                        (*(vettori.v_ordinamenti[r_partenza][i])).data_part,
                        (*(vettori.v_ordinamenti[r_partenza][i])).orario_partenza,
                        (*(vettori.v_ordinamenti[r_partenza][i])).orario_arrivo);
            }
            break;
        }
        case r_capolinea: {
            fprintf(fp, "ORDINAMENTO PER STAZIONI DI ARRIVO");
            for (int i = 0; i < lunghezza; i++) {
                fprintf(fp,
                        "\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                        "Ora arrivo: %s ", (*(vettori.v_ordinamenti[r_capolinea][i])).codice_tratta,
                        (*(vettori.v_ordinamenti[r_capolinea][i])).partenza,
                        (*(vettori.v_ordinamenti[r_capolinea][i])).destinazione,
                        (*(vettori.v_ordinamenti[r_capolinea][i])).data_part,
                        (*(vettori.v_ordinamenti[r_capolinea][i])).orario_partenza,
                        (*(vettori.v_ordinamenti[r_capolinea][i])).orario_arrivo);
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
    string2upper(chiave);
    printf("\nRISULTATI RICERCA: ");
    for (int i = 0; i < lunghezza; i++) {
        if (strncmp((vettori.v_ordinamenti[r_partenza][i]->partenza),chiave,2) == 0)
            fprintf(stdout,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                           "Ora arrivo: %s ", (*(vettori.v_ordinamenti[r_partenza][i])).codice_tratta, (*(vettori.v_ordinamenti[r_partenza][i])).partenza,
                    (*(vettori.v_ordinamenti[r_partenza][i])).destinazione,
                    (*(vettori.v_ordinamenti[r_partenza][i])).data_part,(*(vettori.v_ordinamenti[r_partenza][i])).orario_partenza, (*(vettori.v_ordinamenti[r_partenza][i])).orario_arrivo);
    }
}

void ricerca_lineare_noHeap(set_vettori vettori,int lunghezza) {
    char chiave[__MAX_S__];
    scanf("%s",chiave);

    printf("\nRISULTATI RICERCA: ");
    for (int i = 0; i < lunghezza; i++) {
        if (strncmp(vettori.v_ordinamenti[0][i]->partenza,chiave,2) == 0)
            fprintf(stdout,"\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                           "Ora arrivo: %s ", (*(vettori.v_ordinamenti[0][i])).codice_tratta, (*(vettori.v_ordinamenti[0][i])).partenza,
                    (*(vettori.v_ordinamenti[0][i])).destinazione,
                    (*(vettori.v_ordinamenti[0][i])).data_part,(*(vettori.v_ordinamenti[0][i])).orario_partenza, (*(vettori.v_ordinamenti[0][i])).orario_arrivo);
    }
}

void ricerca_dicotomica(set_vettori vettori,int lunghezza,char chiave[__MAX_S__],int l,int r) {
    
    if (l>r)
        return;
    int m = (r+l)/2;
    int risultato = strncmp(chiave,vettori.v_ordinamenti[r_partenza][m]->partenza,strlen(chiave));

    if ( risultato > 0)
        return ricerca_dicotomica(vettori,lunghezza,chiave,m+1,r);
    else if (risultato < 0)
        return ricerca_dicotomica(vettori,lunghezza,chiave,l,m-1);
    else if (risultato == 0) {
        printf("\nRISULTATI RICERCA: ");
        fprintf(stdout, "\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                        "Ora arrivo: %s ", (*(vettori.v_ordinamenti[r_partenza][m])).codice_tratta,
                (*(vettori.v_ordinamenti[r_partenza][m])).partenza,
                (*(vettori.v_ordinamenti[r_partenza][m])).destinazione,
                (*(vettori.v_ordinamenti[r_partenza][m])).data_part, (*(vettori.v_ordinamenti[r_partenza][m])).orario_partenza,
                (*(vettori.v_ordinamenti[r_partenza][m])).orario_arrivo);
        int tmp = m;
        while ( ++m < lunghezza && strncmp(chiave, vettori.v_ordinamenti[r_partenza][m]->partenza, strlen(chiave)) == 0)
        {    fprintf(stdout, "\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                             "Ora arrivo: %s ", (*(vettori.v_ordinamenti[r_partenza][m])).codice_tratta,
                     (*(vettori.v_ordinamenti[r_partenza][m])).partenza,
                     (*(vettori.v_ordinamenti[r_partenza][m])).destinazione,
                     (*(vettori.v_ordinamenti[r_partenza][m])).data_part, (*(vettori.v_ordinamenti[r_partenza][m])).orario_partenza,
                     (*(vettori.v_ordinamenti[r_partenza][m])).orario_arrivo);
        }
        m = tmp;
        while ( --m >= 0 && strncmp(chiave, vettori.v_ordinamenti[r_partenza][m]->partenza, strlen(chiave)) == 0)
        {    fprintf(stdout, "\nCodice Tratta: %s || Partenza: %s || Capolinea: %s || Data: %s || Ora partenza: %s ||"
                             "Ora arrivo: %s ", (*(vettori.v_ordinamenti[r_partenza][m])).codice_tratta,
                     (*(vettori.v_ordinamenti[r_partenza][m])).partenza,
                     (*(vettori.v_ordinamenti[r_partenza][m])).destinazione,
                     (*(vettori.v_ordinamenti[r_partenza][m])).data_part, (*(vettori.v_ordinamenti[r_partenza][m])).orario_partenza,
                     (*(vettori.v_ordinamenti[r_partenza][m])).orario_arrivo);
        }
        return;
    }
}


void leggi_nome_file(char *nomefile) {

    printf("\nInserisci il nome del file: ");
    scanf("%s",nomefile);
}

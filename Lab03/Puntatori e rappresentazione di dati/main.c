#include <stdio.h>
#define NUMERO 256
#define __SEGNO__ 1
#define __EXP_F__ 8
#define __MANT_F__ 23
#define __EXP_D__ 11
#define __MANT_D__ 52
#define __EXP_LD__ 15
#define __MANT_LD__ 64


typedef enum{FALSE,TRUE} boolean;

boolean bigEndianverify();
void stampaCodifica(void *p,int size,boolean bigEndian);
int dec2bin(int p,int size,int bit_stampati);

int main() {
    boolean bigEndian;
    float af;
    double ad;
    long double ald;
    char *p;

    bigEndian = bigEndianverify();

    printf("\nInserisci un numero in formato float: ");
    scanf("%f",&af);
    ad = af;
    ald = af;

    stampaCodifica((void*)&af, sizeof(af),bigEndian );

    stampaCodifica((void*)&ad, sizeof(ad),bigEndian );

    stampaCodifica((void*)&ald, sizeof(ald)-48/8,bigEndian ); //48bit di padding

    return 0;

}

boolean bigEndianverify() {
    int n=NUMERO;
    int *ptr=&n;
    char *puntatore = (char*)ptr;
    boolean bigEndian = FALSE;

    printf("La codifica bigEndian può essere determinata,salvando il numero intero (tipo int) %d che occupa 4 byte\n"
           "ovvero 4 celle nella memoria da 1 byte,dopo aver dichiarato e assegnato la variabile\n"
           "assegno il suo indirizzo ad un puntatore di tipo intero (int *),dopodichè assegno l'indirizzo: %p\n"
           "ad un puntatore di tipo carattere (char *) che mi permette di verificare cosa contiene ogni cella"
           "delle 4 totali che servono per immagazzinare il mio dato\n"
           "il numero convertito in esadecimale risulta essere %x,\n"
           "dunque nella prima cella che equivale ad un byte posso immagazzinare al massimo 255 come numero intero\n"
           "e allora avrò (16^2)*1 con 1 che corrisponde al valore nella seconda cella\n"
           "e 0 nella prima cella, dunque alla fine avrò\n"
           "(16^2)*1 + (16^1)*0 + (16^0)*0 = 256 in base 10\n"
           "Procediamo alla verifica che mostra il numero della cella, e il valore contenuto in essa.\n"
           "La variabile booleana bigEndian è dapprima supposta falsa\n"
           "Il codice cerca se nella posizione della seconda cella il contenuto è 1,che corrisponde ad una codifica lastEndian\n"
           " se così non fosse\n"
           "allora il calcolatore sarebbe in codifica bigEndian che corrisponderebbe all'1 nella 3 cella dello spazione allocato\n"
           "per l'intero\n",NUMERO,ptr,NUMERO);
    for (int i = 0; i < (int)sizeof(int); i++) {
        printf("Cella n°: %d || Indirizzo : %p || Contenuto : %x",i,puntatore+i,*(puntatore+i));
        if (*(puntatore+i) == 1){
            printf("  Trovato 1 alla cella %d\n",i+1);
            if (i != 1)
                bigEndian = TRUE;

        }
        else {
            printf("  Non trovato 1 alla cella %d\n",i+1);
        }

    }
    if (bigEndian == TRUE){
        printf("\nIl calcolatore è bigEndian");
    } else {
        printf("\nIl calcolatore è lastEndian");
    }
    return bigEndian;
}

void stampaCodifica(void *p,int size,boolean bigEndian){
    int bit_scanditi=0;
    /**Divido il numero considerando la parte intera, poi la parte frazionaria poi il segno e lo salvo nel vettore di bit*/
    /**Se è bigEndian comincio a leggere dall'inizio, altrimenti dalla fine*/

    switch (size){
        case 4:
        {
            printf("\nFLOAT||Size: %d bytes or %d bits\n", size,size*8);
            break;
        }
        case 8:
            printf("\nDOUBLE||Size: %d bytes or %d bits\n",size,size*8);
            break;
        case 10:
            printf("\nLONG DOUBLE||Size: %d bytes or %d bits\n",size,size*8);
        default:
            break;
    }
    if (bigEndian==FALSE) {//stampo dall'ultima cella se è little endian
        for (int i = size - 1; i >= 0; i--) {
            bit_scanditi += dec2bin(*((char *) p + i), size, bit_scanditi);
        }
    } else { //stampo dalla prima cella se è BIG ENDIAN
        for (int i = 0; i <= size - 1; i++) {
            bit_scanditi += dec2bin(*((char *) p + i), size, bit_scanditi);
        }
    }

}

int dec2bin(int p,int size,int bit_stampati){ //NELLE CELLE SONO CONTENUTI I VALORI ESATTI li tratto come interi e li converto, dopodichè li salvo su un vettore
    int risultato;
    int modulo;
    int i;
    int numero[8];
    risultato = p;

    for (int k = 0; k <= 7; k++) { /**Azzero il vettore*/
        numero[k] = 0;
    }

    if (risultato <0){ /**Se il risultato ciò che leggo è minore di 0 in base alla codifica del calcolatore significa che il bit in indice 7 sarà quello che rende
 * negativo il numero letto, quindi per leggere i restanti devo sommare 2^7 al numero letto per decodificare con l'algoritmo delle divisioni successive*/
        numero[7] = 1;
        risultato +=128; //2^7
    }

    for ( i = 0; i < 7 && risultato!= 0; i++) { /*Metodo delle divisioni successive*/
        modulo = risultato%2;
        risultato = risultato/2;
        numero[i]=modulo;
    }

    for (int j = 7; j >=0; j--) { /*Stampo il vettore partendo dal numero più a destra*/
        printf("%d",numero[j]);
        bit_stampati++;
        switch (size){
                case 4: //float
                {
                    if (bit_stampati==__SEGNO__){
                        printf(" :SEGNO ");
                    }

                    if (bit_stampati==__SEGNO__+__EXP_F__){
                        printf(" :ESPONENTE ");
                    }

                    if (bit_stampati==__SEGNO__+__EXP_F__+__MANT_F__){
                        printf(" :MANTISSA ");
                    }
                    break;
                }
            case 8:
            {
                if (bit_stampati==__SEGNO__){
                    printf(" :SEGNO ");
                }

                if (bit_stampati==__SEGNO__+__EXP_D__){
                    printf(" :ESPONENTE ");
                }

                if (bit_stampati==__SEGNO__+__EXP_D__+__MANT_D__){
                    printf(" :MANTISSA ");
                }
                break;
            }
            case 10:
            {
                if (bit_stampati==__SEGNO__){
                    printf(" :SEGNO ");
                }

                if (bit_stampati==__SEGNO__+__EXP_LD__){
                    printf(" :ESPONENTE ");
                }

                if (bit_stampati==__SEGNO__+__EXP_LD__+__MANT_LD__){
                    printf(" :MANTISSA ");
                }
                break;
            }
            default:
                break;
        }
    }
    return 8; //lunghezza in bit di un byte
}


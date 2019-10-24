#include <stdio.h>
#define dimMAX 20

typedef struct {
    int numero_colonne;
    int numero_righe;
}agg_type0;

void lettura_matrice(int matrice[dimMAX][dimMAX],int *nc,int *nr);
void somma_progressiva(agg_type0 dati_matrice,int somme[dimMAX][dimMAX],int matrice[dimMAX][dimMAX]);
void ricerca_max(agg_type0 dati_matrice,int somme[dimMAX][dimMAX]);

int main() {

    int matrice[dimMAX][dimMAX];
    agg_type0 dati_matrice;
    int somme[dimMAX][dimMAX];
    lettura_matrice(matrice,&dati_matrice.numero_colonne,&dati_matrice.numero_righe);
    somma_progressiva(dati_matrice,somme,matrice);
    ricerca_max(dati_matrice,somme);
    return 0;

}

void lettura_matrice(int matrice[dimMAX][dimMAX],int *nc,int *nr){
    int i=0,j=0;
    FILE *fp;
    fp = fopen("giornate.txt","r");
    fscanf(fp,"%d%d",nr,nc);
    for (i=0;i<*nr;i++) {
        for (j=0;j<*nc;j++) {
            fscanf(fp,"%d",&matrice[i][j]);
        }
    }
}

void somma_progressiva(agg_type0 dati_matrice,int somme[dimMAX][dimMAX],int matrice[dimMAX][dimMAX]){
    int i,j;

    for (i=0;i<dati_matrice.numero_righe;i++){
        for (j = 0;j < dati_matrice.numero_colonne; j++) {
            if (j==0)
                somme[i][j] = matrice[i][j];
            else
                somme[i][j] =somme[i][j-1]+matrice[i][j];
        }
    }
}

void ricerca_max(agg_type0 dati_matrice,int somme[dimMAX][dimMAX]) {
    int max_i= -1;
    int record = -1;
    int i,j;
    for (j = 0; j < dati_matrice.numero_colonne; j++) {
        printf("Giornata n: %d \n",j);
        for (i = 0; i < dati_matrice.numero_righe; i++) {
            if (somme[i][j] > record) {
                max_i = i;
                record = somme[i][j];
            }
        }
        printf("Num. Squadra: %d con %d punti\n",max_i,record);
    }
}
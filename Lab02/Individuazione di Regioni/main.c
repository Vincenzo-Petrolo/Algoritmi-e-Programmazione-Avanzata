/**Vincenzo Petrolo s256499*/
#include <stdio.h>
#define __NERO__ 1
#define __BIANCO__ 0
#define __MATRICE__ "matrice.txt"
#define __MAX_RIGHE__ 50
#define __MAX_COLONNE__ 50

typedef enum{FALSE,TRUE} boolean;

typedef struct {
    int i;
    int j;
    int altezza;
    int base;
    int area;
}agg_type0;
int max(int x,int y);
int apertura_lettura_file(int matrice[__MAX_RIGHE__][__MAX_COLONNE__],int* nr_effettive,int* nc_effettive);
void valuta_massimi(int i,int j,int base,int *max_base,int altezza,int *max_altezza,int *max_area,agg_type0 massimi[]);
void stampa(agg_type0 massimi[]);
void ricerca(int nc_effettive,int nr_effettive,int matrice[__MAX_RIGHE__][__MAX_COLONNE__]);

int main() {

    int matrice[__MAX_RIGHE__][__MAX_COLONNE__];
    int nr_effettive,nc_effettive;

    if(apertura_lettura_file(matrice,&nr_effettive,&nc_effettive)){
        ricerca(nc_effettive,nr_effettive,matrice);
    }

    return 0;
}

int apertura_lettura_file(int matrice[][__MAX_COLONNE__],int* nr_effettive,int* nc_effettive){
    FILE *fp_matrice;
    boolean esito=TRUE;
    int i,j;

    fp_matrice = fopen(__MATRICE__,"r");
    if (fp_matrice == NULL){
        printf("\nErrore in apertura file\n");
        esito = FALSE;
    }
    if (esito){
        fscanf(fp_matrice,"%d%d",nr_effettive,nc_effettive);
        for (i = 0; i < *nr_effettive; i++) {
            printf("\n");
            for (j = 0; j < *nc_effettive; j++) {
                fscanf(fp_matrice, "%d", &matrice[i][j]);
                printf("%d", matrice[i][j]);
            }
        }
    }
    return esito;
}
int max(int x,int y){
    int result = 0;
    if (x>=y)
       result = x;
    else
        result=y;

    return result;
}
void ricerca(int nc_effettive,int nr_effettive,int matrice[][__MAX_COLONNE__]){
    int base = 0,max_base=-1,max_altezza=-1,max_area=-1,j,i;
    int altezza = 0,temp;
    agg_type0 massimi[3]; //i=0,max base,i=1 max area,i=2 max altezza

    for ( i = 0; i < nr_effettive; i++) {
        for (j=0; j < nc_effettive; j++) {
            if (matrice[i][j] == __NERO__) {
                base++;
                temp = i;
                altezza=0; //resetto in maniera tale che l'ultima volta che viene eseguito si salva il valore
                while(matrice[i+1][j] == __NERO__ && i+1<nr_effettive) {
                    altezza++;
                    matrice[i+1][j] = __BIANCO__;
                    i++;
                }
                i=temp;//resetto alla i di partenza
                if(j+1 == nc_effettive){ //faccio le mie valutazioni se sono arrivato all'estremo della matrice
                    if (altezza==0)
                        altezza=1; //dato che incremento solo nel caso in cui sotto la mia casella ci sia altezza
                    else
                        altezza++;                //se alla fine del ciclo non ho incrementato l'altezza e ho trovato almeno una casella nera
                    //allora la imposto a 1
                    valuta_massimi(i,j,base,&max_base,altezza,&max_altezza,&max_area,massimi);
                    base =0;
                    altezza=0;
                }
            }
            else if (base>0){
                if (altezza==0)
                    altezza=1; //dato che incremento solo nel caso in cui sotto la mia casella ci sia altezza
                else
                    altezza++;                //se alla fine del ciclo non ho incrementato l'altezza e ho trovato almeno una casella nera
                                //allora la imposto a 1
                valuta_massimi(i,j-base,base,&max_base,altezza,&max_altezza,&max_area,massimi);
                base =0;
                altezza=0;
            }
        }

    }
    stampa(massimi);

}
void valuta_massimi(int i,int j,int base,int *max_base,int altezza,int *max_altezza,int *max_area,agg_type0 massimi[]){
    if (base > *max_base){
        *max_base=max(base,*max_base);
        massimi[0].i=i;
        massimi[0].j=j;
        massimi[0].base = base;
        massimi[0].altezza = altezza;
        massimi[0].area = base*altezza;
    }
    if (altezza > *max_altezza){
        *max_altezza=max(altezza,*max_altezza);
        massimi[1].i=i;
        massimi[1].j=j;
        massimi[1].base = base;
        massimi[1].altezza = altezza;
        massimi[1].area = base*altezza;
    }
    if (base*altezza > *max_area){
        *max_area=max(base*altezza,*max_area);
        massimi[2].i=i;
        massimi[2].j=j;
        massimi[2].base = base;
        massimi[2].altezza = altezza;
        massimi[2].area = *max_area; //glielo assegno in modo da non fare una moltiplicazione in più
    }
}
void stampa(agg_type0 massimi[]){
    char caratteristiche[30][30] = {"Base","Altezza","Area"};
    for (int i = 0; i < 3; i++) {
        printf("\nMax %s: ",caratteristiche[i]);
        printf("estr. sup. SX=<%d,%d>, b=%d,h=%d, Area=%d",massimi[i].i,massimi[i].j,massimi[i].base,massimi[i].altezza,massimi[i].area);
    }
}
/**Vincenzo Petrolo s256499*/
#include <stdio.h>
#define __MAXR__ 50
#define __MATRICE__ "matrice.txt"
#define  __NERO__ 1
#define __BIANCO__ 0

typedef enum {FALSE,TRUE} boolean;
typedef enum {MAX_BASE,MAX_ALTEZZA,MAX_AREA} indici_massimi;
typedef struct {
    int r;
    int c;
    int base;
    int altezza;
}massimi;
int leggiMatrice(int matrice[][__MAXR__],int* nr_effettive,int* nc_effettive);
boolean riconosciRegione(int nc_effettive,int nr_effettive,int matrice[][__MAXR__],int r,int c,int *b,int *h);
void stampa(int r,int c,int b,int h);

int main() {

    int matrice[__MAXR__][__MAXR__];
    int nr_effettive,nc_effettive;
    int b,h;

    massimi vettore_max[3];

    for (int k = 0; k < 3; k++) {
        vettore_max[k].base=0;
        vettore_max[k].altezza=0;
    }


    if (leggiMatrice(matrice,&nr_effettive,&nc_effettive)){
        for (int i = 0; i <nr_effettive ; i++) {
            for (int j = 0; j < nc_effettive; j++) {
                if(riconosciRegione(nc_effettive,nr_effettive,matrice,i,j,&b,&h)){
                    stampa(i,j,b,h);
                    if (b > vettore_max[MAX_BASE].base){
                        vettore_max[MAX_BASE].r = i;
                        vettore_max[MAX_BASE].c = j;
                        vettore_max[MAX_BASE].base = b;
                        vettore_max[MAX_BASE].altezza = h;
                    }
                    if (h > vettore_max[MAX_ALTEZZA].altezza){
                        vettore_max[MAX_ALTEZZA].r = i;
                        vettore_max[MAX_ALTEZZA].c = j;
                        vettore_max[MAX_ALTEZZA].base = b;
                        vettore_max[MAX_ALTEZZA].altezza = h;
                    }
                    if ((b*h) > (vettore_max[MAX_AREA].base*vettore_max[MAX_AREA].altezza)){
                        vettore_max[MAX_AREA].r = i;
                        vettore_max[MAX_AREA].c = j;
                        vettore_max[MAX_AREA].base = b;
                        vettore_max[MAX_AREA].altezza = h;
                    }
                }
            }
        }
    }

    printf("\nMax Base: estr. sup. SX = <%d,%d> b=%d, h=%d, Area=%d",vettore_max[MAX_BASE].r,vettore_max[MAX_BASE].c
    ,vettore_max[MAX_BASE].base,vettore_max[MAX_BASE].altezza,(vettore_max[MAX_BASE].base*vettore_max[MAX_BASE].altezza));

    printf("\nMax Altezza: estr. sup. SX = <%d,%d> b=%d, h=%d, Area=%d",vettore_max[MAX_ALTEZZA].r,vettore_max[MAX_ALTEZZA].c
            ,vettore_max[MAX_ALTEZZA].base,vettore_max[MAX_ALTEZZA].altezza,(vettore_max[MAX_ALTEZZA].base*vettore_max[MAX_ALTEZZA].altezza));

    printf("\nMax Area: estr. sup. SX = <%d,%d> b=%d, h=%d, Area=%d",vettore_max[MAX_AREA].r,vettore_max[MAX_AREA].c
            ,vettore_max[MAX_AREA].base,vettore_max[MAX_AREA].altezza,(vettore_max[MAX_AREA].base*vettore_max[MAX_AREA].altezza));


    return 0;
}

int leggiMatrice(int matrice[][__MAXR__],int* nr_effettive,int* nc_effettive)
{
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
            }
        }
    }
    return esito;
}

boolean riconosciRegione(int nc_effettive,int nr_effettive,int matrice[][__MAXR__],int r,int c,int *b,int *h)

{
    int temp,temp1;
    boolean rettangolo = FALSE;
    (*b) = 0;
    (*h) = 0;
    temp = r;
    temp1 = c;
    if (r <= nr_effettive && c <= nc_effettive) {
        if (matrice[r][c] == __NERO__) {
            rettangolo = TRUE;
            (*b)++; //incremento del primo
            (*h)++;
            while (r<nr_effettive-- && matrice[++r][c] == __NERO__){
                (*h)++;
                matrice[r][c] = __BIANCO__;
            }
            while (c < nc_effettive-- && matrice[temp][++c] == __NERO__){
                (*b)++;
                matrice[temp][c] = __BIANCO__;
            }

        }
    }
    for (int i=0;   i < (*h); i++) { //rimpiazzo tutte quelle rimanenti con il bianco
        for (int j=0 ; j < (*b); j++) {
            if (matrice[temp+i][temp1+j] == __NERO__)
                matrice[temp+i][temp1+j] = __BIANCO__;
        }

    }
    return rettangolo;
}

void stampa(int r,int c,int b,int h) {
    printf("\nRettangolo in (%d,%d) Base: %d Altezza: %d",r,c,b,h);
}

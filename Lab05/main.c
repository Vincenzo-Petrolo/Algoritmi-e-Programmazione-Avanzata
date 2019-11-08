#include <stdio.h>
#include <stdlib.h>

typedef enum{BIANCO,NERO} quadretto;

void malloc2P(int ***mp,int nr,int nc);
void leggi_matrice(FILE *fp,int nr,int nc,int ***mp);
void separa(int **mat, int nr, int nc,int **v_nero,int **v_bianco);

int main() {
    int **mp,nr,nc;
    int *v_nero,*v_bianco;

    FILE *fp;
    fp = fopen("matrix.txt","r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    if (fscanf(fp,"%d%d",&nr,&nc) != 2)
        exit(EXIT_FAILURE);

    leggi_matrice(fp,nr,nc,&mp);
    separa(mp,nr,nc,&v_nero,&v_bianco);
    return 0;
}

void malloc2P(int ***mp,int nr,int nc) {
    *mp = (int **)malloc((size_t)nr*sizeof(int *)); //vettore colonna di puntatori

    for (int i = 0; i < nr; i++) { //aggancio alla colonna così da potervi accedere puntatorei->puntatorej->elemento-ij
        (*mp)[i] = (int*) malloc(nc*sizeof(int)); //ad ogni elemento della prima colonna assegno il valore degli altri
    }
}

void leggi_matrice(FILE *fp,int nr,int nc,int ***mp) {

    malloc2P(mp,nr,nc);

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(fp,"%d",&((*mp)[i][j])); //accedi alla colonna dei puntatori i esima, accedi alla memoria ij, prendine l'indirizzo
        }
    }
}

void separa(int **mat, int nr, int nc,int **v_nero,int **v_bianco) {
    quadretto colore =BIANCO;
    int count_nero = 0,count_bianco = 0;
    int n_nere,n_bianche;

    if ((nc*nr)%2 == 0) { //AREA PARI allora il numero di caselle bianche è A/2
        n_bianche = (int)(((float)(nc*nr))/2.0 - 0.5);
        n_nere = (int)(((float)(nc*nr))/2.0 - 0.5);
    }
    else { //AREAP DISPARI allora il numero i caselle bianche è A/2 +1
        n_bianche = (int)(((float)(nc*nr))/2.0 + 0.5);
        n_nere = (int)(((float)(nc*nr))/2.0 - 0.5);
    }

    *v_nero = (int *) malloc(n_nere*sizeof(int));
    *v_bianco = (int *) malloc(n_bianche*sizeof(int));


    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if (colore == BIANCO) {
                *(*v_bianco+count_bianco) = mat[i][j];
                colore =NERO;
                count_bianco++;
            }
            else {
                *(*v_nero+count_nero) = mat[i][j];
                colore=BIANCO;
                v_nero++;
            }
        }
    }

}



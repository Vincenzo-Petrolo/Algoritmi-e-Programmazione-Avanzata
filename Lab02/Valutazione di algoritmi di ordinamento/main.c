#include <stdio.h>
#include <math.h>
#include <limits.h>
#define __FILENAME__ "sort.txt"


int potenza(int exp,int base);
void SelectionSort(int vettore[],int lunghezza);
void InsertionSort(int vettore[],int lunghezza);
void ShellSort(int vettore[],int lunghezza);
long int power(int intero,int potenza);

int main() {
    FILE *fp;
    int n_sequenze;
    int lunghezza_sequenza;

    fp = fopen(__FILENAME__,"r");

    if (fp!=NULL){
        fscanf(fp,"%d",&n_sequenze);
        for (int i = 0; i < n_sequenze; i++) {
            fscanf(fp,"%d",&lunghezza_sequenza);
            int vettore[lunghezza_sequenza];
            for (int j = 0; j < lunghezza_sequenza; j++) {
                fscanf(fp,"%d",&vettore[j]);
            }
            /*Inserire le funzioni di sorting*/
            printf("\nINSERTION SORT");
            InsertionSort(vettore,lunghezza_sequenza);
            printf("\nSELECTION SORT");
            SelectionSort(vettore,lunghezza_sequenza);
            printf("\nSHELL SORT");
            ShellSort(vettore,lunghezza_sequenza);
        }
    }

    return 0;
}

void InsertionSort(int sub_vettore[],int lunghezza){
    int j=0;
    int temp;
    int vettore[lunghezza];
    int n_scambi = 0, iter_ext = 0,iter_int=0, iter_tot = 0;

    for (int k = 0; k < lunghezza; k++) {
        vettore[k] = sub_vettore[k];
    }


    for (int i = 0; i < lunghezza; i++) {
        j=i;
        iter_ext++;
        iter_int =0;
        while (j>0) {
            iter_int++;
            if (vettore[j]<=vettore[j-1])
            {
                n_scambi++;
                temp=vettore[j];
                vettore[j] = vettore[j-1];
                vettore[j-1] = temp;
            }
            j--;
        }
        iter_tot+=j;
        printf("\nIterazioni al ciclo esterno %d : %d",i,iter_int);
    }

    printf("\nIterazioni totali: %d"
           "\nScambi effettuati totali: %d",iter_tot,n_scambi);
}

void SelectionSort(int sub_vettore[],int lunghezza) {
    /**L'algoritmo volta per volta prima di reitare controlla che sia ordinato il vettore, per evitare
     * di eseguire il ciclo N volte*/

    int minimo;
    int i_sort = 0;
    int j = 0;
    int n_scambi = 0, iter_tot = 0;
    int indice;
    int ordinato = 0;
    int vettore[lunghezza];

    for (int k = 0; k < lunghezza; k++) {
        vettore[k] = sub_vettore[k];
    }

    for (i_sort = 0; i_sort < lunghezza && ordinato == 0; i_sort++) {
        j = i_sort; //incremento l'indice volta per volta
        minimo = INT_MAX;
        while (j < lunghezza) {
            if (vettore[j] <= minimo) {
                n_scambi++;
                minimo = vettore[j];
                indice = j;
                vettore[indice] = vettore[i_sort];
                vettore[i_sort] = minimo;
            }
            j++;
        }
        iter_tot+=j;
        printf("\nIterazioni interne al ciclo esterno %d : %d",i_sort,j);
        j = 0;
        ordinato = 1; //suppongo che sia ordinato
        while (j < lunghezza - 1) {
            if (vettore[j] > vettore[j + 1]) {
                ordinato = 0;
            }
            j++;
        }
    }
    printf("\nNumero iterazioni totali: %d\nNumero scambi totali: %d",iter_tot,n_scambi);
}

void ShellSort(int argvettore[],int lunghezza){
    int k;
    int sub_vettore[lunghezza];
    int succ;
    int vettore[lunghezza];


    for (k = 0; k < lunghezza; k++) {
        vettore[k] = argvettore[k];
    }


    for (k=1 ; ((succ=(potenza(k,3)-1)/2)) <= ((lunghezza/3)+0.5) ; k++) {
        int j=0;
        for (int l = 0; l <= lunghezza/3;l++) {
            j=-1;
            for (int i = l; i < lunghezza; i+=succ) {
                j++;
                sub_vettore[j] = vettore[i];
            }
            InsertionSort(sub_vettore,j+1); //ordino il sottovettore
            j=-1;                            //re inserisco nel vettore di partenza
            for (int i = l; i < lunghezza; i+=succ) {
                j++;
                vettore[i] = sub_vettore[j];
            }
        }

    }

    for (int l = 0; l < lunghezza; l++) {
        printf("%d ",vettore[l]);
    }
}

int potenza(int exp,int base) {
    while (exp>0){
        base*=base;
        exp--;
    }
    return base;
}
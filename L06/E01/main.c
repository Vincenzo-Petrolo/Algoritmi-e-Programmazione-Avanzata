#include <stdio.h>
#include <stdlib.h>
#define __FILE_NAME__ "grafo.txt"

typedef struct {
    int u;
    int v;
}arco_non_orientato_t;

typedef enum {FALSE,TRUE} boolean;

//Tutti i valori sono passati by pointer in maniera da non pagare il costo di copiatura

boolean vertex_cover(arco_non_orientato_t **archi,int **set,int **sol,int n,int n_archi);
void powerset(int pos, int *val, int *sol, int k,arco_non_orientato_t **archi,int n_archi);
void display_set(int **set,int n,int **sol);
void leggi_archi(arco_non_orientato_t **archi,int *n_vertici,int *n_archi);
boolean appartiene_a_W(arco_non_orientato_t arco,int *W,int dim_W,int *sol);

int main() {
    arco_non_orientato_t *archi;
    int n_vertici,n_archi;
    int pos=0;

    leggi_archi(&archi,&n_vertici,&n_archi); //legge e salva nella struttura dati tutti gli archi
    int val[n_vertici];
    int sol[n_vertici];
    int k = n_vertici;
    for (int i = 0; i < n_vertici; i++) {
        val[i] = i;
    }
    powerset(pos, val, sol,k,&archi, n_archi);

    return 0;
}


void leggi_archi(arco_non_orientato_t **archi,int *n_vertici,int *n_archi) {
    FILE *fp;
    arco_non_orientato_t *tmp;
    int u,v;

    if ((fp = fopen(__FILE_NAME__,"r")) == NULL) {
        printf("\nErrore durante l'apertura del file!");
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"%d %d",n_vertici,n_archi);

    tmp = (arco_non_orientato_t*) malloc(*n_archi * sizeof(arco_non_orientato_t));
    if (tmp == NULL) {
        printf("\nERRORE! Heap insufficiente");
        exit(EXIT_FAILURE);
    }
    *archi = tmp; //assegno alla variabile puntatore che punta al vettore di struct

    for (int i = 0; i < *n_archi; i++) {
        fscanf(fp,"%d %d",&u,&v);
        (*archi)[i].u = u;
        (*archi)[i].v = v;
    }
    fclose(fp);
}

void display_set(int **set,int n,int **sol){
    printf("\n{");
    for (int i = 0; i < n; i++) {
        if ((*sol)[i] != 0)
            printf(" %d",(*set)[i]);
    }
    printf(" }");
}

boolean vertex_cover(arco_non_orientato_t **archi,int **set,int **sol,int n,int n_archi){
    boolean vertex_cover = TRUE; //suppongo che  sia un vertex cover

    for (int i = 0; i < n_archi;i++) {
        if (appartiene_a_W((*archi)[i],*set,n,*sol) == FALSE)
            return vertex_cover=FALSE;
    }
    return vertex_cover; //Se arriva fino a qua, allora vertex_cover è TRUE

}

boolean appartiene_a_W(arco_non_orientato_t arco,int *W,int dim_W,int *sol){
    boolean appartenenza = FALSE; //attributo all'arco, suppongo sia falso, nel caso contrario mi ricredo e ritorno TRUE

    for (int i = 0; i < dim_W; i++) {
        if (sol[i] != 0) {
            if (arco.u == W[i] || arco.v == W[i]) {
                return appartenenza = TRUE;
            }
        }
    }
    return appartenenza; //Se arriva fin qui, allora appartenenza è FALSE
}

void powerset(int pos,int *val, int *sol, int k,arco_non_orientato_t **archi,int n_archi) {
    boolean result;
    if (pos >= k) {
        result=vertex_cover(archi,&val,&sol,k,n_archi);
        if (result == TRUE)
            display_set(&val,k,&sol);
    return;
    }
    sol[pos] = 0;
    powerset(pos+1, val, sol, k,archi,n_archi);
    sol[pos] = 1;
    powerset(pos+1, val, sol, k,archi,n_archi);
}
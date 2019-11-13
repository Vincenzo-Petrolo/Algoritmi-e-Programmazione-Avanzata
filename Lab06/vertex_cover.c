#include <stdio.h>
#include <stdlib.h>
#define __FILE_NAME__ "vertex.txt"

typedef struct {
    int u;
    int v;
}arco_non_orientato_t;

typedef enum {FALSE,TRUE} boolean;

//Tutti i valori sono passati by pointer in maniera da non pagare il costo di copiatura

boolean vertex_cover(arco_non_orientato_t **archi,int **set,int n,int n_vertici);
void power_set();
void display_set(int **set,int n);
void leggi_archi(arco_non_orientato_t **archi,int *n_vertici,int *n_archi);
boolean in_vertex(arco_non_orientato_t *archi,int *set,int n_set);
void powerset(int pos, int *val, int *sol, int k,int start, int count,arco_non_orientato_t **archi,int n_archi);

int main() {
    arco_non_orientato_t *archi;
    int n_vertici,n_archi;

    leggi_archi(&archi,&n_vertici,&n_archi); //legge e salva nella struttura dati tutti gli archi

    return 0;
}


void leggi_archi(arco_non_orientato_t **archi,int *n_vertici,int *n_archi) {
    FILE *fp;
    arco_non_orientato_t **tmp;
    int u,v;

    if ((fp = fopen(__FILE_NAME__,"r")) == NULL) {
        printf("\nErrore durante l'apertura del file!");
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"%d %d",n_vertici,n_archi);

    tmp = (arco_non_orientato_t**) malloc(*n_archi * sizeof(arco_non_orientato_t));
    if (tmp == NULL) {
        printf("\nERRORE! Heap insufficiente");
        exit(EXIT_FAILURE);
    }
    archi = tmp;

    for (int i = 0; i < *n_archi; i++) {
        fscanf(fp,"%d %d",&u,&v);
        archi[i]->u = u;
        archi[i]->v = v;
    }
    fclose(fp);
}

void display_set(int **set,int n){
    printf("\n{");
    printf("%d",*set[0]);
    for (int i = 1; i < n; i++) {
        printf(",%d",*set[i]);
    }
    printf("}");
}

boolean vertex_cover(arco_non_orientato_t **archi,int **set,int n,int n_archi){
    for (int i = 0; i < n_archi;i++) {
        if (in_vertex(archi[i],*set,n) == FALSE)
            return FALSE;
    }
    return TRUE;
}

boolean in_vertex(arco_non_orientato_t *archi,int *set,int n_set) {
    for (int i = 0; i < n_set; i++) {
        if (set[i] != archi->u && set[i] != archi->v)
            return FALSE;
    }
    return TRUE;
}

void powerset(int pos, int *val, int *sol, int k,int start, int count,arco_non_orientato_t **archi,int n_archi) {
    int i;
    if (start >= k) {
        vertex_cover(archi,&sol,k,n_archi);
        return;
    }
    for (i = start; i < k; i++) {
        sol[pos] = val[i];
        powerset(pos + 1, val, sol, k, i + 1, count);
    }
    powerset(pos, val, sol, k, k, count);
}
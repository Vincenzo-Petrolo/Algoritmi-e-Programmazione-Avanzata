#include "../include/grafo.h"

struct grafo{
    int V;
    int E;
    int** madj;
    ST tab;
};


static int** matr_init(int r,int c,int val){
    int i,j;
    int **m = (int**) malloc(r*sizeof(int));
    for ( i = 0; i < r; i++){
        m[i] = (int*) malloc(c*sizeof(int));
    }
    for ( i = 0; i < r; i++){
        for ( j = 0; j < c; j++){
            m[i][j] = val;
        }
    }
    return m;
}


Grafo grafo_init(int V){
    Grafo G = (Grafo) malloc(sizeof(*G));
    G->V = V;
    G->E = 0;
    G->madj = matr_init(V,V,0);
    G->tab  = STinit(V);  //leggendo delle coppie di vertici che descrivono il grafo, avrò al massimo 2*V vertici al massimo 
    return G;
}    

void  grafo_free(Grafo G){
    for (int i = 0; i < G->V; i++){
        free(G->madj[i]);
    }
    free(G->madj);
    STfree(G->tab);
    free(G);
}

Grafo grafo_load(char* nome_file){
    int V,i,peso,id1,id2;
    int counter=0;
    char label1[MAX_NAME],label2[MAX_NAME];
    Item val1,val2;
    Grafo G;
    FILE *fin = fopen(nome_file,"r");
    ST tmp;

    //Lettura da file con conta dei vertici e inserimento in tabella di simboli non ordinata
    counter = 0;

    while (fscanf(fin,"%s %s %s %s %d",val1.id_elaboratore,val1.id_rete,val2.id_elaboratore,val2.id_rete,peso) != EOF){
        counter++;
    }

    fclose(fin);
    fin = fopen(nome_file,"r");
    
    tmp = STinit(2*counter);

    counter = 0;

    while (fscanf(fin,"%s %s %s %s %d",val1.id_elaboratore,val1.id_rete,val2.id_elaboratore,val2.id_rete,peso) != EOF){
        if (STsearchByKey(tmp,val1) == -1){
            STinsert(tmp,val1);
            counter++;
        }
        if (STsearchByKey(tmp,val2) == -1){
            STinsert(tmp,val2);
            counter++;
        }
    }

    fclose(fin);
    fin = fopen(nome_file,"r");

    //alla fine ottengo il numero esatto di vertici,tutti distinti fra loro
    G = grafo_init(counter);

    for ( i = 0; i < counter; i++){
        STinsert(G->tab,STsearchByIndex(tmp,i));
    }
    

    while (fscanf(fin,"%s %s %s %s %d",val1.id_elaboratore,val1.id_rete,val2.id_elaboratore,val2.id_rete,&peso) != EOF){
        id1 = STsearchByKey(G->tab,val1);
        id2 = STsearchByKey(G->tab,val2);
        if (id1 >= 0 && id2 >= 0){
            grafo_insert_e(G,id1,id2,peso);
        }
    }

    fclose(fin);
    
    return G;
}

int grafo_get_index(Grafo G,Item k) {
    return STsearchByKey(G->tab,k);
}
#include "../include/grafo.h"

struct grafo{
    int V;
    int E;
    int** madj;
    link* ladj;
    link z; //sentinella
    ST tab;
};


static int** matr_init(int r,int c,int val){
    int i,j;
    int **m = (int**) malloc(r*sizeof(int*));
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


Grafo madj_2_ladj(Grafo G){
    int i,j;
    for ( i = 0; i < G->V; i++){
        for ( j = 0; j < G->V; j++){
            if (G->madj[i][j] != 0){
                G->ladj[i] = new_node(G->ladj[i],STsearchByIndex(G->tab,j),G->madj[i][j]);
            }
        }
    }
    return G;
}

Grafo grafo_init(int V){
    int i;
    Grafo G = (Grafo) malloc(sizeof(*G));
    G->V = V;
    G->E = 0;
    G->madj = matr_init(V,V,0);
    G->tab  = STinit(V); 
    G->ladj = malloc(V*sizeof(link));
    G->z    = new_node(NULL,ItemsetNull(),0);   //sentinella
    for ( i = 0; i < V; i++){
        G->ladj[i]  = G->z;
    }
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

    while (fscanf(fin,"%s %s %s %s %d",val1.id_elaboratore,val1.id_rete,val2.id_elaboratore,val2.id_rete,&peso) != EOF){
        counter++;
    }

    fclose(fin);
    fin = fopen(nome_file,"r");
    
    tmp = STinit(2*counter);

    counter = 0;

    while (fscanf(fin,"%s %s %s %s %d",val1.id_elaboratore,val1.id_rete,val2.id_elaboratore,val2.id_rete,&peso) != EOF){
        if (STsearchByKey(tmp,val1.id_elaboratore) == -1){
            STinsert(tmp,val1);
            counter++;
        }
        if (STsearchByKey(tmp,val2.id_elaboratore) == -1){
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

    STsort(G->tab);

    while (fscanf(fin,"%s %s %s %s %d",val1.id_elaboratore,val1.id_rete,val2.id_elaboratore,val2.id_rete,&peso) != EOF){
        id1 = STsearchByKey(G->tab,val1.id_elaboratore);
        id2 = STsearchByKey(G->tab,val2.id_elaboratore);
        if (id1 >= 0 && id2 >= 0){
            grafo_insert_e(G,id1,id2,peso);
        }
    }

    STfree(tmp);   
    fclose(fin);
    
    return G;
}

int grafo_get_index(Grafo G,Key k) {
    return STsearchByKey(G->tab,k);
}

void grafo_insert_e(Grafo G,int id1,int id2,int peso){
    //non orientato => matrice simmetrica
    G->madj[id1][id2] = peso;
    G->madj[id2][id1] = peso;
}

void grafo_remove_e(Grafo G,int id1,int id2){
    G->madj[id1][id2] = 0;
    G->madj[id2][id1] = 0;
}



void  stampa_grafo(Grafo G,FILE *fout){
    int i,j;
    for ( i = 0; i < G->V; i++){
        fprintf(fout,"\nVertice %d\nNome elaboratore: %s\nRete: %s",i,STsearchByIndex(G->tab,i).id_elaboratore,STsearchByIndex(G->tab,i).id_rete);
        fprintf(fout,"\nArchi con:");
        for ( j = 0; j < G->V; j++){
            if (G->madj[i][j] != 0 )
                fprintf(fout,"\t\nNome elaboratore: %s\nRete: %s",STsearchByIndex(G->tab,j).id_elaboratore,STsearchByIndex(G->tab,j).id_rete);
        }
    }
}

boolean sottografo_m(Grafo G,Key elab1,Key elab2,Key elab3){
    int i,j,k=-1;
    int counter = 0;
    int v[3];
    int sol[3];
    //tabella di simboli che associa ad ogni indice, un indice della tabella di simboli contenuta nel grafo
    v[0] = GetIndex(G->tab,elab1);
    v[1] = GetIndex(G->tab,elab2);
    v[2] = GetIndex(G->tab,elab3);

    counter = comb_sempl(G,0,v,sol,3,2,0,0,0);

    if (counter == 3){
        return TRUE;
    }
    return FALSE;
}   

boolean sottografo_l(Grafo G,Key elab1,Key elab2,Key elab3){
    int j;
    int counter = 0;
    int v[3];
    int sol[3];
    //tabella di simboli che associa ad ogni indice, l'indice relativo all'id_elaboratore della tabella di simboli contenuta nel grafo
    v[0] = GetIndex(G->tab,elab1);
    v[1] = GetIndex(G->tab,elab2);
    v[2] = GetIndex(G->tab,elab3);

    counter = comb_sempl(G,0,v,sol,3,2,0,0,1);

    if (counter == 3)
        return TRUE;
    return FALSE;
}

int comb_sempl(Grafo G,int pos,int* val,int* sol,int n,int k,int start,int count,int param){

    

    if (pos >= k){
        if (param == 0){        //caso per la matrice o per la lista
            if (G->madj[sol[0]][sol[1]] != 0){
                return count +1;
            }
        }else if (param == 1){
            for (link x = G->ladj[sol[0]]; x != NULL; x = x->next){
                if (sol[1] == GetIndex(G->tab,x->dati.id_elaboratore)){
                    return count+1;
                }
            }
        }       
    }else{

        for (int i = start; i < n; i++){
            sol[pos] = val[i];
            count = comb_sempl(G,pos+1,val,sol,n,k,i+1,count,param);
        }
    }
    return count;
}

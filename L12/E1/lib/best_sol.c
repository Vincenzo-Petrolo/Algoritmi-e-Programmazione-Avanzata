#include "../include/best_sol.h"
#include <stdlib.h>
#include <limits.h>

Sol SOLinit(int V){
    Sol tmp;
    tmp.card_min        = INT_MAX;
    tmp.n_sol           = 0;
    tmp.sol.peso        = -1;
    tmp.sol.sol         = (Edge*) malloc((V-1)* sizeof(*(tmp.sol.sol)));
    return tmp;
}

void SOLfree(Sol sol){
    free(sol.sol.sol);
}

static void max_DAG_gen(Graph G,Edge* archi,Edge* archi_prova,int n_archi,Sol *sol,int card,int pos,int start){

    if (pos > card)
        return;


    for (int i = 0; i < pos; i++){       //rimuovo gli archi dell'insieme che ho generato
       GRAPHremoveE(G,archi_prova[i].v,archi_prova[i].w);
    }

    if (DAGVerify(G,0) == TRUE && card <= sol->card_min){
        sol->card_min   = pos;          //attuale lunghezza del vettore   
        int peso = 0;

        printf("\n{ ");
        for (int i = 0; i < sol->card_min; i++){
            printf("(%d,%d) ",  archi_prova[i].v,
                                archi_prova[i].w);
            peso += archi_prova[i].wt;
        }
        printf("}\n");
        
        sol->n_sol++;                   //incremento il numero di sottoinsiemi che ho trovato
        if (peso > sol->sol.peso){      //per la seconda richiesta calcolo anche quale di queste trovate è la soluzione a peso minimo
            sol->sol.peso = peso;
            for (int i = 0; i < card; i++){
                sol->sol.sol[i] = archi_prova[i];
            }
        }
    }
    
    for (int i = 0; i < pos; i++){       //ritorno al grafo di partenza
       GRAPHinsertE(G,archi_prova[i].v,archi_prova[i].w,archi_prova[i].wt);
    }

    if (card <= sol->card_min){           //mi permette di fermarmi a generare le soluzioni di card minima
        for (int j = start; j <= n_archi; j++){    
            archi_prova[pos]  = archi[j];
            max_DAG_gen(G,archi,archi_prova,n_archi,sol,card,pos+1,j+1);
        }
    }
}

Sol max_DAG (Graph G,Edge *archi,int V){
    int i;
    Edge archi_prova[V-1];
    Sol soluzione = SOLinit(V);

    for ( i = 1; i < V-1; i++){
        max_DAG_gen(G,archi,archi_prova,V-1,&soluzione,i,0,0);
    }
    return soluzione;
}
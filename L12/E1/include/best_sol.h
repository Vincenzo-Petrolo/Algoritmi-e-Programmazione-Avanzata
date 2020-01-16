#ifndef __BEST_SOL__H
#define __BEST_SOL__H

#include "../include/Graph.h"
#include "../include/mytypes.h"


typedef struct min_w_sol{
    Edge*   sol;
    int     peso;
}Sol_minw;

typedef struct sol{
    Edge        **set_best_sol;
    int         card_min;
    int         n_sol;
    Sol_minw    sol;
}Sol;

Sol     SOLinit(    int V);

void    SQLfree(    Sol sol,
                    int V);

Sol     max_DAG (   Graph G,
                    Edge *archi,
                    int V);


#endif
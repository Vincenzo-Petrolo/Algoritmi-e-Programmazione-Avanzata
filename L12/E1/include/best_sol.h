#ifndef __BEST_SOL__H
#define __BEST_SOL__H

#include "../include/Graph.h"
#include "../include/mytypes.h"
#include "../include/math.h"


typedef struct max_w_sol{
    Edge*   sol;
    int     peso;
}Sol_maxw;

typedef struct sol{
    int         card_min;
    int         n_sol;
    Sol_maxw    sol;
}Sol;

Sol     SOLinit(    int V);

void    SOLfree(    Sol sol);

Sol     max_DAG (   Graph G,
                    Edge *archi,
                    int V);


#endif
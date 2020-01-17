#include "../include/math.h"


unsigned long int factorialR(int n){
    if (n == 0)
        return 1;
    return factorialR(n-1) * n;
}

unsigned long int coeffBinomiale(int n,int k){
    return(factorialR(n)/(factorialR(k)*factorialR(n-k))) +0.5; //0.5 aggiunto per arrotondare in eccesso
}


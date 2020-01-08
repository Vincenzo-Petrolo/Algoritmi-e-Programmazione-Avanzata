#include "../include/item.h"

Item ItemsetNull(){
    Item tmp;
    int i;
    for ( i = 0; i < 30; i++){
        tmp.id_elaboratore[i] = "\0";
    }
    return tmp;
}

boolean Keycmp(Key k1,Key k2){
    return strcmp(k1,k2);
}

void Keycpy(Key k1,Key k2){
    strcpy(k1,k2);    
}

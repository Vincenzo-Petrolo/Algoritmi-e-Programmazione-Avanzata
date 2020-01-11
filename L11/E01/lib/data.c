#include "../include/data.h"


data_t dataRead(FILE *fin){
    data_t tmp;
    fscanf(fin,"%d/%d/%d",&(tmp.anno),&(tmp.mese),&(tmp.giorno));
    return tmp;
}


int dataCmp(data_t data1,data_t data2){
    if (data1.anno > data2.anno){
        return 1;
    }else if (data1.anno < data2.anno){
        return -1;
    }else{
        if (data1.mese > data2.mese){
            return 1;
        }else if (data1.mese < data2.mese){
            return -1;
        }else{
            if (data1.giorno > data2.giorno){
                return 1;
            }else if (data1.giorno < data2.giorno){
                return -1;
            }else{
                return 0;
            }
        }
    }
}

int dataCpy(data_t *data1,data_t *data2){
    data1->anno     = data2->anno;
    data1->mese     = data2->mese;
    data1->giorno   = data2->giorno;
}
int dataDisplay(FILE *fout,data_t data){
    fprintf(fout,"\nData: %d/%1d/%1d",data.anno,data.mese,data.giorno);
}
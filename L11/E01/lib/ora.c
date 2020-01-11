#include "../include/ora.h"

ora_t   oraRead(FILE *fin){
    ora_t tmp;
    fscanf(fin,"%d:%d",&tmp.h,&tmp.min);
    return tmp;
}


int     oraCmp(ora_t ora1,ora_t ora2){
    if (ora1.h > ora2.h){
        return 1;
    }else if (ora1.h < ora2.h){
        return -1;
    }else{
        if (ora1.min > ora2.min){
            return 1;
        }else if(ora1.min < ora2.min){
            return -1;
        }else {
            return 0;
        }
    }
}
int     oraCpy(ora_t *ora1,ora_t *ora2){
    ora1->h     = ora2->h;
    ora1->min   = ora2->min;
}
void    oraDisplay(FILE *fout,ora_t ora){
    fprintf(fout,"Ora : %1d:%1d",ora.h,ora.min);
}
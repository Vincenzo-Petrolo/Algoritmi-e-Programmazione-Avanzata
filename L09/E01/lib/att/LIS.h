#ifndef __LIS__H__
#define __LIS__H__

typedef enum{FALSE,TRUE} boolean;

typedef struct _att {
    int     inizio;
    int     fine;
}att_t;

typedef struct att_wr {
    att_t*  att_ptr;
    int     n;
}att_wrapper;

void display_att(att_t* att_vet);
void leggi_att(att_wrapper* att_w);
void ordina_att(att_wrapper* att_w);
boolean check(att_t att1,att_t att2);
int calcola_diff(att_t att);
void  LIA_calc(att_wrapper* att);
void LIA_display(att_wrapper* att,int* P,int i);
void LIA_Calcwr();
void att_wr_destroy(att_wrapper* att_w);
#endif

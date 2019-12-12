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
void  LIA_calc(att_t* att_vet,att_t* sol,int* sol_len);
void LIA_display(att_wrapper* att,int* P,int i);
void LIA_Calcwr();
void att_wr_destroy(att_wrapper* att_w);
#endif

//per ogni sottostringa di attività, decido quale considerare in base alla differenza e al fatto che intersechi
//o no la sottosequenza successuva, se invece si tratta dell'ultima casella prende quella più lunga e basta
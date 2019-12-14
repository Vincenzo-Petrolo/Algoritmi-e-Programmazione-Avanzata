#include "../include/equipArray.h"

typedef struct equipArray_s {
    int inUso;
    int vettEq[EQUIP_SLOT];
}equipArray_s;

equipArray_t equipArray_init() { 
    equipArray_t tmp    = (equipArray_t) malloc(sizeof(equipArray_s));
    tmp->inUso          = 0;
    for (int i = 0; i < EQUIP_SLOT; i++) {
        tmp->vettEq[i]   = -1;
    }
    
    return tmp;
}
void equipArray_free(equipArray_t equipArray) { 
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    for (int i = 0; i < EQUIP_SLOT; i++) {
        if (equipArray->vettEq[i] != -1){
            invArray_printByIndex(fp,invArray,equipArray->vettEq[i]);
        }
    }
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    char obj_name[LEN];
    int index,decisione,n;
    printf("Scrivi \n0) Aggiungere\n1) Rimuovere\n");
    scanf("%d",&decisione);
    switch (decisione) {
    case 0:
        printf("\nInserisci il nome dell'oggetto che vuoi aggiungere: ");
        scanf("%s",obj_name);
        index = invArray_searchByName(invArray,obj_name);   
        if (index != OBJ_NOT_FOUND) {
            if (equipArray->inUso >= EQUIP_SLOT -1){
                equipArray->vettEq[EQUIP_SLOT-1] = index;                     //sostituisco all'ultimo in caso fosse pieno
                
        }else {
            for (int i = 0; i < EQUIP_SLOT; i++) {
                if (equipArray->vettEq[i] == -1){
                    equipArray->vettEq[i] = index;
                    return;
                }
            }
        }
        }   
        break;

    case 1:
        printf("\nInserisci il numero dell'oggetto da rimuovere nel tuo inventario");
        scanf("%d",&n);
        if (n >= 0 && n < EQUIP_SLOT){
            equipArray->vettEq[n] = -1;
            equipArray->inUso--;
        }
        break;
    default:
        break;
    }
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index) {
    return equipArray->vettEq[index];
}

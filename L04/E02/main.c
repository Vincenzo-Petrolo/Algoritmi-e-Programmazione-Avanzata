#include <stdio.h>
#define  __NOMEFILE_ "sorgente.txt"

typedef enum{FALSE,TRUE} boolean;

/**Prototypes*/
int majority(int *a,int N);
void Swap(int *v,int i,int j);
void QuickSortR( int *v, int l, int r );
int greater_than (int a,int b);
int less_than (int a,int b);
void QuickSort(int *v, int N);
int partition ( int *v, int l, int r );
/**End of prototypes*/

int main() {

    FILE *fp;
    int lunghezza;
    int elemento_maggioritario =-1;
    fp = fopen(__NOMEFILE_,"r");
    fscanf(fp,"%d",&lunghezza);

    int vettore[lunghezza];

    for (int i = 0; i < lunghezza; i++) {
        fscanf(fp,"%d",vettore+i);
    }
    elemento_maggioritario = majority(vettore,lunghezza);
    printf("\n");
    for (int j = 0; j <lunghezza ; j++) {
        printf("%d ",vettore[j]);
    }
    if (elemento_maggioritario != -1)
        printf("\nL'elemento maggioritario è: %d",elemento_maggioritario);
    else
        printf("\nNon esiste un elemento maggioritario");
    return 0;
}

int majority(int *a,int N){
    boolean trovato = FALSE;
    int num= -1;


    QuickSort(a,N); //ordina il vettore ricorsivamente in loco con T(n)=O(nlogn)

    for (int i = 0; i < N/2 && trovato==FALSE; i++) {
        if (a[i] == a[i+N/2]) {
            trovato = TRUE;
            num = a[i];
        }
    }
    return num;

}

int partition ( int *v, int l, int r ) {
    int i, j;
    int x = v[r];
    i = l-1;
    j = r;
    for ( ; ; ) {
        while(less_than(v[++i], x));
        while(greater_than(v[--j], x))
            if (j == l)
                break;
            if (i >= j)
                break;
            Swap(v, i, j);
    }
    Swap(v, i, r);
    return i;
}

void QuickSortR( int *v, int l, int r ) {
    int q;
    if (r <= l)
        return;
    q = partition(v, l, r);
    QuickSortR(v, l, q-1);
    QuickSortR(v, q+1, r);
}

void QuickSort(int *v, int N) {
    int l=0, r=N-1;
    QuickSortR(v, l, r);
}

void Swap(int *v,int i,int j) {
    int tmp;
    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

int less_than (int a,int b) {
    int minore = FALSE;
    if (a < b)
        minore = TRUE;
    return minore;
}

int greater_than (int a,int b) {
    int maggiore = FALSE;
    if (a > b)
        maggiore = TRUE;
    return maggiore;
}

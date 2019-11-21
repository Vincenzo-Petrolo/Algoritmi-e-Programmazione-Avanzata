#include <stdio.h>
int gcd(int a,int b);


int main() {
    int a,b;
    int mcd;

    printf("\nInserire i due numeri: ");
    scanf("%d%d",&a,&b);
    mcd = gcd(a,b);
    printf("\nIl MCD è: %d",mcd);
    return 0;
}

int gcd(int a,int b){
    int tmp;
    if (b>a){
        tmp = a;
        a = b;
        b=tmp;
    }
    /*Condizione di terminazione, il minore è uguale a 0*/
    if (b==0)
        return a;
    /*Fine condizione di terminazione*/
    if (a%2 == 0 && b%2 == 0)
        return (2*gcd(a/2,b/2));
    if (a%2 != 0 && b%2 == 0)
        return (gcd(a,b/2));
    else if (a%2 == 0 && b%2 != 0)
        return (gcd(a/2,b));
    else
        return (gcd((a-b)/2,b));

}

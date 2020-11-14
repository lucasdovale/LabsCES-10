#include <stdio.h>
#include <stdlib.h>

float fatorial (int x) {
    if (x>1)
        x=x*fatorial(x-1);
    return 1/x;
}

float somafat(int x) {
    float soma;
    if (x==1)
        soma=1;
    if(x>1){
        soma =fatorial(x) + somafat(x-1);
        printf("aezfjxhg");}
    return soma;
}


int main () {
    int x;
    printf("Digite x: ");
    scanf("%d", &x);
    printf("\n%f",fatorial(x));
    return 0;
}

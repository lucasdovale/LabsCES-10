/* Copyright by LUCAS DO VALE BEZERRA */
/* Turma 3 */
/* Lab 06: Criptografia em arquivo texto */
/* Programa compilado com CodeBlocks 17.02 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define max 1000

typedef struct texto texto;
//declarando e definindo a lista ligada do tipo texto
struct texto {
    int numero;
    char letra;
    struct texto *proximo;
};

int EhPrimo (int n) { // funcao que identifica se um numero eh primo
    int i=2;
    if (n!=2) {
        while (n%i!=0 && i<sqrt(n)) {
            i++;
        }
        if (n%i==0)
            return 0;
        else
            return 1;
    }
    else
        return 1;
}

int MDC (int x, int y) { // funcao que calcula o mdc entre dois numeros
    int mdc;
    if (x>y) {
        mdc=y;
        while (x%mdc!=0 || y%mdc!=0)
            mdc--;
    }
    if (x==y)
        mdc==x;
    if (x<y) {
        mdc=x;
        while (x%mdc!=0 || y%mdc!=0)
            mdc--;
    }
    return mdc;
}

int mod (int a, int b, int n) { // funcao que calculo o resto da divisao de a elevado a b por n (a^b mod n)
    if (b==0)
        return 1;
    else
        return (a*mod(a,b-1,n))%n;
}

int main () {
    unsigned int d = 2;
    char letra, frase[max]={0};
    FILE *entrada,*saida;
    entrada=fopen("mensagem.txt","r");
    saida=fopen("mensagemCriptografada.txt","w");
    int p, q, n, totiente, i=0, primeiroE=2, segundoE, terceiroE, c;
    printf("                Digite dois numeros primos primos p e q menores que 100\n\n"); // entrando com os dois primos
    printf("                Primeiro primo:");
    scanf("%d",&p);
    while (EhPrimo(p)==0 || p>=100) {
        printf("                 *Numero invalido!*\n                    Digite outro:"); // verificando se os numeros sao realmente primos
        scanf("%d",&p);
    }
    printf("\n                Segundo primo:");
    scanf("%d",&q);
    while (EhPrimo(q)==0 || q>=100) {
        printf("                 *Numero invalido!*\n                    Digite outro:");
        scanf("%d",&q);
    }
    n=p*q;
    texto *inicio=NULL, *aux;
    totiente=(p-1)*(q-1);
    while (MDC(totiente,primeiroE)!=1) { // calculando a primeira chave publica 'e'
        primeiroE++;
    }
    segundoE=primeiroE+1;
    while (MDC(totiente,segundoE)!=1) { // calculando a segunda chave publica 'e'
        segundoE++;
    }
    terceiroE=segundoE+1;
    while (MDC(totiente,terceiroE)!=1) { // calculando a terceira chave publica 'e'
        terceiroE++;
    }
    printf("\n                             Primeira chave publica: %d\n                             -----------------------", primeiroE);
    printf("\n                             Segunda chave publica: %d\n                             -----------------------", segundoE);
    printf("\n                             Terceira chave publica: %d\n                             -----------------------", terceiroE);
    while (!feof(entrada)) {    // lendo as letras do texto do arquivo
        aux=(texto*)malloc(sizeof(texto));
        do {
            fscanf(entrada,"%c ",&aux->letra);
            aux->letra=toupper(aux->letra);
        } while ((aux->letra<'A' || aux->letra=='K' || aux->letra=='W' || aux->letra=='Y' || aux->letra>'Z') && feof(entrada)==1);
        if (aux->letra>='A' && aux->letra <'K')
            aux->numero=aux->letra-'A'+1;
        if (aux->letra>'K' && aux->letra <'W')
            aux->numero=aux->letra-'A';
        if (aux->letra>='X' && aux->letra <'Y')
            aux->numero=aux->letra-'A'-1;
        if (aux->letra>'Y' && aux->letra <='Z')
            aux->numero=aux->letra-'A'-2;
        aux->proximo=inicio; // estruturando a lista ligada
        inicio=aux;
        c=mod(aux->numero,primeiroE,n);
        fprintf(saida,"%d ",c);
        while(aux->numero!=mod(c,d,n)) { // tentativas para descobrir o valor da chave privada 'd'
            printf("\n                             Tentativa %d: %d\n                             -----------------------",d-1,d);
            d++;
        }
        if (letra!='K' && letra!='W' && letra!='Y')
            letra=mod(c,d,n);
        if (aux->letra>='A' && aux->letra <'K')
            letra=letra+'A'-1;
        if (aux->letra>'K' && aux->letra <'W')
            letra=letra+'A';
        if (aux->letra>='X' && aux->letra <'Y')
            letra=letra+'A'+1;
        if (aux->letra>'Y' && aux->letra <='Z')
            letra=letra+'A'+2;
        letra=tolower(letra);
        frase[i]=letra;
        i++;
    }
    printf("\n                             Tentativa %d: %d\n                             -----------------------",d-1,d); // ultima tentativa para descobrir o 'd'
    printf("\n                             Chave privada: %d",d);
    printf("\n\n                 A frase descriptografada eh: %s\n\n", frase);
    fclose(entrada);
    fclose(saida);
    system("mensagemCriptografada.txt");
    return 0;
}

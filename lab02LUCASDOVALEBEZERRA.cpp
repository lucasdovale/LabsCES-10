/* Copyright by LUCAS DO VALE BEZERRA */
/* Turma 3 */
/* Lab 02: Televisão ASCII */
/* */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int m;
void Binario(int x) // função de mudança para base 2
{
    int numBits=8,i=numBits;
    while (i>0)
    {
        if (x&128)
        {
            if((m>=65 && m<=90) || (m>=97 && m<=122))
            {
                printf("%c", m);
            }
            else
                printf("1");
        }
        else
        {
            if((m>=65 && m<=90) || (m>=97 && m<=122))
            {
                printf(".");
            }
            else
                printf("0");
        }
        x<<=1;
        i--;
    }

}

int Deslocar1BitADireita (int m) // função que desloca um bit a direita os bits do número binário
{
    if (m%2==1)
    {
        m>>=1;
        m+=128;
    }
    else
    {
        m>>=1;
    }
    return m;
}

int Deslocar3BitsADireita (int m) // função que desloca três bits a direita os bits do número binário
{
    int cont=0;
    while (cont<3) {
        m=Deslocar1BitADireita(m);
        cont++;
    }
    return m;
}

int ehPrimo(int m) // função que identifica primos
{
    int divisor=2;
    char resposta;
    if (m!=2)
    {
        while (m%divisor!=0 && divisor<sqrt(m))
        {
            divisor++;
        }
        if (m%divisor==0)
        {
            resposta='N';
        }
        else
        {
            resposta='S';
        }
    }
    else
    {
        resposta='S';
    }
    return resposta;
}

int ehQuadradoPerfeito (int m) // função que identifica quadrados perfeitos
{
    float raizquadrada;
    int parteinteiradaraizquadrada;
    char resposta;
    raizquadrada=sqrt(m);
    parteinteiradaraizquadrada=raizquadrada;
    if (raizquadrada!=parteinteiradaraizquadrada)
    {
        resposta='N';
    }
    else
    {
        resposta='S';
    }
    return resposta;
}

int main()
{
    printf("Esse programa apresenta uma TV ASCII, onde ira aparecer na tela o numero que voce escolher em binario, alem desse numero com deslocamentos unitarios de bits \n\n");
    float n1;
    int Esq,Dir,contador=0,soma=0,somadosmult3=0,impares=0,pares=0,primos=0,quadradosperfeitos=0; // Esq: número da coluna esquerda ; Dir: número da coluna direita
    printf("Digite um inteiro n entre 0 e 255\n");
    scanf("%f", &n1);
    m=n1;
    while (n1!=m || n1<0 || n1>255)
    {
        printf("Digite um NUMERO INTEIRO ENTRE 0 E 255\n");
        scanf("%f", &n1);
        m=n1;
    }
    m=n1;
    Esq=m;
    Dir=Deslocar3BitsADireita(Esq);
    printf("                TV ASCII\n");
    printf("        ###########################\n");
    do
    {
        if (Esq%2==0)
            pares++;
        else
            impares++;
        if (Esq%3==0)
            somadosmult3+=Esq;
        if (Dir%3==0)
            somadosmult3+=Dir;
        if (ehQuadradoPerfeito(Esq)=='S' || ehQuadradoPerfeito(Dir)=='S')
            quadradosperfeitos++;
        if (ehPrimo(Esq)=='S' || ehPrimo(Dir)=='S')
            primos++;
        soma+=Esq+Dir;
        printf("        ## ");
        Binario(Esq);
        printf("|");
        Binario(Dir);
        if(contador==5 || contador==7) { // neste if/else estamos enfeitando a televisão colocando um botão de ligar/desligar
            printf(" ##---#\n");
        }
        else if(contador==6) {
             printf(" ##(o)#\n");
             }
             else {
             printf(" ##   #\n");
             }
        Esq=Deslocar1BitADireita(Esq);
        Dir=Deslocar3BitsADireita(Dir);
        contador++;
    }
    while (contador<8);
    printf("        ###########################\n\n");


    printf("\nSoma total= %1d\n",soma);
    printf("Quantidade de primos= %1d\n",primos);
    printf("Quantidade de quadrados perfeitos= %1d\n",quadradosperfeitos);
    printf("Soma dos multiplos de 3= %1d\n",somadosmult3);
    printf("Quantidade de impares= %1d\n",impares);
    printf("Quantidade de pares= %1d\n",pares);

    system("PAUSE");
    return 0;
}

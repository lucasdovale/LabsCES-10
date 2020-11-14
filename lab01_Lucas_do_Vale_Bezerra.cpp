// incluindo as bibliotecas
#include <stdio.h>
#include <stdlib.h>
// função principal
int main()
{
// declarando variáveis
    int a,b,c=1,produto=0;
// agora, dando oportunidade para o cliente inserir suas variáveis (multiplicando e multiplicador)
    printf("Insira o multiplicando: \n");
    scanf("%d", &a);
    printf("Insira o multiplicador:  \n");
    scanf("%d", &b);
// agora, para descobrirmos o resultado da multiplicação:
    printf("\n-------------------------\n");
    printf("RESULTADO EM CICLOS SUCESSIVOS\n");

    while (c<=b)
    {
        printf("\nCiclo %d= +%d\n", c, a);
        c++;
        produto=produto+a;
        printf("Parcela= %d\n",produto);
    }
// feita a função while corretamente, temos o valor do produto:
    printf("\nO resultado da multiplicacao e: %d\n", produto);

    system("pause");
    return 0;
}

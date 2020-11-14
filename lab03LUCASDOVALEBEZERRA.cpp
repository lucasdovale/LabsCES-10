/* Copyright by LUCAS DO VALE BEZERRA */
/* Turma 3 */
/* Lab 03: Sudoku Inteligente */
/* Programa compilado com CodeBlocks 17.12 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

  int matriz [5][5] = {0},linhas=5,colunas=5,i,j,pontuacao=100,recorde=-200,erros=0;

  int verificaErro (int matriz [5][5]) { //verifica se a matriz obedece às restrições do Sudoku
     int k,linha,coluna;
     for(linha=0;linha<5;linha++) {
        for(coluna=0;coluna<5;coluna++) {
            if(matriz [linha][coluna]!=0) {
                for(k=0;k<5;k++) {
                    if (k!=linha) {
                        if (matriz [linha][coluna]>0 && matriz [linha][coluna]==matriz [k][coluna]) {
                            return 0;
                        }
                    }
                }
                for(k=0;k<5;k++) {
                     if (k!=coluna) {
                        if (matriz [linha][coluna]>0 && matriz [linha][coluna]==matriz [linha][k]) {
                            return 0;
                        }
                     }
                }
            }
        }
     }

     return 1;
 }

  int teste (int i,int j) { // testa se é possivel preencher uma dada posição com um número
      matriz[i][j]=0;
      while (matriz[i][j]<5) {
          matriz[i][j]++;
          verificaErro(matriz);
          if (verificaErro(matriz)==1) {
             return 1;
          }
      }
      return 0;
  }

  void jogadaAuxiliar(int matriz [5][5]) { // ajuda na jogada
      int i,j;
      srand(time(NULL));
      do {
          i=rand() %5;
          j=rand() %5;
      }
      while (matriz [i][j]!=0);
      if (teste(i,j)==1) {
         do {
             matriz [i][j]=rand() %5+1;
             verificaErro(matriz);
         }
         while (verificaErro(matriz)==0);
      }
      else {
         matriz [i][j]=-1;
      }
      pontuacao-=2;
  }

  int verificaFim (int matriz [5][5]) { // verifica se acabou a partida
      int i,j;
      if(erros>=5)
        return 1;
      for(i=0;i<5;i++)
        for(j=0;j<5;j++)
            if (matriz [i][j]==0)
                return 0;
  return 1;
  }

  void telaInicial (int matriz [5][5]) {
     system("cls");
     int i,j, numero;
     for(i=0;i<5;i++) {
        for(j=0;j<5;j++) {
            matriz[i][j]=0;
            printf("    %d  ", matriz [i][j]);
        }
        printf("\n");
     }
     srand(time(NULL));
     for(int contador=0; contador<6; contador++) {
          i=rand() %5;
          j=rand() %5;
          numero = rand() % 5 + 1;

        if (matriz [i][j]==0){
           matriz[i][j] = numero;

           if (verificaErro(matriz)==0) {
               matriz[i][j] = 0;
               contador--;
           }
        }
        else {
          contador--;
        }
     }
 }

  void telaNova (int matriz [5][5]) { // tela impressa a cada nova jogada
       printf("\n     Erros:%d/5     ", erros);
       printf("Pontuacao:%d\n\n", pontuacao);
       for (i=0;i<linhas;i++) {
            for (j=0; j<colunas; j++) {
                      if(matriz [i][j]<0)
                        printf("    X  ");
                      else
                        printf("    %d  ", matriz [i][j]);
            }
         printf("\n");
       }
  }

  int telaFinal (int matriz[5][5]) { // tela que imprime o resultado final da partida
       int cont=0;
       system("cls");
       if (erros>4) {
            for(i=0;i<5;i++) {
                for(j=0;j<5;j++) {
                    if (matriz [i][j]==0)
                        cont++;
                }
            }
            pontuacao-=10*cont;
            if (pontuacao<0)
                pontuacao=0;
            if (pontuacao>=recorde)
                recorde=pontuacao;
            printf("Voce perdeu :( \n\nScore:%d           Best Score:%d\n\n", pontuacao,recorde);
            for (i=0;i<linhas;i++) {
                for (j=0; j<colunas; j++) {
                      printf("    X  ");
                }
            printf("\n");
            }
                  return 0;
       }
       else {
            if (pontuacao>=recorde)
            recorde=pontuacao;
            printf("\n\nScore:%d           Best Score:%d\n\n", pontuacao,recorde);
            for (i=0;i<linhas;i++) {
                for (j=0; j<colunas; j++) {
                      printf("    %d  ", pontuacao);
                }
            printf("\n");
            }
       }
  }

  int inserirNumDeDoisDig () {
       int numDeDoisDigitos;
       printf("\nEscolha um numero de dois digitos, cujos digitos representarao a linha e a coluna que voce quer preencher: ");
               scanf("%d", &numDeDoisDigitos);
                 j=numDeDoisDigitos%10-1;
                 i=(numDeDoisDigitos/10)%10-1;
               while (numDeDoisDigitos<11 || numDeDoisDigitos>55 || numDeDoisDigitos%10==0 || numDeDoisDigitos%10>5 && erros<5) {
                      ++erros;
                      if (verificaFim(matriz)==1){
                          telaFinal(matriz);
                          return 0;
                      }
                      pontuacao-=5;
                      system("cls");
                      telaNova(matriz);
                      printf("\nDigite um numero com posicao valida: ");
                      scanf("%d", &numDeDoisDigitos);
               }
               while (matriz [i][j]!=0 && erros<5) {
                      ++erros;
                      if (verificaFim(matriz)==1) {
                          telaFinal(matriz);
                          return 0;
                      }
                      pontuacao-=5;
                      system("cls");
                      telaNova(matriz);
                      printf("\nDigite uma posicao nao preenchida: ");
                      scanf("%d", &numDeDoisDigitos);
                      j=numDeDoisDigitos%10-1;
                      i=(numDeDoisDigitos/10)%10-1;
               }
      return numDeDoisDigitos;
  }

  int inserirNumPreencher (int i, int j) { // insere um numero de 1 a 5 na posição i,j da matriz
     printf("\nEscolha o numero de 1 a 5 com o qual voce quer preencher: ");
               scanf("%d", &matriz [i][j]);
               while (matriz [i][j]==0 || matriz [i][j]>5 && erros<5) {
                   matriz[i][j]=0;
                   erros++;
                   if (verificaFim(matriz)==1) {
                          telaFinal(matriz);
                          return 0;
                   }
                   pontuacao-=5;
                   system("cls");
                   telaNova(matriz);
                   printf("\nDigite um numero valido para preencher: ");
                   scanf("%d", &matriz [i][j]);
               }
    return matriz[i][j];
 }

  int validarCaractere (char c) {
      if (c=='S' || c=='s' || c=='N' || c=='n')
        return 1;
      else
      {
         printf("Entrada invalida");
         return 0;
      }
  }

  void jogada() { // cada jogada da partida
      int numDeDoisDigitos,cont=0;
      char ajuda='n';
      telaInicial(matriz);
      while (verificaFim(matriz)==0 && erros<5){
        if(erros<5 && verificaFim(matriz)==0){
         do {
               if(ajuda=='S'||ajuda=='s') {
                  jogadaAuxiliar(matriz);
                  if (verificaFim(matriz)==1) {
                    system("cls");
                    telaNova(matriz);
                    return;
                  }
                  system("cls");
                  telaNova(matriz);
               }
               else {
                  system("cls");
                  telaNova(matriz);
               }
               numDeDoisDigitos=inserirNumDeDoisDig();
               j=numDeDoisDigitos%10-1;
               i=(numDeDoisDigitos/10)%10-1;
               if (numDeDoisDigitos!=0)
                    matriz[i][j]=inserirNumPreencher(i,j);
               if (matriz [i][j]<0) {
                   if (teste(i,j)==0) {
                    matriz [i][j]=-1;
                   }
                   else {
                   matriz[i][j]=0;
                   erros++;
                   pontuacao-=5;
                   }
               }
               system("cls");
               if (verificaErro(matriz)==0) {
                  erros++;
                  pontuacao-=5;
                  matriz[i][j]=0;
               }
              if (verificaFim(matriz)==1)
                return;
              telaNova(matriz);
              if (erros<5) {
                do {
                  printf("\nQuer ajuda? (s/n) ");
                  fflush(stdin);
                  scanf("%c", &ajuda);
                }
                while (validarCaractere(ajuda)==0);
              }
         }
         while (verificaErro(matriz)==0 && erros<5);
         telaNova(matriz);
        }
        else {
            system("cls");
            telaFinal(matriz);
        }
      }
  }

  int main() {
     char jogarNovamente='s';
     printf("                                  Bem-vindo ao Sudoku Inteligente!!!\n\nNesse jogo, voce deve conseguir completar todo o tabuleiro 5x5 obedencendo a restricao de\nnao ter um mesmo elemento na linha e na coluna.\nPara o caso de nao haver possibilidade de preencher com algum elemento de 1 a 5, digite\num numero negativo, e, assim, sera atribuido um X na casa a qual voce desejou preencher.\nObs: Voce so pode errar 5 vezes!\n\n\n                                            BOM JOGO!!!\n\n\n\n\n\n\n\n\n\n");
     system("pause");
     while (jogarNovamente=='s' || jogarNovamente=='S'){
        pontuacao=100;
        jogada();
        telaFinal(matriz);
        do {
            printf("\nQuer jogar novamente? (s/n) ");
            fflush(stdin);
            scanf("%c", &jogarNovamente);
        }
        while (validarCaractere(jogarNovamente)==0);
        erros=0;
     }
     system("pause");
     return 0;
 }


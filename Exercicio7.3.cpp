#include <stdio.h>
#include <stdlib.h>
#define max 10

int main() {
   int n;
   int matriz[max][max]={0};
   do {
      printf("Escolha o n da matriz nxn (n<=10):");
      scanf("%d", &n);
   }
   while (n>10 || n<1);
   for(int i=0;i<n;i++) {
      matriz[i][0]=1;
      matriz[i][i]=1;
      for (int l=0;l<n && i!=0 && i!=l;l++) {
           matriz[i][l]=matriz[i-1][l-1]+matriz[i-1][l];
      }
   }
   printf("\n");
   for(int j=0;j<n;j++) {
      for(int k=0;k<n;k++) {
          if(matriz[j][k]!=0)
          printf("%4d  ", matriz[j][k]);
      }
      printf("\n");
   }
   printf("\n");
   system("pause");
   return 0;
}


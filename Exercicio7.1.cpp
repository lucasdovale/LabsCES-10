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
      matriz[i][i]=27;
      matriz[0][i]=27;
      matriz[n-1][i]=27;
      matriz[i][0]=27;
      matriz[i][n-1]=27;
   }
   printf("\n");
   for(int j=0;j<n;j++) {
      for(int k=0;k<n;k++) {
          printf("%4d  ", matriz[j][k]);
      }
      printf("\n");
   }
   printf("\n");
   system("pause");
   return 0;
}

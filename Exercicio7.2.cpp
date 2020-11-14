#include <stdio.h>
#include <stdlib.h>
#define max 10

int main() {
   int n, i, l,j,k;

   do {
      printf("Escolha o n da matriz nxn (n<=10):");
      scanf("%d", &n);
   }
   while (n>10 || n<1);
   int matriz[n][n]={0};
   for(i=0;i<n;i++) {
        for(l=0;l<n;l++) {
           matriz[i+l][l]=82;
        }
   }
   printf("\n");
   for(j=0;j<n;j++) {
      for(k=0;k<n;k++) {
          printf("%4d  ", matriz[j][k]);
      }
      printf("\n");
   }
   printf("\n");
   system("pause");
   return 0;
}

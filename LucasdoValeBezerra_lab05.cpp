/* Copyright by LUCAS DO VALE BEZERRA */
/* Turma 3 */
/* Lab 05: Copa do Mundo 2018 */
/* Programa compilado com CodeBlocks 17.01 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char cadeia[26];

struct selecao {
    cadeia nome;
    int pontos, vitorias, golspro, golscontra, maxgolspro, maxgolscontra, saldogols;
} selecao,vencedorOitavas[9],vencedorQuartas[5],vencedorSemi[3],campeao;

struct grupo {
    char nome;
    struct selecao vetorSelecoes[5];
    int resultados[6][2];
    cadeia primeiro, segundo;
} vetorGrupos[9];

FILE *FileIn, *FileOut, *Estat;

void ResultadosPrimeiraFase() {
    int i, golstime1, golstime2;
    for (i=1;i<=8;i++) {
        printf("                                ---------Grupo %d---------\n",i);
        for (int j=1;j<=3;j++)
            for (int k=1+j;k<=4;k++){
                golstime1=rand() % ((vetorGrupos[i].vetorSelecoes[j].maxgolspro>=vetorGrupos[i].vetorSelecoes[k].maxgolscontra)? vetorGrupos[i].vetorSelecoes[k].maxgolscontra:vetorGrupos[i].vetorSelecoes[j].maxgolspro);
                golstime2=rand() % ((vetorGrupos[i].vetorSelecoes[k].maxgolspro>=vetorGrupos[i].vetorSelecoes[j].maxgolscontra)? vetorGrupos[i].vetorSelecoes[j].maxgolscontra:vetorGrupos[i].vetorSelecoes[k].maxgolspro);
                if (golstime1==golstime2) {
                    vetorGrupos[i].vetorSelecoes[j].golspro+=golstime1;
                    vetorGrupos[i].vetorSelecoes[k].golspro+=golstime2;
                    vetorGrupos[i].vetorSelecoes[j].golscontra+=golstime2;
                    vetorGrupos[i].vetorSelecoes[k].golscontra+=golstime1;
                    vetorGrupos[i].vetorSelecoes[j].saldogols+=golstime1-golstime2;
                    vetorGrupos[i].vetorSelecoes[k].saldogols+=golstime2-golstime1;
                    vetorGrupos[i].vetorSelecoes[j].pontos+=1;
                    vetorGrupos[i].vetorSelecoes[k].pontos+=1;
                }
                else if (golstime1>golstime2) {
                        vetorGrupos[i].vetorSelecoes[j].golspro+=golstime1;
                        vetorGrupos[i].vetorSelecoes[k].golspro+=golstime2;
                        vetorGrupos[i].vetorSelecoes[j].golscontra+=golstime2;
                        vetorGrupos[i].vetorSelecoes[k].golscontra+=golstime1;
                        vetorGrupos[i].vetorSelecoes[j].saldogols+=golstime1-golstime2;
                        vetorGrupos[i].vetorSelecoes[k].saldogols+=golstime2-golstime1;
                        vetorGrupos[i].vetorSelecoes[j].vitorias+=1;
                        vetorGrupos[i].vetorSelecoes[j].pontos+=3;
                    }
                    else {
                        vetorGrupos[i].vetorSelecoes[j].golspro+=golstime1;
                        vetorGrupos[i].vetorSelecoes[k].golspro+=golstime2;
                        vetorGrupos[i].vetorSelecoes[j].golscontra+=golstime2;
                        vetorGrupos[i].vetorSelecoes[k].golscontra+=golstime1;
                        vetorGrupos[i].vetorSelecoes[j].saldogols+=golstime1-golstime2;
                        vetorGrupos[i].vetorSelecoes[k].saldogols+=golstime2-golstime1;
                        vetorGrupos[i].vetorSelecoes[k].vitorias+=1;
                        vetorGrupos[i].vetorSelecoes[k].pontos+=3;
                    }
                vetorGrupos[i].resultados[j+k-3][0]=golstime1;
                vetorGrupos[i].resultados[j+k-3][1]=golstime2;
               printf("                         %-14s  |%d x %d|  %14s\n",vetorGrupos[i].vetorSelecoes[j].nome,golstime1,golstime2,vetorGrupos[i].vetorSelecoes[k].nome);
            }
    }
    printf("\n                           -----------------------------------\n\n");
}

void ClassificarGrupos() {
    int i,k,trocou;
    struct selecao auxiliar;
    for (i=1;i<=8;i++) {
        for(k=0,trocou=1;k<4 && trocou;k++)
            for (int j=1,trocou=0;j<4-k;j++) {
                if (vetorGrupos[i].vetorSelecoes[j].pontos>vetorGrupos[i].vetorSelecoes[j+1].pontos) {
                    auxiliar=vetorGrupos[i].vetorSelecoes[j];
                    vetorGrupos[i].vetorSelecoes[j]=vetorGrupos[i].vetorSelecoes[j+1];
                    vetorGrupos[i].vetorSelecoes[j+1]=auxiliar;
                    trocou=1;
                }
                if (vetorGrupos[i].vetorSelecoes[j].pontos==vetorGrupos[i].vetorSelecoes[j+1].pontos) {
                    if (vetorGrupos[i].vetorSelecoes[j].vitorias>vetorGrupos[i].vetorSelecoes[j+1].vitorias) {
                        auxiliar=vetorGrupos[i].vetorSelecoes[j];
                        vetorGrupos[i].vetorSelecoes[j]=vetorGrupos[i].vetorSelecoes[j+1];
                        vetorGrupos[i].vetorSelecoes[j+1]=auxiliar;
                    }
                    if (vetorGrupos[i].vetorSelecoes[j].vitorias==vetorGrupos[i].vetorSelecoes[j+1].vitorias) {
                        if (vetorGrupos[i].vetorSelecoes[j].saldogols>vetorGrupos[i].vetorSelecoes[j+1].saldogols) {
                            auxiliar=vetorGrupos[i].vetorSelecoes[j];
                            vetorGrupos[i].vetorSelecoes[j]=vetorGrupos[i].vetorSelecoes[j+1];
                            vetorGrupos[i].vetorSelecoes[j+1]=auxiliar;
                        }
                        if (vetorGrupos[i].vetorSelecoes[j].saldogols==vetorGrupos[i].vetorSelecoes[j+1].saldogols) {
                            if (vetorGrupos[i].vetorSelecoes[j].golspro>vetorGrupos[i].vetorSelecoes[j+1].golspro) {
                                auxiliar=vetorGrupos[i].vetorSelecoes[j];
                                vetorGrupos[i].vetorSelecoes[j]=vetorGrupos[i].vetorSelecoes[j+1];
                                vetorGrupos[i].vetorSelecoes[j+1]=auxiliar;
                            }
                        }
                    }
                }
            }
        vetorGrupos[i].vetorSelecoes[4].maxgolspro+=1;
        vetorGrupos[i].vetorSelecoes[4].maxgolscontra-=1;
    }
}

void ResultadosOitavas (int grupo1,int grupo2, int j, int k,int cont) {
    int golstime1,golstime2;
    do {
        golstime1=rand() % ((vetorGrupos[grupo1].vetorSelecoes[j].maxgolspro>=vetorGrupos[grupo2].vetorSelecoes[k].maxgolscontra)? vetorGrupos[grupo2].vetorSelecoes[k].maxgolscontra:vetorGrupos[grupo1].vetorSelecoes[j].maxgolspro);
        golstime2=rand() % ((vetorGrupos[grupo2].vetorSelecoes[k].maxgolspro>=vetorGrupos[grupo1].vetorSelecoes[j].maxgolscontra)? vetorGrupos[grupo1].vetorSelecoes[j].maxgolscontra:vetorGrupos[grupo2].vetorSelecoes[k].maxgolspro);
    } while (golstime1==golstime2);
    if (golstime1>golstime2)
        vencedorOitavas[cont]=vetorGrupos[grupo1].vetorSelecoes[j];
    else
        vencedorOitavas[cont]=vetorGrupos[grupo2].vetorSelecoes[k];
    printf("                          %-14s  |%d x %d|  %14s\n",vetorGrupos[grupo1].vetorSelecoes[j].nome,golstime1,golstime2,vetorGrupos[grupo2].vetorSelecoes[k].nome);
}

void ResultadosQuartas (int j, int k, int cont) {
    int golstime1,golstime2;
    do {
        golstime1=rand() % ((vencedorOitavas[j].maxgolspro>=vencedorOitavas[k].maxgolscontra)? vencedorOitavas[k].maxgolscontra:vencedorOitavas[j].maxgolspro);
        golstime2=rand() % ((vencedorOitavas[k].maxgolspro>=vencedorOitavas[j].maxgolscontra)? vencedorOitavas[j].maxgolscontra:vencedorOitavas[k].maxgolspro);
    } while (golstime1==golstime2);
    if (golstime1>golstime2)
        vencedorQuartas[cont]=vencedorOitavas[j];
    else
        vencedorQuartas[cont]=vencedorOitavas[k];
    printf("                          %-14s  |%d x %d|  %14s\n",vencedorOitavas[j].nome,golstime1,golstime2,vencedorOitavas[k].nome);
}

void ResultadosSemi (int j, int k, int cont) {
    int golstime1,golstime2;
    do {
        golstime1=rand() % ((vencedorQuartas[j].maxgolspro>=vencedorQuartas[k].maxgolscontra)? vencedorQuartas[k].maxgolscontra:vencedorQuartas[j].maxgolspro);
        golstime2=rand() % ((vencedorQuartas[k].maxgolspro>=vencedorQuartas[j].maxgolscontra)? vencedorQuartas[j].maxgolscontra:vencedorQuartas[k].maxgolspro);
    } while (golstime1==golstime2);
    if (golstime1>golstime2)
        vencedorSemi[cont]=vencedorQuartas[j];
    else
        vencedorSemi[cont]=vencedorQuartas[k];
    printf("                          %-14s  |%d x %d|  %14s\n",vencedorQuartas[j].nome,golstime1,golstime2,vencedorQuartas[k].nome);
}

void Final (int j, int k, int cont) {
    int golstime1,golstime2;
    do {
        golstime1=rand() % ((vencedorSemi[j].maxgolspro>=vencedorSemi[k].maxgolscontra)? vencedorSemi[k].maxgolscontra:vencedorSemi[j].maxgolspro);
        golstime2=rand() % ((vencedorSemi[k].maxgolspro>=vencedorSemi[j].maxgolscontra)? vencedorSemi[j].maxgolscontra:vencedorSemi[k].maxgolspro);
    } while (golstime1==golstime2);
    if (golstime1>golstime2)
        campeao=vencedorSemi[j];
    else
        campeao=vencedorSemi[k];
    printf("                        %-14s  |%d x %d|  %14s\n",vencedorSemi[j].nome,golstime1,golstime2,vencedorSemi[k].nome);
    printf("\n\n                  ***************A SELECAO CAMPEA FOI: %s************", campeao.nome);
}

void LerSelecoes() {
    int i,j,lenght;
    char nomegrupo,c;
    for (i=1, nomegrupo='A'; i<=8; nomegrupo++, i++) {
        vetorGrupos[i].nome=nomegrupo;
        for (j=1;j<=4;j++) {
            fgets(vetorGrupos[i].vetorSelecoes[j].nome,31,FileIn);
            lenght=strlen(vetorGrupos[i].vetorSelecoes[j].nome);
            vetorGrupos[i].vetorSelecoes[j].nome[lenght-1]='\0';
            vetorGrupos[i].vetorSelecoes[j].pontos=0;
            vetorGrupos[i].vetorSelecoes[j].vitorias=0;
            vetorGrupos[i].vetorSelecoes[j].golspro=0;
            vetorGrupos[i].vetorSelecoes[j].golscontra=0;
            vetorGrupos[i].vetorSelecoes[j].saldogols=0;
            fscanf(Estat,"%d %d", &vetorGrupos[i].vetorSelecoes[j].maxgolspro,&vetorGrupos[i].vetorSelecoes[j].maxgolscontra);
        }
    }
}

void EscreverGrupos() {
    int i,j;
    for (i=1;i<=8;i++) {
        fprintf(FileOut,"\n\nGRUPO %c: ", vetorGrupos[i].nome);
        fprintf(FileOut,"\n\n%-20s|%8s|%8s|%8s|%8s|%8s","Selecao","Pontos","Vitorias","GolsPro","GolsCon","SaldGols");
        fprintf (FileOut,"\n--------------------|--------|--------|--------|--------|--------");
        for (j=4;j>=1;j--)
            fprintf(FileOut,"\n%-20s|%8d|%8d|%8d|%8d|%8d",
                    vetorGrupos[i].vetorSelecoes[j].nome,
                    vetorGrupos[i].vetorSelecoes[j].pontos,
                    vetorGrupos[i].vetorSelecoes[j].vitorias,
                    vetorGrupos[i].vetorSelecoes[j].golspro,
                    vetorGrupos[i].vetorSelecoes[j].golscontra,
                    vetorGrupos[i].vetorSelecoes[j].saldogols);
    }
}

int main() {
    printf("                    Processamento das informacoes da Copa do Mundo 2018\n\n");
    printf("\tArquivo ListaSelecoes.txt: Contem o nome das 32 selecoes da Copa\n\n");
    printf("\tArquivo RelatorioCopa2018.txt: Relatorio da Copa\n\n");
    char resposta;
    printf("\n        Realizar leitura das selecoes e estatisticas?   ");
    system("PAUSE");
    printf("\n        Leitura feita com sucesso!!        ");
    system("PAUSE");
    system("cls");
    do {
        FileIn=fopen("ListaSelecoes.txt","r");
        FileOut=fopen("RelatorioCopa2018.txt","w");
        Estat=fopen("EstatisticaSelecoes.txt","r");
        fprintf(FileOut,"COPA DO MUNDO 2018");
        srand(time(NULL));
        LerSelecoes();
        printf("                                      SIMULACAO DA COPA DO MUNDO DE 2018\n\n            Nesse programa voce fara uma simulacao dos jogos da copa: Fase de Grupos, Oitavas de Final,\n            Quartas de Final, Semi-Final e a grande Final.\n\n            Voce quer que o Brasil seja campeao? (s/n) ");
        fflush(stdin);
        scanf("%c", &resposta);
        if (resposta=='n' || resposta=='N') {
            printf("\n            Voce nao merece fazer a simulacao!\n\n");
            return 0;
        }
        else
            printf("\n\n                            BOM!!! BORA GANHAR ESSE HEXA!\n\n           ");
        system("PAUSE");
        system("cls");
        printf("                                      FASE DE GRUPOS\n\n                                          JOGOS\n\n");
        ResultadosPrimeiraFase();
        printf("\n\n");
        ClassificarGrupos();
        EscreverGrupos();
        system("PAUSE");
        system("cls");
        fclose(FileOut);
        system("RelatorioCopa2018.txt");
        system("PAUSE");
        system("cls");
        printf("                                      OITAVAS DE FINAL\n\n");
        ResultadosOitavas(3,4,4,3,1);
        ResultadosOitavas(1,2,4,3,2);
        ResultadosOitavas(5,6,4,3,3);
        ResultadosOitavas(7,8,4,3,4);
        ResultadosOitavas(4,3,4,3,5);
        ResultadosOitavas(2,1,4,3,6);
        ResultadosOitavas(6,5,4,3,7);
        ResultadosOitavas(8,7,4,3,8);
        printf("\n\n");
        system("PAUSE");
        system("cls");
        printf("                                      QUARTAS DE FINAL\n\n");
        ResultadosQuartas(1,2,1);
        ResultadosQuartas(3,4,2);
        ResultadosQuartas(5,6,3);
        ResultadosQuartas(7,8,4);
        printf("\n\n");
        system("PAUSE");
        system("cls");
        printf("                                        SEMI-FINAL\n\n");
        ResultadosSemi(1,2,1);
        ResultadosSemi(3,4,2);
        printf("\n\n");
        system("PAUSE");
        system("cls");
        printf("                                         FINAL\n\n");
        Final(1,2,1);
        printf("\n\n                  Voce quer fazer uma nova simulacao? (s/n)");
        fflush(stdin);
        scanf("%c",&resposta);
        system("cls");
        fclose(Estat);
        fclose(FileIn);
    } while (resposta=='s' || resposta=='S');
    return 0;
}

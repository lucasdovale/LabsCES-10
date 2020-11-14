/* Copyright by LUCAS DO VALE BEZERRA */
/* Turma 3 */
/* Lab 04: Mini SGBD */
/* Programa compilado com CodeBlocks 17.12 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct endereco {  // definindo a struct endereco, que sera utilizada na struct registro
        char rua[15];
        int numero;
        char cidade[20];
        int CEP;
        } enderecoPadrao;

struct registro { // definindo a struct registro, para podermos cadastrar os funcionarios
        char nomeCompleto[20];
        char funcao [15];
        char RG[11];
        float salario;
        int dataNasc;
        struct endereco novoEndereco;
    } novoRegistro[100], funcionario[100];

void gotoXY (int x, int y) { // funcao necessaria para mudar o cursos na tela
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD)
    {
        x,y
    });
    return;
}

int validarCaractere (char c) { // funcao que verifica se o cliente digitou um caractere previsto
    if (c=='S' || c=='s' || c=='N' || c=='n')
        return 1;
    else {
        printf("                                              *Entrada invalida*");
        return 0;
    }
}

void cadastrarNovoFunc () { // funcao para cadastrar os novos funcionarios da empresa
    FILE *arqEnt;
    char resposta='s';
    strcpy(enderecoPadrao.rua,"Pca M.E. Gomes");
    enderecoPadrao.numero=50;
    strcpy(enderecoPadrao.cidade,"S J dos Campos");
    enderecoPadrao.CEP=12228900;
    for (int j=0;j<100 && (resposta=='s' || resposta=='S');j++) {
        arqEnt=fopen("miniSGBD.txt", "a");
        printf("    CADASTRO DE NOVO FUNCIONARIO\n\n");
        printf("Nome completo: \n");
        printf("RG: \n");
        printf("Funcao: \n    a.Analista\n    b.Gerente\n    c.Arquiteto\n    d.Programador\n    e.Testador\n    f.Suporte\n");
        printf("Salario: \n");
        printf("Data de nascimento (DDMMAAAA):\n");
        printf("Endereco\n");
        printf("Deseja utilizar o endereco padrao? (s/n): \n");
        printf("    -Rua: \n");
        printf("    -Numero: \n");
        printf("    -Cidade: \n");
        printf("    -CEP: \n");
        printf("\nVoce confirma os dados? (s/n): ");
        printf("\nVoce quer cadastrar mais um funcionario? (s/n):");
        gotoXY(14,2);
        fflush(stdin);
        gets(novoRegistro[j].nomeCompleto);
        gotoXY(3,3);
        fflush(stdin);
        scanf("%s", novoRegistro[j].RG);
        gotoXY(7,4);
        fflush(stdin);
        scanf("%s", novoRegistro[j].funcao);
        gotoXY(8,11);
        fflush(stdin);
        scanf("%f", &novoRegistro[j].salario);
        gotoXY(30,12);
        fflush(stdin);
        scanf("%d", &novoRegistro[j].dataNasc);
        do
        {
            gotoXY(41,14);
            fflush(stdin);
            scanf("%c", &resposta);
        }
        while (validarCaractere(resposta)==0);
        if (resposta=='s' || resposta=='S')
        {
            gotoXY(9,15);
            printf("%s", enderecoPadrao.rua);
            gotoXY(12,16);
            printf("%d", enderecoPadrao.numero);
            gotoXY(12,17);
            printf("%s", enderecoPadrao.cidade);
            gotoXY(9,18);
            printf("%d", enderecoPadrao.CEP);
            strcpy(novoRegistro[j].novoEndereco.rua,enderecoPadrao.rua);
            novoRegistro[j].novoEndereco.numero=enderecoPadrao.numero;
            strcpy(novoRegistro[j].novoEndereco.cidade,enderecoPadrao.cidade);
            novoRegistro[j].novoEndereco.CEP=enderecoPadrao.CEP;
        }
        else
        {
            gotoXY(9,15);
            fflush(stdin);
            gets(novoRegistro[j].novoEndereco.rua);
            fflush(stdin);
            gotoXY(12,16);
            scanf("%d", &novoRegistro[j].novoEndereco.numero);
            fflush(stdin);
            gotoXY(12,17);
            gets(novoRegistro[j].novoEndereco.cidade);
            fflush(stdin);
            gotoXY(9,18);
            scanf("%d", &novoRegistro[j].novoEndereco.CEP);
        }
        do
        {
            gotoXY(30,20);
            fflush(stdin);
            scanf("%c", &resposta);
        }
        while (validarCaractere(resposta)==0);
        do
        {
            gotoXY(47,21);
            fflush(stdin);
            scanf("%c", &resposta);
        }
        while (validarCaractere(resposta)==0);
        system("cls");
        fprintf(arqEnt,"*********************\n%s\n",novoRegistro[j].nomeCompleto);
        fprintf(arqEnt,"%s\n",novoRegistro[j].RG);
        fprintf(arqEnt,"%s\n",novoRegistro[j].funcao);
        fprintf(arqEnt,"%.2f\n",novoRegistro[j].salario);
        fprintf(arqEnt,"%d\n",novoRegistro[j].dataNasc);
        fprintf(arqEnt,"%s\n",novoRegistro[j].novoEndereco.rua);
        fprintf(arqEnt,"%d\n",novoRegistro[j].novoEndereco.numero);
        fprintf(arqEnt,"%s\n",novoRegistro[j].novoEndereco.cidade);
        fprintf(arqEnt,"%d\n",novoRegistro[j].novoEndereco.CEP);
        fclose(arqEnt);
    }
}

void consultaPorNome(){ // funcao para consultar por nome (dentro da consulta simples)
    FILE *arq;
    FILE *arqSaida;
    arq=fopen("minisgbd.txt","r");
    arqSaida=fopen("consultas.txt","a");
    int i=0,teste=1, a=0;
    char lixo[30],nome[30], resposta;
    while (fscanf(arq,"%s\n",lixo) != EOF) {
        fgets(funcionario[i].nomeCompleto,30,arq);
        fscanf(arq,"%s\n", funcionario[i].RG);
        fscanf(arq,"%s\n",funcionario[i].funcao);
        fscanf(arq,"%f\n", &funcionario[i].salario);
        fscanf(arq,"%d\n", &funcionario[i].dataNasc);
        fgets(funcionario[i].novoEndereco.rua,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.numero);
        fgets(funcionario[i].novoEndereco.cidade,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.CEP);
        i++;
    }
    do {
        printf("\n    Digite um nome a ser consultado: ");
        scanf("%s",nome);
        fprintf(arqSaida,"%s\n",nome);
        printf("\n");
        for (i=0; i<100; i++)
        {
            teste=1;
            for (int j=0; j<strlen(nome); j++) {
                if(nome[j]!=funcionario[i].nomeCompleto[j]) {
                    teste=0;
                }
            }
            if(teste!=0) {
                printf("             %s", funcionario[i].nomeCompleto);
                a++;
            }
        }
        if(a==0) {
            printf("\n      Nao ha funcionarios com esse nome\n\n");
        }
        fclose(arq);
        fclose(arqSaida);
        printf("\nDeseja fazer uma nova consulta simples? (s/n): ");
        do {
            fflush(stdin);
            scanf("%c",&resposta);
        } while (validarCaractere(resposta)==0);
        system("cls");
    } while (resposta=='S' || resposta=='s');
}

void consultaPorRG() { // funcao para consultar por RG (dentro da consulta simples)
    FILE *arq;
    FILE *arqSaida;
    arq=fopen("minisgbd.txt","r");
    arqSaida=fopen("consultas.txt","a");
    int i=0,teste=1, a=0;
    char lixo[30],rg[30],resposta;
    while (fscanf(arq,"%s\n",lixo) != EOF) {
        fgets(funcionario[i].nomeCompleto,30,arq);
        fscanf(arq,"%s\n", funcionario[i].RG);
        fscanf(arq,"%s\n", funcionario[i].funcao);
        fscanf(arq,"%f\n", &funcionario[i].salario);
        fscanf(arq,"%d\n", &funcionario[i].dataNasc);
        fgets(funcionario[i].novoEndereco.rua,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.numero);
        fgets(funcionario[i].novoEndereco.cidade,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.CEP);
        i++;
    }
    do {
        printf("\n    Digite um RG a ser consultado: ");
        scanf("%s",rg);
        fprintf(arqSaida,"%s\n",rg);
        printf("\n");
        for (i=0;i<100;i++){
            teste=1;
            for (int j=0;j<strlen(rg);j++) {
                if(rg[j]!=funcionario[i].RG[j]) {
                    teste=0;
                }
            }
            if(teste!=0){
                printf("     Nome:%s    ", funcionario[i].nomeCompleto);
                printf(" RG:%s\n", funcionario[i].RG);
                a++;
            }
        }
        if(a==0){
            printf("\n      Nao ha funcionarios com esse RG\n\n");
        }
        fclose(arq);
        fclose(arqSaida);
        printf("\nDeseja fazer uma nova consulta simples? (s/n): ");
        do {
            fflush(stdin);
            scanf("%c",&resposta);
        } while (validarCaractere(resposta)==0);
        system("cls");
    } while (resposta=='s' || resposta=='S');
}

void consultaPorFuncao() { // funcao para consultar por funcao (dentro da consulta simples)
    FILE *arq;
    FILE *arqSaida;
    arq=fopen("minisgbd.txt","r");
    arqSaida=fopen("consultas.txt","a");
    int i=0,teste=1, a=0;
    char lixo[30],funcao[30],resposta;
    while (fscanf(arq,"%s\n",lixo) != EOF) {
        fgets(funcionario[i].nomeCompleto,30,arq);
        fscanf(arq,"%s\n", funcionario[i].RG);
        fscanf(arq,"%s\n", funcionario[i].funcao);
        fscanf(arq,"%f\n", &funcionario[i].salario);
        fscanf(arq,"%d\n", &funcionario[i].dataNasc);
        fgets(funcionario[i].novoEndereco.rua,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.numero);
        fgets(funcionario[i].novoEndereco.cidade,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.CEP);
        i++;
    }
    do {
        printf("\n    Digite uma funcao a ser consultado: ");
        scanf("%s",funcao);
        fprintf(arqSaida,"%s\n",funcao);
        printf("\n");
        for (i=0;i<100;i++){
            teste=1;
            for (int j=0;j<strlen(funcao);j++) {
                if(funcao[j]!=funcionario[i].funcao[j]) {
                    teste=0;
                }
            }
            if(teste!=0){
                printf("    Nome:%s", funcionario[i].nomeCompleto);
                a++;
            }
        }
        if(a==0){
            printf("\n      Nao ha funcionarios com essa funcao\n\n");
        }
        fclose(arq);
        fclose(arqSaida);
        printf("\nDeseja fazer uma nova consulta simples? (s/n): ");
        do {
            fflush(stdin);
            scanf("%c",&resposta);
        } while (validarCaractere(resposta)==0);
        system("cls");
    } while (resposta=='s'|| resposta=='S');
}

int consultaSimples () { // funcao para a consulta simples
    int escolha;
    printf("          Consulta Simples\n\n");
    printf("\n\n   1- Nome\n   2- RG\n   3- Funcao\n");
    gotoXY(2,2);
    printf(" Escolha um dos tipos de consulta abaixo: ");
    fflush(stdin);
    scanf("%d", &escolha);
    system("cls");
    switch (escolha) {
        case 1: consultaPorNome();break;
        case 2: consultaPorRG();break;
        case 3: consultaPorFuncao();break;
        default: return 0;
    }
    system("pause");
    system("cls");
}

int compararDatas (int x,int y) { // funcao que compara as datas de nascimento dos funcionarios, para podermos imprimi-los por ordem de idade
    int anox,anoy,mesx,mesy,diax,diay;
    anox=x%10000;
    anoy=y%10000;
    mesx=x%1000000;
    mesy=y%1000000;
    diax=x%100000000;
    diay=y%100000000;
    if (anox>anoy)
        return 1;
    else if (anox==anoy) {
        if (mesx>mesy)
            return 1;
        else if (mesx==mesy) {
            if (diax>diay)
                return 1;
        }
        else if (diax==diay)
            return 0;
    }
}

void bubbleSort(struct registro func[100], int n) { // funcao que coloca os funcionarios em ordem de idade
    int i, j; char nome[22];
    int trocou;
    for (i=0, trocou = 1; i<n-1 && trocou; i++){
        for (j=0, trocou = 0; j<n-1-i; j++){
            if (compararDatas(func[j].dataNasc, func[j+1].dataNasc)==1) {
                int x = func[j].dataNasc;
                func[j].dataNasc = func[j+1].dataNasc;
                func[j+1].dataNasc = x;
                trocou = 1;
                strcpy(nome,func[j].nomeCompleto);
                strcpy(func[j].nomeCompleto,func[j+1].nomeCompleto);
                strcpy(func[j+1].nomeCompleto,nome);
            }}}
    for(i=0;i<n;i++) {
        printf("%s\n",func[i].nomeCompleto);
    }
}

void funcPorIdade() { // funcao que imprime na tela os funcionarios em ordem de idade
    FILE *arq;
    arq=fopen("minisgbd.txt","r");
    int i=0,qtddefunc=0;
    char lixo[30], resposta;
    while (fscanf(arq,"%s\n",lixo) != EOF) {
        fgets(funcionario[i].nomeCompleto,30,arq);
        fscanf(arq,"%s\n", funcionario[i].RG);
        fscanf(arq,"%s\n",funcionario[i].funcao);
        fscanf(arq,"%f\n", &funcionario[i].salario);
        fscanf(arq,"%d\n", &funcionario[i].dataNasc);
        fgets(funcionario[i].novoEndereco.rua,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.numero);
        fgets(funcionario[i].novoEndereco.cidade,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.CEP);
        i++;
    }
    qtddefunc=i;
    bubbleSort(funcionario, qtddefunc);
    fclose(arq);
}

void gastoMensal() { // funcao que calcula o gasto mensal da empresa com seus funcionarios
    FILE *arq;
    arq=fopen("minisgbd.txt","r");
    int i=0;
    float gastomensal=0;
    char lixo[30], resposta;
    while (fscanf(arq,"%s\n",lixo) != EOF) {
        fgets(funcionario[i].nomeCompleto,30,arq);
        fscanf(arq,"%s\n", funcionario[i].RG);
        fscanf(arq,"%s\n",funcionario[i].funcao);
        fscanf(arq,"%f\n", &funcionario[i].salario);
        gastomensal+=funcionario[i].salario;
        fscanf(arq,"%d\n", &funcionario[i].dataNasc);
        fgets(funcionario[i].novoEndereco.rua,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.numero);
        fgets(funcionario[i].novoEndereco.cidade,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.CEP);
        i++;
    }
    fclose(arq);
    printf("O gasto mensal da empresa de software com seus funcionarios e' de: %.2f\n\n", gastomensal);
}

void tabelaFuncoes() { // funcao que mostra os funcioarios dispostos pelas suas respectivas funcoes
    FILE *arq;
    arq=fopen("minisgbd.txt","r");
    int i=0,contador1=3,contador2=3,contador3=3,contador4=3,contador5=3,contador6=3;
    char lixo[30],funcao[30],resposta;
    while (fscanf(arq,"%s\n",lixo) != EOF) {
        fgets(funcionario[i].nomeCompleto,30,arq);
        fscanf(arq,"%s\n", funcionario[i].RG);
        fscanf(arq,"%s\n", funcionario[i].funcao);
        fscanf(arq,"%f\n", &funcionario[i].salario);
        fscanf(arq,"%d\n", &funcionario[i].dataNasc);
        fgets(funcionario[i].novoEndereco.rua,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.numero);
        fgets(funcionario[i].novoEndereco.cidade,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.CEP);
        i++;
    }
    for(i=0;i<100;i++) {
        gotoXY(2,1);
        printf("*     Analista     *\n");
        if (strcmp(funcionario[i].funcao,"Analista")==0) {
            gotoXY(2,contador1);
            printf("%s\n",funcionario[i].nomeCompleto);
            contador1++;
        }
        gotoXY(22,1);
        printf("  Gerente     *\n");
        if (strcmp(funcionario[i].funcao,"Gerente")==0) {
            gotoXY(22,contador2);
            printf("%s",funcionario[i].nomeCompleto);
            contador2++;
        }
        gotoXY(42,1);
        printf("Arquiteto     *\n");
        if (strcmp(funcionario[i].funcao,"Arquiteto")==0) {
            gotoXY(42,contador3);
            printf("%s\n",funcionario[i].nomeCompleto);
            contador3++;
        }
        gotoXY(62,1);
        printf("Programador     *\n");
        if (strcmp(funcionario[i].funcao,"Programador")==0) {
            gotoXY(62,contador4);
            printf("%s\n",funcionario[i].nomeCompleto);
            contador4++;
        }
        gotoXY(82,1);
        printf("Testador     *\n");
        if (strcmp(funcionario[i].funcao,"Testador")==0) {
            gotoXY(82,contador5);
            printf("%s\n",funcionario[i].nomeCompleto);
            contador5++;
        }
        gotoXY(102,1);
        printf("Suporte     *\n");
        if (strcmp(funcionario[i].funcao,"Suporte")==0) {
            gotoXY(102,contador6);
            printf("%s\n",funcionario[i].nomeCompleto);
            contador6++;
        }
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    fclose(arq);
}

void funcPorEnd() { // funcao que mostra os funcionarios junto com seus enderecos
    FILE *arq;
    arq=fopen("minisgbd.txt","r");
    int i=0,qtddefunc=0;
    char lixo[30],resposta;
    while (fscanf(arq,"%s\n",lixo) != EOF) {
        fgets(funcionario[i].nomeCompleto,30,arq);
        fscanf(arq,"%s\n", funcionario[i].RG);
        fscanf(arq,"%s\n", funcionario[i].funcao);
        fscanf(arq,"%f\n", &funcionario[i].salario);
        fscanf(arq,"%d\n", &funcionario[i].dataNasc);
        fgets(funcionario[i].novoEndereco.rua,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.numero);
        fgets(funcionario[i].novoEndereco.cidade,30,arq);
        fscanf(arq,"%d\n", &funcionario[i].novoEndereco.CEP);
        i++;
    }
    qtddefunc=i;
    for(i=0;i<qtddefunc;i++) {
        printf("  Nome: %s",funcionario[i].nomeCompleto);
        printf("            Endereco\n  Rua: %s",funcionario[i].novoEndereco.rua);
        printf("  Numero: %d",funcionario[i].novoEndereco.numero);
        printf("  Cidade: %s",funcionario[i].novoEndereco.cidade);
        printf("  CEP: %d\n\n",funcionario[i].novoEndereco.CEP);
    }
        fclose(arq);
}

int consultaAvancada () { // funcao para a consultada avancada
    int escolha;
    printf("                  Consulta Avancada\n\n");
    printf("\n\n   1- Nomes dos funcionarios do mais velho para o mais novo\n");
    printf("   2- Total de gastos mensal da empresa com seus funcionarios\n");
    printf("   3- Tabela com as funcoes e seus respectivos funcionarios\n");
    printf("   4- Funcionarios por endereco");
    gotoXY(2,2);
    printf(" Escolha um dos tipos de consulta abaixo: ");
    fflush(stdin);
    scanf("%d", &escolha);
    system("cls");
    switch (escolha) {
        case 1: funcPorIdade();break;
        case 2: gastoMensal();break;
        case 3: tabelaFuncoes();break;
        case 4: funcPorEnd();break;
        default: return 0;
    }
    system("pause");
    system("cls");
}

int sair () { // funcao para sair do programa
    printf("Voce saiu do miniSGBD\n");
    return 0;
}

int main() { // funcao principal
   int resposta;
   do {
        printf("    Bem-vindo ao Mini SGBD\n\n");
        printf("   Escolha sua opcao: \n\n");
        printf("   1- Cadastrar novo funcionario\n");
        printf("   2- Consulta simples\n");
        printf("   3- Consulta avancada\n");
        printf("   4- Sair");
        gotoXY(21,2);
        fflush(stdin);
        scanf("%d", &resposta);
        system("cls");
        switch(resposta) {
        case 1:
            cadastrarNovoFunc();
            break;
        case 2:
            consultaSimples();
            break;
        case 3:
            consultaAvancada();
            break;
        case 4:
            sair();
            break;
        default:
            return 0;
        }
   } while (resposta!=4);
   printf("\n\n");
   system("pause");
   return 0;
}

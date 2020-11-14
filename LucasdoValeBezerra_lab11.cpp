//Lucas do Vale Bezerra
//Turma 3
//Exerc�cio 11: Torre de Controle
//Programa compilado com Code Blocks 13.12
//Instituto Tecnol�gico de Aeron�utica
//CES-10: Introdu��o � Computa��o
//Prof. Armando
//Julho de 2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noh noh; // definindo os ponteiros de struct do tipo noh (que ser�o utilizados na lista encadeada)
typedef noh *posicao; // definindo os ponteiros de struct do tipo noh que ser�o utilizados para indicar a posi��o de alguma struct na lista
typedef noh *lista; // definindo os ponteiros de struct que ser�o utilizados para criar um novo n� da lista

struct noh { // definindo a struct noh, que servir� de base para a lista encadeada e para armazenarmos as informa��es dos arquivos
    int numero;
    char cidade[32];
    noh *prox;
};

int main() {
    FILE *ent,*sai; // declarando os arquivos de entrada e saida
    ent=fopen("C:\\Lab11\\entrada11.txt","r");
    sai=fopen("C:\\Lab11\\lucasdovalebezerra11.txt","w");
    char mensagem[30],lixo[72],nome[32]; // declarando as vari�veis do tipo string para armazenar a mensagem do arquivo, o lixo quando necessario, e o nome da cidade do voo para ser armazenado na lista encadeada
    int num; // declarando as vari�veis do tipo inteiras para armazenar o n�mero do voo, e outra para indicar se � a primeira vez que ocorre uma urg�ncia nos avi�es
    posicao inicio=NULL,p=NULL,q=NULL,aux=NULL,r=NULL,n=NULL,ultimoUrgente=NULL; // declarando os ponteiros necess�rios para serem utilizados nas condi��es abaixo
    fprintf(sai,"AEROPORTO INTERNACIONAL DO RECIFE\n");
    fprintf(sai,"PERNAMBUCO - BRASIL\n");
    fprintf(sai,"AUTORIZACOES DE POUSO\n");
    fprintf(sai,"=========================================\n");
    fprintf(sai,"FLIGHT  FROM\n\n");
    for (int i=0;i<7;i++)  // lendo as 8 primeiras frases in�teis do arquivo de entrada e armazenando na vari�vel lixo
        fgets(lixo,72,ent);
	fscanf(ent," %s", mensagem); // lendo a mensagem do arquivo
    while (strcmp(mensagem,"FIM")!=0) { // o ciclo ir� acontecer at� a vari�vel mensagem for diferente de "FIM", isto �, ainda h� trabalho para a torre de controle
		if (strcmp(mensagem,"pede_pouso")==0) { // condi��o para a mensagem ser referente � de um avi�o pedindo para pousar
			p=(lista)malloc(sizeof(noh)); // alocando na mem�ria a struct referente ao voo
			fscanf(ent,"%d", &num); // lendo o numero e o nome do voo do arquivo
			fgets(nome,32,ent);
			p->numero=num;  // armazenando nas vari�veis
			strcpy(p->cidade,nome);
			p->prox=NULL;
			if (inicio==NULL) { // caso em que a fila est� vazia
				inicio=p;
			}
			else { // caso em que a fila est� preenchida com pelo menos um avi�o
				aux=inicio;
				while (aux->prox!=NULL)
					aux=aux->prox;
				aux->prox=p;
			}
        }
        if (strcmp(mensagem,"pista_liberada")==0) { // condi��o para a mensagem referente � pista estar liberada para pouso
            fgets(lixo,72,ent);
            if(inicio!=NULL) { // condi��o referente ao caso de haver avi�es na fila esperando para pousar
                fprintf(sai,"%04d  %s", inicio->numero, inicio->cidade); // printando no arquivo de saida o avi�o que pousou (aquele que o ponteiro inicio aponta)
				if (ultimoUrgente!=NULL)
					if (ultimoUrgente->numero==inicio->numero)
						ultimoUrgente=NULL;
				q=inicio->prox;
				free(inicio);
				inicio=q;
            }
            else  // caso em que a lista encadeada est� vazia
                fprintf(sai,"0000    Nenhum avi�o pousando\n"); // printando a mensagem padr�o para esse caso
        }
        if (strcmp(mensagem,"URGENCIA")==0) { // caso onde a mensagem se refere � urg�ncia de algum pouso
            fscanf(ent,"%d", &num); // lendo do arquivo o numero do voo de pouso urgente
			r=inicio;
			if (r->numero==num) {
				ultimoUrgente=r;
			} else {
				while (r->numero!=num) { // o ponteiro r ir� procurar esse voo e apontar para ele
					n=r;
					r=r->prox;
				} // ao final do ciclo, o ponteiro n ir� apontar exatamente no noh anterior ao r
				if (ultimoUrgente==NULL) { // caso em que s� h� um caso de urg�ncia
					n->prox=n->prox->prox; // l�gica dos ponteiros para que coloque o voo urgente para primeiro da fila
					r->prox=inicio;
					inicio=r;
					ultimoUrgente=r;
				}
				else { // caso em que h� mais de um caso de urg�ncia
					n->prox=n->prox->prox;
					r->prox=ultimoUrgente->prox;
					ultimoUrgente->prox=r;
					ultimoUrgente=r;
				}
			}
			fgets(lixo,72,ent); // lendo o lixo ap�s a mensagem de URGENTE e o numero do voo
        }
		fscanf(ent," %s", mensagem); // lendo a mensagem do arquivo
    }
    fprintf(sai,"\n\nSituacao da fila:\n\n");
    if (inicio==NULL)
        fprintf(sai,"Todos os avioes pousaram na melhor cidade do pais com sucesso =D"); // mensagem caso a lista final esteja vazia
    else
        for(p=inicio;p!=NULL;p=p->prox)
            fprintf(sai,"%04d  %s", p->numero, p->cidade); // mensagem caso a lista esteja preenchida
    fclose(ent); // fechando o arquivo de entrada
    fclose(sai); // fechando o arquivo de sa�da
    return 0;
}

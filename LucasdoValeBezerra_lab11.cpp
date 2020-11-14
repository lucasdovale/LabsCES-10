//Lucas do Vale Bezerra
//Turma 3
//Exercício 11: Torre de Controle
//Programa compilado com Code Blocks 13.12
//Instituto Tecnológico de Aeronáutica
//CES-10: Introdução à Computação
//Prof. Armando
//Julho de 2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noh noh; // definindo os ponteiros de struct do tipo noh (que serão utilizados na lista encadeada)
typedef noh *posicao; // definindo os ponteiros de struct do tipo noh que serão utilizados para indicar a posição de alguma struct na lista
typedef noh *lista; // definindo os ponteiros de struct que serão utilizados para criar um novo nó da lista

struct noh { // definindo a struct noh, que servirá de base para a lista encadeada e para armazenarmos as informações dos arquivos
    int numero;
    char cidade[32];
    noh *prox;
};

int main() {
    FILE *ent,*sai; // declarando os arquivos de entrada e saida
    ent=fopen("C:\\Lab11\\entrada11.txt","r");
    sai=fopen("C:\\Lab11\\lucasdovalebezerra11.txt","w");
    char mensagem[30],lixo[72],nome[32]; // declarando as variáveis do tipo string para armazenar a mensagem do arquivo, o lixo quando necessario, e o nome da cidade do voo para ser armazenado na lista encadeada
    int num; // declarando as variáveis do tipo inteiras para armazenar o número do voo, e outra para indicar se é a primeira vez que ocorre uma urgência nos aviões
    posicao inicio=NULL,p=NULL,q=NULL,aux=NULL,r=NULL,n=NULL,ultimoUrgente=NULL; // declarando os ponteiros necessários para serem utilizados nas condições abaixo
    fprintf(sai,"AEROPORTO INTERNACIONAL DO RECIFE\n");
    fprintf(sai,"PERNAMBUCO - BRASIL\n");
    fprintf(sai,"AUTORIZACOES DE POUSO\n");
    fprintf(sai,"=========================================\n");
    fprintf(sai,"FLIGHT  FROM\n\n");
    for (int i=0;i<7;i++)  // lendo as 8 primeiras frases inúteis do arquivo de entrada e armazenando na variável lixo
        fgets(lixo,72,ent);
	fscanf(ent," %s", mensagem); // lendo a mensagem do arquivo
    while (strcmp(mensagem,"FIM")!=0) { // o ciclo irá acontecer até a variável mensagem for diferente de "FIM", isto é, ainda há trabalho para a torre de controle
		if (strcmp(mensagem,"pede_pouso")==0) { // condição para a mensagem ser referente à de um avião pedindo para pousar
			p=(lista)malloc(sizeof(noh)); // alocando na memória a struct referente ao voo
			fscanf(ent,"%d", &num); // lendo o numero e o nome do voo do arquivo
			fgets(nome,32,ent);
			p->numero=num;  // armazenando nas variáveis
			strcpy(p->cidade,nome);
			p->prox=NULL;
			if (inicio==NULL) { // caso em que a fila está vazia
				inicio=p;
			}
			else { // caso em que a fila está preenchida com pelo menos um avião
				aux=inicio;
				while (aux->prox!=NULL)
					aux=aux->prox;
				aux->prox=p;
			}
        }
        if (strcmp(mensagem,"pista_liberada")==0) { // condição para a mensagem referente à pista estar liberada para pouso
            fgets(lixo,72,ent);
            if(inicio!=NULL) { // condição referente ao caso de haver aviões na fila esperando para pousar
                fprintf(sai,"%04d  %s", inicio->numero, inicio->cidade); // printando no arquivo de saida o avião que pousou (aquele que o ponteiro inicio aponta)
				if (ultimoUrgente!=NULL)
					if (ultimoUrgente->numero==inicio->numero)
						ultimoUrgente=NULL;
				q=inicio->prox;
				free(inicio);
				inicio=q;
            }
            else  // caso em que a lista encadeada está vazia
                fprintf(sai,"0000    Nenhum avião pousando\n"); // printando a mensagem padrão para esse caso
        }
        if (strcmp(mensagem,"URGENCIA")==0) { // caso onde a mensagem se refere à urgência de algum pouso
            fscanf(ent,"%d", &num); // lendo do arquivo o numero do voo de pouso urgente
			r=inicio;
			if (r->numero==num) {
				ultimoUrgente=r;
			} else {
				while (r->numero!=num) { // o ponteiro r irá procurar esse voo e apontar para ele
					n=r;
					r=r->prox;
				} // ao final do ciclo, o ponteiro n irá apontar exatamente no noh anterior ao r
				if (ultimoUrgente==NULL) { // caso em que só há um caso de urgência
					n->prox=n->prox->prox; // lógica dos ponteiros para que coloque o voo urgente para primeiro da fila
					r->prox=inicio;
					inicio=r;
					ultimoUrgente=r;
				}
				else { // caso em que há mais de um caso de urgência
					n->prox=n->prox->prox;
					r->prox=ultimoUrgente->prox;
					ultimoUrgente->prox=r;
					ultimoUrgente=r;
				}
			}
			fgets(lixo,72,ent); // lendo o lixo após a mensagem de URGENTE e o numero do voo
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
    fclose(sai); // fechando o arquivo de saída
    return 0;
}

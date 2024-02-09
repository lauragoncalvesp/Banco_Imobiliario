/*TAD*/
#include "cartas.h"
/*BIBLIOTECAS*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

//Protótipos
void TrocaBaralho (Baralho *destino, Baralho *origem);

// Funcao que cria uma pilha de cartas
Baralho* criaBaralho()
{
    Baralho *pilha = (Baralho*)malloc(sizeof(Baralho));
    pilha->topo = NULL;
    return pilha;
}

// Funcao que destroi uma pilha de cartas
void destroiBaralho(Baralho *pilha)
{
    Carta *aux = pilha->topo;
    while(aux != NULL)
    {
        Carta *tmp = aux->prox;
        free(aux); // Cuidar ordem do free
        aux = tmp;
    }
    free(pilha);
}

// Funcao que determina se uma pilha eh vazia
int vaziaPilha(Baralho *pilha)
{
    return (pilha->topo == NULL);
}

// Funcao que insere um elemento na pilha
void empilhaPilha(Baralho *pilha, Mensagem info)
{
    Carta *novo = (Carta*)malloc(sizeof(Carta));
    novo->info = info;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

// Funcao que remove um elemento da pilha
Mensagem desempilhaPilha(Baralho* pilha)
{
    Carta *aux = pilha->topo;
    Mensagem info;
    if (!vaziaPilha(pilha))
    {
        info = aux->info;
        pilha->topo = aux->prox;
    }
    free(aux);
    return info;
}

//Funcao que le as cartas de um arquivo e empilha
int Lecartas (Baralho *pilha)
{
    FILE *codcartas = fopen("Cartas.txt", "r");
    char linha [MAX_MSG];
    Mensagem nova;
    if (codcartas == NULL)
        return 0;
    while(fgets(linha, MAX_MSG, codcartas) != NULL)
    {
        if (isalpha (linha[0]))
        {
            linha[strlen(linha)-1] = '\0';
            strcpy(nova.mensagem,linha);
        }

        else if (isalnum (linha[0]) || linha[0] == '-' )
            nova.valor =atoi(linha);
        else if (linha[0] == '*')
            empilhaPilha (pilha, nova);
    }//fim do while
    fclose(codcartas) ;
    return 1;
}//fim  de Le

//Funcao que embaralha a ordem das cartas
void embaralharCartas (Baralho *pilha)
{
    srand(time(NULL));
    Baralho *monte, *deque;
    monte = criaBaralho();
    deque = criaBaralho();
    Mensagem carta;
    int aleatorio;

    while (!vaziaPilha(pilha))
    {
        aleatorio = rand()%100;
        if (aleatorio%2 == 0 ||aleatorio%5 ==0)
            carta = desempilhaPilha(pilha);
        if (aleatorio%2 == 0)
            empilhaPilha(monte,carta);
        else if (aleatorio%5 ==0)
            empilhaPilha(deque,carta);
    }//fim do while
    while (!vaziaPilha(deque) || (!vaziaPilha(monte)))
    {
        carta.valor = 0;
        aleatorio = rand()%100;
        if (aleatorio%7 == 0 && !vaziaPilha(monte))
            carta = desempilhaPilha(monte);
        else if (aleatorio%3 ==0 && !vaziaPilha(deque))
            carta = desempilhaPilha(deque);
        if (carta.valor !=0)
            empilhaPilha(pilha,carta);
    }//fim do while
}//fim do embaralha

//Funcao que imprime um baralho
void imprimeBaralho (Baralho *pilha)
{
    Mensagem info;
    Baralho *aux = criaBaralho();
    while (!vaziaPilha(pilha))
    {
        info = desempilhaPilha(pilha);
        puts (info.mensagem);
        printf("valor: %d\n",info.valor);
        printf("--------------------------\n");
        empilhaPilha(aux,info);
    }
    TrocaBaralho(pilha,aux);
}//fim do imprime

//Funcao auxiliar que troca um baralho por outro
void TrocaBaralho (Baralho *destino, Baralho *origem)
{
    Mensagem info;
    while (!vaziaPilha(origem))
    {
        info = desempilhaPilha(origem);
        empilhaPilha(destino,info);
    } //fim do while
} // fim do troca


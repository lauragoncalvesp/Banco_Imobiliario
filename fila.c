/*TAD*/
#include "fila.h"

#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma fila
Fila* criaFila()
{
    Fila *fila = (Fila*)malloc(sizeof(Fila));
    fila->ini = NULL;
    fila->fim = NULL;
    fila->qtd = 0;
    return fila;
}

// Funcao que destroi uma fila
void destroiFila(Fila *fila)
{
    if(fila != NULL)
    {
        ListaNodo *aux = fila->ini;
        while(aux != NULL)
        {
            ListaNodo *tmp = aux->prox;
            free(aux); // Cuidar ordem do free
            aux = tmp;
        }
        free(fila);
    }
}

// Funcao que insere um elemento na fila
void enfileiraFila(Fila *fila, Jogador info)
{
    ListaNodo *novo = (ListaNodo*)malloc(sizeof(ListaNodo));
    novo->info = info;
    fila->qtd ++;
    novo->prox = NULL;
    if (fila->fim != NULL)
        fila->fim->prox = novo;
    else
        fila->ini = novo;
    fila->fim = novo;
}

// Funcao que remove um elemento da fila
Jogador desenfileiraFila(Fila *fila)
{
    ListaNodo *aux = fila->ini;
    Jogador info = aux->info;
    fila->qtd -= 1;
    fila->ini = aux->prox;
    if (fila->ini == NULL)
        fila->fim = NULL;
    free(aux);
    return info;
}

// Funcao que determina se uma fila eh vazia
int vaziaFila(Fila *fila)
{
    return (fila->ini == NULL);
}

//Funcao que imprime uma fila
void imprimeFila (Fila *fila)
{
    int i, qtd = fila->qtd;
    Jogador jogador;
    for (i=0; i<qtd; i++)
    {
        jogador = desenfileiraFila(fila);
        imprimeJogador(&jogador);
        if(jogador.posTabuleiro !=NULL)
        {
            printf("Posicao do jogador: \n");
            imprimeCasa(jogador.posTabuleiro);
        }
        enfileiraFila(fila, jogador);
    }
}//fim do imprime


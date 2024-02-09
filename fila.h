
#ifndef _FILA_H_
#define _FILA_H_

#include "jogador.h"

typedef struct listaNodo
{
    Jogador info;
    struct listaNodo *prox;
} ListaNodo;

typedef struct filaEnc
{
    struct listaNodo *ini;
    struct listaNodo *fim;
    int qtd;
} Fila;

// Funcao que cria uma fila
Fila* criaFila();

// Funcao que destroi uma fila
void destroiFila(Fila *fila);

// Funcao que insere um elemento na fila
void enfileiraFila(Fila *fila, Jogador info);

// Funcao que remove um elemento da fila
Jogador desenfileiraFila(Fila *fila);

// Funcao que determina se uma fila eh vazia
int vaziaFila(Fila* fila);

//Funcao que imprime uma fila
void imprimeFila (Fila *fila);

#endif

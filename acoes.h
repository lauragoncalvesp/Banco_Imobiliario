#ifndef _ACOES_H_
#define _ACOES_H_

#include "jogador.h"
#include "tabuleiro.h"
#include "cartas.h"
#include "fila.h"

#define FIANCA 100
#define BONUS_INI 50
#define TAXA_CASA 20
#define TAXA_HOTEL 80
typedef struct atualiza
{
    char nome[MAX_NOME];
    int valor;
    int tam_inicial;
} Atualiza;

//Cria o vetor para atualizar os dados
Atualiza* criaVetor(Fila *fila_jogador);

//Funcao que da o dinheiro recebido dos alugueis para o dono
void atualizaJogador(Jogador *jogador, Atualiza atualiza[], Fila *fila_jogador);

//Funcao que destroi o vetor de atualizacao
void destroiVetor(Atualiza *vetor);

//Funcao que verifica se e possivel e inicia o jogo
int iniciarJogo(Fila *fila_jogador, Tabuleiro *board);

//Funcao que joga os dados e retorna a igualdade
int jogarDados( int *igual);

//Funcao que movimenta o jogador pelo tabuleiro
void andarTabuleiro (Jogador *jogador, Tabuleiro *board);

//Funcao que faz o pagamento do aluguel
int pagarAluguel(int qtd, Jogador *pagador, Atualiza *atualiza);

//Quita as dívidas do jogador
int quitarDividas (Jogador *jogador, Tabuleiro *board);

//Declara a vitoria para o jogador
void vitoria (Jogador *jogador);

//Funcao para terminar o jogo
void terminarjogo (Fila *fila1, Fila *fila2);

#endif

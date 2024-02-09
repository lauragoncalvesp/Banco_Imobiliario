#ifndef _JOGADOR_H_
#define _JOGADOR_H_

#define MAX_NOME 30
#define QTD_INI 200

#include "tabuleiro.h"

typedef struct Jogador
{
    char nome [MAX_NOME];
    int dinheiro;
    int preso;
    int dono;
    Casa_tab *posTabuleiro;
} Jogador;



//Função que adiciona os dados iniciais
Jogador CadastraJogador ();

//Funcao que imprime os dados de um Jogador
void imprimeJogador (Jogador *jogador);

//Verifica se o jogador faliu
int falencia (Jogador *jogador);

//Verifica se o jogador esta preso
int estapreso (Jogador *jogador);
#endif //_JOGADOR_H_

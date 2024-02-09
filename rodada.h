#ifndef _RODADA_H_
#define _RODADA_H_



#include "cartas.h"
#include "jogador.h"
#include "tabuleiro.h"

//Macro para limpar a tela que é compatível com Windows e Linux
#include <stdlib.h>
#if defined(_WIN32)
#define clear_screen() system("cls")
#elif defined(__unix__)
#define clear_screen() system("clear")
#endif


//Funcao auxiliar que faz as opções da rodada
void Rodada (Jogador *jogador, Tabuleiro *board, Baralho *monte);


#endif

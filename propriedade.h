#ifndef PROPRIEDADE_H_INCLUDED
#define PROPRIEDADE_H_INCLUDED

#include "jogador.h"
#include "tabuleiro.h"
//Funcao que faz a compra da propriedade
int comprarProp(Jogador *jogador);

//Funcao que compra uma casa para a propriedade
int comprarCasa(Jogador *jogador, Tabuleiro *board);

//Funcao que compra hotel para propriedade
int comprarHotel(Jogador *jogador);

//Vende a propriedade para o Banco
int devolverProp(Jogador *jogador, Casa_tab *prop);

#endif // PROPRIEDADE_H_INCLUDED

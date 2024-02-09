#include "tabuleiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Casa_tab* criaCasa(int tipo, int cor, int preco, int aluguel, int preco_casa);
void addCasa(Tabuleiro *board, Casa_tab *casa);


Tabuleiro *criarTabuleiro()
{
    Tabuleiro *board = (Tabuleiro*) malloc(sizeof(Tabuleiro));
    board->inicio = NULL;
    Casa_tab* casa = criaCasa(PROPRIEDADE, VERDE, 150, 100, 50);
    addCasa(board, casa);
    casa = criaCasa(PROPRIEDADE, AMARELA, 10, 5, 50);
    addCasa(board, casa);
    casa = criaCasa(PRISAO, BRANCO, -1, -1, -1);
    board->prisao = casa;
    addCasa(board, casa);
    casa = criaCasa(PROPRIEDADE, VERDE, 75, 10, 60);
    addCasa(board, casa);
    casa = criaCasa(SORTE, BRANCO, -1, -1, -1);
    addCasa(board, casa);
    casa = criaCasa(PROPRIEDADE, AZUL, 20, 10, 100);
    addCasa(board, casa);
    casa = criaCasa(POLICIA, BRANCO, -1, -1, -1);
    addCasa(board, casa);
    casa = criaCasa(SORTE, BRANCO, -1, -1, -1);
    addCasa(board, casa);
    casa = criaCasa(PROPRIEDADE, AMARELA, 10, 10, 10);
    addCasa(board, casa);
    casa = criaCasa(PROPRIEDADE, AZUL, 15, 16, 50);
    addCasa(board, casa);
    casa = criaCasa(SORTE, BRANCO, -1, -1, -1);
    addCasa(board, casa);
    casa = criaCasa(INICIO, BRANCO, -1, -1, -1);
    addCasa(board, casa);
    casa = board->inicio;
    while(casa->prox != NULL)
        casa = casa->prox;
    casa->prox = board->inicio;
    return board;
}


void imprimeTabuleiro(Tabuleiro *board)
{
    Casa_tab* casa = board->inicio;
    do
    {
        imprimeCasa(casa);
        casa = casa->prox;
    }
    while(casa != board->inicio);
}

void destroiTabuleiro(Tabuleiro *board)
{
    if(board != NULL)
    {
        Casa_tab *aux = board->inicio;
        if(aux != NULL)
        {
            do
            {
                Casa_tab *tmp = aux->prox;
                free(aux);
                aux = tmp;
            }
            while(aux != board->inicio);
        }
        free(board);
    }
}

Casa_tab* criaCasa(int tipo, int cor, int preco, int aluguel, int preco_casa)
{
    Casa_tab* casa = (Casa_tab*) malloc(sizeof(Casa_tab));
    casa->tipo = tipo;
    casa->cor = cor;
    casa->preco = preco;
    casa->aluguel = aluguel;
    casa->preco_casa = preco_casa;
    casa->qtd_casas = 0;
    casa->hotel = 0;
    strcpy(casa->dono, BANCO);
    casa->prox = NULL;

    return casa;
}

void addCasa(Tabuleiro *board, Casa_tab *casa)
{
    casa->prox = board->inicio;
    board->inicio = casa;
}

void imprimeCasa(Casa_tab *casa)
{
    int tipo = casa->tipo;
    int cor =  casa->cor;
    int preco = casa->preco;
    int aluguel = casa->aluguel;
    int preco_casa = casa->preco_casa;
    int qtd_casas = casa->qtd_casas;
    int hotel = casa->hotel;
    char dono[MAX_NOME];
    strcpy(dono, casa->dono);

    switch(tipo)
    {
    case INICIO:
        printf("Tipo: Inicio\n");
        break;
    case PROPRIEDADE:
        printf("Tipo: Propriedade\n");
        switch(cor)
        {
        case AZUL:
            printf("Cor: Azul\n");
            break;
        case AMARELA:
            printf("Cor: Amarela\n");
            break;
        case VERDE:
            printf("Cor: Verde\n");
        }
        printf("Preco de compra: %d\n", preco);
        printf("Preco do aluguel: %d\n", aluguel);
        printf("Preco das casas: %d\n", preco_casa);
        printf("Quantidade de casas: %d\n", qtd_casas);
        printf("Hotel: %d\n", hotel);
        printf("Dono: %s\n", dono);
        break;
    case SORTE:
        printf("Tipo: Carta da Sorte\n");
        break;
    case POLICIA:
        printf("Tipo: Policia!!\n");
        break;
    case PRISAO:
        printf("Tipo: Prisao\n");
        break;
    }
    printf("<----------------------------->\n\n");
}

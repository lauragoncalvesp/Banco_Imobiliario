#ifndef _TABULEIRO_H_
#define _TABULEIRO_H_

#define MAX_NOME 30
#define BANCO "Banco"


typedef enum tipo_casa
{
    INICIO = 1,
    PROPRIEDADE = 2,
    SORTE = 3,
    POLICIA= 4,
    PRISAO = 5
} tipo_casa;

typedef enum cores
{
    AZUL = 1,
    AMARELA = 2,
    VERDE= 3,
    BRANCO = 0
} cores;

typedef struct Casa_tab
{
    int tipo;
    int cor;
    int preco;
    int aluguel;
    int preco_casa;
    int qtd_casas;
    int hotel;
    char dono[MAX_NOME];
    struct Casa_tab *prox;
} Casa_tab;

typedef struct Tabuleiro
{
    struct Casa_tab *inicio;
    struct Casa_tab *prisao;
} Tabuleiro;


//Funcao que anda pelo Tabuleiro
//void AndarTabuleiro (Tabuleiro *inicio, Jogador *jogador ,int casas);

//Funcao que cria um Tabuleiro
Tabuleiro *criarTabuleiro();

//Funcao que imprime o Tabuleiro
void imprimeTabuleiro(Tabuleiro *board);

//Funcao que destroi o Tabuleiro
void destroiTabuleiro(Tabuleiro *board);

//Funcao que imprime uma casa do tabuleiro
void imprimeCasa(Casa_tab *casa);
#endif

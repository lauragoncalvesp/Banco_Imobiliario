#ifndef CARTAS_H_INCLUDED
#define CARTAS_H_INCLUDED
/*CONSTANTES*/

#define MAX_MSG 150

/*DECLARAÇÃO DE ESTRUTURAS*/
typedef struct
{
    char mensagem[MAX_MSG];
    int valor;
} Mensagem;

typedef struct Carta
{
    Mensagem info;
    struct Carta *prox;

} Carta;

typedef struct
{
    struct Carta *topo;
} Baralho;


/*DECLARAÇÃO DE FUNÇÕES*/

//Funcao que embaralha a ordem das cartas
void embaralharCartas (Baralho *pilha);

//Funcao que le as cartas de um arquivo e empilha
int Lecartas (Baralho *pilha);

// Funcao que cria uma pilha de cartas
Baralho* criaBaralho();

// Funcao que destroi uma pilha de cartas
void destroiBaralho(Baralho *pilha);

// Funcao que determina se uma pilha eh vazia
int vaziaPilha(Baralho *pilha);

// Funcao que insere um elemento na pilha
void empilhaPilha(Baralho *pilha, Mensagem info);

// Funcao que remove um elemento da pilha
Mensagem desempilhaPilha(Baralho *pilha);


//Funcao que imprime um baralho
void imprimeBaralho (Baralho *pilha);

void teste (Baralho *pilha);
#endif // CARTAS_H_INCLUDED

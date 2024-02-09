#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acoes.h"
#include "propriedade.h"


//Cria o vetor para atualizar os dados
Atualiza* criaVetor (Fila *fila_jogador)
{
    Atualiza *acerto = (Atualiza*) malloc(sizeof(Atualiza)*(fila_jogador->qtd));
    if(acerto != NULL)
    {
        acerto->tam_inicial = fila_jogador->qtd;
        Jogador jogador;
        for(int i = 0; i < fila_jogador->qtd; i++)
        {
            jogador = desenfileiraFila(fila_jogador);
            acerto[i].valor = 0;
            strcpy(acerto[i].nome, jogador.nome);
            enfileiraFila(fila_jogador, jogador);
        }
    }
    return acerto;
}

//Funcao que destroi o vetor de atualizacao
void destroiVetor(Atualiza *vetor)
{
    if(vetor != NULL)
    {
        free(vetor);
    }
}

//Funcao que da o dinheiro recebido pelos jogadores para o jogador da rodada
void atualizaJogador(Jogador *jogador, Atualiza atualiza[], Fila *fila_jogador)
{
    for(int i = 0; i < fila_jogador->qtd; i++)
    {
        if(strcmp(jogador->nome, atualiza[i].nome) == 0)
        {
            jogador->dinheiro += atualiza[i].valor;
            atualiza[i].valor = 0;
        }
    }
}
//Funcao que verifica se e possivel e inicia o jogo
int iniciarJogo(Fila *fila_jogador, Tabuleiro *board)
{
    if(fila_jogador->qtd >= 2 && board != NULL)
    {
        Jogador jogador;
        for(int i = 0; i < fila_jogador->qtd; i++)
        {
            jogador = desenfileiraFila(fila_jogador);
            jogador.posTabuleiro = board->inicio;
            enfileiraFila(fila_jogador, jogador);
        }
        return 1;
    }
    return 0;
}

//Funcao que joga os dados e permite que o jogador jogue aquela rodada
int jogarDados (int *igual)
{
    int dado1,dado2;
    dado1 = (rand() % 6)+ 1;
    dado2 = (rand() % 6)+ 1;
    printf("Dado 1: %d e Dado 2: %d\n",dado1,dado2);
    if (dado1 == dado2)
        *igual = 1;
    else *igual =0;

    return dado1+dado2;
} //fim do jogar dados

void andarTabuleiro (Jogador *jogador, Tabuleiro *board)
{
    if (!estapreso(jogador))
    {
        int repetiu;
        int total = jogarDados(&repetiu);
        printf("Andando pelo tabuleiro...\n");
        //Anda a quatidade de cartas do tabuleiro
        for(int i = 0; i < total; i++)
        {
            jogador->posTabuleiro = jogador->posTabuleiro->prox;
            if(jogador->posTabuleiro == board->inicio)
            {
                jogador->dinheiro += BONUS_INI;
                printf("\t\tVoce recebeu o bonus do incio!\n");
            }
        }
    }//fim do if
}//fim do andar

//Funcao que faz o pagamento do aluguel
int pagarAluguel(int qtd, Jogador *pagador, Atualiza *atualiza)
{
    if(pagador->posTabuleiro->tipo == PROPRIEDADE)
    {
        char dono[MAX_NOME];
        strcpy(dono, pagador->posTabuleiro->dono);
        if(strcmp(pagador->nome, pagador->posTabuleiro->dono) != 0 && strcmp(BANCO, pagador->posTabuleiro->dono) != 0)
        {
            for(int i = 0; i < atualiza->tam_inicial; i++)
            {
                if(strcmp(atualiza[i].nome, pagador->posTabuleiro->dono) == 0)
                {
                    int pagamento = pagador->posTabuleiro->aluguel + TAXA_CASA*pagador->posTabuleiro->qtd_casas + TAXA_HOTEL*pagador->posTabuleiro->hotel;
                    atualiza[i].valor += pagamento;
                    pagador->dinheiro -= pagamento;
                    return pagamento;
                }
            }
        }
    }
    return 0;
}

//Quita as dívidas do jogador
int quitarDividas (Jogador *jogador, Tabuleiro *board)
{
    Casa_tab* casa = jogador->posTabuleiro;

//Verifica se  o jogador possui dinheiro ou divida
    if (jogador->dinheiro > 0 || falencia(jogador))
    {
        return -1;
    }
    do
    {
        //Procura a propriedade do jogador
        if (strcmp(casa->dono, jogador->nome)==0)
        {
            devolverProp(jogador, casa); //vende a propriedade para o banco
        }
        casa = casa->prox;
    }
    while(casa != jogador->posTabuleiro && jogador->dinheiro <= 0);

    if  (jogador->dinheiro>0)
        return 1;
    else
        return 0;
}//fim do quitar

//Declara a vitoria para o jogador
void vitoria (Jogador *jogador)
{
    printf("PARABENS!\n");
    fputs (jogador->nome,stdout);
    printf("\n voce ganhou o jogo com R$%d.00 e %d propriedade(s)",jogador->dinheiro, jogador->dono);
}//fim do vitoria


void insertionSort(Jogador V[], int tam)
{
    int i, j;
    Jogador aux;
    for(i = 1; i < tam; i++)
    {
        j = i;
        while((j != 0) && (V[j].dinheiro > V[j - 1].dinheiro))
        {
            aux = V[j];
            V[j] = V[j - 1];
            V[j - 1] = aux;
            j--;
        }
    }
}

//Funcao para terminar o jogo
void terminarjogo (Fila *fila1, Fila *fila2)
{
    int i=0, qtd = fila1->qtd + fila2->qtd, j;
    Jogador lista[qtd];
    for (i=0; i<qtd; i++)
    {
        if(!vaziaFila(fila1))
            lista[i] = desenfileiraFila(fila1);
        if(j == 1)
        {
            lista[i] = desenfileiraFila(fila2);
        }
        if(vaziaFila(fila1))
            j = 1;
    }
    insertionSort(lista,qtd);
    printf ("Ranking da partida:\n");
    for (i=0; i<qtd; i++)
    {
        printf("\n %d Lugar:\n",i+1);
        imprimeJogador(&lista[i]);
        printf("\n");
    }
}//fim do termina

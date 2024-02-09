#include "casa.h"
#include "acoes.h"

/*BIBLIOTECAS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Faz os tramites da casa Carta da sorte
void cartadaSorte (Baralho *monte, Jogador *jogador)
{
    Mensagem info;
    if (vaziaPilha(monte))
    {
        Lecartas (monte);
        embaralharCartas(monte);
    }
    else
    {
        info = desempilhaPilha(monte);
        puts(info.mensagem);
        jogador->dinheiro += info.valor;
    }//fim do else
}//fim do carta da sorte

//Verifica se o jogador esta preso
void prisao (Jogador *jogador, Tabuleiro *board)
{
    int op, total,igual=0;
    if (estapreso(jogador))
    {
        printf("Escolha uma opcao:\n1 - Pagar fianca de %d\n2 - Tentar sorte nos dados\n ", FIANCA);
        scanf ( " %d",&op);
        switch (op)
        {
        case 1:
            if (jogador->dinheiro>=FIANCA)
            {
                jogador->dinheiro -= FIANCA;
                jogador->preso = 0;
                printf ("\nFianca paga com sucesso.\n");
                total = jogarDados (&igual);
                printf("Andando pelo tabuleiro...\n");
                for(int i = 0; i < total; i++)
                {
                    jogador->posTabuleiro = jogador->posTabuleiro->prox;
                    if(jogador->posTabuleiro == board->inicio)
                    {
                        jogador->dinheiro += BONUS_INI;
                        printf("\t\t Voce recebeu o bonus do incio!\n");
                    }
                }
            }
            break;
        case 2:
            total = jogarDados (&igual);
            if (igual)
            {
                jogador->preso =0;
                printf("Andando pelo tabuleiro...\n");
                for(int i = 0; i < total; i++)
                {
                    jogador->posTabuleiro = jogador->posTabuleiro->prox;
                    if(jogador->posTabuleiro == board->inicio)
                    {
                        jogador->dinheiro += BONUS_INI;
                        printf("\t\t Voce recebeu o bonus do incio!\n");
                    }
                }
            }
            break;
        default:
            printf("Opcao invalida. Perdeu a rodada.\n");
        }//fim do switch
    }//fim do if
}//fim da prisao

//faz os tramites da policia
void policia (Jogador *jogador, Tabuleiro *board)
{
    jogador->preso = 1;
    jogador->posTabuleiro = board->prisao;
    printf ("\nVoce acaba de ser preso e levado para a prisao\n");
}//fim do policia

//Opera as casas especiais
int casaEspecial  (Baralho *monte,Jogador *jogador, Tabuleiro *board)
{
    int tipo = jogador->posTabuleiro->tipo;
    if (tipo == PROPRIEDADE)
        return 0;
    else
    {
        switch (tipo)
        {
        case INICIO:
            printf ("\nVoce esta no inicio do tabuleiro.\n");
            break;
        case PRISAO:
            prisao (jogador, board);
            if (estapreso(jogador))
                printf ("\nVoce esta preso na prisao.\n");
            else
                printf("\nVoce esta na prisao, mas nao esta preso\n");
            break;
        case POLICIA:
            policia (jogador, board);
            break;
        case SORTE:
            cartadaSorte (monte, jogador);
            break;
        }//fim do switch
        return 1;
    }//fim do else
} //fim do casas especiais






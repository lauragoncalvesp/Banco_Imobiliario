#include "jogador.h"
#include<stdio.h>
#include <string.h>
#include "fila.h"
//Função que adiciona os dados iniciais
Jogador  CadastraJogador ()
{
    Jogador aux;
    printf ("Digite o nome do jogador:\n");
    fgets (aux.nome,MAX_NOME,stdin);
    aux.nome[strlen(aux.nome)-1] ='\0';//limpa o \n do ultimo caracter
    aux.preso = 0;
    aux.dono =0;
    aux.dinheiro = QTD_INI;
    aux.posTabuleiro = NULL;
    return aux;
}//fim do cadastra

//Funcao que imprime os dados de um Jogador
void imprimeJogador (Jogador *jogador)
{
    printf("Nome: ");
    fputs (jogador->nome,stdout);
    printf("\nDinheiro R$ %d.00\nNumero de Propriedades: %d\n",jogador->dinheiro, jogador->dono);
    if (jogador->preso)
        printf("Preso: SIM\n");
    else
        printf("Preso: NAO\n");
    printf("-----------------\n\n");
}//fim do imprime

//Verifica se o jogador faliu
int falencia (Jogador *jogador)
{
    if (jogador->dinheiro <= 0 && !(jogador->dono))
    {
        jogador->posTabuleiro =NULL;
        return 1;
    }
    else
        return 0;
}//fim do falencia

//Verifica se o jogador esta preso
int estapreso (Jogador *jogador)
{
    return jogador->preso;
} //fim do esta

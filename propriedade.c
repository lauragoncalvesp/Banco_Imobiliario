#include "propriedade.h"
#include <stdio.h>
#include <string.h>
//Funcao que faz a compra da propriedade
int comprarProp(Jogador *jogador)
{
    Casa_tab *casa;
    casa = jogador->posTabuleiro;
    if (casa->tipo != PROPRIEDADE)
        return 0;
    else if (strcmp(casa->dono,BANCO))
        return 0;
    else if (jogador->dinheiro >= casa->preco)
    {
        jogador->dinheiro -= casa->preco;
        strcpy( casa->dono,jogador->nome);
        jogador->dono +=1;
        return 1;
    }
    return 0;
}//fim do compra

//Vende a propriedade para o Banco
int devolverProp(Jogador *jogador, Casa_tab *prop)
{
    int total=0;
    if (prop->tipo != PROPRIEDADE || strcmp(jogador->nome, prop->dono) != 0)
    {
        printf("Voce nao pode vender uma propriedade que nao eh sua!!\n");
        return 0;
    }
    total += prop->preco_casa*prop->qtd_casas;
    total += prop->preco_casa*prop->hotel;
    total += prop->preco;
    prop->qtd_casas = 0;
    prop->hotel = 0;
    strcpy(prop->dono,BANCO);
    jogador->dinheiro += total;
    jogador->dono -= 1;
    return 1;
} //fim do devolve


//Funcao que compra uma casa para a propriedade
int comprarCasa(Jogador *jogador, Tabuleiro *board)
{
    if (jogador->dinheiro < jogador->posTabuleiro->preco_casa)
        return 0;
    if(strcmp(jogador->nome, jogador->posTabuleiro->dono) == 0)
    {
        int qtd_prop = 0;
        Casa_tab *aux = board->inicio;
        do
        {
            if(aux->tipo == PROPRIEDADE)
            {
                if(aux->cor == jogador->posTabuleiro->cor)
                {
                    if(strcmp(jogador->nome, aux->dono) == 0)
                    {
                        qtd_prop += 1;
                    }
                }
            }
            aux = aux->prox;
        }
        while(aux != board->inicio);

        if(qtd_prop == 2)
        {
            if(jogador->posTabuleiro->qtd_casas < 3 &&jogador->posTabuleiro->hotel == 0)
            {
                jogador->posTabuleiro->qtd_casas += 1;
                jogador->dinheiro -= jogador->posTabuleiro->preco_casa;
                return 1;
            }
        }
    }
    return 0;
}

//Funcao que compra hotel para propriedade
int comprarHotel(Jogador *jogador)
{
    if (jogador->dinheiro < jogador->posTabuleiro->preco_casa)
        return 0;
    if(strcmp(jogador->nome, jogador->posTabuleiro->dono) == 0 && jogador->posTabuleiro->qtd_casas == 3 && !jogador->posTabuleiro->hotel)
    {
        jogador->posTabuleiro->qtd_casas = 0;
        jogador->posTabuleiro->hotel = 1;
        jogador->dinheiro -= jogador->posTabuleiro->preco_casa;
        return 1;
    }
    return 0;
}

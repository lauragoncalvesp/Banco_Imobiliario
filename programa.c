
/*
Jogo Banco Imobiliario
Desenvolvido por:Laura Gonçalves e Vinicius Navarro
Novembro de 2021
*/
/*Modulos*/
#include "fila.h"
#include "jogador.h"
#include "tabuleiro.h"
#include "cartas.h"
#include "acoes.h"
#include "casa.h"
#include "rodada.h"
/*BIBLIOTECAS*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Funcao auxiliar que imprime o menu
void imprimirMenu();

int main(void)
{
    //VARIAVEIS
    int opcao, inicio=0, aluguel = 0;
    Jogador jogador;
// PONTEIROS
    Fila *fila_jogador, *falidos;
    Baralho *SorteAzar = NULL;
    Tabuleiro *jogo = NULL;
    Atualiza *atualiza = NULL;
//COMANDOS
    fila_jogador = criaFila();
    falidos = criaFila();

    srand(time(NULL));
    SorteAzar = criaBaralho();
    if (Lecartas(SorteAzar))
        embaralharCartas(SorteAzar);
    else
        printf("Não foi possivel carregar o arquivo de cartas.");

    do
    {
        imprimirMenu();
        scanf(" %d", &opcao);
        switch (opcao)
        {
        case 1:
            //limpa a tela
            getchar();                    // para esperar o usuário ler a msg
            clear_screen() ;
            printf("\t\tCADASTRA JOGADORES\n");
            if (!inicio)
            {
                jogador = CadastraJogador();
                enfileiraFila(fila_jogador,jogador);
            }
            else
                printf("Nao e possivel cadastrar jogador");
            break;
        case 2:
            //limpa a tela
            getchar();                    // para esperar o usuário ler a msg
            clear_screen();
            inicio = iniciarJogo(fila_jogador, jogo);
            if (inicio)
            {
                atualiza = criaVetor(fila_jogador);
                printf("Jogo iniciado.");
            }
            else
                printf("Erro ao iniciar o jogo");
            break;
        case 3:
            //limpa a tela
            getchar();                    // para esperar o usuário ler a msg
            clear_screen() ;
            printf("\t\t CRIAR TABULEIRO\n");
            jogo = criarTabuleiro ();
            if (jogo != NULL)
                printf ("Tabuleiro criado com sucesso.");
            else
                printf ("Erro ao criar o tabuleiro.");
            break;
        case 4:
            //limpa a tela
            getchar();                    // para esperar o usuário ler a msg
            clear_screen() ;
            printf("\t\t IMPRIME TABULEIRO\n");
            if (jogo != NULL)
                imprimeTabuleiro(jogo);
            else
                printf ("Erro ao imprimir o tabuleiro.");
            break;
        case 5:
            //limpa a tela
            getchar();                    // para esperar o usuário ler a msg
            clear_screen() ;
            printf("\t\t IMPRIME DADOS JOGADORES\nJogadores ativos: \n");
            imprimeFila(fila_jogador);
            printf("\nJogadores desativados: \n");
            if (!vaziaFila(falidos))
                imprimeFila(falidos);
            break;
        case 6:
            //limpa a tela
            getchar();                    // para esperar o usuário ler a msg
            clear_screen() ;
            if (inicio)
            {
                jogador = desenfileiraFila(fila_jogador);
                printf("RODADA DO JOGADOR: %s\n", jogador.nome);
                if (vaziaFila(fila_jogador))
                {
                    vitoria(&jogador);
                    while(!vaziaFila(falidos))
                    {
                        desenfileiraFila(falidos);
                    }
                    inicio =0;
                }
                else
                {
                    andarTabuleiro (&jogador, jogo);
                    printf("Voce parou na posicao: \n");
                    imprimeCasa(jogador.posTabuleiro);
                    aluguel = pagarAluguel(fila_jogador->qtd,&jogador, atualiza);
                    if (aluguel)
                        printf("Sobre o aluguel: Foram pagos %d a %s\n", aluguel, jogador.posTabuleiro->dono);
                    atualizaJogador(&jogador, atualiza, fila_jogador);
                    Rodada(&jogador,jogo,SorteAzar);
                    if (!falencia(&jogador))
                        enfileiraFila(fila_jogador,jogador);
                    else
                        enfileiraFila(falidos,jogador);
                }//fim do else
            }//fim do if
            else
                printf ("Nao e possivel iniciar uma rodada.");
            break;
        case 7:
            //limpa a tela
            getchar();                    // para esperar o usuário ler a msg
            clear_screen() ;
            printf("\t\t VER BARALHO:\n\n");
            imprimeBaralho(SorteAzar);
            break;
        case 8:
            //limpa a tela
            getchar();                    // para esperar o usuário ler a msg
            clear_screen() ;
            if (inicio)
            {
                terminarjogo(fila_jogador, falidos);
                inicio = 0;
            }
            else
                printf ("Nao e possivel terminar esse jogo.");
            break;
        case 9:
            destroiFila(fila_jogador);
            destroiFila(falidos);
            destroiBaralho (SorteAzar);
            destroiVetor(atualiza);
            destroiTabuleiro(jogo);
            printf("\n ENCERRANDO O SISTEMA \n");
            break;

        default:
            printf("Opcao invalida.");
        }//fim do switch
        if (opcao !=9)
        {
            //limpa a tela
            printf("\nTecle 'ENTER' para continuar.\n");
            getchar();                    // para esperar o usuário ler a msg
            getchar();                    // para esperar o usuário ler a msg
            clear_screen() ;
        }//fim do if
    } // fim do do
    while (opcao !=9);

    return(0);
}//fim da main


//Funcao auxiliar que imprime o menu
void imprimirMenu()
{
    printf("\t\tMenu do banco Imobiliario\n"
           "Escolha uma das opcoes abaixo:\n"
           "1 - Cadastrar jogadores \n"
           "2 - Iniciar jogo\n"
           "3 - Criar tabuleiro\n"
           "4 - Imprime tabuleiro\n"
           "5 - Imprime dados dos jogadores Cadastrados \n"
           "6 - Rodada\n"
           "7 - Ver todo o baralho de cartas\n"
           "8 - Terminar jogo\n"
           "9 - Sair\n");
}

#include "rodada.h"
#include "acoes.h"
#include "propriedade.h"
#include "casa.h"
#include "fila.h"

#include <stdio.h>




//Funcao auxiliar que gerencia o menu da rodada
void Rodada (Jogador *jogador, Tabuleiro *board, Baralho *monte)
{
    int auxiliar, retorno;
    retorno = casaEspecial (monte,jogador, board);
    if (retorno)
    {
        printf("\t\tSEUS DADOS:\n");
        imprimeJogador(jogador);
    }
    else
    {
        printf("\nTecle 'ENTER' para continuar.\n");
        //limpa a tela
        getchar();                    // para esperar o usuário ler a msg
        clear_screen();
        do
        {
            printf("\t\tSEUS DADOS:\n");
            imprimeJogador(jogador);
            printf("\t\tSUA POSICAO:\n");
            imprimeCasa(jogador->posTabuleiro);
            printf("\nEscolha uma das opcoes abaixo:\n1 - Comprar propriedade\n2 - Vender propriedade\n3 -  Colocar casa\n4 -  Colocar hotel\n5 - Verifica dinheiro\n6 - Terminar Rodada\n");
            scanf(" %d", &auxiliar);
            switch (auxiliar)
            {
            case 1:
                //limpa a tela
                getchar();                    // para esperar o usuário ler a msg
                clear_screen();
                printf("\t\tCOMPRAR PROPRIEDADE\n");
                retorno = comprarProp(jogador);
                if (retorno)
                    printf("A propriedade foi comprada com sucesso.");
                else
                    printf("Erro ao comprar a propriedade.");
                break;
            case 2:
                //limpa a tela
                getchar();                    // para esperar o usuário ler a msg
                clear_screen() ;
                printf("\t\t VENDER PROPRIEDADE\n");
                retorno = devolverProp(jogador,jogador->posTabuleiro);
                if (retorno)
                    printf("A propriedade foi vendida com sucesso.");
                else
                    printf("Erro ao vender a propriedade.");
                break;
            case 3:
                //limpa a tela
                getchar();                    // para esperar o usuário ler a msg
                clear_screen() ;
                printf("\t\tCOLOCAR CASA \n");
                retorno = comprarCasa(jogador,board);
                if (retorno)
                    printf("A casa foi colocada com sucesso.");
                else
                    printf("Erro ao colocar a Casa.");
                break;
            case 4:
                //limpa a tela
                getchar();                    // para esperar o usuário ler a msg
                clear_screen() ;
                printf("\t\tCOLOCAR HOTEL \n");
                retorno = comprarHotel(jogador);
                if (retorno)
                    printf("O hotel foi colocado com sucesso.");
                else
                    printf("Erro ao colocar o hotel.");
                break;
            case 5:
                //limpa a tela
                getchar();                    // para esperar o usuário ler a msg
                clear_screen() ;
                printf("\t\t VERIFICA DINHEIRO \n");
                retorno = falencia(jogador);
                if (retorno)
                    printf("Voce faliu");
                else
                    printf("Voce tem R$ %d.00 e %d propriedades",jogador->dinheiro,jogador->dono);
                break;
            case 6:
                break;
            default:
                printf("Opcao invalida.");
            }//fim do switch
            if (auxiliar != 6)
            {
                //limpa a tela
                printf("\nTecle 'ENTER' para continuar.\n");
                getchar();                    // para esperar o usuário ler a msg
                getchar();                    // para esperar o usuário ler a msg
                clear_screen() ;
            }//fim do if
        } // fim do do
        while (auxiliar !=6);
    }//fim do if
    if(jogador->dinheiro <= 0)
    {
        printf("\n\n O jogador esta com dividas a pagar! Tentando quitar suas dividas... \n");
        retorno = quitarDividas(jogador, board);
        switch (retorno)
        {
        case -1:
            printf("Nao ha dividas para serem quitadas ou nao possui forma de quitar as dividas");
            break;
        case 0:
            printf("Nao foi possivel quitar a divida");
            break;
        case 1:
            printf( "Divida quitada com sucesso.");
            break;
        }
    }
    printf("\nRODADA ENCERRADA \n");

}//fim do rodada


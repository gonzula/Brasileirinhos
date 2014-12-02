#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "structures/structures.h"
#include "sgbd/binary_file.h"

#include "campeonato.h"
#include "impressao.h"

void selecionaOpcao(int, Campeonato *);

void
menu(Campeonato *c)
{
    int opcao = -1;
    while (opcao != 0)
    {
        printf("\nEscolha a opção:\n");
        printf("1 - Registrar um jogo\n");
        printf("2 - Gerar um jogo aleatório da rodada\n");
        printf("3 - Gerar uma rodada\n");
        printf("4 - Gerar o campeonato\n");
        printf("5 - Imprime tabela do campeonato\n");
        printf("6 - Imprime artilheiros\n");
        printf("7 - Zera Campeonato\n");
        printf("0 - Salvar e Sair\n");
        printf("Opção: ");
        scanf("%d",&opcao);
        selecionaOpcao(opcao,c);
    }
}

void
selecionaOpcao(int opcao, Campeonato *c)
{
    switch(opcao)
    {
        case 1:
            registraJogo(c);
            break;
        case 2:
            geraResultadosJogo(c);
            break;
        case 3:
            geraResultadoRodada(c);
            break;
        case 4:
            geraResultadoCampeonato(c);
            break;
        case 5:
            ImprimirTabela(c);
            break;
        case 6:
            ImprimirArtilheiro(c);
            break;
        case 7:
            zerarCampeonato(c);
            break;
        case 0:
            break;
        default:
            printf("Opção inválida\n");
            break;
    }
}

int
main(int argc, const char * argv[])
{
    srand(time(NULL));
    Campeonato *champ = campeonato_read_from_file("brasileirao.json");
    menu(champ);
    campeonato_write_to_file("brasileirao.json", champ);
    release(champ);

    return EXIT_SUCCESS;
}

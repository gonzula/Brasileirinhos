#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "structures/structures.h"
#include "sgbd/binary_file.h"

#include "campeonato.h"

int
main(int argc, const char * argv[])
{
    // file_manager *fm = construct_file_manager("/Users/gonzo/Desktop/fb.json");
    // char *content = read_all_bytes(fm);
    // String *str = str_create(content);
    // Serializable *ser = serializable_read_json(str);


    // String *jsonOut = serializable_write_json(ser);
    // puts(jsonOut->string);
    // release(jsonOut);


    // release(ser);
    // release(str);
    // free(content);
    // destroy_file_manager(fm);


    // Campeonato *champ = alloc(sizeof(Campeonato), campeonato_release);
    // champ->rodadas = list_init();
    // champ->times = list_init();

    // Time *time1, *time2, *time3;
    // {
    //     time1 = alloc(sizeof(Time), time_release);
    //     list_append(champ->times, time1);
    //     release(time1);
    //     time1->nome = malloc(sizeof(char) * 100);
    //     time1->pontos = 10;
    //     time1->saldo = 10;
    //     time1->vit = 10;
    //     time1->emp = 10;
    //     time1->der = 10;
    //     strcpy(time1->nome, "Palmeiras");
    //     time1->jogadores = list_init();
    //     {
    //         Jogador *j = alloc(sizeof(Jogador), jogador_release);
    //         list_append(time1->jogadores, j);
    //         j->nome = malloc(sizeof(char) * 100);
    //         j->numero = 69;
    //         j->gols = 100;
    //         strcpy(j->nome, "Gonzo");
    //         release(j);
    //     }
    //     {
    //         Jogador *j = alloc(sizeof(Jogador), jogador_release);
    //         list_append(time1->jogadores, j);
    //         j->nome = malloc(sizeof(char) * 100);
    //         j->numero = 24;
    //         j->gols = 200;
    //         strcpy(j->nome, "Gracinha Vira Homem");
    //         release(j);
    //     }
    // }
    // {
    //     time2 = alloc(sizeof(Time), time_release);
    //     list_append(champ->times, time2);
    //     release(time2);
    //     time2->nome = malloc(sizeof(char) * 100);
    //     time2->pontos = 1;
    //     time2->saldo = 2;
    //     time2->vit = 3;
    //     time2->emp = 4;
    //     time2->der = 5;
    //     strcpy(time2->nome, "Corinthians");
    //     time2->jogadores = list_init();
    //     {
    //         Jogador *j = alloc(sizeof(Jogador), jogador_release);
    //         list_append(time2->jogadores, j);
    //         j->nome = malloc(sizeof(char) * 100);
    //         j->numero = 69;
    //         j->gols = 100;
    //         strcpy(j->nome, "Toru Seu Troxa");
    //         release(j);
    //     }
    //     {
    //         Jogador *j = alloc(sizeof(Jogador), jogador_release);
    //         list_append(time2->jogadores, j);
    //         j->nome = malloc(sizeof(char) * 100);
    //         j->numero = 24;
    //         j->gols = 200;
    //         strcpy(j->nome, "Abominavel");
    //         release(j);
    //     }
    // }
    // {
    //     time3 = alloc(sizeof(Time), time_release);
    //     list_append(champ->times, time3);
    //     release(time3);
    //     time3->nome = malloc(sizeof(char) * 100);
    //     time3->pontos = 666;
    //     time3->saldo = 999;
    //     time3->vit = 321;
    //     time3->emp = 412;
    //     time3->der = 3215;
    //     strcpy(time3->nome, "Sao Paulo");
    //     time3->jogadores = list_init();
    //     {
    //         Jogador *j = alloc(sizeof(Jogador), jogador_release);
    //         list_append(time3->jogadores, j);
    //         j->nome = malloc(sizeof(char) * 100);
    //         j->numero = 69;
    //         j->gols = 100;
    //         strcpy(j->nome, "Clone lourenco");
    //         release(j);
    //     }
    //     {
    //         Jogador *j = alloc(sizeof(Jogador), jogador_release);
    //         list_append(time3->jogadores, j);
    //         j->nome = malloc(sizeof(char) * 100);
    //         j->numero = 24;
    //         j->gols = 200;
    //         strcpy(j->nome, "Kelly Key");
    //         release(j);
    //     }
    // }
    // {
    //     Rodada *r = alloc(sizeof(Rodada), rodada_release);
    //     list_append(champ->rodadas, r);
    //     release(r);
    //     r->jaFoiRodada = 1;
    //     r->numero = 1;
    //     r->jogos = list_init();
    //     {
    //         Jogo *j = alloc(sizeof(Jogo), jogo_release);
    //         j->jaFoiJogo = 1;
    //         j->gols1 =
    //         j->gols2 = 3;
    //         j->time1 = time1;
    //         j->time2 = time2;
    //         list_append(r->jogos, j);
    //         retain(j->time1);
    //         retain(j->time2);
    //         release(j);
    //     }
    //     {
    //         Jogo *j = alloc(sizeof(Jogo), jogo_release);
    //         j->jaFoiJogo = 1;
    //         j->gols1 = 1;
    //         j->gols2 = 3;
    //         j->time1 = time2;
    //         j->time2 = time3;
    //         list_append(r->jogos, j);
    //         retain(j->time1);
    //         retain(j->time2);
    //         release(j);
    //     }
    //     {
    //         Jogo *j = alloc(sizeof(Jogo), jogo_release);
    //         j->jaFoiJogo = 1;
    //         j->gols1 = 0;
    //         j->gols2 = 0;
    //         j->time1 = time3;
    //         j->time2 = time1;
    //         retain(j->time1);
    //         retain(j->time2);
    //         list_append(r->jogos, j);
    //         release(j);
    //     }
    // }

    // {
    //     Rodada *r = alloc(sizeof(Rodada), rodada_release);
    //     list_append(champ->rodadas, r);
    //     release(r);
    //     r->jaFoiRodada = 0;
    //     r->numero = 2;
    //     r->jogos = list_init();
    //     {
    //         Jogo *j = alloc(sizeof(Jogo), jogo_release);
    //         j->jaFoiJogo = 0;
    //         j->gols1 =
    //         j->gols2 = 3;
    //         j->time1 = time1;
    //         j->time2 = time2;
    //         retain(j->time1);
    //         retain(j->time2);
    //         list_append(r->jogos, j);
    //         release(j);
    //     }
    //     {
    //         Jogo *j = alloc(sizeof(Jogo), jogo_release);
    //         j->jaFoiJogo = 0;
    //         j->gols1 = 1;
    //         j->gols2 = 3;
    //         j->time1 = time2;
    //         j->time2 = time3;
    //         retain(j->time1);
    //         retain(j->time2);
    //         list_append(r->jogos, j);
    //         release(j);
    //     }
    //     {
    //         Jogo *j = alloc(sizeof(Jogo), jogo_release);
    //         j->jaFoiJogo = 0;
    //         j->gols1 = 0;
    //         j->gols2 = 0;
    //         j->time1 = time3;
    //         j->time2 = time1;
    //         retain(j->time1);
    //         retain(j->time2);
    //         list_append(r->jogos, j);
    //         release(j);
    //     }
    // }


    Campeonato *champ = campeonato_read_from_file("champ.json");


    // campeonato_write_to_file("saida.json", champ);


    release(champ);


    return EXIT_SUCCESS;
}

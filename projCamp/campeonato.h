#ifndef CAMPEONATO_H_INCLUDED
#define CAMPEONATO_H_INCLUDED

#include "structures/structures.h"

typedef struct Jogador{
    char *nome;
    int numero,gols;
}Jogador;

typedef struct Time{
    char *nome;
    List *jogadores;
    int pontos,saldo,vit,emp,der;
}Time;

typedef struct Jogo{
    int jaFoiJogo;
    Time *time1,*time2;
    int gols1,gols2;
}Jogo;

typedef struct Rodada{
    List *jogos;
    int jaFoiRodada,numero;
}Rodada;

typedef struct Campeonato{
    List *times;
    List *rodadas;
}Campeonato;

void campeonato_write_to_file(char *filename, Campeonato *champ);
Campeonato * campeonato_read_from_file(char *filename);

void campeonato_release(void *champ);
void jogador_release(void *jogador);
void time_release(void *_time);
void rodada_release(void *rodada);
void jogo_release(void *jogo);
void registraJogo(Campeonato *c);
void geraResultadoCampeonato(Campeonato *c);
void geraResultadoRodada(Campeonato *c,int rodada);
void geraResultadosJogo(Campeonato *c);


#endif // CAMPEONATO_H_INCLUDED

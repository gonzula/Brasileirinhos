#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "campeonato.h"
#include "structures/structures.h"


#define streq(a, b) (strcmp(a,b)==0)

int
comparaTimes(const void * o1, const void * o2)
{
    Time **t1p = (Time **)o1;
    Time **t2p = (Time **)o2;
    Time *t1 = *t1p;
    Time *t2 = *t2p;

    if (t1->pontos < t2->pontos) return 1;
    if (t1->pontos > t2->pontos) return -1;

    if (t1->saldo > t2->saldo) return 1;
    if (t1->saldo < t2->saldo) return -1;

    if (t1->vit > t2->vit) return 1;
    if (t1->vit < t2->vit) return -1;
    return strcmp(t1->nome, t2->nome);
}

int
numeroDeJogosDoTime(Campeonato *c, Time *t)
{
    int cnt = 0;
    LIST_LOOP(c->rodadas)
    {
        Rodada *r = node->object;
        LIST_LOOP(r->jogos)
        {
            Jogo *j = node->object;
            if (j->jaFoiJogo)
            {
                if (j->time1 == t || j->time2 == t)
                    cnt++;
            }
        }
    }
    return cnt;
}

void
ImprimirTabela(Campeonato *c)
{
    int i=0;
    Vector *v = vector_from_list(c->times);

    vector_sort(v, comparaTimes);//ordena o vetor

    int maiorNome = 0;
    for(i=0; i < v->count; i++)
    {
        Time *t = v->objs[i];
        String *nome = str_create(t->nome);
        int esteNome = str_unicode_len(nome);
        if (esteNome > maiorNome)
            maiorNome = esteNome;
        release(nome);
    }
    String *str = str_init();
    String *separador = str_init();
    str_append(separador, "+---+--");
    for (i = 0; i < maiorNome; i++)
    {
        str_append_char(separador, '-');
    }
    str_append(separador, "+---+---+---+---+---+---+\n");

    str_append(str, separador->string);
    {
        char linha[100];
        String *nome = str_create("Nome");
        str_center(nome, maiorNome + 2);
        sprintf(linha, "| # |%s| P | J | V | E | D | S |\n", nome->string);
        release(nome);
        str_append(str, linha);
    }
    str_append(str, separador->string);

    for(i=0; i < v->count; i++)
    {
        Time *t = v->objs[i];
        String *nome = str_create(t->nome);
        str_center(nome, maiorNome + 2);
        char linha[100];
        sprintf(linha, "|%3d|%s|%3d|%3d|%3d|%3d|%3d|%3d|\n", i + 1, nome->string, t->pontos, numeroDeJogosDoTime(c, t), t->vit, t->emp, t->der, t->saldo);
        release(nome);
        str_append(str, linha);
        // str_append(str, separador->string);
    }
    str_append(str, separador->string);
    puts(str->string);

    release(separador);
    release(str);

    release(v);
}

void
ImprimirTime(Campeonato *c, char *ntime)//imprime os jogadores do time, entrada  nome do time
{
    Time *t = encontraTime(c, ntime);
    Jogador *j;

    LIST_LOOP(t->jogadores)
    {
        j = node->object;
        printf("%d - %s", j->numero, j->nome);
    }
}

Time *
timeDoJogador(Campeonato *c, Jogador *j)
{
    LIST_LOOP(c->times)
    {
        Time *t = node->object;
        LIST_LOOP(t->jogadores)
        {
            if (j == node->object)
                return t;
        }
    }
    return NULL;
}


int
comparaArtilheiros(const void *o1, const void *o2)
{
    Jogador **j1p = (Jogador **)o1;
    Jogador **j2p = (Jogador **)o2;
    Jogador *j1 = *j1p;
    Jogador *j2 = *j2p;
    if (j1->gols < j2->gols) return 1;
    if (j1->gols > j2->gols) return -1;
    return strcmp(j1->nome, j2->nome);
}


void
ImprimirArtilheiro(Campeonato *c) //imprimi o jogador(es) com  maior numero de gols
{
    Vector *artilheiros = vector_init();

    LIST_LOOP(c->times)
    {
        Time *t = node->object;
        LIST_LOOP(t->jogadores)
        {
            vector_append(artilheiros, node->object);
        }
    }

    vector_sort(artilheiros, comparaArtilheiros);

    int maiorJogador = 0;
    int maiorTime = 0;
    for(int i = 0; i < artilheiros->count; i++)
    {
        Jogador *j = artilheiros->objs[i];
        String *nome = str_create(j->nome);
        // str_append(nome, " - ");
        // str_append(nome, timeDoJogador(c, j)->nome);
        int esteNome = str_unicode_len(nome);
        maiorJogador = esteNome > maiorJogador?esteNome:maiorJogador;
        release(nome);
    }
    LIST_LOOP(c->times)
    {
        Time *t = node->object;
        String *nome = str_create(t->nome);
        int esteNome = str_unicode_len(nome);
        maiorTime = esteNome > maiorTime?esteNome:maiorTime;
        release(nome);
    }

    String *saida = str_init();
    String *separador;
    {
        separador  = str_init();
        str_append(separador, "+----+--");
        for (int i = 0; i < maiorJogador; i++)
        {
            str_append_char(separador, '-');
        }
        str_append(separador, "+--");
        for (int i = 0; i < maiorTime; i++)
        {
            str_append_char(separador, '-');
        }
        str_append(separador, "+---+\n");
        str_append(saida, separador->string);
    }
    {
        char linha[100];
        String *j = str_create("Jogador");
        String *t = str_create("Time");
        str_center(j, maiorJogador + 2);
        str_center(t, maiorTime + 2);
        sprintf(linha, "|  # |%s|%s| G |\n", j->string, t->string);
        str_append(saida, linha);
    }
    str_append(saida, separador->string);
    for(int i = 0; i < artilheiros->count && i < 20; i++)
    {
        Jogador *j = artilheiros->objs[i];
        char linha[100];

        String *nome = str_create(j->nome);
        str_center(nome, maiorJogador + 2);

        Time *t = timeDoJogador(c, j);
        String *tNome = str_create(t->nome);
        str_center(tNome, maiorTime + 2);

        sprintf(linha, "|%4d|%s|%s|%3d|\n", i + 1, nome->string, tNome->string, j->gols);
        str_append(saida, linha);

        release(nome);
        release(tNome);
    }
    str_append(saida, separador->string);
    puts(saida->string);
    release(saida);
    release(artilheiros);
}

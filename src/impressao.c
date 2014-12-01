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
    return 0;
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
        int esteNome = strlen(t->nome);
        if (esteNome > maiorNome)
            maiorNome = esteNome;
        printf("%d - %s  %d pontos\n", i, t->nome, t->pontos);
    }
    // for(i=0; i < v->count; i++)
    // {
    //     Time *t = v->objs[i];
    //     int esteNome = strlen(t->nome);
    //     if (esteNome > maiorNome)
    //         maiorNome = esteNome;
    //     printf("%d - %s  %d pontos\n", i, t->nome, t->pontos);
    // }

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

int
comparaArtilheiros(const void *o1, const void *o2)
{
    Jogador **j1p = (Jogador **)o1;
    Jogador **j2p = (Jogador **)o2;
    Jogador *j1 = *j1p;
    Jogador *j2 = *j2p;
    if (j1->gols < j2->gols) return 1;
    if (j1->gols > j2->gols) return -1;
    return 0;
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

    for(int i = 0; i < artilheiros->count; i++)
    {
        Jogador *j = artilheiros->objs[i];
        printf("GOLS:%d - %s  \n", j->gols, j->nome);
    }
    release(artilheiros);
}

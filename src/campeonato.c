#include "campeonato.h"
#include <stdio.h>

#include "sgbd/binary_file.h"

#define streq(a, b) (strcmp(a,b)==0)

#define KEY_TIMES "times"
#define KEY_NOME "nome"
#define KEY_PONTOS "pontos"
#define KEY_SALDO "saldo"
#define KEY_VIT "vit"
#define KEY_EMP "emp"
#define KEY_DER "der"
#define KEY_JOGADORES "jogadores"
#define KEY_NUMERO "numero"
#define KEY_GOLS "gols"
#define KEY_RODADAS "rodadas"
#define KEY_JA_FOI_RODADA "ja foi rodada"
#define KEY_JOGOS "jogos"
#define KEY_GOLS1 "gols 1"
#define KEY_GOLS2 "gols 2"
#define KEY_JA_FOI_JOGO "ja foi jogo"
#define KEY_TIME1 "time 1"
#define KEY_TIME2 "time 2"

void
campeonato_write_to_file(char *filename, Campeonato *champ)
{
    HashTable *campeonato_ht = htable_init();
    Serializable *campeonato_s = serializable_create(campeonato_ht, ht_t);
    release(campeonato_ht);

    List *times_l = list_init();
    Serializable *times_s = serializable_create(times_l, list_t);
    release(times_l);

    htable_set(campeonato_ht, KEY_TIMES, times_s);
    release(times_s);

    LIST_LOOP(champ->times)
    {
        Time *_time = node->object;
        HashTable *time_ht = htable_init();
        Serializable *time_s = serializable_create(time_ht, ht_t);
        release(time_ht);
        list_append(times_l, time_s);
        release(time_s);
        {
            String *nome_str = str_create(_time->nome);
            Serializable *nome_s = serializable_create(nome_str, str_t);
            htable_set(time_ht, KEY_NOME, nome_s);
            release(nome_s);
            release(nome_str);
        }
        {
            Serializable *s = serializable_init();
            s->type = int_t;
            s->i = _time->pontos;
            htable_set(time_ht, KEY_PONTOS, s);
            release(s);
        }
        {
            Serializable *s = serializable_init();
            s->type = int_t;
            s->i = _time->saldo;
            htable_set(time_ht, KEY_SALDO, s);
            release(s);
        }
        {
            Serializable *s = serializable_init();
            s->type = int_t;
            s->i = _time->vit;
            htable_set(time_ht, KEY_VIT, s);
            release(s);
        }
        {
            Serializable *s = serializable_init();
            s->type = int_t;
            s->i = _time->emp;
            htable_set(time_ht, KEY_EMP, s);
            release(s);
        }
        {
            Serializable *s = serializable_init();
            s->type = int_t;
            s->i = _time->der;
            htable_set(time_ht, KEY_DER, s);
            release(s);
        }
        {
            List *jogadores_l = list_init();
            Serializable *jogadores_s = serializable_create(jogadores_l, list_t);
            htable_set(time_ht, KEY_JOGADORES, jogadores_s);
            release(jogadores_l);
            release(jogadores_s);
            LIST_LOOP(_time->jogadores)
            {
                Jogador *jogador = node->object;
                HashTable *jogador_ht = htable_init();
                Serializable *jogador_s = serializable_create(jogador_ht, ht_t);
                list_append(jogadores_l, jogador_s);
                release(jogador_ht);
                release(jogador_s);
                {
                    String *nome_str = str_create(jogador->nome);
                    Serializable *nome_s = serializable_create(nome_str, str_t);
                    htable_set(jogador_ht, KEY_NOME, nome_s);
                    release(nome_s);
                    release(nome_str);
                }
                {
                    Serializable *s = serializable_init();
                    s->type = int_t;
                    s->i = jogador->numero;
                    htable_set(jogador_ht, KEY_NUMERO, s);
                    release(s);
                }
                {
                    Serializable *s = serializable_init();
                    s->type = int_t;
                    s->i = jogador->gols;
                    htable_set(jogador_ht, KEY_GOLS, s);
                    release(s);
                }
            }
        }

        List *rodadas_l = list_init();
        Serializable *rodadas_s = serializable_create(rodadas_l, list_t);
        htable_set(campeonato_ht, KEY_RODADAS, rodadas_s);
        release(rodadas_l);
        release(rodadas_s);
        LIST_LOOP(champ->rodadas)
        {
            Rodada *rodada = node->object;
            HashTable *rodada_ht = htable_init();
            Serializable *rodada_s = serializable_create(rodada_ht, ht_t);
            list_append(rodadas_l, rodada_s);
            release(rodada_ht);
            release(rodada_s);

            {
                Serializable *s = serializable_init();
                s->type = bool_t;
                s->i = rodada->jaFoiRodada;
                htable_set(rodada_ht, KEY_JA_FOI_RODADA, s);
                release(s);
            }
            {
                Serializable *s = serializable_init();
                s->type = int_t;
                s->i = rodada->numero;
                htable_set(rodada_ht, KEY_NUMERO, s);
                release(s);
            }
            List *jogos_l = list_init();
            Serializable *jogos_s = serializable_create(jogos_l, list_t);
            htable_set(rodada_ht, KEY_JOGOS, jogos_s);
            release(jogos_l);
            release(jogos_s);
            LIST_LOOP(rodada->jogos)
            {
                Jogo *jogo = node->object;
                HashTable *jogo_ht = htable_init();
                Serializable *jogo_s = serializable_create(jogo_ht, ht_t);
                list_append(jogos_l, jogo_s);
                release(jogo_ht);
                release(jogo_s);

                {
                    Serializable *s = serializable_init();
                    s->type = int_t;
                    s->i = jogo->gols1;
                    htable_set(jogo_ht, KEY_GOLS1, s);
                    release(s);
                }
                {
                    Serializable *s = serializable_init();
                    s->type = int_t;
                    s->i = jogo->gols2;
                    htable_set(jogo_ht, KEY_GOLS2, s);
                    release(s);
                }
                {
                    Serializable *s = serializable_init();
                    s->type = bool_t;
                    s->i = jogo->jaFoiJogo;
                    htable_set(jogo_ht, KEY_JA_FOI_JOGO, s);
                    release(s);
                }
                {
                    String *time1_str = str_create(jogo->time1->nome);
                    Serializable *time1_s = serializable_create(time1_str, str_t);
                    htable_set(jogo_ht, KEY_TIME1, time1_s);
                    release(time1_str);
                    release(time1_s);
                }
                {
                    String *time1_str = str_create(jogo->time2->nome);
                    Serializable *time1_s = serializable_create(time1_str, str_t);
                    htable_set(jogo_ht, KEY_TIME2, time1_s);
                    release(time1_str);
                    release(time1_s);
                }
            }
        }
    }
    String *json = serializable_write_json(campeonato_s);
    release(campeonato_s);

    file_manager *fm = construct_file_manager(filename);
    write_bytes(fm, json->string);

    release(json);
    destroy_file_manager(fm);

}

Campeonato *
campeonato_read_from_file(char *filename)
{
    file_manager *fm = construct_file_manager(filename);
    char *content = read_all_bytes(fm);
    destroy_file_manager(fm);
    String *str = str_create(content);
    free(content);
    Serializable *champ_s = serializable_read_json(str);
    release(str);
    HashTable * champ_ht = champ_s->ht;

    Campeonato *champ = alloc(sizeof(Campeonato), campeonato_release);
    champ->times = list_init();
    List *times_l = ((Serializable *)htable_retrieve(champ_ht, KEY_TIMES, 0))->list;
    LIST_LOOP(times_l)
    {
        HashTable *time_ht = ((Serializable *)(node->object))->ht;
        Time *_time = alloc(sizeof(Time), time_release);
        String *nome_str = ((Serializable *)htable_retrieve(time_ht, KEY_NOME, 0))->str;
        _time->nome = malloc(sizeof(char) * (nome_str->len + 1));
        strcpy(_time->nome, nome_str->string);
        _time->pontos = ((Serializable *)htable_retrieve(time_ht, KEY_PONTOS, 0))->i;
        _time->saldo = ((Serializable *)htable_retrieve(time_ht, KEY_SALDO, 0))->i;
        _time->vit = ((Serializable *)htable_retrieve(time_ht, KEY_VIT, 0))->i;
        _time->emp = ((Serializable *)htable_retrieve(time_ht, KEY_EMP, 0))->i;
        _time->der = ((Serializable *)htable_retrieve(time_ht, KEY_DER, 0))->i;
        _time->jogadores = list_init();
        List *jogadores_l = ((Serializable *)htable_retrieve(time_ht, KEY_JOGADORES, 0))->list;
        LIST_LOOP(jogadores_l)
        {
            HashTable *jogador_ht = ((Serializable *)(node->object))->ht;
            Jogador *j = alloc(sizeof(Jogador), jogador_release);
            String *nome_str = ((Serializable *)htable_retrieve(jogador_ht, KEY_NOME, 0))->str;
            j->nome = malloc(sizeof(char) * (nome_str->len + 1));
            strcpy(j->nome, nome_str->string);
            j->numero = ((Serializable *)htable_retrieve(jogador_ht, KEY_NUMERO, 0))->i;
            j->gols = ((Serializable *)htable_retrieve(jogador_ht, KEY_GOLS, 0))->i;
            list_append(_time->jogadores, j);
            release(j);
        }
        list_append(champ->times, _time);
        release(_time);
    }
    champ->rodadas = list_init();
    List *rodadas_l = ((Serializable *)htable_retrieve(champ_ht, KEY_RODADAS, 0))->list;
    LIST_LOOP(rodadas_l)
    {
        HashTable *rodada_ht = ((Serializable *)(node->object))->ht;
        Rodada *rodada = alloc(sizeof(Rodada), rodada_release);
        list_append(champ->rodadas, rodada);
        release(rodada);
        rodada->jaFoiRodada = ((Serializable *)htable_retrieve(rodada_ht, KEY_JA_FOI_RODADA, 0))->i;
        rodada->numero = ((Serializable *)htable_retrieve(rodada_ht, KEY_NUMERO, 0))->i;
        rodada->jogos = list_init();
        List *jogos_l = ((Serializable *)htable_retrieve(rodada_ht, KEY_JOGOS, 0))->list;
        LIST_LOOP(jogos_l)
        {
            HashTable *jogo_ht = ((Serializable *)(node->object))->ht;
            Jogo *j = alloc(sizeof(Jogo), jogo_release);
            list_append(rodada->jogos, j);
            j->jaFoiJogo = ((Serializable *)htable_retrieve(jogo_ht, KEY_JA_FOI_JOGO, 0))->i;
            j->gols1 = ((Serializable *)htable_retrieve(jogo_ht, KEY_GOLS1, 0))->i;
            j->gols2 = ((Serializable *)htable_retrieve(jogo_ht, KEY_GOLS2, 0))->i;
            char *time1 = ((Serializable *)htable_retrieve(jogo_ht, KEY_TIME1, 0))->str->string;
            char *time2 = ((Serializable *)htable_retrieve(jogo_ht, KEY_TIME2, 0))->str->string;
            LIST_LOOP(champ->times)
            {
                Time *_t = node->object;
                if (streq(_t->nome, time1))
                {
                    j->time1 = _t;
                    retain(_t);
                }
                if (streq(_t->nome, time2))
                {
                    j->time2 = _t;
                    retain(_t);
                }
            }
            release(j);
        }
    }

    release(champ_s);
    return champ;
}


void
campeonato_release(void *champ)
{
    Campeonato *c = champ;
    release(c->times);
    release(c->rodadas);
}

void
jogador_release(void *jogador)
{
    Jogador *j = jogador;
    if (j->nome)
        free(j->nome);
}

void
time_release(void *_time)
{
    Time *t = (Time *)_time;
    if (t->nome)
        free(t->nome);
    release(t->jogadores);
}

void
rodada_release(void *rodada)
{
    Rodada *r = (Rodada *)rodada;
    release(r->jogos);
}

void
jogo_release(void *jogo)
{
    Jogo *j = (Jogo *)jogo;
    release(j->time1);
    release(j->time2);
}

Rodada *
rodadaAtual(Campeonato *c){
    LIST_LOOP(c->rodadas){
        Rodada *r = node->object;
        if(!r->jaFoiRodada)
            return r;
    }
    return NULL;
}

Rodada *
encontraRodada(Campeonato *c,int numero){
     LIST_LOOP(c->rodadas){
        Rodada *r = node->object;
        if(r->numero == numero)
            return r;
     }
     return NULL;
}


Vector *
jogosDisponiveis(Rodada *r)
{
    Vector *v = vector_init();
    LIST_LOOP(r->jogos)
    {
        Jogo *j = node->object;
        if(!j->jaFoiJogo)
            vector_append(v, j);
    }
    return v;
}

Time *
encontraTime(Campeonato *c, char *nome){
    LIST_LOOP(c->times)
    {
        Time *t = node->object;
        if(streq(t->nome,nome))
            return t;
    }
    return NULL;
}

void
imprimeVetorJogos(Vector *v)
{
    for (int i = 0; i < v->count; i++)
    {
        Jogo *j = v->objs[i];
        printf("%d - %s X %s \n", i, j->time1->nome, j->time2->nome);
    }
}

void
adicionaGolsJogadores(Time *t)
{
    int i = rand() % (t->jogadores->count); // gera um numero randomico entra 0 e numero de jogadores
    Vector * jogadores = vector_from_list(t->jogadores);
    Jogador *j = jogadores->objs[i];
    j->gols++;
    release(jogadores);
}

int
verificaAcabouRodada(Rodada *r)
{
    r->jaFoiRodada = 1;
    LIST_LOOP(r->jogos)
    {
        Jogo *j = node->object;
        if(!j->jaFoiJogo)
        {
            r->jaFoiRodada = 0;
            break;
        }
    }
    return r->jaFoiRodada;
}

void alteraCampeonato(Campeonato *c, Jogo *j)
{
    int g1 = j->gols1,g2 = j->gols2;
    Time *time1 = j->time1;//encontraTime(c, j->time1->nome);
    Time *time2 = j->time2;//encontraTime(c, j->time2->nome);
    if (g1 > g2)
    {
        time1->vit++;
        time1->pontos = time1->pontos + 3;
        time2->der++;
    }
    else if(g1 < g2)
    {
        time1->der++;
        time2->vit++;
        time2->pontos = time2->pontos + 3;
    }
    else if(g1 == g2)
    {
        time1->emp++;
        time1->pontos = time1->pontos + 1;
        time2->emp++;
        time2->pontos = time2->pontos + 1;
    }
    time1->saldo += g1 - g2;
    time2->saldo += g2 - g1;
    while(g1 > 0)
    {
        adicionaGolsJogadores(time1);
        g1--;
    }
    while(g2 > 0)
    {
        adicionaGolsJogadores(time2);
        g2--;
    }
}

void
registraJogo(Campeonato *c)
{
    Rodada *rodadaAt = rodadaAtual(c);
    if (rodadaAt == NULL)
    {
        printf("O campeonato ja acabou.\n");
        return;
    }
    else
    {
        Vector *jogos;
        int selecao, gols1, gols2;
        jogos = jogosDisponiveis(rodadaAt);
        printf("Rodada atual: %d\n", rodadaAt->numero);
        printf("Jogos Disponiveis:\n");
        imprimeVetorJogos(jogos);
        printf("Opção: ");
        scanf("%d",&selecao);
        Jogo *j = jogos->objs[selecao];
        printf("Digite o resultado da partida entre %s X %s:", j->time1->nome, j->time2->nome);
        scanf("%d %d", &gols1, &gols2);
        j->gols1 = gols1;
        j->gols2 = gols2;
        alteraCampeonato(c, jogos->objs[selecao]);
        j->jaFoiJogo = 1;
        release(jogos);
    }
    verificaAcabouRodada(rodadaAt);
}

void geraResultadoRodada(Campeonato *c)
{
    Rodada *rodadaAt = rodadaAtual(c);
    if (rodadaAt == NULL || rodadaAt->jaFoiRodada)
    {
        printf("Ja foram todas as rodadas do campeonato.");
        return;
    }
    else
    {
        Vector *jogos;
        int gols1,gols2,i;
        jogos = jogosDisponiveis(rodadaAt);
        for (i = 0; i < jogos->count; i++)
        {
            Jogo *j = jogos->objs[i];
            if(!j->jaFoiJogo)
            {
                gols1 =  rand() % 7;
                gols2 =  rand() % 7;
                j->gols1 = gols1;
                j->gols2 = gols2;
                alteraCampeonato(c, j);
                j->jaFoiJogo = 1;
            }
        }
        release(jogos);
    }
}

void
geraResultadosJogo(Campeonato *c)
{
    Rodada *rodadaAt = rodadaAtual(c);
    if (rodadaAt == NULL)
    {
        printf("O campeonato acabou\n");
        return;
    }
    else{
        Vector *jogos;
        int gols1, gols2, selecao;
        jogos = jogosDisponiveis(rodadaAt);

        selecao = rand() % jogos->count;
        gols1 =  rand() % 7;
        gols2 =  rand() % 7;
        Jogo *j = jogos->objs[selecao];
        j->gols1 = gols1;
        j->gols2 = gols2;
        alteraCampeonato(c, j);
        j->jaFoiJogo = 1;
        release(jogos);
    }
    verificaAcabouRodada(rodadaAt);
    return;
}

void
geraResultadoCampeonato(Campeonato *c)
{
    while(rodadaAtual(c))
        geraResultadoRodada(c);
}

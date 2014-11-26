#include "campeonato.h"
#include <stdio.h>

#include "sgbd/binary_file.h"

#define streq(a, b) (strcmp(a,b)==0)

void
campeonato_write_to_file(char *filename, Campeonato *champ)
{
    HashTable *campeonato_ht = htable_init();
    Serializable *campeonato_s = serializable_create(campeonato_ht, ht_t);
    release(campeonato_ht);

    List *times_l = list_init();
    Serializable *times_s = serializable_create(times_l, list_t);
    release(times_l);

    htable_set(campeonato_ht, "times", times_s);
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
            htable_set(time_ht, "nome", nome_s);
            release(nome_s);
            release(nome_str);
        }
        {
            Serializable *s = serializable_init();
            s->type = int_t;
            s->i = _time->pontos;
            htable_set(time_ht, "pontos", s);
            release(s);
        }
        {
            Serializable *s = serializable_init();
            s->type = int_t;
            s->i = _time->saldo;
            htable_set(time_ht, "saldo", s);
            release(s);
        }
        {
            Serializable *s = serializable_init();
            s->type = int_t;
            s->i = _time->vit;
            htable_set(time_ht, "vit", s);
            release(s);
        }
        {
            Serializable *s = serializable_init();
            s->type = int_t;
            s->i = _time->emp;
            htable_set(time_ht, "emp", s);
            release(s);
        }
        {
            Serializable *s = serializable_init();
            s->type = int_t;
            s->i = _time->der;
            htable_set(time_ht, "der", s);
            release(s);
        }
        {
            List *jogadores_l = list_init();
            Serializable *jogadores_s = serializable_create(jogadores_l, list_t);
            htable_set(time_ht, "jogadores", jogadores_s);
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
                    htable_set(jogador_ht, "nome", nome_s);
                    release(nome_s);
                    release(nome_str);
                }
                {
                    Serializable *s = serializable_init();
                    s->type = int_t;
                    s->i = jogador->numero;
                    htable_set(jogador_ht, "numero", s);
                    release(s);
                }
                {
                    Serializable *s = serializable_init();
                    s->type = int_t;
                    s->i = jogador->gols;
                    htable_set(jogador_ht, "gols", s);
                    release(s);
                }
            }
        }

        List *rodadas_l = list_init();
        Serializable *rodadas_s = serializable_create(rodadas_l, list_t);
        htable_set(campeonato_ht, "rodadas", rodadas_s);
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
                htable_set(rodada_ht, "ja foi rodada", s);
                release(s);
            }
            {
                Serializable *s = serializable_init();
                s->type = int_t;
                s->i = rodada->numero;
                htable_set(rodada_ht, "numero", s);
                release(s);
            }
            List *jogos_l = list_init();
            Serializable *jogos_s = serializable_create(jogos_l, list_t);
            htable_set(rodada_ht, "jogos", jogos_s);
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
                    htable_set(jogo_ht, "gols 1", s);
                    release(s);
                }
                {
                    Serializable *s = serializable_init();
                    s->type = int_t;
                    s->i = jogo->gols2;
                    htable_set(jogo_ht, "gols 2", s);
                    release(s);
                }
                {
                    Serializable *s = serializable_init();
                    s->type = bool_t;
                    s->i = jogo->jaFoiJogo;
                    htable_set(jogo_ht, "ja foi jogo", s);
                    release(s);
                }
                {
                    String *time1_str = str_create(jogo->time1->nome);
                    Serializable *time1_s = serializable_create(time1_str, str_t);
                    htable_set(jogo_ht, "time 1", time1_s);
                    release(time1_str);
                    release(time1_s);
                }
                {
                    String *time1_str = str_create(jogo->time2->nome);
                    Serializable *time1_s = serializable_create(time1_str, str_t);
                    htable_set(jogo_ht, "time 2", time1_s);
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
    List *times_l = ((Serializable *)htable_retrieve(champ_ht, "times", 0))->list;
    LIST_LOOP(times_l)
    {
        HashTable *time_ht = ((Serializable *)(node->object))->ht;
        Time *_time = alloc(sizeof(Time), time_release);
        String *nome_str = ((Serializable *)htable_retrieve(time_ht, "nome", 0))->str;
        _time->nome = malloc(sizeof(char) * (nome_str->len + 1));
        strcpy(_time->nome, nome_str->string);
        _time->pontos = ((Serializable *)htable_retrieve(time_ht, "pontos", 0))->i;
        _time->saldo = ((Serializable *)htable_retrieve(time_ht, "saldo", 0))->i;
        _time->vit = ((Serializable *)htable_retrieve(time_ht, "vit", 0))->i;
        _time->emp = ((Serializable *)htable_retrieve(time_ht, "emp", 0))->i;
        _time->der = ((Serializable *)htable_retrieve(time_ht, "der", 0))->i;
        _time->jogadores = list_init();
        List *jogadores_l = ((Serializable *)htable_retrieve(time_ht, "jogadores", 0))->list;
        LIST_LOOP(jogadores_l)
        {
            HashTable *jogador_ht = ((Serializable *)(node->object))->ht;
            Jogador *j = alloc(sizeof(Jogador), jogador_release);
            String *nome_str = ((Serializable *)htable_retrieve(jogador_ht, "nome", 0))->str;
            j->nome = malloc(sizeof(char) * (nome_str->len + 1));
            strcpy(j->nome, nome_str->string);
            j->numero = ((Serializable *)htable_retrieve(jogador_ht, "numero", 0))->i;
            j->gols = ((Serializable *)htable_retrieve(jogador_ht, "gols", 0))->i;
            list_append(_time->jogadores, j);
            release(j);
        }
        list_append(champ->times, _time);
        release(_time);
    }
    champ->rodadas = list_init();
    List *rodadas_l = ((Serializable *)htable_retrieve(champ_ht, "rodadas", 0))->list;
    LIST_LOOP(rodadas_l)
    {
        HashTable *rodada_ht = ((Serializable *)(node->object))->ht;
        Rodada *rodada = alloc(sizeof(Rodada), rodada_release);
        list_append(champ->rodadas, rodada);
        release(rodada);
        rodada->jaFoiRodada = ((Serializable *)htable_retrieve(rodada_ht, "ja foi rodada", 0))->i;
        rodada->numero = ((Serializable *)htable_retrieve(rodada_ht, "numero", 0))->i;
        rodada->jogos = list_init();
        List *jogos_l = ((Serializable *)htable_retrieve(rodada_ht, "jogos", 0))->list;
        LIST_LOOP(jogos_l)
        {
            HashTable *jogo_ht = ((Serializable *)(node->object))->ht;
            Jogo *j = alloc(sizeof(Jogo), jogo_release);
            list_append(rodada->jogos, j);
            j->jaFoiJogo = ((Serializable *)htable_retrieve(jogo_ht, "ja foi jogo", 0))->i;
            j->gols1 = ((Serializable *)htable_retrieve(jogo_ht, "gols 1", 0))->i;
            j->gols2 = ((Serializable *)htable_retrieve(jogo_ht, "gols 2", 0))->i;
            char *time1 = ((Serializable *)htable_retrieve(jogo_ht, "time 1", 0))->str->string;
            char *time2 = ((Serializable *)htable_retrieve(jogo_ht, "time 2", 0))->str->string;
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
    free(j->nome);
}

void
time_release(void *_time)
{
    Time *t = (Time *)_time;
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



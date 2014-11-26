#include "campeonato.h"
#include <stdio.h>

#include "sgbd/binary_file.h"

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

    file_manager *fm = construct_file_manager(filename);
    write_bytes(fm, json->string);

    release(json);
    destroy_file_manager(fm);

}

void
champ_release(void *champ)
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


Campeonato *
campeonato_read_from_file(char *filename)
{
    return NULL;
}

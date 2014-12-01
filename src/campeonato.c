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

void OrdenarTabela(Time *v){// ordenado por  pontos  utilizando insertion sort
   int i, j, aux,aux3,aux4;  //e depois loops que ordenam por saldos e vitórias
   char aux1[20];

   for(j=1; j<20; j++) {
      aux=v[j].pontos;
      strcpy(aux1,v[j].nome);
      aux3=v[j].saldo;
      aux4=v[j].vit;

      i = j-1;

      while(i>=0 && v[i].pontos>aux){
        strcpy(v[i+1].nome,v[i].nome);
	v[i+1].pontos=v[i].pontos;
        v[i+1].saldo=v[i].saldo;
        v[i+1].vit=v[i].vit;
        i--;
      }
        v[i+1].pontos=aux;
        strcpy(v[i+1].nome,aux1);
        v[i+1].saldo=aux3;
        v[i+1].vit=aux4;
   }//termina insertionsort

   for(j=0;j<=18;j++){  //ordenar por saldo se pontos forem iguais
     aux=v[j].pontos;
     strcpy(aux1,v[j].nome);
     aux3=v[j].saldo;
     aux4=v[j].vit;

     for(i=j+1;i<=19;i++){
       if(v[j].pontos==v[i].pontos){ //se  pontos forem iguais
       if(v[j].saldo>v[i].saldo){ // se v[j]>v[i]nao faz nada
       }
       else if(v[j].saldo<v[i].saldo){
         strcpy(aux1,v[i].nome);  //tornando assim  v[i]=v[j]  e v[j]=v[i]
         aux=v[i].pontos;         //e o loop continua normalmente comparando com o resto dos elementos.
         aux3=v[i].saldo;
	 aux4=v[i].vit;
         strcpy(v[i].nome,v[j].nome);
	 v[i].pontos=v[j].pontos;
	 v[i].saldo=v[j].saldo;
	 v[i].vit=v[j].vit;
	 strcpy(v[j].nome,aux1);
	 v[j].pontos=aux;
	 v[j].saldo=aux3;
	 v[j].vit=aux4;
       }
       else{ //se os saldos forem iguais também, comeca comparar por vitorias
         if(v[j].vit>v[i].vit){// nao faz nada
	  }
	  else if(v[j].vit<v[i].vit){
	    strcpy(aux1,v[i].nome);  //tornando assim  v[i]=v[j]  e v[j]=v[i]
	    aux=v[i].pontos;  //e o loop continua normalmente comparando o novo v[j] com o resto dos elementos.
	    aux3=v[i].saldo;
	    aux4=v[i].vit;
            strcpy(v[i].nome,v[j].nome);
	    v[i].pontos=v[j].pontos;
	    v[i].saldo=v[j].saldo;
	    v[i].vit=v[j].vit;
	    strcpy(v[j].nome,aux1);
	    v[j].pontos=aux;
	    v[j].saldo=aux3;
	    v[j].vit=aux4;
	  }
          else{// se o numero de vitorias também forem iguais  não faz nada
          }
        }
     }
     else{ //se nao for  igual numero de pontos não faz nada
     }
    }
   }
}

void ImprimirTabela(Campeonato *c){
  int i=0;
  Time *aux,*v;
  v=alloc(sizeof(Time)*20,NULL);
  release(v);

  LIST_LOOP(c->times){ //coloca os 20 times em um vetor
    aux = Node->object;
    strcpy(v[i]->nome,aux->nome);
    v[i]->pontos=aux->pontos;
    v[i]->saldo=aux->saldo;
    v[i]->vit=aux->vit;
    v[i]->der=aux->der;
    v[i]->emp=aux->emp;
  }
  OrdenarTabela(v); //ordena o vetor

  for(i=0;i<20;i++){
    printf("%d - %s  %d pontos",i,v[i].nome,v[i].pontos);
  }
  return;
}

void ImprimirTime(Campeonato *c, char *ntime){ //imprime os jogadores do time, entrada  nome do time

  Time *aux;
  Jogador *aux2;

  LIST_LOOP(c->times){
  aux=Node->object;
  if(strcmp(aux->nome,ntime)==0){
  LIST_LOOP(aux->jogadores){
  aux2=Node->object;
  printf("%d - ",aux2->numero);
  puts(aux2->nome);
  }
  break;
  }
  }
  return;
}

void ImprimirArtilheiro(Campeonato *c){ //imprimi o jogador(es) com  maior numero de gols

  int i,cont;
  char art1[20];
  Time *aux;
  Jogagor *aux2;
  i=0;

  Time *v=alloc(sizeof(Jogador)*220,null);

  LIST_LOOP(c->times){
    aux=Node->object;
    LIST_LOOP(aux->jogadores){
    aux2=Node->object;
    if(aux2->gols>0){
      v[i].gols=aux2->gols;
      strcpy(v[i].nome,aux2->nome);
      v[i].numero=aux2->numero;
      i++;
    }
   }
 }

 OrdenarArtilheiros(v,i);

 for(cont=0;cont<i;cont++){
 printf("GOLS:%d - %s  \n",v[cont].gols,v[i].nome);
 }
 return;
}

 void OrdenarArtilheiros(Jogador *v,int tamanho){

  int i, j, aux,aux2;
  char aux1[20];

  for(j=1; j<tamanho; j++){
    strcpy(aux1,v[j].nome);
    aux=v[j].gols;
    aux2=v[j].numero;
    i=j-1;

    while(i>=0&& v[i].gols>aux){
      strcpy(v[i+1].nome,v[i].nome);
      v[i+1].gols=v[i].gols;
      v[i+1].numero=v[i].numero;
      i--;
    }
    strcpy(v[i+1].nome,aux1);
    v[i+1].gols=aux;
    v[i+1].numero=aux2;
  }
  return;
}

Rodada *rodadaAtual(Campeonato *c){
    LIST_LOOP(c->rodadas){
        Rodada *r = node->object;
        if(!r->jaFoiRodada)
            return r;
    }
    return NULL;
}

Rodada *encontraRodada(Campeonato *c,int numero){
     LIST_LOOP(c->rodadas){
        Rodada *r = node->object;
        if(r->numero == numero)
            return r;
     }
     return NULL;
}

void jogosDisponiveis(Rodada *r,Jogo *vJogos[]){
    int i = 0;
    LIST_LOOP(r->jogos){
        Jogo *j = node->object;
        if(!j->jaFoiJogo){
            vJogos[i] = j;
            i++;
        }
    }

}

void limpaVetorJogos(Jogo *vJogos[]){
    int i = 0;
    for(i = 0;i < 10; i++)
        vJogos[i] = NULL;
}

Time *encontraTime(char *nome, Campeonato *c){
    LIST_LOOP(c->times){
        Time *t = node->object;
        if(strcmp(t->nome,nome) == 0)
            return t;
    }
    return NULL;
}

void imprimeVetorJogos(Jogo *vJogos[]){
    int i = 0;
    for(i = 0; i < 10; i++)
        if(vJogos[i] != NULL)
            printf("%d - %s X %s \n",i,vJogos[i]->time1->nome,vJogos[i]->time2->nome);
}

void adicionaGolsJogadores(Time *t){
    srand(time(NULL));
    int i = rand() % 11,k = 0; // gera um numero randomico entra 0 e 10
    LIST_LOOP(t->jogadores){
        Jogador *j = node->object;
        if (i == k){
            j->gols++;
            break;
        }
        else
            k++;
    }
}
int verificaAcabouRodada(Rodada *r){
    LIST_LOOP(r->jogos){
        Jogo *j = node->object;
        if(!j->jaFoiJogo)
            return 0;
    }
    return 1;
}

void alteraCampeonato(Jogo *j,Campeonato *c){
    int g1 = j->gols1,g2 = j->gols2;
    Time *time1 = encontraTime(j->time1->nome,c);
    Time *time2 = encontraTime(j->time2->nome,c);
    if (j->gols1 > j->gols2){
        time1->vit++;
        time1->pontos = time1->pontos+3;
        time2->der++;
    }
    else if(j->gols1 < j->gols2){
        time1->der++;
        time2->vit++;
        time2->pontos = time2->pontos+3;
    }
    else if(j->gols1 == j->gols2){
        time1->emp++;
        time1->pontos = time1->pontos+1;
        time2->emp++;
        time2->pontos = time2->pontos+1;
    }
    time1->saldo += g1-g2;
    time2->saldo += g2-g1;
    while(g1 > 0){
        adicionaGolsJogadores(time1);
        g1--;
    }
    while(g2 > 0){
        adicionaGolsJogadores(time2);
        g2--;
    }
}

void registraJogo(Campeonato *c){
    Rodada *rodadaAt = rodadaAtual(c);
    if (rodadaAt == NULL){
        printf("O campeonato ja acabou.\n");
        return;
    }
    else{
        Jogo *jogos[10];
        int selecao,gols1,gols2;
        limpaVetorJogos(jogos);
        jogosDisponiveis(rodadaAt,jogos);
        printf("Rodada atual: %d\n",rodadaAt->numero);
        printf("Jogos Disponiveis:\n");
        imprimeVetorJogos(jogos);
        printf("Opção: ");
        scanf("%d",&selecao);
        printf("Digite o resultado da partida entre %s X %s:",jogos[selecao]->time1->nome,jogos[selecao]->time2->nome);
        scanf("%d %d",&gols1,&gols2);
        jogos[selecao]->gols1 = gols1;
        jogos[selecao]->gols2 = gols2;
        alteraCampeonato(jogos[selecao],c);
        jogos[selecao]->jaFoiJogo = 1;
    }
    if (verificaAcabouRodada(rodadaAt))
        rodadaAt->jaFoiRodada = 1;
}

void geraResultadoRodada(Campeonato *c,int rodada){
    Rodada *rodadaAt = encontraRodada(c,rodada);
    if (rodadaAt == NULL || rodadaAt->jaFoiRodada){
        printf("Ja foram todas as rodadas do campeonato.");
        return;
    }
    else{
        Jogo *jogos[10];
        int gols1,gols2,i;
        limpaVetorJogos(jogos);
        jogosDisponiveis(rodadaAt,jogos);
        for (i = 0; i<10;i++){
            if(jogos[i] != NULL && !jogos[i]->jaFoiJogo){
                srand(time(NULL));
                gols1 =  rand() % 7;
                gols2 =  rand() % 7;
                jogos[i]->gols1 = gols1;
                jogos[i]->gols2 = gols2;
                alteraCampeonato(jogos[i],c);
                jogos[i]->jaFoiJogo = 1;
            }
        }
    }

}
void geraResultadosJogo(Campeonato *c){
    Rodada *rodadaAt = rodadaAtual(c);
    if (rodadaAt == NULL){
        printf("O campeonato acabou\n");
        return;
    }
    else{
        Jogo *jogos[10];
        int i,tamanho = 0,gols1,gols2,selecao;
        limpaVetorJogos(jogos);
        jogosDisponiveis(rodadaAt,jogos);
        for(i = 0; i < 10;i++)
            if (jogos[i] != NULL)
                tamanho++;
        srand(time(NULL));
        selecao = rand() % tamanho;
        gols1 =  rand() % 7;
        gols2 =  rand() % 7;
        jogos[selecao]->gols1 = gols1;
        jogos[selecao]->gols2 = gols2;
        alteraCampeonato(jogos[selecao],c);
        jogos[selecao]->jaFoiJogo = 1;
    }
    if (verificaAcabouRodada(rodadaAt))
        rodadaAt->jaFoiRodada = 1;
}

void geraResultadoCampeonato(Campeonato *c){
    LIST_LOOP(c->rodadas){
        Rodada *r = node->object;
        if(!r->jaFoiRodada)
            geraResultadoRodada(c,r->numero);
    }
}



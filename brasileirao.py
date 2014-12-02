#!/usr/bin/env python
#-*- coding:utf-8 -*-
import requests
import json
import re
import random

base_url = "http://globoesporte.globo.com/futebol/brasileirao-serie-a/"
base_req = requests.get(base_url)
base_text = base_req.text

re_pattern = r'<a class="tabela-times-time-link" href="(http\:\/\/[a-zA-Z0-9\-\.]+\.[a-zA-Z]{2,3}(?:\/\S*)?)" title="[\-\w\s]+" alt="[\-\w\s]+" itemprop="url">'
times_urls = re.findall(re.compile(re_pattern, re.UNICODE), base_text)

re_pattern = r'<strong class="tabela-times-time-nome" itemprop="name">([\-\w\s]+)</strong>'
nomes = re.findall(re.compile(re_pattern, re.UNICODE), base_text)

re_pattern = r'<td class="tabela-pontos-ponto">(\-?\d+)</td><td>(\-?\d+)</td><td>(\-?\d+)</td><td>(\-?\d+)</td><td>(\-?\d+)</td><td>(\-?\d+)</td><td>(\-?\d+)</td><td>(\-?\d+)</td>'
infos = re.findall(re.compile(re_pattern, re.UNICODE), base_text)

assert len(nomes) == len(infos) == len(times_urls) == 20
times = []
for nome, info, url in zip(nomes, infos, times_urls):
    pontos, jogos, vitorias, empates, derrotas, golsFeitos, golsSofridos, saldo = info
    pontos, jogos, vitorias, empates, derrotas, golsFeitos, golsSofridos, saldo = tuple([0] * 8)
    time = {'nome': nome,
            'pontos': pontos,
            'saldo': saldo,
            'vit': vitorias,
            'emp': empates,
            'der': derrotas,
            }
    time['jogadores'] = []
    time_request = requests.get(url)
    re_pattern = r'<span class="ge-card-elenco-jogador-nome">([\w\s]+)</span>'
    jogadores_lst = re.findall(re.compile(re_pattern, re.UNICODE), time_request.text)
    jogadores = []
    for idx, nome_jogador in enumerate(jogadores_lst, 1):
        # if idx > 11:
        #     break
        jogador = {}
        jogador['nome'] = nome_jogador
        jogador['numero'] = idx
        jogador['gols'] = 0
        jogadores.append(jogador)
    time['jogadores'] = jogadores
    times.append(time)

campeonato = {}
campeonato['times'] = times

rodadas = []
for i in range(1, 38 + 1):
    rodada = {}
    random.shuffle(times)
    times1 = times[:len(times)/2]
    times2 = times[len(times)/2:]
    jogos = []
    for time1, time2 in zip(times1, times2):
        jogo = {}
        jogo['time 1'] = time1['nome']
        jogo['time 2'] = time2['nome']
        jogo['ja foi jogo'] = False
        jogo['gols 1'] = 0
        jogo['gols 2'] = 0
        jogos.append(jogo)
    rodada['jogos'] = jogos
    rodada['ja foi rodada'] = False
    rodada['numero'] = i
    rodadas.append(rodada)

campeonato['rodadas'] = rodadas

print json.dumps(campeonato, indent=4)

#ifndef JOGADAS_H_INCLUDED
#define JOGADAS_H_INCLUDED

#include "Posicao.h"
#include "Jogador.h"
#include "Tabuleiro.h"

typedef struct jogadas jogada, * pjogada;

struct jogadas 
{
	jogadores jogador;
	posicao posicao;
	char tabuleiroJogada[9][9];
	int linhas;
	int colunas;
	int escolha;

	pjogada prox;
};

pjogada guardaJogada(pjogada lista, tabuleiro tabuleiro, jogadores jogador, int x, int y, int escolha);
pjogada retrocedeJogada(ptabuleiro tab_jogo, pjogada lista);
void libertaMemoriaJogadas(pjogada lista);
void mostraJogadas(pjogada lista, int k);

#endif // !JOGADAS_H_INCLUDED
#include "Tabuleiro.h"
#include "Jogada.h"

typedef struct jogos jogo, * pjogo;

struct jogos
{
	pjogada listaJogadas; 
	tabuleiro tab_jogo;
	jogadores jogadores_jogo[2];
	int turno;
	int jogadorAleatorio;
};

/*
* turno
* jogadorAleatorio
* jogadorA
* jogadorB

* jogador
* posicao
* linhas
* colunas
* escolha
* tabuleiro
*/

char joga(int jogadorAleatorio);
int jogadaAleatoria(ptabuleiro tab_jogo, pjogadores jogador, int* x, int* y, int* opcao);
void escreveFicheiro(jogo jogo);
void escreveFicheiroBinario(jogo jogo);
int lerFicheiroBinario(pjogo jogo);
int passaTurno(int turno);
#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED

typedef struct matriz tabuleiro, * ptabuleiro;

struct matriz
{
	char **matriz;
	int linhas;
	int colunas;
};

/*
* Atualizar tabuleiro X
* 
* Aumentar tabuleiro 
* 
* Criar tabuleiro 
*/

int criarTabuleiro (ptabuleiro tab_jogo);
int adicionaLinha (ptabuleiro tab_jogo);
int adicionaColuna (ptabuleiro tab_jogo);
int adicionaPedra (ptabuleiro tab_jogo, int x, int y);
int adicionaPeca (ptabuleiro tab_jogo, int x, int y);
int verificaPedra (tabuleiro tab_jogo);
int verificaVitoria(tabuleiro tab_jogo, int x, int y);
void libertaMemoriaTabuleiro(ptabuleiro tab_jogo);
void imprimeTabuleiro (tabuleiro tab_jogo);

#endif
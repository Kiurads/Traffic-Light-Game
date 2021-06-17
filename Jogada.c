#include <stdlib.h>

#include "Jogada.h"

pjogada guardaJogada(pjogada lista, tabuleiro tabuleiro, jogadores jogador, int x, int y, int escolha)
{
	pjogada novo;

	novo = malloc(sizeof(jogada));

	if (novo == NULL)
	{
		return NULL;
	}

	novo->linhas = tabuleiro.linhas;
	novo->colunas = tabuleiro.colunas;
	novo->jogador.id = jogador.id;
	novo->jogador.pedra = jogador.pedra;
	novo->jogador.linhas_colunas = jogador.linhas_colunas;
	novo->posicao.x = x;
	novo->posicao.y = y;
	novo->escolha = escolha;

	for (int i = 0; i < novo->linhas; i++)
	{
		for (int j = 0; j < novo->colunas; j++)
		{
			novo->tabuleiroJogada[i][j] = tabuleiro.matriz[i][j];
		}
	}

	novo->prox = NULL;

	if (lista == NULL)
	{
		lista = novo;
	}
	else
	{
		novo->prox = lista;
		lista = novo;
	}

	return lista;
}

pjogada retrocedeJogada(ptabuleiro tab_jogo, pjogada lista)
{
	pjogada apagar;

	apagar = lista;
	lista = lista->prox;
	free(apagar);

	tab_jogo->linhas = lista->linhas;
	tab_jogo->colunas = lista->colunas;

	tab_jogo->matriz = realloc(tab_jogo->matriz, sizeof(char*) * lista->linhas);

	if (tab_jogo->matriz == NULL)
	{
		return 1;
	}

	for (int i = 0; i < lista->linhas; i++)
	{
		tab_jogo->matriz[i] = realloc(tab_jogo->matriz[i], sizeof(char) * lista->colunas);

		if (tab_jogo->matriz[i] == NULL)
		{
			return 1;
		}
	}

	for (int i = 0; i < lista->linhas; i++)
	{
		for (int j = 0; j < lista->colunas; j++)
		{
			tab_jogo->matriz[i][j] = lista->tabuleiroJogada[i][j];
		}
	}

	return lista;
}

void libertaMemoriaJogadas(pjogada lista)
{
	pjogada apagar;

	while (lista != NULL)
	{
		apagar = lista;
		lista = lista->prox;
		free(apagar);
	}
}

void mostraJogadas(pjogada lista, int k)
{
	pjogada aux;

	aux = lista->prox;

	while (aux != NULL && k > 0)
	{
		switch (aux->escolha)
		{
		case 0: // Tabuleiro inicial
			printf("Tabuleiro inicial\n\n");
			break;

		case 1: // Peca
			printf("O jogador %c jogou uma peca na posicao [%d, %d]\n\n", aux->jogador.id, aux->posicao.x, aux->posicao.y);
			break;

		case 2: // Linha
			printf("O jogador %c adicionou uma linha ao tabuleiro\n\n", aux->jogador.id);
			break;

		case 3: // Coluna
			printf("O jogador %c adicionou uma coluna ao tabuleiro\n\n", aux->jogador.id);
			break;

		case 4: // Pedra
			printf("O jogador %c jogou uma pedra na posicao [%d, %d]\n\n", aux->jogador.id, aux->posicao.x, aux->posicao.y);
			break;
		}

		for (int i = 0; i < aux->linhas; i++)
		{
			for (int j = 0; j < aux->colunas; j++)
			{
				printf("|%c", aux->tabuleiroJogada[i][j]);
			}

			printf("|\n");
		}

		printf("\n");

		aux = aux->prox;
		k--;
	}

	printf("\n\n");
}

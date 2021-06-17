#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tabuleiro.h"

#pragma once

int criarTabuleiro(ptabuleiro tab_jogo)
{
	srand(time(NULL));

	int num = (rand() % 3) + 3;

	tab_jogo->colunas = num;
	tab_jogo->linhas = num;

	tab_jogo->matriz = malloc(sizeof(char*) * num);

	if (tab_jogo->matriz == NULL)
	{
		return 1;
	}
	
	for (int i = 0; i < num; i++)
	{
		tab_jogo->matriz[i] = malloc(sizeof(char) * num);

		if (tab_jogo->matriz[i] == NULL)
		{
			return 1;
		}
	}

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			tab_jogo->matriz[i][j] = ' ';
		}
	}

	return 0;
}

int adicionaLinha(ptabuleiro tab_jogo) 
{
	tab_jogo->linhas++;

	tab_jogo->matriz = realloc(tab_jogo->matriz, sizeof(char*) * tab_jogo->linhas);

	if (tab_jogo->matriz == NULL)
	{
		return 1;
	}

	tab_jogo->matriz[tab_jogo->linhas - 1] = malloc(sizeof(char) * tab_jogo->colunas);

	if (tab_jogo->matriz[tab_jogo->linhas - 1] == NULL)
	{
		return 1;
	}

	for (int i = 0; i < tab_jogo->colunas; i++)
	{
		tab_jogo->matriz[tab_jogo->linhas - 1][i] = ' ';
	}

	return 0;
}

int adicionaColuna(ptabuleiro tab_jogo) {
	tab_jogo->colunas++;

	for (int i = 0; i < tab_jogo->linhas; i++)
	{
		tab_jogo->matriz[i] = realloc(tab_jogo->matriz[i], sizeof(char) * tab_jogo->colunas);

		if (tab_jogo->matriz[i] == NULL)
		{
			return 1;
		}

		tab_jogo->matriz[i][tab_jogo->colunas - 1] = ' ';
	}

	return 0;
}

int adicionaPedra(ptabuleiro tab_jogo, int x, int y)
{
	if (x >= tab_jogo->linhas || x < 0 || y >= tab_jogo->colunas || y < 0)
	{
		printf("Jogada fora dos limites\n\n");
		return 1;
	}

	if (tab_jogo->matriz[x][y] == ' ')
	{
		tab_jogo->matriz[x][y] = 'P';
		return 0;
	}
	else
	{
		printf("A posicao esta ocupada\n\n");
		return 1;
	}
}

int adicionaPeca(ptabuleiro tab_jogo, int x, int y)
{
	if (x >= tab_jogo->linhas || x < 0 || y >= tab_jogo->colunas || y < 0)
	{
		printf("Jogada fora dos limites\n\n");
		return 1;
	}

	switch (tab_jogo->matriz[x][y])
	{
	case ' ':
		tab_jogo->matriz[x][y] = 'G';
		break;

	case 'G':
		tab_jogo->matriz[x][y] = 'Y';
		break;

	case 'Y':
		tab_jogo->matriz[x][y] = 'R';
		break;

	default:
		printf("Posicao invalida! A celula ja tem uma peca vermelha ou uma pedra\n\n");
		
		return 1;
	}

	return 0;
}

int verificaPedra(tabuleiro tab_jogo)
{
	for (int i = 0; i < tab_jogo.linhas; i++)
	{
		for (int j = 0; j < tab_jogo.colunas; j++)
		{
			if (tab_jogo.matriz[i][j] == ' ')
			{
				return 0;
			}
		}
	}

	return 1;
}

int verificaVitoria(tabuleiro tab_jogo, int x, int y)
{
	if (x >= tab_jogo.linhas || x < 0 || y >= tab_jogo.colunas || y < 0)
	{
		return 1;
	}

	int vitoria = 0;
	char peca = tab_jogo.matriz[x][y];

	for (int i = 0; i < tab_jogo.colunas; i++)
	{
		if (peca != tab_jogo.matriz[x][i])
		{
			vitoria = 1;
			break;
		}
	}

	if (vitoria == 0)
	{
		return vitoria;
	}

	vitoria = 0;

	for (int i = 0; i < tab_jogo.linhas; i++)
	{
		if (peca != tab_jogo.matriz[i][y])
		{
			vitoria = 1;
			break;
		}
	}

	if (vitoria == 0)
	{
		return vitoria;
	}

	if (tab_jogo.linhas == tab_jogo.colunas)
	{
		if (x == y)
		{
			vitoria = 0;

			for (int i = 0; i < tab_jogo.linhas; i++)
			{
				if (peca != tab_jogo.matriz[i][i])
				{
					vitoria = 1;
					break;
				}
			}

			if (vitoria == 0)
			{
				return vitoria;
			}
		}

		if (x + y == tab_jogo.linhas - 1)
		{
			vitoria = 0;

			for (int i = 0; i < tab_jogo.linhas; i++)
			{
				if (peca != tab_jogo.matriz[tab_jogo.linhas - i - 1][i])
				{
					vitoria = 1;
					break;
				}
			}

		}
	}

	return vitoria;
}

void libertaMemoriaTabuleiro(ptabuleiro tab_jogo)
{
	for (int i = 0; i < tab_jogo->linhas; i++)
	{
		free(tab_jogo->matriz[i]);
	}

	free(tab_jogo->matriz);
}

void imprimeTabuleiro(tabuleiro tab_jogo)
{
	for (int i = 0; i < tab_jogo.linhas; i++)
	{
		for (int j = 0; j < tab_jogo.colunas; j++)
		{
			printf("|%c", tab_jogo.matriz[i][j]);
		}
		printf("|\n");
	}

	printf("\n");
}
#include <stdio.h>
#include <stdlib.h>
#include "Jogo.h"

char joga(int modo)
{
    int x, y, k;
	int opcao = 0;
    int vitoria = 0;
	jogo jogoAtual;

    if (modo != 2)
    {
        inicia_jogador(&jogoAtual.jogadores_jogo[0], 'A');
        inicia_jogador(&jogoAtual.jogadores_jogo[1], 'B');

        jogoAtual.jogadorAleatorio = modo;
        jogoAtual.turno = 0;

        if (criarTabuleiro(&jogoAtual.tab_jogo) == 1)
        {
            printf("ERRO: Alocacao de memoria falhou!\n");
            return NULL;
        }

        x = y = -1;

        jogoAtual.listaJogadas = NULL;

        if ((jogoAtual.listaJogadas = guardaJogada(jogoAtual.listaJogadas, jogoAtual.tab_jogo, jogoAtual.jogadores_jogo[jogoAtual.turno], x, y, opcao)) == NULL)
        {
            printf("ERRO: Alocacao de memoria falhou!\n");
            return NULL;
        }
    }
    else
    {
        if (lerFicheiroBinario(&jogoAtual) == 1) {
            return NULL;
        }
    }

    do
    {
        x = y = -1;

        imprimeTabuleiro(jogoAtual.tab_jogo);

        printf("\n\tJogador %c\n\n", jogoAtual.jogadores_jogo[jogoAtual.turno].id);
        printf("Pedras x%d\n", jogoAtual.jogadores_jogo[jogoAtual.turno].pedra);
        printf("Linhas/Colunas x%d\n\n", jogoAtual.jogadores_jogo[jogoAtual.turno].linhas_colunas);

        printf("1. Jogar pecas\n");
        
        if (jogoAtual.jogadores_jogo[jogoAtual.turno].linhas_colunas != 0)
        {
            printf("2. Adicionar linha\n");
            printf("3. Adicionar coluna\n");
        }

        if (jogoAtual.jogadores_jogo[jogoAtual.turno].pedra != 0 && verificaPedra(jogoAtual.tab_jogo) == 0)
        {
            printf("4. Adicionar pedra\n");
        }

        printf("5. Ver jogadas anteriores\n");

        printf("6. Retroceder jogada\n");

        printf("0. Sair\n");

        scanf(" %d", &opcao);
        system("cls || clear");

        switch (opcao)
        {
        case 1:
            imprimeTabuleiro(jogoAtual.tab_jogo);

            printf("Para que celula quer jogar a peca (linha coluna): ");
            scanf(" %d %d", &x, &y);

            if (adicionaPeca(&jogoAtual.tab_jogo, x, y) == 0)
            {
                if ((jogoAtual.listaJogadas = guardaJogada(jogoAtual.listaJogadas, jogoAtual.tab_jogo, jogoAtual.jogadores_jogo[jogoAtual.turno], x, y, opcao)) == NULL)
                {
                    printf("ERRO: Alocacao de memoria falhou!\n");
                    return NULL;
                }

                if (verificaVitoria(jogoAtual.tab_jogo, x, y) == 0)
                {
                    vitoria = 1;
                    opcao = 0;
                }

                break;
            }

            opcao = -1;

            break;

        case 2:
            if (jogoAtual.jogadores_jogo[jogoAtual.turno].linhas_colunas == 0)
            {
                opcao = -1;

                printf("Digite uma opcao valida\n\n");
                break;
            }
            
            if (adicionaLinha(&jogoAtual.tab_jogo) == 1)
            {
                printf("ERRO: Alocacao de memoria falhou!\n");
                return NULL;
            }

            if ((jogoAtual.listaJogadas = guardaJogada(jogoAtual.listaJogadas, jogoAtual.tab_jogo, jogoAtual.jogadores_jogo[jogoAtual.turno], x, y, opcao)) == NULL)
            {
                printf("ERRO: Alocacao de memoria falhou!\n");
                return NULL;
            }

            jogoAtual.jogadores_jogo[jogoAtual.turno].linhas_colunas--;

            break;

        case 3:
            if (jogoAtual.jogadores_jogo[jogoAtual.turno].linhas_colunas == 0)
            {
                opcao = -1;

                printf("Digite uma opcao valida\n\n");
                break;
            }

            if (adicionaColuna(&jogoAtual.tab_jogo) == 1)
            {
                printf("ERRO: Alocacao de memoria falhou!\n");
                return NULL;
            }

            if ((jogoAtual.listaJogadas = guardaJogada(jogoAtual.listaJogadas, jogoAtual.tab_jogo, jogoAtual.jogadores_jogo[jogoAtual.turno], x, y, opcao)) == NULL)
            {
                printf("ERRO: Alocacao de memoria falhou!\n");
                return NULL;
            }

            jogoAtual.jogadores_jogo[jogoAtual.turno].linhas_colunas--;

            break;

        case 4:
            if (jogoAtual.jogadores_jogo[jogoAtual.turno].pedra == 0 || verificaPedra(jogoAtual.tab_jogo) == 1)
            {
                opcao = -1;

                printf("Digite uma opcao valida\n\n");
                break;
            }

            imprimeTabuleiro(jogoAtual.tab_jogo);

            printf("Para que celula quer jogar a pedra (linha coluna): ");
            scanf(" %d %d", &x, &y);

            if (adicionaPedra(&jogoAtual.tab_jogo, x, y) == 0)
            {
                if ((jogoAtual.listaJogadas = guardaJogada(jogoAtual.listaJogadas, jogoAtual.tab_jogo, jogoAtual.jogadores_jogo[jogoAtual.turno], x, y, opcao)) == NULL)
                {
                    printf("ERRO: Alocacao de memoria falhou!\n");
                    return NULL;
                }

                jogoAtual.jogadores_jogo[jogoAtual.turno].pedra--;

                break;
            }
            
            opcao = -1;

            printf("A pedra apenas pode ser colocada numa celula vazia\n\n");

            break;

        case 5:
            printf("Quantas jogadas: ");
            scanf(" %d", &k);

            mostraJogadas(jogoAtual.listaJogadas, k);

            break;

        case 6:
            if (jogoAtual.listaJogadas->prox == NULL)
            {
                printf("Nao existem jogadas anteriores\n\n");
            }
            else
            {
                jogoAtual.listaJogadas = retrocedeJogada(&jogoAtual.tab_jogo, jogoAtual.listaJogadas);
            }

            break;

        case 0:
            printf("Bye :(");
            break;

        default:
            printf("Digite uma opcao valida\n");
        }

        if (jogoAtual.jogadorAleatorio == 0 && (opcao >= 1 && opcao <= 4 || opcao == 6))
        {
            jogoAtual.turno = passaTurno(jogoAtual.turno);
        }
        else
        {
            if (opcao >= 1 && opcao <= 4 || opcao == 6)
            {
                jogoAtual.turno = passaTurno(jogoAtual.turno);

                if (jogadaAleatoria(&jogoAtual.tab_jogo, &jogoAtual.jogadores_jogo[jogoAtual.turno], &x, &y, &opcao) == 1)
                {
                    printf("ERRO: Alocacao de memoria falhou!\n");
                    return NULL;
                }

                if ((jogoAtual.listaJogadas = guardaJogada(jogoAtual.listaJogadas, jogoAtual.tab_jogo, jogoAtual.jogadores_jogo[jogoAtual.turno], x, y, opcao)) == NULL)
                {
                    printf("ERRO: Alocacao de memoria falhou!\n");
                    return NULL;
                }

                if (verificaVitoria(jogoAtual.tab_jogo, x, y) == 0)
                {
                    vitoria = 1;
                    opcao = 0;
                }
                else
                {
                    jogoAtual.turno = passaTurno(jogoAtual.turno);
                }
            }
        }

    } while (opcao);

    imprimeTabuleiro(jogoAtual.tab_jogo);

    if (opcao == 0 && vitoria == 1)
    {
        printf("O vencedor foi o jogador %c\n\n", jogoAtual.jogadores_jogo[jogoAtual.turno].id);
        escreveFicheiro(jogoAtual);
    }

    if (opcao == 0 && vitoria == 0)
    {
        escreveFicheiroBinario(jogoAtual);
    }

    //TODO Libertar memória da lista ligada

    libertaMemoriaTabuleiro(&jogoAtual.tab_jogo);

	return jogoAtual.jogadores_jogo[jogoAtual.turno].id;
}

int jogadaAleatoria(ptabuleiro tab_jogo, pjogadores jogador, int* x, int* y, int* opcao)
{
    int tamanho, num;
    pposicao jogadas; 
    
    jogadas = malloc(sizeof(posicao));

    if (jogadas == NULL)
    {
        printf("ERRO: Alocacao de memoria falhou!\n");
        return 1;
    }

    srand(time(NULL));

    tamanho = 0;

    num = 0;

    if (jogador->linhas_colunas > 0)
    {
        num = rand() % 2;
    }

    if (num == 0)
    {
        int pedra = 0;

        if (jogador->pedra > 0)
        {
            if (verificaPedra(*tab_jogo) == 0)
            {
                pedra = 1;
            }
        }

        if (pedra == 1)
        {
            pedra = rand() % 2;
        }

        for (int i = 0; i < tab_jogo->linhas; i++)
        {
            for (int j = 0; j < tab_jogo->colunas; j++)
            {
                if (tab_jogo->matriz[i][j] != 'R' && tab_jogo->matriz[i][j] != 'P')
                {
                    if (tab_jogo->matriz[i][j] == ' ' && pedra == 1)
                    {
                        tamanho++;

                        jogadas = realloc(jogadas, sizeof(posicao) * tamanho);

                        if (jogadas == NULL)
                        {
                            printf("ERRO: Alocacao de memoria falhou!\n");
                            return 1;
                        }

                        jogadas[tamanho - 1].x = i;
                        jogadas[tamanho - 1].y = j;
                    }
                    
                    if (pedra == 0)
                    {
                        tamanho++;

                        jogadas = realloc(jogadas, sizeof(posicao) * tamanho);

                        if (jogadas == NULL)
                        {
                            printf("ERRO: Alocacao de memoria falhou!\n");
                            return 1;
                        }

                        jogadas[tamanho - 1].x = i;
                        jogadas[tamanho - 1].y = j;
                    }
                }
            }
        }

        num = rand() % tamanho;

        if (pedra == 1)
        {
            tab_jogo->matriz[jogadas[num].x][jogadas[num].y] = 'P';

            jogador->pedra--;

            *x = jogadas[num].x;
            *y = jogadas[num].y;

            *opcao = 4;

            printf("O jogador B jogou uma pedra na posicao (%d, %d)\n\n", jogadas[num].x, jogadas[num].y);
        }
        else
        {
            switch (tab_jogo->matriz[jogadas[num].x][jogadas[num].y])
            {
            case ' ':
                tab_jogo->matriz[jogadas[num].x][jogadas[num].y] = 'G';
                break;

            case 'G':
                tab_jogo->matriz[jogadas[num].x][jogadas[num].y] = 'Y';
                break;

            case 'Y':
                tab_jogo->matriz[jogadas[num].x][jogadas[num].y] = 'R';
                break;
            }

            *x = jogadas[num].x;
            *y = jogadas[num].y;

            *opcao = 1;

            printf("O jogador B jogou uma peca na posicao (%d, %d)\n\n", jogadas[num].x, jogadas[num].y);
        }

        free(jogadas);
    }
    else
    {
        num = rand() % 2;

        if (num == 0)
        {
            if (adicionaLinha(tab_jogo) == 1)
            {
                printf("ERRO: Alocacao de memoria falhou!\n");
                return 1;
            }

            *opcao = 2;

            printf("O jogador B adicionou uma linha\n\n");
        }
        else
        {
            if (adicionaColuna(tab_jogo) == 1)
            {
                printf("ERRO: Alocacao de memoria falhou!\n");
                return 1;
            }

            *opcao = 3;

            printf("O jogador B adicionou uma coluna\n\n");
        }

        jogador->linhas_colunas--;
    }

    return 0;
}

void escreveFicheiro(jogo jogo)
{
    FILE* f;
    pjogada aux;
    char nome[100];

    printf("Nome do ficheiro de jogo: ");
    scanf(" %s", nome);

    f = fopen(nome, "w");

    aux = jogo.listaJogadas;

    while (aux != NULL)
    {
        switch (aux->escolha)
        {
        case 0: // Tabuleiro inicial
            fprintf(f, "Tabuleiro inicial\n\n");
            break;

        case 1: // Peca
            fprintf(f, "O jogador %c jogou uma peca na posicao [%d, %d]\n\n", aux->jogador.id, aux->posicao.x, aux->posicao.y);
            break;

        case 2: // Linha
            fprintf(f, "O jogador %c adicionou uma linha ao tabuleiro\n\n", aux->jogador.id);
            break;

        case 3: // Coluna
            fprintf(f, "O jogador %c adicionou uma coluna ao tabuleiro\n\n", aux->jogador.id);
            break;

        case 4: // Pedra
            fprintf(f, "O jogador %c jogou uma pedra na posicao [%d, %d]\n\n", aux->jogador.id, aux->posicao.x, aux->posicao.y);
            break;
        }

        for (int i = 0; i < aux->linhas; i++)
        {
            for (int j = 0; j < aux->colunas; j++)
            {
                fprintf(f, "|%c", aux->tabuleiroJogada[i][j]);
            }

            fprintf(f, "|\n");
        }

        fprintf(f, "\n");

        aux = aux->prox;
    }

    fprintf(f, "\n\n");

    fclose(f);
}

void escreveFicheiroBinario(jogo jogo)
{
    FILE* f;
    pjogada aux;

    f = fopen("jogo.bin", "wb");

    fwrite(&jogo.turno, sizeof(int), 1, f);
    fwrite(&jogo.jogadorAleatorio, sizeof(int), 1, f);

    fwrite(jogo.jogadores_jogo, sizeof(jogadores), 2, f);

    aux = jogo.listaJogadas;

    while (aux != NULL)
    {
        fwrite(aux, sizeof(jogada), 1, f);

        aux = aux->prox;
    }

    fclose(f);
}

int lerFicheiroBinario(pjogo jogo)
{
    FILE* f;

    f = fopen("jogo.bin", "rb");

    fread(&jogo->turno, sizeof(int), 1, f);
    fread(&jogo->jogadorAleatorio, sizeof(int), 1, f);

    fread(jogo->jogadores_jogo, sizeof(jogadores), 2, f);

    printf("%d %d\n", jogo->turno, jogo->jogadorAleatorio);

    for (int i = 0; i < 2; i++)
    {
        printf("ID: %c\n", jogo->jogadores_jogo[i].id);
        printf("Pedras: %d\n", jogo->jogadores_jogo[i].pedra);
        printf("LC: %d\n\n", jogo->jogadores_jogo[i].linhas_colunas);
    }

    jogada jogadaAux;
    pjogada aux;

    jogo->listaJogadas = aux = NULL;

    while (fread(&jogadaAux, sizeof(jogada), 1, f) == 1)
    {
        pjogada novo;

        novo = malloc(sizeof(jogada));

        if (novo == NULL)
        {
            return NULL;
        }

        novo->linhas = jogadaAux.linhas;
        novo->colunas = jogadaAux.colunas;
        novo->jogador.id = jogadaAux.jogador.id;
        novo->jogador.pedra = jogadaAux.jogador.pedra;
        novo->jogador.linhas_colunas = jogadaAux.jogador.linhas_colunas;
        novo->posicao.x = jogadaAux.posicao.x;
        novo->posicao.y = jogadaAux.posicao.y;
        novo->escolha = jogadaAux.escolha;

        for (int i = 0; i < novo->linhas; i++)
        {
            for (int j = 0; j < novo->colunas; j++)
            {
                novo->tabuleiroJogada[i][j] = jogadaAux.tabuleiroJogada[i][j];
            }
        }

        novo->prox = NULL;

        if (jogo->listaJogadas == NULL)
        {
            jogo->listaJogadas = novo;
            aux = jogo->listaJogadas;
        }
        else
        {
            aux->prox = novo;
            aux = aux->prox;

        }
    }

    jogo->tab_jogo.linhas = jogo->listaJogadas->linhas;
    jogo->tab_jogo.colunas = jogo->listaJogadas->colunas;

    jogo->tab_jogo.matriz = malloc(sizeof(char*) * jogo->listaJogadas->linhas);

    if (jogo->tab_jogo.matriz == NULL)
    {
        return 1;
    }

    for (int i = 0; i < jogo->listaJogadas->linhas; i++)
    {
        jogo->tab_jogo.matriz[i] = malloc(sizeof(char) * jogo->listaJogadas->colunas);

        if (jogo->tab_jogo.matriz[i] == NULL)
        {
            return 1;
        }
    }

    for (int i = 0; i < jogo->listaJogadas->linhas; i++)
    {
        for (int j = 0; j < jogo->listaJogadas->colunas; j++)
        {
            jogo->tab_jogo.matriz[i][j] = jogo->listaJogadas->tabuleiroJogada[i][j];
        }
    }

    fclose(f);
}

int passaTurno(int turno)
{
    if (turno)
        return 0;
    return 1;
}

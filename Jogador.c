#include "Jogador.h"

void inicia_jogador(pjogadores jogador, char id) {
    jogador->id = id;
    jogador->pedra = 1;
    jogador->linhas_colunas = 2;
}
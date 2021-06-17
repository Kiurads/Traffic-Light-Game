typedef struct jogador jogadores, * pjogadores;

struct jogador 
{
	char id;
	int pedra;
	int linhas_colunas;
};

void inicia_jogador(pjogadores jogador, char id);
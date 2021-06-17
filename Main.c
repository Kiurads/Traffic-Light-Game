#include <stdio.h>
#include <stdlib.h>
#include "Jogo.h"

int main() {
    int continuar = 1;
    int carregaJogo = 0;
    char resultado;

    FILE* f;

    if ((f = fopen("jogo.bin", "rb")) != NULL) {
        fclose(f);

        printf("Retomar jogo? (1 - Sim / 0 - Nao): ");
        scanf(" %d", &carregaJogo);
    }

    if (carregaJogo == 1)
    {
        resultado = joga(2);

        if (resultado == NULL)
        {
            return 1;
        }
    }

    do
    {
        printf("\n\tJogo do Semaforo\n\n");
        printf("1. Jogo contra computador\n");
        printf("2. Jogo com dois jogadores\n");
        printf("3. Regras\n");
        printf("0. Sair\n");

        scanf(" %d", &continuar);
        system("cls || clear");

        switch (continuar)
        {
        case 1:
            resultado = joga(1);

            if (resultado == NULL)
            {
                continuar = 0;
            }

            break;

        case 2:
            resultado = joga(0);

            if (resultado == NULL)
            {
                continuar = 0;
            }

            break;

        case 3:

            break;

        case 0:
            printf("Bye :(");
            break;

        default:
            printf("Digite uma opcao valida\n");
        }
    } while (continuar);
}
#include <stdio.h>
#include "disciplina.h"

int main() {

    Disciplina *lista = NULL;
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Inserir disciplina (final)\n");
        printf("2 - Listar disciplinas\n");
        printf("3 - Remover disciplina\n");
        printf("4 - Calcular média\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                lista = inserirFinal(lista);
                break;

            case 2:
                listar(lista);
                break;

            case 3:
                lista = remover(lista);
                break;

            case 4:
                calcularMedia(lista);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}
/**
 * @file main.c
 * @brief Ponto de entrada da aplicação de gerenciamento de alunos e disciplinas.
 * 
 * Esta é a função principal que inicializa o programa e coordena a execução
 * das operações disponíveis através de um menu interativo.
 * 
 * @author Daniel Costa Carvalho Martins
 * @date 02 - 04 - 2026
 */

#include <stdio.h>

#include "estruturas.h"

/**
 * main
 * 
 * Função principal do programa. Responsável por:
 * 1. Inicializar as estruturas de dados
 * 2. Apresentar o menu de opções
 * 3. Coordenar as operações solicitadas pelo usuário
 * 
 * @return EXIT_SUCCESS (0) se o programa terminou corretamente,
 *         EXIT_FAILURE (1) em caso de erro fatal.
 */
int main(void)
{
    /* Declara a lista de alunos que será gerenciada pelo programa */
    ListaAlunos lista;

    /* Configura a saída do console para exibir acentos corretamente */
    if (configurar_saida_portugues_brasil() == FALHA) {
        fprintf(stderr, "Aviso: Nao foi possivel configurar a saida em portugues do Brasil.\n");
    }

    /* Inicializa a lista de alunos em estado vazio */
    if (inicializar_lista_alunos(&lista) == FALHA) {
        fprintf(stderr, "Erro: Falha na inicializacao da lista de alunos.\n");
        return 1;
    }

    /* Exibe mensagem de boas-vindas e informações do programa */
    printf("============================================\n");
    printf("  Gerenciador de Alunos e Disciplinas\n");
    printf("  Trabalho de Estrutura de Dados 1\n");
    printf("============================================\n\n");

    printf("Sistema inicializado com sucesso.\n");
    printf("Capacidade maxima suportada: %d alunos.\n\n", MAX_ALUNOS);

    printf("Modulo da lista sequencial principal concluido.\n");
    printf("Etapas previstas para a integracao final do trabalho:\n");
    printf("- Integrar o menu principal as operacoes da lista de alunos.\n");
    printf("- Conectar a lista encadeada de disciplinas a cada registro de aluno.\n");
    printf("- Finalizar as rotinas de busca, exibicao e interacao com o usuario.\n");
    printf("- Realizar a validacao final do sistema em conjunto com a dupla.\n");

    return 0;
}

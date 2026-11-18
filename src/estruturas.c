/**
 * @file estruturas.c
 * @brief Implementação das funções de validação e inicialização de estruturas.
 * 
 * Este módulo fornece as implementações das variações de validação de dados
 * de entrada e inicialização da lista de alunos, garantindo a integridade
 * dos dados e seguindo boas práticas de C.
 * 
 * @author Daniel Costa Carvalho Martins
 * @date 02 - 04 - 2026
 */

#include <locale.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "estruturas.h"

/* ============================================================================
 * FUNÇÕES AUXILIARES INTERNAS
 * ============================================================================ */

/**
 * limpar_aluno
 *
 * Restaura os campos de um aluno para um estado neutro.
 */
static void limpar_aluno(Aluno *aluno)
{
    if (aluno == NULL) {
        return;
    }

    aluno->rgm = RGM_INVALIDO; // Define um RGM inválido para indicar que a posição está livre
    aluno->nome[0] = '\0'; // Define o nome como string vazia
    aluno->disciplinas = NULL; // Inicializa o apontador para a lista de disciplinas como NULL
}

/**
 * liberar_disciplinas
 *
 * Libera a memória eventualmente associada à lista de disciplinas.
 * Nesta etapa do trabalho, os alunos são mantidos sem disciplinas cadastradas,
 * mas a limpeza preventiva facilita a integração futura.
 */
static void liberar_disciplinas(Disciplina *disciplina)
{
    Disciplina *atual = disciplina; // Apontador para percorrer a lista encadeada de disciplinas

    while (atual != NULL) {
        Disciplina *proxima = atual->proxima; // Armazena o próximo elemento antes de liberar o atual
        free(atual); // Libera a memória do elemento atual
        atual = proxima; // Avança para o próximo elemento
    }
}

/**
 * encontrar_posicao_insercao
 *
 * Determina em qual índice um novo aluno deve ser inserido para preservar
 * a ordenação crescente por RGM.
 */
static int encontrar_posicao_insercao(const ListaAlunos *lista, int rgm)
{
    int indice = 0; // Inicia a busca a partir do primeiro elemento

    while (indice < lista->quantidade && lista->alunos[indice].rgm < rgm) {
        indice++; // Avança enquanto o RGM do aluno atual for menor que o RGM a ser inserido
    }

    return indice; // Retorna a posição onde o novo aluno deve ser inserido
}

/**
 * encontrar_posicao_por_rgm
 *
 * Procura a posição exata de um aluno na lista a partir do seu RGM.
 */
static int encontrar_posicao_por_rgm(const ListaAlunos *lista, int rgm)
{
    int indice;

    for (indice = 0; indice < lista->quantidade; indice++) { // Percorre a lista de alunos até encontrar o RGM ou atingir o final
        if (lista->alunos[indice].rgm == rgm) { // Verifica se o RGM do aluno atual corresponde ao RGM buscado
            return indice; // Retorna a posição do aluno encontrado
        }
    }

    return -1; // Retorna -1 se o aluno não for encontrado
}

/* ============================================================================
 * FUNÇÕES DE CONFIGURAÇÃO
 * ============================================================================ */

/**
 * configurar_saida_portugues_brasil
 * 
 * Configura a saída do programa para exibir caracteres acentuados do
 * português do Brasil corretamente no console.
 * 
 * Estratégia adotada:
 * - Usa a localidade padrão do ambiente
 * - Mantém uma implementação simples e portável
 * 
 * Complexidade: O(1) - constante, apenas chamadas de configuração do ambiente
 */
int configurar_saida_portugues_brasil(void)
{
    /* Usa apenas a localidade padrão do sistema para saída em português */
    if (setlocale(LC_ALL, "") == NULL) {
        return FALHA;
    }

    return SUCESSO;
}

/* ============================================================================
 * FUNÇÕES DE VALIDAÇÃO
 * ============================================================================ */

/**
 * rgm_eh_valido
 * 
 * Valida se o RGM (Registro Geral de Matrícula) atende aos critérios:
 * - Deve ser um número positivo (maior que zero)
 * - Valores negativos ou zero são considerados inválidos
 * 
 * Complexidade: O(1) - constante, apenas comparação numérica
 */
int rgm_eh_valido(int rgm)
{
    /* Verifica se o RGM é maior que zero */
    if (rgm > 0) {
        return SUCESSO;
    }

    return FALHA;
}

/**
 * nome_eh_valido
 * 
 * Valida se o nome atende aos critérios:
 * - Não pode ser NULL
 * - Não pode ser vazio (primeiro caractere não deve ser '\0')
 * - Deve ter pelo menos um caractere válido na primeira posição
 * 
 * Complexidade: O(1) - constante, apenas acesso ao primeiro caractere
 */
int nome_eh_valido(const char *nome)
{
    /* Valida se o apontador é nulo */
    if (nome == NULL) {
        return FALHA;
    }

    /* Valida se o nome não é uma string vazia */
    if (nome[0] != '\0') {
        return SUCESSO;
    }

    return FALHA;
}

/**
 * nota_eh_valida
 * 
 * Valida se a nota atende aos critérios:
 * - Deve estar no intervalo [0.0, 10.0]
 * - Valores fora deste intervalo são considerados inválidos
 * 
 * Complexidade: O(1) - constante, apenas comparações numéricas
 */
int nota_eh_valida(float nota)
{
    /* Verifica se a nota está no intervalo permitido */
    const float NOTA_MINIMA = 0.0f;
    const float NOTA_MAXIMA = 10.0f;

    if (nota >= NOTA_MINIMA && nota <= NOTA_MAXIMA) {
        return SUCESSO;
    }

    return FALHA;
}

/**
 * lista_esta_cheia
 * 
 * Verifica se a lista de alunos atingiu sua capacidade máxima.
 * 
 * Lógica:
 * - Se lista é NULL, considera-se um erro (retorna FALHA preventivamente)
 * - Se quantidade == MAX_ALUNOS, a lista está cheia
 * 
 * Complexidade: O(1) - constante, apenas acesso a campo da struct
 */
int lista_esta_cheia(const ListaAlunos *lista)
{
    /* Valida se o apontador é válido */
    if (lista == NULL) {
        return FALHA;
    }

    /* Compara a quantidade com a capacidade máxima */
    if (lista->quantidade >= MAX_ALUNOS) {
        return SUCESSO;
    }

    return FALHA;
}

/**
 * lista_esta_vazia
 * 
 * Verifica se a lista de alunos não contém nenhum aluno cadastrado.
 * 
 * Lógica:
 * - Se lista é NULL, considera-se um erro (retorna FALHA preventivamente)
 * - Se quantidade == 0, a lista está vazia
 * 
 * Complexidade: O(1) - constante, apenas acesso a campo da struct
 */
int lista_esta_vazia(const ListaAlunos *lista)
{
    /* Valida se o apontador é válido */
    if (lista == NULL) {
        return FALHA;
    }

    /* Verifica se não há alunos cadastrados */
    if (lista->quantidade == 0) {
        return SUCESSO;
    }

    return FALHA;
}

/* ============================================================================
 * FUNÇÕES DE INICIALIZAÇÃO
 * ============================================================================ */

/**
 * inicializar_lista_alunos
 * 
 * Prepara a lista de alunos para uso, zerando a contagem de alunos.
 * Esta função DEVE ser chamada uma única vez no início do programa antes
 * de realizar qualquer operação na lista.
 * 
 * Precondições:
 * - O apontador lista não pode ser NULL
 * 
 * Pós-condições:
 * - lista->quantidade será igual a 0
 * - A lista estará pronta para receber novos cadastros
 * 
 * Complexidade: O(1) - constante, apenas atribuição
 * 
 * Tratamento de erros:
 * - Retorna FALHA se lista é NULL
 * - Retorna SUCESSO se a inicialização foi bem-sucedida
 */
int inicializar_lista_alunos(ListaAlunos *lista)
{
    int indice;

    /* Valida se o apontador é válido */
    if (lista == NULL) {
        return FALHA;
    }

    /* Define a quantidade inicial de alunos como zero */
    lista->quantidade = 0;

    /* Limpa todas as posições da estrutura sequencial */
    for (indice = 0; indice < MAX_ALUNOS; indice++) { // Percorre o array de alunos para garantir que todas as posições estejam em um estado neutro
        limpar_aluno(&lista->alunos[indice]); // Garante que cada posição do array de alunos esteja em um estado neutro
    }

    return SUCESSO;
}

/* ============================================================================
 * FUNÇÕES DE MANUTENÇÃO DA LISTA SEQUENCIAL
 * ============================================================================ */

/**
 * inserir_aluno_ordenado
 *
 * Insere um novo aluno preservando a ordem crescente de RGM.
 * Não permite duplicidade de RGM e não manipula a lista de disciplinas nesta
 * etapa do projeto.
 *
 * Complexidade: O(n), devido ao possível deslocamento dos elementos.
 */
int inserir_aluno_ordenado(ListaAlunos *lista, int rgm, const char *nome)
{
    int indice;
    int posicao_insercao;

    if (lista == NULL || rgm_eh_valido(rgm) == FALHA || nome_eh_valido(nome) == FALHA) {
        return FALHA; // Valida os parâmetros de entrada para garantir que são adequados para a operação
    }

    if (lista_esta_cheia(lista) == SUCESSO) {
        return FALHA; // Verifica se a lista está cheia antes de tentar inserir
    }

    posicao_insercao = encontrar_posicao_insercao(lista, rgm); // Determina a posição onde o novo aluno deve ser inserido para manter a ordenação

    if (posicao_insercao < lista->quantidade && lista->alunos[posicao_insercao].rgm == rgm) {
        return FALHA; // Verifica se já existe um aluno com o mesmo RGM na posição de inserção, o que indicaria duplicidade
    }

    for (indice = lista->quantidade; indice > posicao_insercao; indice--) {
        lista->alunos[indice] = lista->alunos[indice - 1]; // Desloca os elementos para a direita para abrir espaço para o novo aluno
    }

    lista->alunos[posicao_insercao].rgm = rgm; // Insere o RGM do novo aluno na posição determinada
    strncpy(lista->alunos[posicao_insercao].nome, nome, TAM_MAX_NOME_ALUNO - 1); // Copia o nome do aluno para a posição determinada, garantindo que não ultrapasse o tamanho máximo
    lista->alunos[posicao_insercao].nome[TAM_MAX_NOME_ALUNO - 1] = '\0'; // Garante que a string do nome seja terminada corretamente
    lista->alunos[posicao_insercao].disciplinas = NULL; // Inicializa o apontador para a lista de disciplinas como NULL, indicando que o aluno ainda não tem disciplinas cadastradas
    lista->quantidade++; // Incrementa a quantidade de alunos após a inserção

    return SUCESSO;
}

/**
 * remover_aluno_por_rgm
 *
 * Remove um aluno localizado pelo RGM e compacta a lista sequencial.
 *
 * Complexidade: O(n), devido ao deslocamento dos elementos após a remoção.
 */
int remover_aluno_por_rgm(ListaAlunos *lista, int rgm)
{
    int indice;
    int posicao_remocao;

    if (lista == NULL || rgm_eh_valido(rgm) == FALHA) {
        return FALHA; // Valida os parâmetros de entrada para garantir que são adequados para a operação
    }

    if (lista_esta_vazia(lista) == SUCESSO) {
        return FALHA; // Verifica se a lista está vazia antes de tentar remover
    }

    posicao_remocao = encontrar_posicao_por_rgm(lista, rgm);
    if (posicao_remocao < 0) {
        return FALHA; // Verifica se o aluno com o RGM especificado foi encontrado na lista
    }

    liberar_disciplinas(lista->alunos[posicao_remocao].disciplinas); // Libera a memória alocada para as disciplinas do aluno

    for (indice = posicao_remocao; indice < lista->quantidade - 1; indice++) {
        lista->alunos[indice] = lista->alunos[indice + 1]; // Desloca os elementos para a esquerda para preencher o espaço do aluno removido
    }

    lista->quantidade--; // Decrementa a quantidade de alunos após a remoção
    limpar_aluno(&lista->alunos[lista->quantidade]); // Limpa a última posição da lista após a remoção

    return SUCESSO;
}

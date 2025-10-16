#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define o número máximo de componentes que a torre pode ter.
#define MAX_COMPONENTES 20

// Variáveis globais para contar operações de desempenho.
// Usamos long long para evitar estouro em listas maiores ou algoritmos ineficientes.
long long int comparacoes = 0;
long long int trocas = 0;

//======================================================================
// ESTRUTURA DE DADOS (STRUCT)
//======================================================================

/**
 * @brief Define a estrutura de um componente da torre.
 * Contém nome, tipo e um nível de prioridade para a montagem.
 */
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;


//================== INICIO PROTÓTIPO INDÍCE FUNÇÕES============================//

// --- Funções de Interface e Utilitários ---
void limparBufferEntrada();
void pausa();
void mostrarComponentes(const Componente torre[], int n);
void adicionarComponente(Componente torre[], int *n, int *ordenadoPorNome);

// --- Algoritmos de Ordenação ---
void bubbleSortNome(Componente torre[], int n);
void insertionSortTipo(Componente torre[], int n);
void selectionSortPrioridade(Componente torre[], int n);

// --- Algoritmo de Busca ---
int buscaBinariaPorNome(const Componente torre[], int n, const char* nomeChave);

// --- Função para Medição de Desempenho ---
void medirDesempenhoOrdenacao(void (*algoritmo)(Componente[], int), Componente torre[], int n);

int main() {
   Componente torre[MAX_COMPONENTES];
    int numComponentes = 0;
    // Flag crucial para garantir que a busca binária só rode no cenário correto.
    int ordenadoPorNome = 0;
    int opcao;

    printf("====================================================\n");
    printf("        SIMULADOR DE MONTAGEM: TORRE DE FUGA        \n");
    printf("====================================================\n");
    printf("Sua missão: priorizar e montar os componentes para escapar!\n");

    do {
        printf("\n-------------------[ MENU PRINCIPAL ]-------------------\n");
        printf("1. Adicionar Componente\n");
        printf("2. Listar Componentes Atuais\n");
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Buscar Componente-Chave por NOME (Busca Binaria)\n");
        printf("0. Sair\n");
        printf("------------------------------------------------------\n");
        printf("Escolha sua estratégia: ");

        scanf("%d", &opcao);
        limparBufferEntrada();
        switch (opcao) {
            case 1:
                adicionarComponente(torre, &numComponentes, &ordenadoPorNome);
                break;
            case 2:
                mostrarComponentes(torre, numComponentes);
                break;
            case 3:
                printf("\nIniciando ordenação por NOME com Bubble Sort...\n");
                medirDesempenhoOrdenacao(bubbleSortNome, torre, numComponentes);
                ordenadoPorNome = 1; // A torre agora está ordenada por nome.
                mostrarComponentes(torre, numComponentes);
                break;
            case 4:
                printf("\nIniciando ordenação por TIPO com Insertion Sort...\n");
                medirDesempenhoOrdenacao(insertionSortTipo, torre, numComponentes);
                ordenadoPorNome = 0; // A ordenação por tipo desfaz a ordenação por nome.
                mostrarComponentes(torre, numComponentes);
                break;
            case 5:
                printf("\nIniciando ordenação por PRIORIDADE com Selection Sort...\n");
                medirDesempenhoOrdenacao(selectionSortPrioridade, torre, numComponentes);
                ordenadoPorNome = 0; // A ordenação por prioridade desfaz a ordenação por nome.
                mostrarComponentes(torre, numComponentes);
                break;
            case 6:
                if (!ordenadoPorNome) {
                    printf("\n[ALERTA!] A busca binária por nome exige que os componentes\n");
                    printf("sejam ordenados por NOME primeiro. Use a opção 3.\n");
                } else {
                    char nomeChave[30];
                    printf("\nDigite o nome do componente-chave para buscar: ");
                    fgets(nomeChave, sizeof(nomeChave), stdin);
                    nomeChave[strcspn(nomeChave, "\n")] = 0;

                    comparacoes = 0; // Zera o contador para a busca
                    int indice = buscaBinariaPorNome(torre, numComponentes, nomeChave);

                    printf("\n--- Resultado da Busca Binária ---\n");
                    if (indice != -1) {
                        printf("Componente-chave \"%s\" ENCONTRADO na posição %d!\n", nomeChave, indice);
                        printf("Montagem da torre pode ser iniciada!\n");
                    } else {
                        printf("Componente-chave \"%s\" NÃO FOI ENCONTRADO!\n", nomeChave);
                    }
                    printf("Número de comparações na busca: %lld\n", comparacoes);
                }
                break;
            case 0:
                printf("\nDesligando sistema. Boa sorte na fuga!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }
        if (opcao != 0) pausa();

    } while (opcao != 0);

    return 0;
    
}


//================== INICIO FUNÇÕES ============================//

// --- Funções de Interface e Utilitários ---

/**
 * @brief Limpa o buffer de entrada do teclado (stdin).
 * Essencial para ser usado após scanf para consumir o '\n' restante.
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Pausa a execução do programa até que o usuário pressione ENTER.
 */
void pausa() {
    printf("\nPressione [ENTER] para continuar...");
    getchar();
}

/**
 * @brief Exibe todos os componentes da torre de forma formatada.
 * @param torre O array de componentes.
 * @param n O número de componentes atualmente no array.
 */
void mostrarComponentes(const Componente torre[], int n) {
    printf("\n[ STATUS ATUAL DA TORRE DE FUGA - %d/%d Componentes ]\n", n, MAX_COMPONENTES);
    if (n == 0) {
        printf("  -> Nenhum componente cadastrado.\n");
        return;
    }
    printf("------------------------------------------------------------\n");
    printf("  %-25s | %-15s | %s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("  %-25s | %-15s | %d\n", torre[i].nome, torre[i].tipo, torre[i].prioridade);
    }
    printf("------------------------------------------------------------\n");
}

/**
 * @brief Adiciona um novo componente ao array da torre.
 * @param torre O array de componentes.
 * @param n Ponteiro para o contador de componentes.
 * @param ordenadoPorNome Ponteiro para a flag de ordenação por nome.
 */
void adicionarComponente(Componente torre[], int *n, int *ordenadoPorNome) {
    if (*n >= MAX_COMPONENTES) {
        printf("\n[ERRO] Limite máximo de componentes atingido!\n");
        return;
    }

    printf("\n--- Adicionando Novo Componente (%d/%d) ---\n", *n + 1, MAX_COMPONENTES);
    printf("Nome do componente: ");
    fgets(torre[*n].nome, sizeof(torre[*n].nome), stdin);
    torre[*n].nome[strcspn(torre[*n].nome, "\n")] = 0;

    printf("Tipo (controle, suporte, propulsao, etc.): ");
    fgets(torre[*n].tipo, sizeof(torre[*n].tipo), stdin);
    torre[*n].tipo[strcspn(torre[*n].tipo, "\n")] = 0;

    printf("Prioridade (1 a 10): ");
    scanf("%d", &torre[*n].prioridade);
    limparBufferEntrada();

    (*n)++;
    *ordenadoPorNome = 0; // Adicionar um novo item quebra a ordenação.
    printf("\nComponente adicionado com sucesso!\n");
}

// --- Algoritmos de Ordenação ---

/**
 * @brief Ordena os componentes por NOME usando Bubble Sort.
 */
void bubbleSortNome(Componente torre[], int n) {
    if (n < 2) return;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                Componente temp = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = temp;
                trocas++;
            }
        }
    }
}

/**
 * @brief Ordena os componentes por TIPO usando Insertion Sort.
 */
void insertionSortTipo(Componente torre[], int n) {
    if (n < 2) return;
    for (int i = 1; i < n; i++) {
        Componente chave = torre[i];
        int j = i - 1;
        while (j >= 0 && (comparacoes++, strcmp(torre[j].tipo, chave.tipo) > 0)) {
            torre[j + 1] = torre[j];
            j = j - 1;
            trocas++;
        }
        torre[j + 1] = chave;
        // Conta a troca final para colocar a chave na posição certa
        if (j != i - 1) trocas++;
    }
}

/**
 * @brief Ordena os componentes por PRIORIDADE (int) usando Selection Sort.
 */
void selectionSortPrioridade(Componente torre[], int n) {
    if (n < 2) return;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (torre[j].prioridade < torre[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Componente temp = torre[min_idx];
            torre[min_idx] = torre[i];
            torre[i] = temp;
            trocas++;
        }
    }
}

// --- Algoritmo de Busca ---

/**
 * @brief Busca um componente por nome usando Busca Binária.
 * @param torre O array de componentes (DEVE ESTAR ORDENADO POR NOME).
 * @return O índice do componente se encontrado, -1 caso contrário.
 */
int buscaBinariaPorNome(const Componente torre[], int n, const char* nomeChave) {
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        comparacoes++;
        int meio = inicio + (fim - inicio) / 2;
        int res = strcmp(torre[meio].nome, nomeChave);

        if (res == 0) return meio; // Encontrado
        if (res < 0) inicio = meio + 1; // Busca na metade direita
        else fim = meio - 1; // Busca na metade esquerda
    }
    return -1; // Não encontrado
}

// --- Função para Medição de Desempenho ---

/**
 * @brief Mede o tempo de execução de um algoritmo de ordenação e exibe as métricas.
 * @param algoritmo Ponteiro para a função de ordenação a ser executada.
 * @param torre O array de componentes.
 * @param n O número de componentes.
 */
void medirDesempenhoOrdenacao(void (*algoritmo)(Componente[], int), Componente torre[], int n) {
    // Zera os contadores antes de cada execução
    comparacoes = 0;
    trocas = 0;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    algoritmo(torre, n); // Executa o algoritmo passado como parâmetro
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\n--- Análise de Desempenho ---\n");
    printf("Tempo de execução: %f segundos\n", cpu_time_used);
    printf("Número de comparações: %lld\n", comparacoes);
    printf("Número de trocas: %lld\n", trocas);
    printf("-----------------------------\n");
}
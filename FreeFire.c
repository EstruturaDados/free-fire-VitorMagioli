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
    printf("======================== SIMULAÇÃO FREE FIRE ========================\n");
    printf("Seja bem-vindo ao jogo de simulação Free Fire. Nessa fase, adicione os itens recolhidos\n");
    printf("Você pode listar os itens recolhidos.\n");

    listaItens mochilaVetor;
    MochilaListaEncadeada mochilaLista;

    // CORREÇÃO: Chamando a função correta para o vetor.
    inicializarVetor(&mochilaVetor);
    
    // CORREÇÃO: A lista encadeada é inicializada como NULL, não com uma função.
    mochilaLista = NULL;

    int opcao = -1;

    do {
        printf("\n====== MENU PRINCIPAL ======\n");
        printf("Escolha a estrutura de dados para gerenciar:\n");
        printf("1. Mochila com Vetor (Lista Sequencial)\n");
        printf("2. Mochila com Lista Encadeada\n");
        printf("0. Sair do Simulador\n");
        printf("============================================\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparbufferentrada();

        switch (opcao) {
            case 1:
                menuVetor(&mochilaVetor);
                break;
            case 2:
                menuLista(&mochilaLista);
                break;
            case 0:
                printf("\nSaindo do simulador...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

// Menu de operações para a mochila com vetor
void menuVetor(listaItens *mochila) {
    int opcao;
    Item item; // Usaremos uma variável 'item' temporária para coletar dados

    do {
        printf("\n---[ Menu Vetor ]---\n");
        // CORREÇÃO: Chamando a função de listar específica do vetor
        listarItensVetor(mochila);
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Buscar Item (Sequencial)\n");
        printf("4. Ordenar Itens (para Busca Binaria)\n");
        printf("5. Buscar Item (Binaria)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparbufferentrada();

        switch (opcao) {
            case 1:
                printf("Nome do item: ");
                fgets(item.nome, 30, stdin);
                item.nome[strcspn(item.nome, "\n")] = 0;
                printf("Tipo do item: ");
                fgets(item.tipo, 20, stdin);
                item.tipo[strcspn(item.tipo, "\n")] = 0;
                printf("Quantidade: ");
                scanf("%d", &item.quantidade);
                limparbufferentrada();
                // CORREÇÃO: Passando a struct 'item' inteira para a função correta
                inserirItemVetor(mochila, item);
                pausa();
                break;
            case 2:
                if (mochila->total > 0) {
                    printf("Nome do item a remover: ");
                    fgets(item.nome, 30, stdin);
                    item.nome[strcspn(item.nome, "\n")] = 0;
                    removerItemVetor(mochila, item.nome);
                } else {
                    printf("\nMochila vazia, nada para remover.\n");
                }
                pausa();
                break;
            case 3:
                if (mochila->total > 0) {
                    printf("Nome do item a buscar: ");
                    fgets(item.nome, 30, stdin);
                    item.nome[strcspn(item.nome, "\n")] = 0;
                    comparacoes = 0;
                    int pos = buscarSequencialVetor(mochila, item.nome);
                    printf("\n--- Resultado da Busca Sequencial ---\n");
                    if (pos != -1) {
                        printf("Item encontrado na posicao %d!\n", pos);
                    } else {
                        printf("Item nao encontrado.\n");
                    }
                    printf("Numero de comparacoes: %ld\n", comparacoes);
                } else {
                    printf("\nMochila vazia, nada para buscar.\n");
                }
                pausa();
                break;
            case 4:
                ordenarVetor(mochila);
                pausa();
                break;
            case 5:
                if (mochila->estaOrdenado) {
                    if (mochila->total > 0) {
                        printf("Nome do item a buscar (binaria): ");
                        fgets(item.nome, 30, stdin);
                        item.nome[strcspn(item.nome, "\n")] = 0;
                        comparacoes = 0;
                        int pos = buscarBinariaVetor(mochila, item.nome);
                        printf("\n--- Resultado da Busca Binaria ---\n");
                        if (pos != -1) {
                            printf("Item encontrado na posicao %d!\n", pos);
                        } else {
                            printf("Item nao encontrado.\n");
                        }
                        printf("Numero de comparacoes: %ld\n", comparacoes);
                    } else {
                        printf("\nMochila vazia, nada para buscar.\n");
                    }
                } else {
                    printf("\n[ATENCAO] O vetor nao esta ordenado! Use a opcao 4 primeiro.\n");
                }
                pausa();
                break;
            case 0: break;
            default:
                printf("\nOpcao invalida!\n");
                pausa();
                break;
        }
    } while (opcao != 0);
}

// Menu de operações para a mochila com lista encadeada
void menuLista(MochilaListaEncadeada *mochila) {
    int opcao;
    Item item;

    do {
        printf("\n---[ Menu Lista Encadeada ]---\n");
        // CORREÇÃO: Chamando a função correta para listar itens da lista encadeada.
        listarItensListaEncadeada(mochila);
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Buscar Item (Sequencial)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparbufferentrada();

        switch (opcao) {
            case 1:
                printf("Nome do item: ");
                fgets(item.nome, 30, stdin);
                item.nome[strcspn(item.nome, "\n")] = 0;
                printf("Tipo do item: ");
                fgets(item.tipo, 20, stdin);
                item.tipo[strcspn(item.tipo, "\n")] = 0;
                printf("Quantidade: ");
                scanf("%d", &item.quantidade);
                limparbufferentrada();
                // CORREÇÃO: Chamando a função correta para inserir na lista encadeada.
                inserirItemListaEncadeada(mochila, item);
                pausa();
                break;
            case 2:
                if (*mochila != NULL) {
                    printf("Nome do item a remover: ");
                    fgets(item.nome, 30, stdin);
                    item.nome[strcspn(item.nome, "\n")] = 0;
                    // CORREÇÃO: Chamando a função correta para remover da lista encadeada.
                    removerItemListaEncadeada(mochila, item.nome);
                } else {
                    printf("\nMochila vazia, nada para remover.\n");
                }
                pausa();
                break;
            case 3:
                if (*mochila != NULL) {
                    printf("Nome do item a buscar: ");
                    fgets(item.nome, 30, stdin);
                    item.nome[strcspn(item.nome, "\n")] = 0;
                    comparacoes = 0;
                    // CORREÇÃO: Chamando a função correta para buscar na lista encadeada.
                    No *encontrado = buscarSequencialListaEncadeada(mochila, item.nome);
                    printf("\n--- Resultado da Busca Sequencial ---\n");
                    if (encontrado != NULL) {
                        printf("Item encontrado!\n");
                        printf("   Nome: %s, Tipo: %s, Qtd: %d\n", encontrado->dados.nome, encontrado->dados.tipo, encontrado->dados.quantidade);
                    } else {
                        printf("Item nao encontrado.\n");
                    }
                    printf("Numero de comparacoes: %ld\n", comparacoes);
                } else {
                    printf("\nMochila vazia, nada para buscar.\n");
                }
                pausa();
                break;
            case 0: break;
            default:
                printf("\nOpcao invalida!\n");
                pausa();
                break;
        }
    } while (opcao != 0);
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
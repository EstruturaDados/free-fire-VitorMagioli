#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ITENS 10

long int comparacoes;

// Estrutura para cada item inserido (Sem alterações, está perfeita)
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura para a mochila com vetor (Sem alterações, está perfeita)
typedef struct {
    Item itens[ITENS];
    int total;
    int estaOrdenado;
} listaItens;

// Estrutura para o Nó da lista encadeada (Sem alterações, está perfeita)
typedef struct No {
    Item dados;
    struct No *proximo;
} No;

typedef No* MochilaListaEncadeada;

//================== INICIO PROTÓTIPO INDÍCE FUNÇÕES============================//

// --- Funções Auxiliares ---
void limparbufferentrada();
void pausa();

// --- Funções para o VETOR ---
// CORREÇÃO: Renomeando todas as funções do vetor para serem únicas.
void inicializarVetor(listaItens *lista);
void inserirItemVetor(listaItens *lista, Item novoItem);
int removerItemVetor(listaItens *lista, const char *nome);
void listarItensVetor(const listaItens *lista);
int buscarSequencialVetor(const listaItens *lista, const char *nome);
void ordenarVetor(listaItens *lista);
int buscarBinariaVetor(const listaItens *lista, const char *nome);

// --- Funções para a LISTA ENCADEADA ---
// CORREÇÃO: Adicionando protótipos para as funções da lista com nomes únicos.
void inserirItemListaEncadeada(MochilaListaEncadeada *mochila, Item novoItem);
int removerItemListaEncadeada(MochilaListaEncadeada *mochila, const char *nome);
void listarItensListaEncadeada(const MochilaListaEncadeada *mochila);
No* buscarSequencialListaEncadeada(const MochilaListaEncadeada *mochila, const char *nome);

// --- Menus ---
void menuVetor(listaItens *mochila);
void menuLista(MochilaListaEncadeada *mochila);


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

void limparbufferentrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausa() {
    printf("\nPressione [ENTER] para continuar...");
    getchar(); // getchar() é mais simples que limpar o buffer aqui.
}

//======================================================================
// IMPLEMENTAÇÃO COM VETOR (LISTA SEQUENCIAL)
//======================================================================

// CORREÇÃO: Nome alterado para inicializarVetor.
void inicializarVetor(listaItens *lista) {
    lista->total = 0;
    lista->estaOrdenado = 0;
}

// CORREÇÃO: Nome alterado e parâmetro de 'Item' inteiro.
void inserirItemVetor(listaItens *lista, Item novoItem) {
    if (lista->total >= ITENS) {
        printf("\nErro! A lista está cheia.\n");
        return;
    }
    lista->itens[lista->total] = novoItem;
    lista->total++;
    lista->estaOrdenado = 0;
    printf("\nItem \"%s\" inserido com sucesso!\n", novoItem.nome);
}

// CORREÇÃO: Nome alterado, retorna status e usa busca sequencial.
int removerItemVetor(listaItens *lista, const char *nome) {
    int pos = buscarSequencialVetor(lista, nome);

    if (pos == -1) {
        printf("\n[ERRO] O nome digitado não foi encontrado\n");
        return 0;
    }

    for (int i = pos; i < lista->total - 1; i++) {
        lista->itens[i] = lista->itens[i + 1];
    }
    lista->total--;
    lista->estaOrdenado = 0;
    printf("\nItem \"%s\" removido com sucesso!\n", nome);
    return 1;
}

// CORREÇÃO: Nome alterado e formatação melhorada.
void listarItensVetor(const listaItens *lista) {
    printf("Itens na Mochila (Vetor) [%d/%d]:\n", lista->total, ITENS);
    if (lista->total == 0) {
        printf(" -> Mochila vazia.\n");
        return;
    }
    for (int i = 0; i < lista->total; i++) {
        printf(" -> Nome: %-20s | Tipo: %-15s | Qtd: %d\n", lista->itens[i].nome, lista->itens[i].tipo, lista->itens[i].quantidade);
    }
}

// CORREÇÃO: Nova função de busca que retorna int e conta comparações.
int buscarSequencialVetor(const listaItens *lista, const char *nome) {
    for (int i = 0; i < lista->total; i++) {
        comparacoes++;
        if (strcmp(lista->itens[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// CORREÇÃO: NOVA FUNÇÃO - Ordenação com Selection Sort.
void ordenarVetor(listaItens *lista) {
    if(lista->total < 2) return;
    for (int i = 0; i < lista->total - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < lista->total; j++) {
            if (strcmp(lista->itens[j].nome, lista->itens[min_idx].nome) < 0) {
                min_idx = j;
            }
        }
        Item temp = lista->itens[min_idx];
        lista->itens[min_idx] = lista->itens[i];
        lista->itens[i] = temp;
    }
    lista->estaOrdenado = 1;
    printf("\nMochila (vetor) ordenada por nome!\n");
}

// CORREÇÃO: NOVA FUNÇÃO - Busca Binária.
int buscarBinariaVetor(const listaItens *lista, const char *nome) {
    int inicio = 0, fim = lista->total - 1;
    while (inicio <= fim) {
        comparacoes++;
        int meio = inicio + (fim - inicio) / 2;
        int res = strcmp(lista->itens[meio].nome, nome);
        if (res == 0) return meio;
        if (res < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}


//======================================================================
// IMPLEMENTAÇÃO COM LISTA ENCADEADA
//======================================================================

// CORREÇÃO: Nome alterado.
void inserirItemListaEncadeada(MochilaListaEncadeada *mochila, Item novoItem) {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\n[ERRO FATAL] Falha de memoria!\n");
        exit(1);
    }
    novoNo->dados = novoItem;
    novoNo->proximo = *mochila;
    *mochila = novoNo;
    printf("\nItem \"%s\" inserido na lista encadeada com sucesso!\n", novoItem.nome);
}

// CORREÇÃO: Nome alterado.
void listarItensListaEncadeada(const MochilaListaEncadeada *mochila) {
    printf("Itens na Mochila (Lista Encadeada):\n");
    if (*mochila == NULL) {
        printf(" -> Mochila vazia.\n");
        return;
    }
    No *atual = *mochila;
    while (atual != NULL) {
        printf(" -> Nome: %-20s | Tipo: %-15s | Qtd: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

// CORREÇÃO: Nome alterado.
No* buscarSequencialListaEncadeada(const MochilaListaEncadeada *mochila, const char *nome) {
    No *atual = *mochila;
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// CORREÇÃO: Nome alterado.
int removerItemListaEncadeada(MochilaListaEncadeada *mochila, const char *nome) {
    No *atual = *mochila;
    No *anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("\n[ERRO] Item \"%s\" nao encontrado na lista.\n", nome);
        return 0;
    }
    if (anterior == NULL) {
        *mochila = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("\nItem \"%s\" removido da lista encadeada com sucesso!\n", nome);
    return 1;
}

// Struct Item:
// Representa um componente com nome, tipo, total e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (total atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, total e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a total de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do  buscado.
// Caso contrário, informa que não encoitemntrou o item.

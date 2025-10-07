#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ITENS 10

typedef struct 
{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;


//================== INICIO PROTÓTIPO INDÍCE FUNÇÕES============================//

void exibirMenu();
void inicializarLista(Item *lista);

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair
    printf("======================== SIMULAÇÃO FREE FIRE ========================\n");
    printf("Seja bem-vindo ao jogo de simulação Free Fire. Nessa fase, encontre os\n");
    printf("Você pode listar os itens recolhidos.\n");
    exibirMenu();

    Item novoItem;
    inicializarLista(&novoItem);

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

//================== INICIO FUNÇÕES ============================//
//Exibe menu principal
void exibirMenu(){
    printf("1. Adicionar um Item: \n");
    printf("2. Remover um Item: \n");
    printf("3. Listar todos os Itens: \n");
    printf("4. Buscar Item: \n");
    printf("0. Sair\n");
}

//inicializa o vetor
void inicializarLista(Item *lista){
    lista->quantidade = 0;
}

void inserirItemLista(Item *lista, const char *nome, const char *tipo){
    if (lista->quantidade == ITENS){
        printf("Erro! A lista está cheia. Não é possível inserir mais itens.\n");
        printf("Caso queira inserir um novo item, remova um existente.\n");
        return;
    }
    strcpy(lista->nome[lista->quantidade], nome);
    strcpy(lista->tipo[lista->quantidade], tipo);
    lista->quantidade++;
    printf("Item inserido com sucesso!");
}


// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

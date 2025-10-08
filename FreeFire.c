#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ITENS 10

//Estrutura para cada item inserido
typedef struct 
{
    char nome[30];
    char tipo[20];
} Item;

typedef struct
{
    Item itens[ITENS];
    int quantidade;
}listaItens;


//================== INICIO PROTÓTIPO INDÍCE FUNÇÕES============================//

void exibirMenu();
void inicializarLista(listaItens *lista);
void inserirItemLista(listaItens *lista, const char *nome, const char *tipo);
void removerItensLista(listaItens *lista, const char *nome);
void listarItens(const listaItens *lista);
void buscarItemPorNome(const listaItens *lista, const char *nome);
void limparbufferentrada();

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair
    printf("======================== SIMULAÇÃO FREE FIRE ========================\n");
    printf("Seja bem-vindo ao jogo de simulação Free Fire. Nessa fase, adicione os itens recolhidos\n");
    printf("Você pode listar os itens recolhidos.\n");

    listaItens novoItem;
    inicializarLista(&novoItem);

    int opcao = -1;

    do
    {
        exibirMenu();
        printf("\nO que você deseja fazer? ");
        scanf("%d", &opcao);
        limparbufferentrada();

        switch (opcao)
        {
        case 1: {
            //-----------INSERINDO ITENS NA LISTA//-----------
            char nomeItem[30];
            char tipoItem[20];

            printf("\nNome do item recolhido: ");
            fgets(nomeItem, sizeof(nomeItem), stdin);
            nomeItem[strcspn(nomeItem, "\n")] = '\0';

            printf("\nTipo do item recolhido: ");
            fgets(tipoItem, sizeof(tipoItem), stdin);
            tipoItem[strcspn(tipoItem, "\n")] ='\0';
            printf("========================\n\n");
            inserirItemLista(&novoItem, nomeItem, tipoItem);
            printf("\nPressione [ENTER] para continuar...");
            getchar();
            break;
        }

        case 2:{
            char apagar [30];
            printf("\nQual item você deseja remover? ");
            fgets(apagar, sizeof(apagar), stdin);
            apagar[strcspn(apagar, "\n")] ='\0';
            removerItensLista(&novoItem, apagar);
            printf("\nPressione [ENTER] para continuar...");
            getchar();
            break;
        }

        case 3: {
            listarItens(&novoItem);
            printf("Pressione [ENTER] para continuar...");
            getchar();
            break;
        }

        case 4: {
            char busca[30];

            printf("========================\n");
            printf("==== BUSCA DE ITENS ====\n");
            printf("========================\n");
            printf("\nDigite o NOME do item: ");
            fgets(busca, sizeof(busca), stdin);
            busca[strcspn(busca, "\n")] = '\0';

            buscarItemPorNome(&novoItem, busca);
            printf("Pressione [ENTER] para continuar...");
            getchar();
            break;
        }

        case 0:
            printf("Saindo do jogo...\n");
            break;

        default:
            printf("[ERRO] Opção inválida!\n");
            break;
        }

    } while (opcao != 0);

    

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    return 0;
}

//================== INICIO FUNÇÕES ============================//
//Exibe menu principal
void exibirMenu(){
    printf("1. Adicionar um Item \n");
    printf("2. Remover um Item \n");
    printf("3. Listar todos os Itens \n");
    printf("4. Buscar Item \n");
    printf("0. Sair\n");
}

//inicializa o vetor
void inicializarLista(listaItens *lista){
    lista->quantidade = 0;
}

//insere itens no array estático
void inserirItemLista(listaItens *lista, const char *nome, const char *tipo){
    if (lista->quantidade == ITENS){
        printf("Erro! A lista está cheia. Não é possível inserir mais itens.\n");
        printf("Caso queira inserir um novo item, remova um existente.\n\n");
        return;
    }
    strcpy(lista->itens[lista->quantidade].nome, nome);
    strcpy(lista->itens[lista->quantidade].tipo, tipo);
    lista->quantidade++;
    printf("\nItem inserido com sucesso!\n\n");
    printf("========================\n\n");
}

void removerItensLista(listaItens *lista, const char *nome){
    int pos = -1;

    for(int i = 0; i < lista->quantidade; i++){
        if(strcmp(lista->itens[i].nome, nome) == 0){
            pos = i;
            break;
        }
    }

    if (pos == -1){
        printf("\n[ERRO] O nome digitado não foi encontrado\n");
        return;
    }

    for(int i = pos; i < lista->quantidade -1; i++){
        lista->itens[i] = lista->itens [i+1];
    }
    lista->quantidade--;
    printf("\nItem %s removido com sucesso!\n\n", nome);
    printf("========================\n\n");
}

void listarItens(const listaItens *lista){
    if(lista->quantidade == 0){
        printf("Não há itens na lista! Por favor, cadastre os itens.\n");
        printf("========================\n\n");
        return;
    }
    printf("========================\n\n");
    printf("Itens guardados: \n");
    for(int i = 0; i < lista->quantidade; i++){
        printf("Nome: %s | Tipo: %s\n", lista->itens[i].nome, lista->itens[i].tipo);
    }
    printf("========================\n\n");
}

void buscarItemPorNome(const listaItens *lista, const char *nome){

    int encontrado = 0;

    for(int i = 0; i < lista->quantidade; i++){
        if(strcmp(lista->itens[i].nome, nome) == 0){
            printf("Item: %s | Tipo: %s\n", lista->itens[i].nome, lista->itens[i].tipo);
            encontrado = 1;
            break;
        }
    }
    if (encontrado == 0){
        printf("O item ''%s'' não foi encontrado!", nome);
    }
}

void limparbufferentrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

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
// Se encontrar, exibe os dados do  buscado.
// Caso contrário, informa que não encoitemntrou o item.

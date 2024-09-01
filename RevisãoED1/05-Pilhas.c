#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura Node, que representa um nó de uma lista duplamente encadeada.
typedef struct Node
{
    int data;             // Armazena o valor do nó.
    struct Node *next;    // Ponteiro para o próximo nó na lista.
    struct Node *prev;    // Ponteiro para o nó anterior na lista.
} Node;

// Ponteiro global que aponta para o início da lista.
Node *head = NULL;

// Função para inserir um valor no início da lista.
void insertFront(int value)
{
    // Aloca memória para um novo nó.
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    // Inicializa o novo nó com o valor fornecido e ajusta os ponteiros.
    newNode->data = value;
    newNode->next = head;  // O próximo nó do novo nó será o nó atualmente no início da lista.
    newNode->prev = NULL;  // O nó anterior do novo nó será NULL, pois ele será o primeiro nó.

    // Se a lista não estiver vazia, ajusta o ponteiro anterior do antigo primeiro nó.
    if (head != NULL)
        head->prev = newNode;

    // Atualiza o ponteiro head para apontar para o novo nó.
    head = newNode;
}

// Função para deletar um nó específico da lista.
void deleteNode(Node *node)
{
    // Se o nó a ser deletado for o primeiro da lista, ajusta o ponteiro head.
    if (node == head)
        head = node->next;

    // Ajusta o ponteiro prev do nó seguinte, se existir.
    if (node->next != NULL)
        node->next->prev = node->prev;

    // Ajusta o ponteiro next do nó anterior, se existir.
    if (node->prev != NULL)
        node->prev->next = node->next;

    // Libera a memória alocada para o nó.
    free(node);
}

// Função para imprimir todos os elementos da lista.
void printList()
{
    Node *temp = head;

    // Itera sobre a lista e imprime os valores de cada nó.
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Função para buscar um valor específico na lista.
void buscarValor(int value)
{
    Node *temp = head;

    // Itera sobre a lista para encontrar o valor.
    while (temp != NULL)
    {
        if (temp->data == value)
        {
            // Valor encontrado, imprime as informações do nó atual, anterior e próximo.
            printf("Valor %d encontrado.\n", value);
            
            if (temp->prev != NULL)
                printf("Anterior: %d\n", temp->prev->data);
            else
                printf("Anterior: NULL\n");

            if (temp->next != NULL)
                printf("Próximo: %d\n", temp->next->data);
            else
                printf("Próximo: NULL\n");

            return;
        }
        temp = temp->next;
    }

    // Se o valor não for encontrado, imprime mensagem informando.
    printf("Valor %d não encontrado.\n", value);
}

// Função principal que fornece um menu para o usuário interagir com a lista.
int main()
{
    int escolha, valor;

    // Loop infinito para manter o programa rodando até que o usuário escolha sair.
    while (1)
    {
        // Menu de opções.
        printf("1. Inserir valor na lista\n");
        printf("2. Buscar valor na lista\n");
        printf("3. Imprimir lista\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Processa a escolha do usuário.
        switch (escolha)
        {
        case 1:
            // Inserir um valor no início da lista.
            printf("Insira o valor a ser adicionado: ");
            scanf("%d", &valor);
            insertFront(valor);
            break;
        case 2:
            // Buscar um valor na lista.
            printf("Insira o valor a ser buscado: ");
            scanf("%d", &valor);
            buscarValor(valor);
            break;
        case 3:
            // Imprimir a lista.
            printList();
            break;
        case 4:
            // Sair do programa.
            exit(0);
        default:
            // Mensagem de erro para opção inválida.
            printf("Opção inválida.\n");
        }
    }

    return 0;
}

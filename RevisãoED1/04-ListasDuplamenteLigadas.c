#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó para uma lista duplamente encadeada
typedef struct Node
{
    int data;          // Armazena o valor do nó
    struct Node *next; // Ponteiro para o próximo nó na lista
    struct Node *prev; // Ponteiro para o nó anterior na lista
} Node;

Node *head = NULL; // Ponteiro para o primeiro nó da lista, inicialmente NULL (lista vazia)

// Função para inserir um novo nó no início da lista
void insertFront(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node)); // Aloca memória para um novo nó
    newNode->data = value;                        // Atribui o valor ao novo nó
    newNode->next = head;                         // O próximo nó do novo nó será o nó atual apontado por head
    newNode->prev = NULL;                         // Como este nó será o primeiro, o ponteiro prev será NULL

    if (head != NULL)         // Se a lista não estiver vazia,
        head->prev = newNode; // atualiza o ponteiro prev do nó atual para apontar para o novo nó

    head = newNode; // Atualiza o ponteiro head para apontar para o novo nó (novo início da lista)
}

// Função para deletar um nó da lista
void deleteNode(Node *node)
{
    if (node == head)      // Se o nó a ser deletado é o primeiro nó,
        head = node->next; // atualiza head para apontar para o próximo nó

    if (node->next != NULL)            // Se o nó a ser deletado não é o último,
        node->next->prev = node->prev; // atualiza o ponteiro prev do próximo nó

    if (node->prev != NULL)            // Se o nó a ser deletado não é o primeiro,
        node->prev->next = node->next; // atualiza o ponteiro next do nó anterior

    free(node); // Libera a memória alocada para o nó deletado
}

// Função para imprimir todos os valores da lista
void printList()
{
    Node *temp = head; // Começa do início da lista
    while (temp != NULL)
    {                              // Percorre a lista até o final
        printf("%d ", temp->data); // Imprime o valor do nó atual
        temp = temp->next;         // Move para o próximo nó
    }
    printf("\n"); // Nova linha após imprimir todos os valores
}

// Função para buscar um valor na lista
void buscarValor(int value)
{
    Node *temp = head; // Começa do início da lista
    while (temp != NULL)
    { // Percorre a lista até o final
        if (temp->data == value)
        {                                                   // Se o valor for encontrado
            printf("Valor %d encontrado.\n", value);        // Imprime que o valor foi encontrado
            if (temp->prev != NULL)                         // Se houver um nó anterior,
                printf("Anterior: %d\n", temp->prev->data); // Imprime o valor do nó anterior
            else
                printf("Anterior: NULL\n"); // Se não houver nó anterior, imprime NULL

            if (temp->next != NULL)                        // Se houver um próximo nó,
                printf("Próximo: %d\n", temp->next->data); // Imprime o valor do próximo nó
            else
                printf("Próximo: NULL\n"); // Se não houver próximo nó, imprime NULL

            return; // Sai da função após encontrar o valor
        }
        temp = temp->next; // Move para o próximo nó
    }
    printf("Valor %d não encontrado.\n", value); // Se o valor não for encontrado
}

int main()
{
    int escolha, valor;

    while (1)
    { // Loop infinito para o menu de opções
        printf("1. Inserir valor na lista\n");
        printf("2. Buscar valor na lista\n");
        printf("3. Imprimir lista\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha)
        { // Executa a opção escolhida pelo usuário
        case 1:
            printf("Insira o valor a ser adicionado: ");
            scanf("%d", &valor);
            insertFront(valor); // Chama a função para inserir um valor na lista
            break;
        case 2:
            printf("Insira o valor a ser buscado: ");
            scanf("%d", &valor);
            buscarValor(valor); // Chama a função para buscar um valor na lista
            break;
        case 3:
            printList(); // Chama a função para imprimir a lista
            break;
        case 4:
            exit(0); // Sai do programa
        default:
            printf("Opção inválida.\n"); // Trata escolhas inválidas
        }
    }

    return 0;
}

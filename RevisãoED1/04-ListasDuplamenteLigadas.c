/*
O código apresenta uma lista duplamente ligada com operações básicas para inserir, deletar e imprimir.

1 - comente o código.
2 - Modifique a operação de inserção de dados, para que o usuário seja capaz de inserir valores para a lista.
3 - Faça uma operação de buscar por um valor específico, informado pelo usuário, onde o programa deve apresentar se o valor foi encontrado e, em caso afirmativo, exibir detalhes(vizinhos) do nó correspondente.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

Node *head = NULL;

void insertFront(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = head;
    newNode->prev = NULL;
    if (head != NULL)
        head->prev = newNode;
    head = newNode;
}

void deleteNode(Node *node)
{
    if (node == head)
        head = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    if (node->prev != NULL)
        node->prev->next = node->next;
    free(node);
}

void printList()
{
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void buscar()
{
    int elemento;
    printf("Digite o valor a ser buscado: ");
    scanf("%d", &elemento);

    while (1)
    {
        int temp = 1;
        Node *current = head;
        while (current != NULL)
        {
            if (current->data == elemento)
            {
                break;
            }
            current = current->next;
            temp++;
        }
        if (current != NULL)
        {
            printf("Elemento %d encontrado na posição %d \n", elemento, temp);
            printf("Elemento anterior: %d \n", current->prev->data);
            printf("Elemento seguinte: %d", current->next->data);
        }
        else
        {
            printf("Elemento %d não encontrado\n", elemento);
        }
        return;
    }
}

int main()
{
    int tamanho = 1;
    while (1)
    {
        printf("Digite o valor a ser inserido:");
        int n;
        int m = 0;
        int temp = 0;
        scanf("%d", &n);
        insertFront(n);
        printf("Deseja inserir um novo valor?\n");
        printf("(1) SIM ");
        printf("(2) NAO\n");
        scanf("%d", &m);
        while (m < 1 || m > 2)
        {
            printf("Digite um valor válido (1 ou 2): ");
            scanf("%d", &m);
        }
        if (m == 2)
        {
            break;
        }
        if (m == 1)
        {
            tamanho++;
        }
    }
    printf("Lista criada: ");
    printList();
    buscar();
    return 0;
}
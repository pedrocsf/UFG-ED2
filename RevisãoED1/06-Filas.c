#include <stdio.h>
#include <stdlib.h>

// Definição do nó da fila
typedef struct Node
{
    int data;          // Dado armazenado no nó
    struct Node *next; // Ponteiro para o próximo nó na fila
} Node;

// Definição da estrutura da fila
typedef struct Queue
{
    Node *front; // Ponteiro para o início da fila
    Node *rear;  // Ponteiro para o fim da fila
} Queue;

// Função para criar e inicializar uma nova fila
Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue)); // Aloca memória para a fila
    if (q == NULL)                             // Verifica se a alocação de memória falhou
    {
        printf("Falha na alocação de memória para a fila.\n");
        return NULL;
    }
    q->front = q->rear = NULL; // Inicializa os ponteiros como NULL
    return q;
}

// Função para adicionar um elemento à fila
void enqueue(Queue *q, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node)); // Aloca memória para um novo nó
    if (newNode == NULL)                          // Verifica se a alocação de memória falhou
    {
        printf("Falha na alocação de memória para o novo nó.\n");
        return;
    }
    newNode->data = value; // Armazena o valor no nó
    newNode->next = NULL;  // O próximo nó é NULL, pois será o último na fila
    if (q->rear == NULL)   // Se a fila está vazia
    {
        q->front = q->rear = newNode; // O novo nó é tanto o início quanto o fim da fila
    }
    else // Se a fila não está vazia
    {
        q->rear->next = newNode; // Adiciona o novo nó ao fim da fila
        q->rear = newNode;       // Atualiza o ponteiro de fim da fila
    }
}

// Função para remover um elemento da fila
int dequeue(Queue *q)
{
    if (q->front == NULL) // Verifica se a fila está vazia
    {
        printf("Fila está vazia.\n");
        return -1;
    }
    Node *temp = q->front;     // Armazena o nó da frente para liberar memória depois
    int data = temp->data;     // Armazena o valor do nó que será removido
    q->front = q->front->next; // Move o ponteiro de frente para o próximo nó
    if (q->front == NULL)      // Se a fila ficou vazia após a remoção
    {
        q->rear = NULL; // Atualiza o ponteiro de fim da fila para NULL
    }
    free(temp);  // Libera a memória do nó removido
    return data; // Retorna o valor do nó removido
}

// Função para contar o número de elementos na fila
int countQueue(Queue *q)
{
    int count = 0;
    Node *temp = q->front;
    while (temp != NULL) // Percorre todos os nós da fila
    {
        count++;           // Incrementa o contador para cada nó
        temp = temp->next; // Vai para o próximo nó
    }
    return count; // Retorna o número de elementos na fila
}

// Função para limpar todos os elementos da fila e liberar a memória
void clearQueue(Queue *q)
{
    while (!isEmpty(q)) // Continua removendo elementos até que a fila esteja vazia
    {
        dequeue(q); // Remove o elemento da frente da fila e libera a memória
    }
}

// Função para verificar se a fila está vazia
int isEmpty(Queue *q)
{
    return q->front == NULL; // Retorna 1 (true) se a fila estiver vazia, caso contrário, 0 (false)
}

// Função para imprimir todos os elementos da fila
void printQueue(Queue *q)
{
    if (isEmpty(q)) // Verifica se a fila está vazia
    {
        printf("A fila está vazia.\n");
        return;
    }
    Node *temp = q->front; // Começa do início da fila
    printf("Elementos da fila: ");
    while (temp != NULL) // Percorre cada nó da fila
    {
        printf("%d ", temp->data); // Imprime o valor do nó
        temp = temp->next;         // Vai para o próximo nó
    }
    printf("\n");
}

int main()
{
    Queue *q = createQueue(); // Cria uma nova fila
    enqueue(q, 10);           // Adiciona 10 à fila
    enqueue(q, 20);           // Adiciona 20 à fila
    enqueue(q, 30);           // Adiciona 30 à fila
    printQueue(q);            // Imprime a fila

    printf("Número de elementos na fila: %d\n", countQueue(q));

    printf("Desenfileirado: %d\n", dequeue(q));
    printQueue(q);
    printf("Número de elementos na fila: %d\n", countQueue(q));

    clearQueue(q);
    printQueue(q);
    printf("Número de elementos na fila: %d\n", countQueue(q));

    return 0;
}

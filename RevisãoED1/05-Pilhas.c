/*
O código abaixo apresenta a implementação de uma pilha e suas operações básicas.

1 - comente o código
2 - implemente uma função para verificar se a pilha está vazia.
3 - proponha uma função que possa fazer expansão dinâmica quando a capacidade máxima é atingida, em vez de simplesmente negar novas inserções na pilha.
*/

#include <stdio.h>
#define MAX_SIZE 3

int *pilha;
int topo = -1;
int capacidade = 3;

void expandir_pilha()
{
    capacidade *= 2;
    pilha = realloc(pilha, capacidade * sizeof(int));
    if (!pilha)
    {
        printf("Erro ao expandir a pilha!\n");
        exit(1);
    }
    printf("Pilha expandida para capacidade %d.\n", capacidade);
}
const char *isEmpty()
{
    return (topo == -1) ? "A pilha está vazia." : "A pilha não está vazia.";
}

void push(int elemento)
{
    if (topo < MAX_SIZE - 1)
    {
        pilha[++topo] = elemento;
    }
    else
    {
        printf("Pilha cheia!\n");
    }
}

int pop()
{
    if (topo == -1)
    {
        printf("Pilha vazia!\n");
        return -1;
    }
    else
    {
        return pilha[topo--];
    }
}

int top()
{
    if (topo == -1)
    {
        printf("Pilha vazia!\n");
        return -1;
    }
    else
    {
        return pilha[topo];
    }
}

void imprimir()
{
    printf("Conteúdo da pilha:\n");
    for (int i = topo; i >= 0; i--)
    {
        printf("%d ", pilha[i]);
    }
    printf("\n");
}

int main()
{
    pilha = malloc(capacidade * sizeof(int));
    printf("%s\n", isEmpty());
    push(10);
    push(20);
    push(30);
    imprimir();
    printf("Elemento no topo: %d\n", top());
    printf("Elemento removido: %d\n", pop());
    imprimir();
    push(40);
    imprimir();
    printf("%s\n", isEmpty());
    return 0;
}
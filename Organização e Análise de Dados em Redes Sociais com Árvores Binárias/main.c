#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int Id;
    int curtidas;
    int comentarios;
    int interacoesTotais;
    struct Node *esquerda;
    struct Node *direita;
} Node;

Node *createNode(int Id, int curtidas, int comentarios)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->Id = Id;
    newNode->curtidas = curtidas;
    newNode->comentarios = comentarios;
    newNode->interacoesTotais = curtidas + comentarios;
    newNode->esquerda = NULL;
    newNode->direita = NULL;
    return newNode;
}

Node *insertNode(Node *root, int Id, int curtidas, int comentarios)
{
    if (root == NULL)
    {
        return createNode(Id, curtidas, comentarios);
    }

    if ((curtidas + comentarios) > root->interacoesTotais)
    {
        root->direita = insertNode(root->direita, Id, curtidas, comentarios);
    }
    else if ((curtidas + comentarios) < root->interacoesTotais)
    {
        root->esquerda = insertNode(root->esquerda, Id, curtidas, comentarios);
    }
    else
    {
        printf("Usuário com mesmo número de interações já existente. ID não duplicado.\n");
    }

    return root;
}

Node *buscarUsuario(Node *root, int Id)
{
    if (root == NULL || root->Id == Id)
    {
        return root;
    }

    if (Id < root->Id)
    {
        return buscarUsuario(root->esquerda, Id);
    }
    else
    {
        return buscarUsuario(root->direita, Id);
    }
}

void exibirMaisEngajados(Node *root)
{
    if (root != NULL)
    {
        exibirMaisEngajados(root->direita);
        printf("ID: %d, Curtidas: %d, Comentários: %d, Total Interações: %d\n",
               root->Id, root->curtidas, root->comentarios, root->interacoesTotais);
        exibirMaisEngajados(root->esquerda);
    }
}

Node *minNode(Node *node)
{
    Node *current = node;
    while (current && current->esquerda != NULL)
    {
        current = current->esquerda;
    }
    return current;
}
Node *removerUsuario(Node *root, int Id)
{
    if (root == NULL)
    {
        return root;
    }

    if (Id < root->Id)
    {
        root->esquerda = removerUsuario(root->esquerda, Id);
    }
    else if (Id > root->Id)
    {
        root->direita = removerUsuario(root->direita, Id);
    }
    else
    {
        if (root->esquerda == NULL)
        {
            Node *temp = root->direita;
            free(root);
            printf("Usuário ID %d removido.\n", Id);
            return temp;
        }
        else if (root->direita == NULL)
        {
            Node *temp = root->esquerda;
            free(root);
            printf("Usuário ID %d removido.\n", Id);
            return temp;
        }

        Node *temp = minNode(root->direita);
        root->Id = temp->Id;
        root->curtidas = temp->curtidas;
        root->comentarios = temp->comentarios;
        root->interacoesTotais = temp->interacoesTotais;
        root->direita = removerUsuario(root->direita, temp->Id);
        printf("Usuário ID %d removido.\n", Id);
    }
    return root;
}

void atualizarInteracoes(Node *root, int Id, int novasCurtidas, int novosComentarios)
{
    Node *usuario = buscarUsuario(root, Id);
    if (usuario != NULL)
    {
        usuario->curtidas += novasCurtidas;
        usuario->comentarios += novosComentarios;
        usuario->interacoesTotais = usuario->curtidas + usuario->comentarios;
        printf("Interações do usuário ID %d atualizadas: Curtidas = %d, Comentários = %d, Total Interações = %d\n",
               usuario->Id, usuario->curtidas, usuario->comentarios, usuario->interacoesTotais);
    }
    else
    {
        printf("Usuário ID %d não encontrado.\n", Id);
    }
}

int main()
{
    Node *root = NULL;
    root = insertNode(root, 101, 50, 30);
    root = insertNode(root, 102, 40, 10);
    root = insertNode(root, 103, 60, 25);
    printf("Usuários em ordem decrescente de engajamento:\n");
    exibirMaisEngajados(root);

    int idBusca = 101;
    Node *usuario = buscarUsuario(root, idBusca);
    if (usuario != NULL)
    {
        printf("\nUsuário ID %d encontrado: Curtidas = %d, Comentários = %d, Total Interações = %d\n",
               usuario->Id, usuario->curtidas, usuario->comentarios, usuario->interacoesTotais);
    }
    else
    {
        printf("\nUsuário ID %d não encontrado.\n", idBusca);
    }

    atualizarInteracoes(root, 101, 10, 5);
    printf("\nUsuários em ordem decrescente de engajamento após atualização:\n");
    exibirMaisEngajados(root);
    root = removerUsuario(root, 102);
    printf("\nUsuários em ordem decrescente de engajamento após remoção:\n");
    exibirMaisEngajados(root);

    return 0;
}

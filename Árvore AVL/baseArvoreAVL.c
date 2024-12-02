#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da árvore AVL
struct Node
{
    int id;             // ID do cliente (chave de busca)
    char name[50];      // Nome do cliente
    struct Node *left;  // Ponteiro para o filho esquerdo
    struct Node *right; // Ponteiro para o filho direito
    int height;         // Altura do nó
};

// Função para calcular a altura de um nó
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// Função para obter o máximo entre dois inteiros
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Função para criar um novo nó
struct Node *createNode(int id, const char *name)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->id = id;
    strcpy(node->name, name);
    node->left = node->right = NULL;
    node->height = 1; // Altura inicial é 1
    return node;
}

// Rotação à direita
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotação à esquerda
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Calcula o fator de balanceamento
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Função para inserir um novo nó na árvore AVL
struct Node *insert(struct Node *node, int id, const char *name)
{
    // Passo 1: Realiza a inserção normal na árvore binária de busca
    if (node == NULL)
        return createNode(id, name);

    if (id < node->id)
        node->left = insert(node->left, id, name);
    else if (id > node->id)
        node->right = insert(node->right, id, name);
    else // IDs duplicados não são permitidos
        return node;

    // Passo 2: Atualiza a altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // Passo 3: Calcula o fator de balanceamento
    int balance = getBalance(node);

    // Se o nó ficar desbalanceado, aplica rotações

    // Caso LL
    if (balance > 1 && id < node->left->id)
        return rightRotate(node);

    // Caso RR
    if (balance < -1 && id > node->right->id)
        return leftRotate(node);

    // Caso LR
    if (balance > 1 && id > node->left->id)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso RL
    if (balance < -1 && id < node->right->id)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Função para encontrar o nó com o menor valor na árvore
struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Função para remover um nó da árvore AVL
struct Node *deleteNode(struct Node *root, int id)
{
    if (root == NULL)
        return root;

    // Passo 1: Realiza a remoção normal
    if (id < root->id)
        root->left = deleteNode(root->left, id);
    else if (id > root->id)
        root->right = deleteNode(root->right, id);
    else
    {
        // Nó com um ou nenhum filho
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;

            free(temp);
        }
        else
        {
            // Nó com dois filhos
            struct Node *temp = minValueNode(root->right);
            root->id = temp->id;
            strcpy(root->name, temp->name);
            root->right = deleteNode(root->right, temp->id);
        }
    }

    if (root == NULL)
        return root;

    // Passo 2: Atualiza a altura do nó
    root->height = 1 + max(height(root->left), height(root->right));

    // Passo 3: Calcula o fator de balanceamento
    int balance = getBalance(root);

    // Se o nó ficar desbalanceado, aplica rotações

    // Caso LL
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Caso LR
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Caso RR
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Caso RL
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Função para buscar um cliente pelo ID
struct Node *search(struct Node *root, int id)
{
    if (root == NULL || root->id == id)
        return root;

    if (id < root->id)
        return search(root->left, id);

    return search(root->right, id);
}

// Percorre a árvore em ordem crescente
void inOrder(struct Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("ID: %d, Nome: %s\n", root->id, root->name);
        inOrder(root->right);
    }
}

// Função principal
int main()
{
    struct Node *tree = NULL;

    // Inserindo clientes
    tree = insert(tree, 10, "Alice");
    tree = insert(tree, 20, "Bob");
    tree = insert(tree, 30, "Charlie");
    tree = insert(tree, 40, "Diana");
    tree = insert(tree, 50, "Eve");
    tree = insert(tree, 25, "Frank");

    printf("Árvore AVL em ordem após inserções:\n");
    inOrder(tree);

    // Busca
    int searchID = 30;
    struct Node *found = search(tree, searchID);
    if (found != NULL)
        printf("\nCliente encontrado: ID = %d, Nome = %s\n", found->id, found->name);
    else
        printf("\nCliente com ID %d não encontrado.\n", searchID);

    // Removendo um cliente
    tree = deleteNode(tree, 20);
    printf("\nÁrvore AVL em ordem após remoção do ID 20:\n");
    inOrder(tree);

    return 0;
}

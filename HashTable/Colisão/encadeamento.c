#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

typedef struct Entrega
{
    int id;
    char endereco[50];
    float tam_pacote;
    unsigned int tempo_entrega;
    struct Entrega *proximo; // Ponteiro para a próxima entrega na lista
} Entrega;

typedef struct
{
    Entrega *tabela[TAMANHO_HASH]; // Cada índice contém uma lista encadeada
} TabelaHash;

// Função para inicializar a tabela hash com NULL em todos os índices
void inicializar_tabela(TabelaHash *tabela)
{
    for (int i = 0; i < TAMANHO_HASH; i++)
    {
        tabela->tabela[i] = NULL; // Inicializa todas as posições da tabela com NULL
    }
}

int funcao_hash(int id)
{
    return id % TAMANHO_HASH;
}

void inserir(TabelaHash *tabela, Entrega *novaEntrega)
{
    int indice = funcao_hash(novaEntrega->id);
    Entrega *atual = tabela->tabela[indice];

    // Inserir no início da lista encadeada
    novaEntrega->proximo = atual;
    tabela->tabela[indice] = novaEntrega;
}

Entrega *buscar(TabelaHash *tabela, int id)
{
    int indice = funcao_hash(id);
    Entrega *atual = tabela->tabela[indice];

    // Percorre a lista encadeada para encontrar o ID
    while (atual != NULL)
    {
        if (atual->id == id)
        {
            return atual;
        }
        atual = atual->proximo;
    }

    return NULL;
}

void remover(TabelaHash *tabela, int id)
{
    int indice = funcao_hash(id);
    Entrega *atual = tabela->tabela[indice];
    Entrega *anterior = NULL;

    // Percorre a lista para encontrar e remover o item
    while (atual != NULL && atual->id != id)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        // O item não foi encontrado
        return;
    }

    if (anterior == NULL)
    {
        // Remover o primeiro item da lista
        tabela->tabela[indice] = atual->proximo;
    }
    else
    {
        // Remover um item do meio/fim da lista
        anterior->proximo = atual->proximo;
    }

    free(atual); // Liberar a memória da entrega removida
}

void showEntregas(TabelaHash *tabela)
{
    for (int i = 0; i < TAMANHO_HASH; i++)
    {
        Entrega *atual = tabela->tabela[i];

        while (atual != NULL)
        {
            printf("Entrega encontrada: ID: %d, Destino: %s, Peso: %.2f, Estimativa: %d dias\n",
                   atual->id, atual->endereco, atual->tam_pacote, atual->tempo_entrega);
            atual = atual->proximo;
        }
    }
    printf("\n\n");
}

int main()
{
    TabelaHash tabela;
    inicializar_tabela(&tabela); // Inicializa todos os elementos com NULL

    Entrega *e1 = (Entrega *)malloc(sizeof(Entrega));
    *e1 = (Entrega){1345, "Goiania", 0.45, 1, NULL};
    Entrega *e2 = (Entrega *)malloc(sizeof(Entrega));
    *e2 = (Entrega){2299, "Parnaiba", 5.0, 10, NULL};
    Entrega *e3 = (Entrega *)malloc(sizeof(Entrega));
    *e3 = (Entrega){8756, "Natal", 1.2, 8, NULL};
    Entrega *e4 = (Entrega *)malloc(sizeof(Entrega));
    *e4 = (Entrega){8290, "Bodoco", 0.1, 3, NULL};
    Entrega *e5 = (Entrega *)malloc(sizeof(Entrega));
    *e5 = (Entrega){1001, "Guapo", 2, 1, NULL};

    inserir(&tabela, e1);
    inserir(&tabela, e2);
    inserir(&tabela, e3);
    inserir(&tabela, e4);
    inserir(&tabela, e5);

    showEntregas(&tabela);

    Entrega *t = buscar(&tabela, 8290);
    if (t != NULL)
    {
        printf("Entrega procurada: ID: %d, Destino: %s, Peso: %.2f, Estimativa: %d dias\n\n",
               t->id, t->endereco, t->tam_pacote, t->tempo_entrega);
    }
    else
    {
        printf("Entrega não encontrada.\n");
    }

    remover(&tabela, 8290);

    Entrega *t2 = buscar(&tabela, 8290);
    if (t2 != NULL)
    {
        printf("Entrega encontrada: ID: %d, Destino: %s, Peso: %.2f, Estimativa: %d dias\n",
               t2->id, t2->endereco, t2->tam_pacote, t2->tempo_entrega);
    }
    else
    {
        printf("Entrega nao encontrada.\n");
    }

    // Liberar a memória alocada para as entregas
    for (int i = 0; i < TAMANHO_HASH; i++)
    {
        Entrega *atual = tabela->tabela[i];
        while (atual != NULL)
        {
            Entrega *proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        tabela->tabela[i] = NULL; // Marcar a tabela como vazia
    }

    return 0;
}

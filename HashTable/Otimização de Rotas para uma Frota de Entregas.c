#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

typedef struct
{
    int id;
    char endereco[50];
    float tam_pacote;
    unsigned int tempo_entrega;
} Entrega;

typedef struct
{
    Entrega *tabela[TAMANHO_HASH];
} TabelaHash;

int funcao_hash(int id)
{
    return id % TAMANHO_HASH;
}

void inserir(TabelaHash *tabela, Entrega *Entrega)
{
    int indice = funcao_hash(Entrega->id);
    tabela->tabela[indice] = Entrega;
}

Entrega *buscar(TabelaHash *tabela, int id)
{
    int indice = funcao_hash(id);
    return tabela->tabela[indice];
}

void remover(TabelaHash *tabela, int id)
{
    tabela->tabela[funcao_hash(id)] = NULL;
}

void showEntregas(TabelaHash *tabela)
{

    for (int i = 0; i < TAMANHO_HASH; i++)
    {
        Entrega *n = tabela->tabela[i];

        if (n != NULL)
        {
            printf("Entrega encontrada: ID: %d, Destino: %s, Peso: %.2f, Estimativa: %d dias\n",
                   n->id, n->endereco, n->tam_pacote, n->tempo_entrega);
        }
    }

    printf("\n\n");
}

int main()
{

    TabelaHash tabela = {NULL};

    Entrega e1 = {3421, "Fortaleza", 3.75, 7};
    Entrega e2 = {9150, "Salvador", 2.3, 5};
    Entrega e3 = {6438, "Joao Pessoa", 1.8, 4};
    Entrega e4 = {2774, "Recife", 0.9, 2};
    Entrega e5 = {5612, "Cuiaba", 4.1, 9};

    inserir(&tabela, &e1);
    inserir(&tabela, &e2);
    inserir(&tabela, &e3);
    inserir(&tabela, &e4);
    inserir(&tabela, &e5);

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

    return 0;
}

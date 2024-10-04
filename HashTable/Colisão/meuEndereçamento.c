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
    int ocupada;
} Entrega;

typedef struct
{
    Entrega tabela[TAMANHO_HASH];
} TabelaHash;

int funcao_hash(int id)
{
    return id % TAMANHO_HASH;
}

int hash2(int id)
{
    return 7 - (id % 7);
}

int sondagem_linear(TabelaHash *tabela, int id)
{
    int indice = funcao_hash(id);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH)
    {
        indice = (indice + 1) % TAMANHO_HASH;
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;
}

int sondagem_quadratica(TabelaHash *tabela, int id)
{
    int indice = funcao_hash(id);
    int i = 1;
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH)
    {
        indice = (funcao_hash(id) + i * i) % TAMANHO_HASH;
        i++;
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;
}

int duplo_hashing(TabelaHash *tabela, int id)
{
    int indice = funcao_hash(id);
    int step = hash2(id);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH)
    {
        indice = (indice + step) % TAMANHO_HASH;
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;
}

void inserir_linear(TabelaHash *tabela, Entrega entrega)
{
    int indice = funcao_hash(entrega.id);

    if (!tabela->tabela[indice].ocupada)
    {
        tabela->tabela[indice] = entrega;
        tabela->tabela[indice].ocupada = 1;
    }
    else
    {
        int novo_indice = sondagem_linear(tabela, entrega.id);
        if (novo_indice != -1)
        {
            tabela->tabela[novo_indice] = entrega;
            tabela->tabela[novo_indice].ocupada = 1;
        }
        else
        {
            printf("Erro: Tabela hash está cheia (Sondagem Linear).\n");
        }
    }
}

void inserir_quadratica(TabelaHash *tabela, Entrega entrega)
{
    int indice = funcao_hash(entrega.id);

    if (!tabela->tabela[indice].ocupada)
    {
        tabela->tabela[indice] = entrega;
        tabela->tabela[indice].ocupada = 1;
    }
    else
    {
        int novo_indice = sondagem_quadratica(tabela, entrega.id);
        if (novo_indice != -1)
        {
            tabela->tabela[novo_indice] = entrega;
            tabela->tabela[novo_indice].ocupada = 1;
        }
        else
        {
            printf("Erro: Tabela hash está cheia (Sondagem Quadrática).\n");
        }
    }
}

void inserir_duplo_hashing(TabelaHash *tabela, Entrega entrega)
{
    int indice = funcao_hash(entrega.id);

    if (!tabela->tabela[indice].ocupada)
    {
        tabela->tabela[indice] = entrega;
        tabela->tabela[indice].ocupada = 1;
    }
    else
    {
        int novo_indice = duplo_hashing(tabela, entrega.id);
        if (novo_indice != -1)
        {
            tabela->tabela[novo_indice] = entrega;
            tabela->tabela[novo_indice].ocupada = 1;
        }
        else
        {
            printf("Erro: Tabela hash está cheia (Duplo Hashing).\n");
        }
    }
}

void showEntregas(TabelaHash *tabela)
{
    for (int i = 0; i < TAMANHO_HASH; i++)
    {
        if (tabela->tabela[i].ocupada)
        {
            Entrega *n = &tabela->tabela[i];
            printf("Entrega encontrada: ID: %d, Destino: %s, Peso: %.2f, Estimativa: %d dias (Índice: %d)\n",
                   n->id, n->endereco, n->tam_pacote, n->tempo_entrega, i);
        }
    }
}

Entrega *buscar(TabelaHash *tabela, int id)
{
    int indice = funcao_hash(id);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tabela->tabela[indice].id != id && tentativas < TAMANHO_HASH)
    {
        indice = (indice + 1) % TAMANHO_HASH;
        tentativas++;
    }

    if (tabela->tabela[indice].ocupada && tabela->tabela[indice].id == id)
    {
        return &tabela->tabela[indice];
    }

    return NULL;
}

void remover(TabelaHash *tabela, int id)
{
    Entrega *entrega = buscar(tabela, id);

    if (entrega != NULL)
    {
        entrega->ocupada = 0;
        printf("Entrega ID %d removida.\n", id);
    }
    else
    {
        printf("Entrega ID %d não encontrada.\n", id);
    }
}

int main()
{
    TabelaHash tabela_linear = {0};

    Entrega e1 = {3421, "Fortaleza", 3.75, 7, 0};
    Entrega e2 = {9150, "Salvador", 2.3, 5, 0};
    Entrega e3 = {6438, "Joao Pessoa", 1.8, 4, 0};
    Entrega e4 = {2774, "Recife", 0.9, 2, 0};
    Entrega e5 = {5612, "Cuiaba", 4.1, 9, 0};

    inserir_linear(&tabela_linear, e1);
    inserir_linear(&tabela_linear, e2);
    inserir_linear(&tabela_linear, e3);
    inserir_linear(&tabela_linear, e4);
    inserir_linear(&tabela_linear, e5);

    showEntregas(&tabela_linear);

    Entrega *t = buscar(&tabela_linear, 6438);
    if (t != NULL)
    {
        printf("Entrega encontrada: ID: %d, Destino: %s\n", t->id, t->endereco);
    }
    else
    {
        printf("Entrega não encontrada.\n");
    }

    remover(&tabela_linear, 6438);
    showEntregas(&tabela_linear);

    return 0;
}

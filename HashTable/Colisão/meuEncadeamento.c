#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

typedef struct No
{
    int chave;
    char valor[100];
    struct No *proximo;
} No;

typedef struct
{
    No *tabela[TAMANHO_HASH];
} TabelaHash;

int funcao_hash(int chave)
{
    return chave % TAMANHO_HASH;
}

No *criar_no(int chave, const char *valor)
{
    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL)
    {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novo_no->chave = chave;
    strcpy(novo_no->valor, valor);
    novo_no->proximo = NULL;
    return novo_no;
}

void inserir(TabelaHash *tabela, int chave, const char *valor)
{
    int indice = funcao_hash(chave);
    No *novo_no = criar_no(chave, valor);
    novo_no->proximo = tabela->tabela[indice];
    tabela->tabela[indice] = novo_no;
}

No *buscar(TabelaHash *tabela, int chave)
{
    int indice = funcao_hash(chave);
    No *atual = tabela->tabela[indice];

    while (atual != NULL)
    {
        if (atual->chave == chave)
        {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void remover(TabelaHash *tabela, int chave)
{
    int indice = funcao_hash(chave);
    No *atual = tabela->tabela[indice];
    No *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->chave == chave)
        {
            if (anterior == NULL)
            {
                tabela->tabela[indice] = atual->proximo;
            }
            else
            {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Elemento com chave %d foi removido.\n", chave);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Elemento com chave %d não encontrado para remoção.\n", chave);
}

void exibir_tabela(TabelaHash *tabela)
{
    for (int i = 0; i < TAMANHO_HASH; i++)
    {
        No *atual = tabela->tabela[i];
        printf("Índice %d: ", i);
        while (atual != NULL)
        {
            printf("(Chave: %d, Valor: %s) -> ", atual->chave, atual->valor);
            atual = atual->proximo;
        }
        printf("NULL\n");
    }
}

int main()
{
    TabelaHash tabela = {NULL};

    inserir(&tabela, 10, "Valor 1");
    inserir(&tabela, 20, "Valor 2");
    inserir(&tabela, 15, "Valor 3");
    inserir(&tabela, 5, "Valor 4");
    inserir(&tabela, 25, "Valor 5");

    printf("Tabela Hash:\n");
    exibir_tabela(&tabela);

    int chave_busca = 15;
    No *elemento = buscar(&tabela, chave_busca);
    if (elemento != NULL)
    {
        printf("Elemento encontrado: Chave %d, Valor: %s\n", elemento->chave, elemento->valor);
    }
    else
    {
        printf("Elemento com chave %d não encontrado.\n", chave_busca);
    }

    remover(&tabela, 15);

    printf("Tabela Hash após remoção:\n");
    exibir_tabela(&tabela);

    return 0;
}

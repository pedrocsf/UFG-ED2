#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

typedef struct PatriciaNode
{
    char *word;                        // Palavra armazenada (nó terminal)
    struct PatriciaNode *children[26]; // Ponteiros para filhos ('a' a 'z')
} PatriciaNode;

// Função auxiliar para criar um novo nó
PatriciaNode *createNode()
{
    PatriciaNode *node = (PatriciaNode *)malloc(sizeof(PatriciaNode));
    node->word = NULL;
    for (int i = 0; i < 26; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

// Função para inserir uma palavra na Árvore Patricia
void insertWord(PatriciaNode *root, const char *word)
{
    PatriciaNode *current = root;

    while (*word)
    {
        int index = *word - 'a';

        // Verifica caracteres inválidos
        if (index < 0 || index >= 26)
        {
            printf("Erro: Caractere inválido '%c' detectado.\n", *word);
            return;
        }

        // Cria um novo nó se necessário
        if (current->children[index] == NULL)
        {
            current->children[index] = createNode();
        }

        current = current->children[index];
        word++;
    }

    // Insere a palavra no nó terminal, se ainda não existir
    if (current->word == NULL)
    {
        current->word = strdup(word - strlen(word)); // Copia a palavra
    }
}

// Função para buscar uma palavra na Árvore Patricia
int searchWord(PatriciaNode *root, const char *word)
{
    PatriciaNode *current = root;
    while (*word)
    {
        int index = *word - 'a';
        if (current->children[index] == NULL)
        {
            return 0; // Palavra não encontrada
        }
        current = current->children[index];
        word++;
    }
    return current->word != NULL;
}

// Função auxiliar para sugerir palavras com base em um prefixo
void suggestRecursive(PatriciaNode *node, char *buffer, int depth)
{
    if (node->word != NULL)
    {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }
    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != NULL)
        {
            buffer[depth] = 'a' + i;
            suggestRecursive(node->children[i], buffer, depth + 1);
        }
    }
}

// Função para sugerir palavras com base em um prefixo
void suggestWords(PatriciaNode *root, const char *prefix)
{
    PatriciaNode *current = root;
    char buffer[MAX_WORD_LENGTH];
    strcpy(buffer, prefix);

    // Navegar até o final do prefixo
    while (*prefix)
    {
        int index = *prefix - 'a';
        if (current->children[index] == NULL)
        {
            printf("Nenhuma sugestão encontrada.\n");
            return;
        }
        current = current->children[index];
        prefix++;
    }

    // Listar sugestões a partir desse ponto
    suggestRecursive(current, buffer, strlen(buffer));
}

// Função para carregar palavras do arquivo dicionário
void loadDictionary(PatriciaNode *root, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo dicionario.txt");
        exit(EXIT_FAILURE);
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF)
    {
        insertWord(root, word); // Insere cada palavra no dicionário
    }
    fclose(file);

    printf("Palavras inseridas no dicionário.\n");
}

// Menu interativo para o usuário
void menu(PatriciaNode *root)
{
    int option;
    char input[MAX_WORD_LENGTH];

    do
    {
        printf("\nEscolha uma opção:\n");
        printf("1. Inserir palavra\n");
        printf("2. Buscar palavra\n");
        printf("3. Sugerir palavras (autocompletar)\n");
        printf("4. Sair\n");
        printf("Opção: ");

        // Lê a opção do usuário e valida a entrada
        if (scanf("%d", &option) != 1)
        {
            printf("Entrada inválida. Por favor, digite um número.\n");
            while (getchar() != '\n')
                ; // Limpa o buffer
            continue;
        }

        // Limpa o buffer após a leitura da opção
        while (getchar() != '\n')
            ;

        switch (option)
        {
        case 1:
            printf("Digite a palavra para inserir: ");
            if (fgets(input, sizeof(input), stdin) != NULL)
            {
                input[strcspn(input, "\n")] = '\0'; // Remove o '\n' do final
                insertWord(root, input);
                printf("Palavra inserida no dicionário.\n");
            }
            break;

        case 2:
            printf("Digite a palavra para buscar: ");
            if (fgets(input, sizeof(input), stdin) != NULL)
            {
                input[strcspn(input, "\n")] = '\0'; // Remove o '\n' do final
                if (searchWord(root, input))
                {
                    printf("Palavra encontrada.\n");
                }
                else
                {
                    printf("Palavra não encontrada.\n");
                }
            }
            break;

        case 3:
            printf("Digite o prefixo para autocompletar: ");
            if (fgets(input, sizeof(input), stdin) != NULL)
            {
                input[strcspn(input, "\n")] = '\0'; // Remove o '\n' do final
                printf("Sugestões:\n");
                suggestWords(root, input);
            }
            break;

        case 4:
            printf("Encerrando o programa...\n");
            return; // Sai da função `menu` imediatamente
            break;

        default:
            printf("Opção inválida. Por favor, escolha entre 1 e 4.\n");
        }
    } while (1); // O loop continua até encontrar `return`
}

// Função principal
int main()
{
    PatriciaNode *root = createNode();

    // Carregar dicionário do arquivo
    loadDictionary(root, "dicionario.txt");

    // Iniciar menu interativo
    menu(root);

    return 0;
}

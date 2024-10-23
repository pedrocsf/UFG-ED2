#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCTS 1000      // Número de produtos
#define MAX_NAME_LENGTH 50     // Tamanho máximo do nome do produto
#define NUM_REPETICOES 1000000 // Número de repetições das buscas

// Estrutura que representa um produto no e-commerce
typedef struct
{
    int id;                     // ID único do produto
    char name[MAX_NAME_LENGTH]; // Nome do produto
    float price;                // Preço do produto
} Product;

// Função para gerar um nome de produto aleatório a partir da lista predefinida
void generateProductName(char *name)
{
    const char *productNames[] = {
        "Smartphone Samsung Galaxy", "Notebook Dell Inspiron", "Geladeira Brastemp Frost Free", "Cafeteira Nespresso",
        "Fritadeira Airfryer Mondial", "TV LED 50 Polegadas LG", "Console Playstation 5", "Headset Gamer HyperX",
        "Máquina de Lavar Electrolux", "Ventilador Arno Turbo", "Teclado Mecânico Razer", "Impressora Multifuncional HP",
        "Relógio Smartwatch Apple", "Câmera DSLR Canon", "Micro-ondas Panasonic", "Bicicleta Caloi Aro 29",
        "Perfume Chanel No 5", "Sapato Social Masculino", "Bolsa Feminina de Couro", "Óculos de Sol Ray-Ban"};

    int index = rand() % (sizeof(productNames) / sizeof(productNames[0]));
    strncpy(name, productNames[index], MAX_NAME_LENGTH - 1);
    name[MAX_NAME_LENGTH - 1] = '\0'; // Garante que a string termina corretamente
}

// Função para gerar uma lista de produtos com preços aleatórios
void generateProductList(Product products[], int numProducts)
{
    for (int i = 0; i < numProducts; ++i)
    {
        products[i].id = i + 1;                       // ID sequencial
        generateProductName(products[i].name);        // Nome aleatório
        products[i].price = (rand() % 10000) / 100.0; // Preço aleatório entre $0 e $100
    }
}

// Função para imprimir um produto
void printProduct(Product product)
{
    printf("ID: %d, Nome: %s, Preço: $%.2f\n", product.id, product.name, product.price);
}

// Implementação da busca sequencial
int sequentialSearch(Product products[], int numProducts, const char *target)
{
    for (int i = 0; i < numProducts; i++)
    {
        if (strcmp(products[i].name, target) == 0)
        {
            return i; // Retorna a posição do produto encontrado
        }
    }
    return -1; // Produto não encontrado
}

// Implementação da busca binária
int binarySearch(Product products[], int low, int high, const char *target)
{
    while (low <= high)
    {
        int mid = (low + high) / 2;
        int comparison = strcmp(products[mid].name, target);

        if (comparison == 0)
        {
            return mid; // Produto encontrado
        }
        else if (comparison < 0)
        {
            low = mid + 1; // Busca na metade superior
        }
        else
        {
            high = mid - 1; // Busca na metade inferior
        }
    }
    return -1; // Produto não encontrado
}

// Função para medir o tempo de execução da busca sequencial repetida
double measureSequentialTime(Product products[], int numProducts, const char *target, int repetitions)
{
    clock_t start = clock();
    for (int i = 0; i < repetitions; i++)
    {
        sequentialSearch(products, numProducts, target);
    }
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC / repetitions;
}

// Função para medir o tempo de execução da busca binária repetida
double measureBinaryTime(Product products[], int low, int high, const char *target, int repetitions)
{
    clock_t start = clock();
    for (int i = 0; i < repetitions; i++)
    {
        binarySearch(products, low, high, target);
    }
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC / repetitions;
}

int compareByName(const void *a, const void *b)
{
    Product *productA = (Product *)a;
    Product *productB = (Product *)b;
    return strcmp(productA->name, productB->name);
}

// Função principal
int main()
{
    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios

    Product products[MAX_PRODUCTS]; // Array de produtos
    int numProducts = MAX_PRODUCTS; // Quantidade de produtos a serem gerados

    // Gera a lista de produtos
    generateProductList(products, numProducts);

    // Imprime a lista de produtos gerados
    printf("Lista de produtos gerados:\n");
    for (int i = 0; i < numProducts; i++)
    {
        printProduct(products[i]);
    }

    // Define o produto alvo para busca
    char target[MAX_NAME_LENGTH] = "Notebook Dell Inspiron";

    // Busca sequencial
    int seqIndex = sequentialSearch(products, numProducts, target);
    if (seqIndex != -1)
    {
        printf("\nProduto encontrado na posição %d (Busca Sequencial):\n", seqIndex);
        printProduct(products[seqIndex]);
    }
    else
    {
        printf("\nProduto não encontrado (Busca Sequencial).\n");
    }

    // Ordena a lista de produtos por nome para a busca binária
    qsort(products, MAX_PRODUCTS, sizeof(Product), compareByName);

    // Busca binária
    int binIndex = binarySearch(products, 0, MAX_PRODUCTS - 1, target);
    if (binIndex != -1)
    {
        printf("\nProduto encontrado na posição %d (Busca Binária):\n", binIndex);
        printProduct(products[binIndex]);
    }
    else
    {
        printf("\nProduto não encontrado (Busca Binária).\n");
    }

    // Medir o tempo das buscas com múltiplas repetições
    double seqTime = measureSequentialTime(products, MAX_PRODUCTS, target, NUM_REPETICOES);
    double binTime = measureBinaryTime(products, 0, MAX_PRODUCTS - 1, target, NUM_REPETICOES);

    printf("\nTempo médio de execução da busca sequencial: %f segundos\n", seqTime);
    printf("Tempo médio de execução da busca binária: %f segundos\n", binTime);

    return 0;
}

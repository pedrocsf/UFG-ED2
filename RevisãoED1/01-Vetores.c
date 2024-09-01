#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída

int main()
{
    int n;                                 // Declara uma variável inteira para armazenar o tamanho do vetor
    printf("Digite o tamanho do vetor: "); // Exibe uma mensagem pedindo o tamanho do vetor
    scanf("%d", &n);                       // Lê o tamanho do vetor a partir da entrada do usuário
    int vetor[n];                          // Declara um vetor de tamanho n
    int i, temp;                           // Declara variáveis inteiras para controle de loops e armazenamento temporário

    // Loop para preencher o vetor
    for (i = 0; i < n; i++)
    {
        temp = i;        // Atribui o valor de i a temp
        vetor[i] = temp; // Atribui o valor de temp à posição i do vetor
        temp++;          // Incrementa temp (não tem efeito real no código pois temp não é usado novamente)
    }

    printf("Vetor invertido:\n"); // Exibe uma mensagem antes de imprimir o vetor invertido
    // Loop para imprimir o vetor de trás para frente
    for (i = (n - 1); i != -1; i--)
    {
        printf("%d ", vetor[i]); // Imprime o valor na posição i do vetor
    }

    return 0; // Retorna 0, indicando que o programa terminou com sucesso
}

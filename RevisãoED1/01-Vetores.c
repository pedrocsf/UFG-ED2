/*
O código abaixo realiza a impressão do vetor na ordem inversa.
1 - comente o código
2 - faça uma modificação para que seja possível inserir um vetor de n elementos.
*/

#include <stdio.h>

int main()
{
    int n;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    int vetor[n];
    int i, temp;

    for (i = 0; i < n; i++)
    {
        temp = i;
        vetor[i] = temp;
        temp++;
    }

    printf("Vetor invertido:\n");
    for (i = (n - 1); i != -1; i--)
    {
        printf("%d ", vetor[i]);
    }

    return 0;
}
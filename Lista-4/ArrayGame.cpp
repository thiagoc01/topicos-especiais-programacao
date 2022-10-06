#include <iostream>
#include <vector>

int main()
{
    int numNumeros, esquerda, direita;
    std::vector<int> numeros;

    std::cin >> numNumeros;

    numeros = std::vector<int>(numNumeros);

    for (int i = 0 ; i < numNumeros ; i++)
        std::cin >> numeros[i];

    esquerda = 0;
    direita = numeros.size() - 1;

    while (esquerda + 1 < numeros.size() && numeros[esquerda] < numeros[esquerda + 1])
        esquerda++;

    while (direita + 1 < numeros.size() && numeros[direita] < numeros[direita - 1])
        direita++;

    esquerda++;

    direita = numeros.size() - direita;

    

    return 0;
}
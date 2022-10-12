#include <iostream>
#include <vector>

/*
    Devemos ter que a_i * a_j = i + j e comparar pares.
    Dividindo ambos os lados por a_i, temos:

    a_j = (i + j) / a_i.

    Ou seja, a_i divide a soma. Como i é fixado em uma iteração,
    j deve ser da forma a_i * k acrescido de um valor que
    somado ao i dê um número divisível por a_i.
    Para fazermos o número a_i * k, podemos fazer um incremento em j
    de a_i. E para tornar i + j divisível por a_i, inicializamos j subtraindo
    dele o i. Dessa forma, podemos encontrar todos os múltiplos de a_i
    menores que n.
*/

int main()
{
    int numCasos;

    std::cin >> numCasos;

    while (numCasos--)
    {
        long long int n, numPares = 0;
        std::cin >> n;

        std::vector<long long int> numeros = std::vector<long long int>(n + 1);

        for (int i = 1 ; i <= n ; i++)
            std::cin >> numeros[i];
        
        for (long long int i = 1 ; i <= n ; i++)
        {
            for (long long int j = numeros[i] - i ; j <= n ; j += numeros[i])
            {
                if (j >= 0)
                {
                    if (numeros[i] * numeros[j] == i + j && i < j)
                        numPares++;
                }
            }
        }

        std::cout << numPares << std::endl;
    }

    return 0;
}
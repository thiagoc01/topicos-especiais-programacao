#include <iostream>
#include <vector>
#include <limits.h>

/*
    Um sapo que utilizar uma pedra irá utilizar qualquer pedra a frente
    até a distância l dada (pode-se saltar 1, 2, ..., l seções a frente).
    Logo, sempre calculamos o pior caso: os sapos que utilizarem as pedras
    na i-ésima seção passarem por cada uma das anteriores dentro de 1 até l.
    Portanto, ao receber um valor, sempre somamos com o anterior para realizar um acúmulo.
    Se a dada posição for maior ou igual a l, subtraímos o valor da posição até a seção
    anterior com distância l. Isso será capaz de calcular o número de sapos que podem passar por aquela seção.
    Como queremos o número mínimo, basta realizar o mínimo com a quantidade atual.
*/

int main()
{
    unsigned int w, l, qtdSapos = INT_MAX;
    std::vector<unsigned int> a;

    std::cin >> w >> l;
    
    a.push_back(0);

    for (unsigned int i = 1 ; i < w; i++)
    {
        unsigned int a_i;

        std::cin >> a_i;

        a.push_back(a_i);

        a[i] += a[i - 1];

        if (i >= l)
            qtdSapos = std::min(qtdSapos, a[i] - a[i - l]);
    }

    std::cout << qtdSapos << std::endl;

    return 0;
}
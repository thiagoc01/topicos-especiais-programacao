#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

int main()
{
    int numCasos;

    std::cin >> numCasos;

    while (numCasos--)
    {
        int numNumeros, mediana, soma = 0;
        std::vector<int> numeros;
        std::cin >> numNumeros;

        for (int i = 0 ; i < numNumeros ; i++)
        {
            int num;
            std::cin >> num;

            numeros.push_back(num);
        }

        std::sort(numeros.begin(), numeros.end());

        mediana = numeros[numNumeros / 2];
        
        for (int i = 0 ; i < numNumeros ; i++)
            soma += std::abs(numeros[i] - mediana);

        std::cout << soma << std::endl;
    }

    return 0;
}

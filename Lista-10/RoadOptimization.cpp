#include <iostream>
#include <vector>
#include <limits.h>

int main()
{
    int n, l, k, menorTempo = INT_MAX;
    std::vector<int> coordenadas, velocidades; 
    std::vector<std::vector<int>> temposTotais;

    std::cin >> n >> l >> k;

    velocidades = std::vector<int>(n + 2);
    coordenadas = std::vector<int>(n + 2);
    temposTotais = std::vector<std::vector<int>>(n + 2, std::vector<int>(n + 2, (INT_MAX - 1) / 2));

    for (short int i = 1 ; i <= n ; i++)
        std::cin >> coordenadas[i];

    for (short int i = 1 ; i <= n ; i++)
        std::cin >> velocidades[i];

    n++;

    coordenadas[n] = l;
    temposTotais[1][0] = 0;

    for (int i = 2 ; i <= n ; i++)
    {
        for (int j = 0 ; j <= k ; j++)
        {
            for (int p = 1 ; p < i ; p++)
            {
                if (i - p - 1 <= j)
                    temposTotais[i][j] = std::min(temposTotais[i][j], temposTotais[p][j - (i - p - 1)] + velocidades[p] * (coordenadas[i] - coordenadas[p]));
            }

            if (i == n)
                menorTempo = std::min(menorTempo, temposTotais[i][j]);
        }
    }

    std::cout << menorTempo;

    return 0;
}
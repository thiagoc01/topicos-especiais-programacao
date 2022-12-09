#include <iostream>
#include <vector>

int main()
{
    short int numCasos, caso = 1, n, m;
    int orcamento;
    
    std::cin >> numCasos;

    while (numCasos--)
    {
        int melhorArea = 0;
        long long int melhorPreco = 0;
        std::vector<std::vector<int>> precos;

        std::cin >> n >> m >> orcamento;

        precos = std::vector<std::vector<int>>(n, std::vector<int>(m));

        for (short int i = 0 ; i < n ; i++)
        {
            for (short int j = 0 ; j < m ; j++)
                std::cin >> precos[i][j];
        }

        for (short int i = 0 ; i < n ; i++)
        {
            std::vector<long long int> somaColuna(m, 0);

            for (short int j = i ; j < n ; j++)
            {
                int indiceAreaAtual = 0;
                long long int soma = 0;
                int area;

                for (short int k = 0 ; k < m ; k++)
                {
                    somaColuna[k] += precos[j][k];
                    soma += somaColuna[k];

                    while (soma > orcamento)
                        soma -= somaColuna[indiceAreaAtual++];

                    area = (j - i + 1) * (k - indiceAreaAtual + 1); // Os pedaços são retangulares

                    if (area > melhorArea)
                    {
                        melhorArea = area;
                        melhorPreco = soma;
                    }

                    else if (area == melhorArea && soma < melhorPreco)
                        melhorPreco = soma;
                }
            }
        }

        std::cout << "Case #" << caso++ << ": " << melhorArea << " " << melhorPreco << std::endl;
    }
    return 0;
}
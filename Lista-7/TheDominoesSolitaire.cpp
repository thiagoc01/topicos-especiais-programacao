#include <iostream>
#include <vector>

#define MAX_PECAS 14

/*
    Precisamos realizar uma busca em profundidade, testando todas as possibilidades
    de encaixes de peças, até preencher o espaço dado.
*/

int n, m;
std::pair<int, int> fim;
std::vector<std::pair<int, int>> pecas = std::vector<std::pair<int, int>>(MAX_PECAS);
std::vector<bool> pecaFoiUsada = std::vector<bool>(MAX_PECAS, false);

bool testaSolucao(std::pair<int, int> peca, int d, int i)
{
    if (d == n)
    {
        if (fim.first == peca.second)
            return true;

        else
            return false;
    }

    pecaFoiUsada[i] = true;

    for (int j = 0 ; j < m ; j++)
    {
        if (!pecaFoiUsada[j])
        {
            if (peca.second == pecas[j].first)
            {

                if (testaSolucao(pecas[j], d + 1, j))
                    return true;           
            }

            else if (peca.second == pecas[j].second)
            {
                auto aux = std::pair<int, int>({pecas[j].second, pecas[j].first});

                if (testaSolucao(aux, d + 1, j))
                    return true;
            }

            else
                continue;
        }
        
    }

    pecaFoiUsada[i] = false;

    return false;
}

bool buscadorSolucao(std::pair<int, int> raiz)
{
    for (int i = 0 ; i < m ; i++)
    {
        if (raiz.second == pecas[i].first)
        {
            if (testaSolucao(pecas[i], 1, i))
                return true;     
        }

        else if (raiz.second == pecas[i].second)
        {
            auto aux = std::pair<int, int>({pecas[i].second, pecas[i].first});

            if (testaSolucao(aux, 1, i))
                return true;
        }

        else
            continue;
    }

    return false;
}

int main()
{
    std::cin >> n;

    while (n)
    {
        int naoUsar;
        std::cin >> m;

        std::pair<int, int> inicio;

        std::cin >> naoUsar >> inicio.second;
        std::cin >> fim.first >> naoUsar;

        for (int i = 0 ; i < m ; i++)
            std::cin >> pecas[i].first >> pecas[i].second;

        if (buscadorSolucao(inicio))
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;

        pecaFoiUsada = std::vector<bool>(MAX_PECAS, false);

        std::cin >> n;
    }
    return 0;
}
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

/*
    Iremos reduzir os doces de um em um. Em qualquer caso possível, iremos ver que sempre teremos praticamente todos zerados, exceto por um, que será o último a ser consumido.
    O único caso impossível é o que o maior número possui pelo menos duas unidades a mais que os demais.
    Se isso ocorre, necessariamente ele será o próximo. Dessa forma, é impossível poder consumir os doces seguindo ambas as restrições.
    Para obter o resultado final, sem precisar percorrer o vetor inteiro e testar valores, além de subtrair, basta realizar uma ordenação decrescente.
    Com isso, iremos verificar os dois maiores valores, pois os demais serão zerados devido à restrição de não sequenciamento.
    Se os dois maiores valores têm uma diferença de uma ou nenhuma unidade, então não há um doce que terá a maior quantidade duas vezes seguidas.
*/

void verificaPossibilidade(const std::vector<int>& v)
{
    if (v.size() == 1)
    {
        if (v[0] == 1)
            std::cout << "YES" << std::endl;

        else
            std::cout << "NO" << std::endl;
    }
    
    else
    {
        std::vector<int> qtdDoces = std::vector<int>{v};

        std::sort(qtdDoces.begin(), qtdDoces.end(), [](int x, int y){ return x > y; });

        if (qtdDoces[1] - qtdDoces[0] == -1 || qtdDoces[1] - qtdDoces[0] == 0)
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;
    }
}

int main()
{
    int numCasos;
    
    std::cin >> numCasos;

    while (numCasos > 0)
    {
        int numTiposDoces;
        std::vector<int> numDoces;

        std::cin >> numTiposDoces;

        for (int i = 0 ; i < numTiposDoces ; i++)
        {
            int entrada;

            std::cin >> entrada;

            numDoces.push_back(entrada);
        }

        verificaPossibilidade(numDoces);

        numCasos--;
    }

    return 0;
}
#include <iostream>
#include <set>
#include <climits>
#include <vector>

/*
    Devemos imprimir número de trens que não estão na mesma velocidade,
    sem contar o primeiro que possui a velocidade dada, ou seja, o primeiro vagão do trem
    formado.

    Para que um trem seja formado, a velocidade deve ser maior ou igual que o vagão da frente,
    para que essa seja reduzida.
    
    Como queremos o cálculo complementar, iremos fazer o seguinte: guardamos um conjunto
    com os índices das posições do maior para o menor. 

    Ao receber o vetor de velocidades, se uma velocidade é menor que a da frente,
    inserimos nesse conjunto. Se esse vagão ou o da frente não forem alterados,
    necessariamente esse vagão não estará em um trem. Ou seja, o tamanho do conjunto descrito
    será exatamente o número de vagões que não estão em um trem.

    Em uma iteração, iremos reduzir a velocidade de um vagão.
    Se essa velocidade nova seguir o critério dito anteriormente, então esse é um vagão
    que não estará em um trem. Deverá ser inserido no conjunto.

    Após isso, devemos verificar se as velocidades no conjunto não são maiores ou iguais,
    pois se isso ocorre elas irão formar um trem com esse vagão.
    Com isso, devemos removê-las.

    A operação anterior pode ser feita usando busca binária, pois o conjunto está ordenado
    com as posições dos vagões da esquerda para a direita.

    Ao fim de uma iteração, o tamanho do conjunto representa o número de vagões que não possuem
    velocidade consecutiva.
*/

int main()
{   
    int numCasos;
    std::cin >> numCasos;

    while (numCasos--)
    {
        int n, m;
        std::set<int> indicesMenoresVelocidadesConsec;

        std::cin >> n >> m;

        std::vector<int> velocidades(n + 1);
        int ultimaVelocidade = INT_MAX;

        for (int i = 1 ; i <= n ; i++)
        {
            std::cin >> velocidades[i];

            if (ultimaVelocidade > velocidades[i])
            {
                ultimaVelocidade = velocidades[i];
                indicesMenoresVelocidadesConsec.insert(i);
            }
        }

        while (m--)
        {
            int vagao, velocidadeReducao;
            
            std::cin >> vagao >> velocidadeReducao;

            velocidades[vagao] -= velocidadeReducao;

            auto maiorVelocidadeAdjacente = --indicesMenoresVelocidadesConsec.upper_bound(vagao);

            if (velocidades[*maiorVelocidadeAdjacente] > velocidades[vagao])
                indicesMenoresVelocidadesConsec.insert(vagao);

            maiorVelocidadeAdjacente = indicesMenoresVelocidadesConsec.upper_bound(vagao);

            while (maiorVelocidadeAdjacente != indicesMenoresVelocidadesConsec.end() && velocidades[vagao] <= velocidades[*maiorVelocidadeAdjacente])
            {
                indicesMenoresVelocidadesConsec.erase(maiorVelocidadeAdjacente);
                maiorVelocidadeAdjacente = indicesMenoresVelocidadesConsec.upper_bound(vagao);
            }

            std::cout << indicesMenoresVelocidadesConsec.size() << " ";
        }

        std::cout << std::endl;
    }

    return 0;

}

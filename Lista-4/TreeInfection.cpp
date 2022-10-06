#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

/*
    Como temos a liberdade de escolher os vértices, podemos representar o grafo em um vetor.
    Para reduzir o tempo, devemos aplicar as duas operações sempre que possível.
    A primeira operação, para ser aplicada, precisa que um vértice tenha pelo menos um vizinho infectado para infectar outro.
    Logo, para aplicá-la no maior número de vezes, precisamos sempre utilizar os vértices com mais filhos.
    Pois, quando um estiver infectado, podemos sempre escolher os vizinhos, até zerar todos os vértices adjacentes ao pai.
    Para a segunda operação, devemos escolher vértices dos que possuem mais filhos na iteração.

    Como os vértices com mais filhos fornecem opção para a primeira operação, podemos ver que,
    se ordenarmos o vetor de número de adjacências de forma decrescente, a cada iteração i
    até a quantidade de nós com filhos mais a raiz podemos infectar até i + 1 vértices.

    O tempo mínimo de infecção é a quantidade de nós que possuem filhos mais a raiz.
    Podemos verificar se é possível infectar todos no tempo mínimo fazendo o seguinte:
    ordenamos o vetor de forma decrescente e para cada iteração até a quantidade de nós que possuem filhos mais a raiz,
    calculamos a subtração entre o i-ésimo vértice com mais filhos subtraído da quantidade de nós que possuem filhos mais a raiz acrescido de um.
    Se esse valor for 0, então é possível infectar o vértice e os adjacentes no tempo mínimo.
    Se esse valor for maior que 0, então não é possível infectar todos.
    Será necessário aplicar a primeira operação até todos estarem infectados.    
*/

int main()
{
    int numCasos;
    std::cin >> numCasos;

    while (numCasos--)
    {
        int numVertices;
        std::map<int, int> numFilhos; // Chave: vértice / Valor: Qtd. de filhos
        std::vector<int> nosNaoInfectados;

        std::cin >> numVertices;

        for (int i = 0 ; i < numVertices - 1 ; i++)
        {
            int pai;
            std::cin >> pai;

            numFilhos[pai]++;
        }

        for (const auto& n : numFilhos)
            nosNaoInfectados.push_back(n.second);
        
        nosNaoInfectados.push_back(1); // Inclui a raiz

        std::sort (nosNaoInfectados.begin(), nosNaoInfectados.end(), [](int n1, int n2){ return n1 > n2; });

        int tempo = nosNaoInfectados.size();
        int qtdZeros = 0;
        bool todosZerados = false;

        for (int i = 0 ; i < nosNaoInfectados.size() ; i++)
        {
            nosNaoInfectados[i] = std::max(nosNaoInfectados[i] - tempo + i, 0);

            if (nosNaoInfectados[i] == 0)
                qtdZeros++;
        }

        if (qtdZeros == tempo)
            todosZerados = true;

        while (!todosZerados)
        {
            std::sort (nosNaoInfectados.begin(), nosNaoInfectados.end(), [](int n1, int n2){ return n1 < n2; });

            for (int i = 0 ; i < nosNaoInfectados.size() ; i++)
            {
                if (nosNaoInfectados[i] > 0)
                    nosNaoInfectados[i]--;
            }

            if (nosNaoInfectados[nosNaoInfectados.size() - 1] > 0)
                nosNaoInfectados[nosNaoInfectados.size() - 1]--;

            tempo++;

            todosZerados = true;

            for (const auto& no : nosNaoInfectados)
            {
                if (no != 0)
                {
                    todosZerados = false;
                    break;
                }
            }
        }

        std::cout << tempo << std::endl;
    }
    return 0;
}
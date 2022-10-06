#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
    Problema simples de comparar valores com um valor específico.
    Uma busca binária fornece o resultado.
    A biblioteca padrão do C++ oferece uma implementação de complexidade logarítimica.
    Basta ordenar o vetor de preços de forma crescente e aplicar a função que retorna o iterador para o último valor possível.
    Subtraindo da posição inicial, encontramos o número de lojas possíveis para comprar a bebida no dia.
*/

int main()
{
    int numLojas, numDias;
    std::vector<int> precosBebida;

    std::cin >> numLojas;

    for (int i = 0 ; i < numLojas ; i++)
    {
        int preco;
        std::cin >> preco;

        precosBebida.push_back(preco);
    }

    std::cin >> numDias;
    std::sort(precosBebida.begin(), precosBebida.end());

    for (int i = 0 ; i < numDias ; i++)
    {
        int qtd;
        std::cin >> qtd;
        
        std::cout << std::upper_bound(precosBebida.begin(), precosBebida.end(), qtd) - precosBebida.begin() << std::endl;
    }

    return 0;
}
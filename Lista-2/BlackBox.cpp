#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <vector>

std::vector<int> numerosParaAdicionar; // Vetor A (ADD) com os valores fora de ordem a serem colocados na Black Box

/* Mapeia o vetor U (GET) onde a chave é o tamanho da Black Box onde iremos realizar um GET e o valor é o número de GETs que realizaremos nesse tamanho. */
std::unordered_map<int, int> posicoesParaRequisitar; 

int main()
{
    int numConjuntos;

    scanf("%d\n", &numConjuntos);

    while (numConjuntos--)
    {
        std::multiset<int> numeros; // Black Box utilizando multiset. Estrutura que funciona como uma heap binária.
        std::multiset<int>::iterator elementoMinimo; // Iterador que aponta para o i-ésimo elemento mínimo.
        int numAdicoes, numRequisicoes; // M, N

        std::cin >> numAdicoes;
        std::cin >> numRequisicoes;

        /* Inicializa vetor A */

        for (int i = 0 ; i < numAdicoes ; i++)
        {
            int num;
            std::cin >> num;
            numerosParaAdicionar.push_back(num);
        }

        /* Inicializa vetor U */

        for (int i = 0 ; i < numRequisicoes ; i++)
        {
            int tamanho;
            std::cin >> tamanho;

            if (posicoesParaRequisitar.find(tamanho) == posicoesParaRequisitar.end()) // Se o tamanho da Black Box não foi mapeado ainda
            {
                posicoesParaRequisitar.insert({tamanho, 1}); // Pelo menos um GET será efetuado quando estiver nesse tamanho.
            }
            
            else
                posicoesParaRequisitar[tamanho]++; // Já está mapeado, incrementa a contagem de GETs.
        }

        elementoMinimo = numeros.begin(); // Aponta para o primeiro elemento, assume como mínimo.

        for (int i = 0 ; i <= numerosParaAdicionar.size() ; i++) // Itera todo o vetor A
        {
            /* Se o tamanho da Black Box está no map, então devemos realizar um GET agora */

            if (posicoesParaRequisitar.find(numeros.size()) != posicoesParaRequisitar.end())
            {                
                posicoesParaRequisitar[numeros.size()]--; // Decrementa, pois vai realizar um GET.

                if (posicoesParaRequisitar[numeros.size()] == 0) // Se zerou, todos os GETs foram realizados. Removemos do map.
                    posicoesParaRequisitar.erase(numeros.size());

                i--; // Decrementa o índice da posição do vetor A, pois não inserimos o elemento.

                std::cout << *elementoMinimo++ << std::endl; // Imprime o i-ésimo elemento mínimo.             
            }

            else // Caso contrário, não será realizado um GET com o tamanho atual da Black Box.
            {
                numeros.insert(numerosParaAdicionar[i]); // Insere o número de forma ordenada crescentemente.

                /* Se o número inserido é menor que o elemento mínimo atual a ser impresso ou chegamos no fim da Black Box, devemos decrementar o iterador. */

                if (elementoMinimo == numeros.end() || *elementoMinimo > numerosParaAdicionar[i])
                    elementoMinimo--;
            }
        }

        /* Reinicia o vetor A e o map U auxiliares para a próxima iteração. */

        numerosParaAdicionar.clear();
        posicoesParaRequisitar.clear();

        if (numConjuntos) std::cout << std::endl;
    }

    return 0;
}
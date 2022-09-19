#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

/*
    Para atingir o objetivo, devemos organizar mini-pilhas, girando ao contrário, onde a base é o maior número que não está mais a direita na pilha principal.
    Quando giramos a mini-pilha, giramos a pilha principal tal que a base desta é o maior número menos a direita, ou seja, que não tenha sido flipado.
    Ao realizar essas organizações de mini-pilhas, iremos chegar até ao topo, com a pilha ordenada de forma crescente.
*/

void realizaFlip(std::vector<int>& v, int pos) // pos é a posição do maior elemento, servindo como base da mini-pilha
{
    for (int i = 0 ; i <= pos / 2 ; i++)
        std::swap(v[i], v[pos - i]); // Realiza a troca de forma espelhada
}

int main()
{
    std::string entrada;

    while (std::getline(std::cin, entrada))
    {
        int auxLeitura, posMaior; // auxLeitura : para receber um inteiro da entrada; posMaior : índice do maior número que não foi flipado
        std::vector<int>::iterator itPosMaior; // Iterador que aponta para o maior número que não foi flipado
        std::istringstream nums = std::istringstream(entrada); // Inteiros em forma de string para entrada formatada
        std::vector<int> pilha; // Pilha com os números

        std::cout << entrada << std::endl;

        while (nums >> auxLeitura) // Recebe entrada formatada
            pilha.push_back(auxLeitura);

        for (int qtdElementos = 0 ; qtdElementos < pilha.size() ; qtdElementos++)
        {
            itPosMaior = std::max_element(pilha.begin(), pilha.end() - qtdElementos); // Acha o maior número que não foi flipado
            posMaior = std::distance(pilha.begin(), itPosMaior); // Calcula a posição dele

            if (posMaior != pilha.size() - qtdElementos - 1) // Depois que a pilha está organizada, só iremos obter números flipados
            {
                if (posMaior != 0) // Se está no topo, já está pronto para ser flipado. Caso contrário, flipamos uma mini-pilha, onde posMaior é a base
                {
                    realizaFlip(pilha, posMaior);
                    std::cout << pilha.size() - posMaior << " ";                
                }

                realizaFlip(pilha, pilha.size() - qtdElementos - 1);
                std::cout << qtdElementos + 1 << " ";                
            }
        }

        std::cout << "0" << std::endl;        
    }

    return 0;
}
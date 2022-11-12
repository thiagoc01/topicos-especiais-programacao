#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
    Outro problema de backtracking.
    Devemos pegar uma letra, fixar na primeira posição e depois chamar a função novamente
    para realizar a mesma coisa.
    Se percorrermos todas as letras na chamada recursiva, iremos ter as permutações,
    pois sempre chegamos à folha.
    Obviamente, para realizar da forma que o enunciado pede, o texto recebido deve estar em ordem léxica crescente.
    Quando utilizamos a letra, marcamo-na para não ser reutilizada.
    Caso contrário, teríamos a mesma letra sendo reutilizada várias vezes.
*/

#define MAX 10

std::vector<bool> letraFoiUsada = std::vector<bool>(MAX, false); // Marca os usos das letras
std::string texto; // Entrada

void geraPermutacoes(std::string& perm)
{
    if (perm.size() == texto.size()) // Colocamos todas as letras, imprimos.
    {
        std::cout << perm << std::endl;
        return;
    }

    char ultimo = '\0'; // Marcamos o último utilizado

    for (int i = 0 ; i < texto.size() ; i++)
    {
        if (!letraFoiUsada[i] && texto[i] != ultimo)
        {
            letraFoiUsada[i] = true;

            perm.push_back(texto[i]);
            
            ultimo = texto[i];

            geraPermutacoes(perm);

            perm.pop_back();

            letraFoiUsada[i] = false;
        }
    }
}

int main()
{
    int numCasos;

    std::cin >> numCasos;

    while (numCasos--)
    {
        std::string permutacao;

        std::cin >> texto;

        std::sort(texto.begin(), texto.end());

        geraPermutacoes(permutacao);

        std::cout << permutacao << std::endl;

        permutacao.clear();

        for (auto u : letraFoiUsada)
            u = false;
    }

    return 0;
}
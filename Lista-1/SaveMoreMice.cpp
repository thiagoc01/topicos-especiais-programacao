#include <iostream>
#include <vector>
#include <algorithm>



int main()
{
    int numCasos;

    std::cin >> numCasos;

    while (numCasos--)
    {
        int numPontos, numRatos, coordenadaGato = 0, ratosSalvos = 0;
        bool ratoFoiCapturado = false;
        std::vector<int> coordenadasRatos;

        std::cin >> numPontos;
        std::cin >> numRatos;

        for (int i = 0 ; i < numRatos ; i++)
        {
            int coordenada;

            std::cin >> coordenada;

            coordenadasRatos.push_back(coordenada);
        }

        std::sort(coordenadasRatos.begin(), coordenadasRatos.end(), [](int n1, int n2) { return n1 > n2; });        

        for (const auto& rato : coordenadasRatos)
        {
            if (rato > coordenadaGato)
            {
                coordenadaGato += (numPontos - rato);
                ratosSalvos++;
            }

            else
                break;
        }

       std::cout << ratosSalvos << std::endl;
    }

    return 0;
    
}
#include <iostream>
#include <string>

int main()
{
    int numCasos;
    std::cin >> numCasos;

    while (numCasos--)
    {
        std::string entrada;
        int remocoes, contagemBrancos = 0, comprimento, tamSequencia;

        std::cin >> comprimento;
        std::cin >> tamSequencia;
        std::cin >> entrada;
        
        for (int i = 0 ; i < tamSequencia ; i++)
        {
            if (entrada[i] == 'W')
                contagemBrancos++;
        }

        remocoes = contagemBrancos;

        for (int i = tamSequencia ; i < comprimento ; i++)
        {
            if (entrada[i] == 'W')
                contagemBrancos++;
                
            if (entrada[i - tamSequencia] == 'W')
                contagemBrancos--;

            remocoes = std::min(remocoes, contagemBrancos);
        }

        std::cout << remocoes << std::endl;
    }

    return 0;
}
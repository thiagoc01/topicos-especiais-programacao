#include <iostream>
#include <vector>
#include <string>
#include <cstring>

typedef struct Cubo
{
    short int cores[6];
} Cubo;

typedef struct CuboResposta
{
    short int cor, id;
} CuboResposta;

const std::string posicoes[6] = {"front", "back", "left", "right", "top", "bottom"};
std::vector<std::vector<short int>> nivelCorCubo;
std::vector<Cubo> cubos;
std::vector<CuboResposta> torre, aux;
short int n;

void constroiTorre(short int id, short int base, short int nivel, short int& resultado)
{
    for (short int i = id + 1; i <= n ; i++)
    {
        for (short int j = 0 ; j < 6 ; j++)
        {
            if (id == 0 || (cubos[i].cores[j] == base && nivelCorCubo[i][j] < nivel + 1))
            {
                nivelCorCubo[i][j] = nivel + 1;

                if (j % 2 == 1)
                {
                    aux[nivel].id = i;
                    aux[nivel].cor = j;
                    constroiTorre(i, cubos[i].cores[j - 1], nivel + 1, resultado);
                }

                else
                {
                    aux[nivel].id = i;
                    aux[nivel].cor = j;
                    constroiTorre(i, cubos[i].cores[j + 1], nivel + 1, resultado);
                }
            }
        }
    }

    if (resultado < nivel)
    {
        resultado = nivel;

        for (short int i = 0 ; i < nivel ; i++)
            torre[i] = aux[i];
    }
}

int main()
{
    int numCasos = 1;

    std::cin >> n;

    while (n)
    {
        cubos = std::vector<Cubo>(n + 1);
        torre = std::vector<CuboResposta>(n + 1);
        aux = std::vector<CuboResposta>(n + 1);

        short int tamanhoTorre = 0;

        for (short int i = 1 ; i <= n ; i++)
        {
            for (short int j = 0 ; j < 6 ; j++)
                std::cin >> cubos[i].cores[j];
        }

        nivelCorCubo = std::vector<std::vector<short int>>(n + 1, std::vector<short int>(6, 0));

        constroiTorre(0, 0, 0, tamanhoTorre);

        std::cout << "Case #" << numCasos++ << std::endl << tamanhoTorre << std::endl;

        for (short int i = 0 ; i < tamanhoTorre ; i++)
            std::cout << torre[i].id << " " << posicoes[torre[i].cor] << std::endl;            
            
        std::cout << std::endl;

        std::cin >> n;
    }

    return 0;
}


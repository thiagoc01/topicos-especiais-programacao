#include <iostream>
#include <string>
#include <map>

/*
    A ideia é casar pares de letras, seguindo o critério da próxima letra ser igual a anterior.
    Se encontramos um caso que isso não ocorre, devemos percorrer até encontrar uma letra igual.
    Tudo que estiver nesse intervalo serão letras descartadas.
    Para sabermos quando parar, basta manter um mapeamento onde a letra é a chave e as ocorrências o valor.
    Quando uma tiver o valor 2, então essa será o fim do intervalo.
*/

int main()
{
    int numCasos;

    std::cin >> numCasos;

    while (numCasos > 0)
    {
        std::string string;
        int qtdIntrusas = 0, i;
        std::map<char, int> letrasOcorrencias;

        std::cin >> string;

        for (i = 0 ; i < string.size() - 1 ; i++)
        {
            if (string[i] == string[i + 1])
                i++;

            else
            {
                while (i < string.size() && letrasOcorrencias[string[i]] != 1)
                {
                    letrasOcorrencias[string[i]] = 1;
                    qtdIntrusas++;
                    i++;
                }
                
                if (i < string.size())
                    qtdIntrusas--;
                
                letrasOcorrencias.clear();                
            }
        }

        if (i == string.size() - 1)
            qtdIntrusas++;

        std::cout << qtdIntrusas << std::endl;

        numCasos--;
    }

    return 0;
}
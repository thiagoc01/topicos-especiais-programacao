#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    std::string entrada, aux;
    int tamanhoSenha;

    while (std::cin >> tamanhoSenha)
    {
        std::cin >> entrada;

        int maior = 0;
        std::string maisOcorrencias;
        std::unordered_map<std::string, int> ocorrencias;

        for (int i = 0 ; i < entrada.size() - tamanhoSenha + 1 ; i++)
        {
            aux = entrada.substr(i, tamanhoSenha);

            ocorrencias[aux]++;
        }

        for (const auto& obj : ocorrencias)
        {
            if (obj.second > maior)
            {
                maior = obj.second;
                maisOcorrencias = obj.first;
            }
        }

        std::cout << maisOcorrencias << std::endl;
    }
    
    return 0;
}
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

/*
    Temos a liberdade de escolher qualquer número maior ou igual a 2.
    Portanto, o número de tipos casos em que há problema é muito baixo.
    Como não podemos escolher 0 e 1, é possível verificar que,
    se um número deixar resto 1 e outro deixar 0, não há solução.
    Assim como, se houver 1, redução a 0 não será possível e vice-versa.
    O outro caso é, se existem dois números consecutivos, é ímpossível haver solução,
    pois um será 0 e outro será 1 após aplicar a operação do enunciado.
*/

int main()
{
    int numCasos;    

    std::cin >> numCasos;

    while (numCasos--)
    {
        std::unordered_map<int, int> ocorrenciasNumeros;
        std::vector<int> numeros;
        int qtdNums;

        std::cin >> qtdNums;

        while (qtdNums--)
        {
            int numero;
            std::cin >> numero;

            numeros.push_back(numero);
            ocorrenciasNumeros[numero]++;
        }

        std::sort(numeros.begin(), numeros.end()); // Para realizar a comparação de números consecutivos

        /* Caso em que temos 0 e 1 e o 1 não pode ser reduzido a 0, o que torna impossível igualar o vetor. */

        if (ocorrenciasNumeros[0] != 0 && ocorrenciasNumeros[1] != 0) 
            std::cout << "NO" << std::endl;
        
        /* Caso em que o vetor interior é igual a 1 ou não há 1. Logo, todos os números podem ser reduzidos a 0. */

        else if (ocorrenciasNumeros[1] == numeros.size() || ocorrenciasNumeros[1] == 0)
            std::cout << "YES" << std::endl;

        else
        {
            bool ok = true;

            if (ocorrenciasNumeros[2] != 0) // Se chegamos aqui, então há pelo menos um 1. Logo, se há pelo menos um 2, teremos o caso 0 e 1.
            {
                std::cout << "NO" << std::endl;
                ok = false;
            }

            else
            {
                for (int i = 0 ; i < numeros.size() - 1 ; i++)
                {
                    if (numeros[i + 1] - numeros[i] == 1) // Há números consecutivos, caíremos no caso 0 e 1.
                    {
                        std::cout << "NO" << std::endl;
                        ok = false;
                        break;
                    }
                }
            }            

            if (ok) // Não há problemas para reduzir o vetor
                std::cout << "YES" << std::endl;
        }
    }

    return 0;
}

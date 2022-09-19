#include <iostream>
#include <algorithm>
#include <vector>
/*
    O critério de divisibilidade por 25 é os dois últimos algarismos serem 00, 25, 50 ou 75, pois, ao decompor um número decimal, temos: a1 * 10 + a0 === 0 mod 25 
    Com isso, iremos procurar, para cada dígito 0, 2, 5 ou 7, o seu par, supondo que eles estivessem juntos, ao percorrer realizando um segundo laço.
    Se eles forem 00, 25, 50 ou 75, iremos remover todos os números entre eles.
    Como queremos a distância mínima, será verificado se encontramos um par tal que a distância seja menor que a do par anterior.
*/

int main()
{
    int numCasos;

    std::cin >> numCasos;

    while (numCasos > 0)
    {
        std::string numero;
        int remocoes;

        std::cin >> numero;

        remocoes = numero.length();

        for (int i = 0 ; i < numero.length() ; i++)
        {
            if (numero[i] != '0' && numero[i] != '2' && numero[i] != '5' && numero[i] != '7') // O primeiro algarismo dos últimos dois dígitos é 0, 2, 5 ou 7. Não há por que seguir em frente.
                continue;

            for (int j = i + 1 ; j < numero.length() ; j++)
            {
                if (numero[j] != '0' && numero[j] != '5') // O segundo algarismo dos últimos dois dígitos é 0 ou 5. Não há por que seguir em frente.
                    continue;

                int aux = 10 * std::stoi(std::string{numero[i]}) + std::stoi(std::string{numero[j]}); // Verificamos se é um par 00, 25, 50 ou 75. 

                if (aux % 25 == 0) // Se o número anterior for 00, 25, 50 ou 75, qualquer número entre eles será descartado. Logo, iremos uni-los para torná-los os dois últimos dígitos.
                {
                    remocoes = std::min(remocoes, (int) numero.length() - (i + 2));
                }
            }
        }

        std::cout << remocoes << std::endl;

        numCasos--;
    }

    return 0;
}
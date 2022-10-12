#include <iostream>
#include <string>

/*
    Para um número ser divisível por 60, precisamos que ele seja divisível por 3, 4 e 5.
    Para ser divisível por 3, basta somar todos os dígitos e ver se essa soma é divisível por 3.
    Para ser divisível por 4, precisamos que os últimos dois dígitos sejam divisíveis por 4.
    Entretanto, como devemos ter pelo menos um zero, se tivermos 2 pares ou mais,
    então o número é divisível por 4.
    Para ser divisível por 5, basta ter pelo menos um zero.

    Logo, as condições são: ter a soma dos dígitos divisível por 3, ter um zero ao menos e ter mais de um par.
*/

int main()
{
    int numGrandeMestres;

    std::cin >> numGrandeMestres;

    for (int i = 0 ; i < numGrandeMestres ; i++)
    {
        std::string numero;
        unsigned long long int somaDigitos = 0;
        int numPares = 0;
        bool temZero = false;

        std::cin >> numero;

        for (const auto& digito : numero)
        {
            int d = std::stoi(std::string{digito});
            
            if (d % 2 == 0)
                numPares++;

            if (d == 0)
                temZero = true;

            somaDigitos += d;
        }

        if (numPares > 1 && somaDigitos % 3 == 0 && temZero)
            std::cout << "red" << std::endl;
        
        else
            std::cout << "cyan" << std::endl;
    }

    return 0;
}
#include <iostream>
#include <vector>

/*
    Como cada ataque causa 1 de dano a cada segundo, precisamos encontrar o primeiro valor
    tal que a soma do dano até ali seja o dano mínimo.
    Isso pode ser feito realizando uma busca binária nos momentos de ataque até encontrar
    uma soma dos ataques onde o último ataque não seja maior que o próximo.

    Assumimos que o menor dano possível é o meio entre o maior ataque possível, que é a quantidade de dano necessária,
    e o mínimo, que é 1.

    A partir daí, percorremos os ataques dados e comparamos o ataque atual com o posterior.
    Se essa distância é menor que o meio, então levamos menos tempo para causar o dano.
    Logo, o dano causado é a distância entre eles.
    Caso contrário, um ataque não sobrepõe o outro e devemos esperar o tempo mínimo, que é o meio atual.

    Se o dano obtido total é maior ou igual a quantidade de dano, o dano médio é exatamente o mínimo necessário.
    Diminuímos o maior ataque possível para esse valor menos um, para encontrar melhora.

    Caso contrário, o dano médio não é suficiente. Aumentamos o menor ataque possível e mantemos os segundos necessários.
*/

int main()
{
    int numCasos;

    std::cin >> numCasos;

    while (numCasos--)
    {
        unsigned short int numAtaques;
        unsigned long long int qtdDano, segundos, menorAtaquePossivel = 1, maiorAtaquePossivel;
                
        std::vector<unsigned long long int> ataques;

        std::cin >> numAtaques;
        std::cin >> qtdDano;

        maiorAtaquePossivel = segundos = qtdDano;

        for (unsigned short int i = 0 ; i < numAtaques ; i++)
        {
            unsigned long long int ataque;
            std::cin >> ataque;

            ataques.push_back(ataque);
        }      

        while (menorAtaquePossivel <= maiorAtaquePossivel)
        {
            unsigned long long int meio = (menorAtaquePossivel + maiorAtaquePossivel) / 2;

            unsigned long long int dano = 0;

            for (unsigned short int i = 0 ; i < numAtaques - 1; i++)
            {
                if ((ataques[i + 1] - ataques[i]) <= meio)
                    dano += (ataques[i + 1] - ataques[i]);
                    
                else
                    dano += meio;               
            }

            dano += meio;

            if (dano >= qtdDano)
            {
                segundos = meio;
                maiorAtaquePossivel = meio - 1;
            }
            
            else
                menorAtaquePossivel = meio + 1;
        }

        std::cout << segundos << std::endl;
    }

    return 0;
}
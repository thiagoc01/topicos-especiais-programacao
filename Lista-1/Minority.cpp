#include <iostream>
#include <string>

int main()
{
    int numCasos;

    std::cin >> numCasos;

    while (numCasos--)
    {
        int contZero = 0, contUm = 0;
        std::string string;

        std::cin >> string;

        for (const auto& numero : string)
        {
            if (numero == '0')
                contZero++;
            else
                contUm++;
        }

        if (contZero != contUm)
            std::cout << std::min(contZero, contUm) << std::endl;
        else
            std::cout << contZero - 1 << std::endl;
    }

    return 0;
}
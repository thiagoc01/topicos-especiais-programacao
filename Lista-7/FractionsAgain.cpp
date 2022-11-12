#include <iostream>
#include <vector>

/*
    Dado um k, o maior valor que podemos ter é 2k, já que 1/2k + 1/2k = 1/k.
    Logo, o teto de verificação é 2k.

    Caso x >= 2k, como x >= y e 1/x + 1/y = 1/k, é impossível que y seja k, pois x é
    um inteiro positivo. Logo, o piso é k + 1.

    Agora, dado que x >= y, basta isolar o 1/x e teremos:

    1/k - 1/y = 1/x <=> 1/x = (y - k) / (k * y)  <=> x = (k * y) / (y - k)

    Como x é inteiro, basta que a divisão anterior seja um inteiro para que x e y sejam inteiros.
*/

int main()
{
    short int k;

    while (std::cin >> k)
    {
        std::vector<std::pair<int, int>> pares;

        for (int y = k + 1 ; y <= 2 * k ; y++)
        {
            if ( (k * y) % (y - k) == 0 )
                pares.push_back({(k * y) / (y - k), y});
        }

        std::cout << pares.size() << std::endl;

        for (const auto &p : pares)
        {
            std::cout << "1/" << k << " = 1/" << p.first
                    << " + 1/" << p.second << std::endl;
        }
    }

    return 0;
}
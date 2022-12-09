#include <iostream>
#include <string>
#include <vector>


int main()
{
    std::string s;
    std::vector<long long int> wEsquerdo, wDireito;
    long long int numWows = 0;
    std::cin >> s;

    wEsquerdo = std::vector<long long int>(s.size() + 2, 0);
    wDireito = std::vector<long long int>(s.size() + 2, 0);

    for (int i = 1 ; i < s.size() ; i++)
    {
        if (s[i] == 'v' && s[i - 1] == 'v')
            wEsquerdo[i] = wEsquerdo[i - 1] + 1;

        else
            wEsquerdo[i] = wEsquerdo[i - 1];
    }

    for (int i = s.size() - 1 ; i > 0 ; i--)
    {
        if (s[i] == 'v' && s[i - 1] == 'v')
            wDireito[i] = wDireito[i + 1] + 1;

        else
            wDireito[i] = wDireito[i + 1];
    }

    for (int i = 0 ; i < s.size() ; i++)
    {
        if (s[i] == 'o')
            numWows += wEsquerdo[i] * wDireito[i];
    }

    std::cout << numWows;

    return 0;
}
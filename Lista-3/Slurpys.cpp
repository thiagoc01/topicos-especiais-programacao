#include <string>
#include <iostream>

bool verificaSlump(const std::string& s, int &i)
{
    if (s[i] != 'D' && s[i] != 'E')
        return false;
    
    if (s[++i] != 'F')
        return false;
    
    while (s[i] == 'F')
    {
        i++;
    }

    if (s[i] == 'G')
    {
        i++;
        return true;
    }
    return verificaSlump(s, i);
}

bool verificaSlimp(const std::string& s, int &i)
{
    if (s[i] != 'A')
        return false;
    
    if (s[++i] == 'H')
    {
        i++;
        return true;
    }

    if (s[i] == 'B')
    {
        i++;
        
        bool ret = verificaSlimp(s, i) && s[i] == 'C';

        i++;

        return ret;
    }

    bool ret = verificaSlump(s, i) && s[i] == 'C';

    i++;

    return ret;


}

bool verificaSlurpy(std::string s)
{
    int i = 0;
    return verificaSlimp(s,i) && verificaSlump(s, i) && i == s.size();
}

int main()
{
    int numStrings;

    std::cin >> numStrings;
    std::cout << "SLURPYS OUTPUT" << std::endl;

    while (numStrings--)
    {
        std::string stringEntrada;
        std::cin >> stringEntrada;

        if(verificaSlurpy(stringEntrada))
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;
    }

    std::cout << "END OF OUTPUT" << std::endl;

    return 0;
}

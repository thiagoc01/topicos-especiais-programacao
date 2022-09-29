#include <iostream>
#include <string>
#include <map>
#include <sstream>


int main()
{
    std::string s1, s2;

    while (std::getline(std::cin, s1) && std::getline(std::cin, s2))
    {
        
        std::map<char, int> ocorrString1;
        std::map<char, int> ocorrString2;
        std::string resultado;
        std::map<char, int>::iterator it1, it2;

        for (int i = 0 ; i < 26 ; i++)
        {
            ocorrString1.insert({'a' + i, 0});
            ocorrString2.insert({'a' + i, 0});
        }

        for (int i = 0 ; i < s1.size() ; i++)
            ocorrString1[s1[i]]++;
        
        for (int i = 0 ; i < s2.size() ; i++)
            ocorrString2[s2[i]]++;

        
        it1 = ocorrString1.begin();
        it2 = ocorrString2.begin();

        for (int i = 0 ; i < 26 ; i++)
        {
            int ocorrenciasLetra = std::min(it1->second, it2->second);

            while (ocorrenciasLetra > 0)
            {
                resultado += it1->first;
                ocorrenciasLetra--;
            }

            it1++;
            it2++;
        }

        std::cout << resultado << std::endl;
    

    }
    return 0;
}


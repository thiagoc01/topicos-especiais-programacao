#include <iostream>
#include <cmath>
#include <string>

int main()
{
    std::string n;
    short int resultado, nModQuatro;

    std::cin >> n;

    /* Teorema de Fermat : Se mdc(a, p) = 1 e p é primo, então a^(p - 1) == 1 mod p 
        Como p = 5 no problema e p - 1 = 4, basta decompormos o n no formato n = 4x + y, onde x e y são inteiros.
        Isso é equivalente a fazer n % 4.
        Com isso, descobrimos o número tal que a^n é congruente a ele no módulo 5.
    */
    
    if (n.length() == 1)
        nModQuatro = stoi(n) % 4;

    else
        nModQuatro = stoi(n.substr(n.length() - 2)) % 4;

    resultado = static_cast<unsigned long long int>(1 + std::pow(2, nModQuatro) + std::pow(3, nModQuatro) + std::pow(4, nModQuatro)) % 5;

    std::cout << resultado << std::endl;

    return 0;
}
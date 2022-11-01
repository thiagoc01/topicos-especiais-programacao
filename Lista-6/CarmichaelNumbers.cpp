#include <iostream>
#include <vector>

/*
    Precisamos testar se a^n === a mod n para um n dado.
    Se esse resultado valer para qualquer n entre 2 e n - 1, o número é de Carmichael.
    Entretanto, os primos, pelo teorema de Fermat, irão atender ao resultado.
    Logo, devemos fazer um crivo para eliminar os primos.

    Como, em C++, ocorre overflow ao fazer base ^ expoente para números grandes,
    devemos usar um método alternativo.

    Temos que base ^ 2 == base * base mod n == (base mod n * base mod n) mod n.
    Logo, se tivermos potência de 2 no expoente, podemos partir de base mod n até base ^ 2 ^ n mod n.

    Generalizando para qualquer expoente, podemos fazer o seguinte processo:
        - Transformar o número em binário;
        - Para cada i-ésimo dígito 1, esse i será o expoente para a base;
        - Depois basta realizar a operação anterior.

    No código, poderíamos fazer o seguinte. Se o expoente é ímpar, então é o caso em que o último bit é 1 e esse seria um expoente válido.
    Com isso, pegamos o resultado atual e multiplicamos pela base.
    Dividimos o expoente por 2 para obter o próximo bit (direita para a esquerda) e elevamos a base ao quadrado.
    Somente guardamos no resultado quando o último bit for 1, o qual representaria uma potência 2^i.
*/

std::vector<bool> numeros = std::vector<bool>(65005, true); // Supõe-se que todos são primos

std::vector<unsigned short int> primos = std::vector<unsigned short int>(65000, -1);

void iniciaCrivo()
{
    primos[2] = 2;

    for (long long int i = 3 ; i * i <= 65000 ; i += 2)    //even numbers are exclusive
    {
        if (numeros[i]) // É primo
        {
            for (long long int j = i * i ; j <= 65000 ; j += i)
                numeros[j] = false;
        }
    }

    for (unsigned short int i = 3 ; i <= 65000 ; i += 2)
    {
        if (numeros[i])
            primos[i] = i;
    }
}

bool retornaPrimalidade(const unsigned short int &b, const unsigned short int &e, const unsigned short int &m)
{
    long long baseElevadoExpoenteReduzidoMod = 1, base = b, expoente = e, modulo = m;
    const unsigned short int baseOriginal = base;

    while (expoente)
    {
        if(expoente % 2 == 1)
            baseElevadoExpoenteReduzidoMod = baseElevadoExpoenteReduzidoMod * base % modulo;

        expoente /= 2;

        base = base * base % modulo;
    }
    
    if (baseElevadoExpoenteReduzidoMod == baseOriginal)
        return true;

    else
        return false;
}

bool eNumCarmichael(const unsigned short int &n)
{
    if (primos[n] == n)
        return false;

    for (unsigned short int i = 2 ; i < n - 1 ; i++)
    {
        if (!retornaPrimalidade(i, n, n))
            return false;
    }

    return true;
}


int main()
{
    unsigned short int n;

    iniciaCrivo();

    while (std::cin >> n && n)
    {
        if (eNumCarmichael(n))
           std::cout << "The number " << n << " is a Carmichael number." << std::endl;

        else
           std::cout << n << " is normal." << std::endl;   
    }

    return 0;
}
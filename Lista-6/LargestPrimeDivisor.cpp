#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

std::vector<bool> numeros = std::vector<bool>(100000000, true); // Supõe-se que todos são primos

std::vector<long long int> primos;

void iniciaCrivo()
{
    primos.push_back(2);

    for (long long int i = 3 ; i * i <= 10000000 ; i += 2)    //even numbers are exclusive
    {
        if (numeros[i]) // É primo
        {
            for (long long int j = i * i ; j <= 10000000 ; j += i * i)
                numeros[j] = false;
        }
    }

    for (long long int i = 3 ; i <= 10000000 ; i += 2)
    {
        if(numeros[i])
            primos.push_back(i);
    }        
}

int main()
{
    long long int n;

    iniciaCrivo(); // Poderíamos passar o n, mas iríamos fazer o crivo m vezes, onde m é a quantidade de números no input

    while (std::cin >> n && n)
    {
        long long int maiorDivisorPrimo = 0, numeroPrimosDivisores = 0;

        if (n < 0)
            n = static_cast<long long int>(std::abs(n));

        for (long long int i = 0 ; i < primos.size() && primos[i] * primos[i] <= n ; i++)
        {
            if (n % primos[i] == 0)
            {
                numeroPrimosDivisores++;
                maiorDivisorPrimo = primos[i];

                while (n % primos[i] == 0) // Fatora o número com esse primo até reduzir o expoente a 0
                    n /= primos[i];
                
            }            
        }

        if (n > 1) // Caso em que atingimos o teto de análise, mas o número ainda deve ser dividido
        {
            numeroPrimosDivisores++;
            maiorDivisorPrimo = n;
        }


        if (numeroPrimosDivisores > 1) // Há mais de um divisor
            std::cout << maiorDivisorPrimo << std::endl;

        else
            std::cout << -1 << std::endl;
    }

    return 0;
}
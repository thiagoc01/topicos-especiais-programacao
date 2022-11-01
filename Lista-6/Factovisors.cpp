#include <iostream>
#include <vector>

/*
    Para resolver o problema, precisamos verificar se a quantidade de um fator em n! é maior ou igual à quantidade desse fator em m.
    Caso contrário, m não divide n.

    Primeiro, precisamos obter os primos até a maior entrada do programa. 
    Como vamos até 2 ^ 31 - 1 para n e m, basta calcular até 2 ^16 aproximadamente.

    Em seguida, realizamos a fatoração do m, como no problema Largest Prime Divisor.
    Se um dado fator não divide m, ele não divide n! devido à transitividade.
    Logo, não precisamos verificar.

    Após fatorar m, comparamos se o expoente de cada fator primo é menor ou igual à quantidade desse fator em n!.
    Caso isso não ocorra, o m não divide n!.

    Para contar a quantidade de um fator primo em n!, basta dividir n pelo fator primo e somar esse quociente à variável acumuladora.
    Repetiremos isso até n ser 0.
    A quantidade correta é obtida pelo simples fato de reduzirmos o n a cada iteração para a potência inferior do primo mais próxima dele.
    Entre essa potência e o n da iteração, existem exatamente o quociente como quantidade de ocorrências desse fator.
    Se o n for uma potência desse primo, ainda restarão os outros primos. Mas esses serão incluídos na próxima iteração.

    Se, ao final do for, o m for maior que 1 e o n for menor que o m, necessariamente o m possui um fator primo que não divide n!.
    Portanto, não é possível que m divida n!.

*/

std::vector<bool> numeros = std::vector<bool>(65550, true); // Supõe-se que todos são primos

std::vector<int> primos;

void iniciaCrivo()
{
    primos.push_back(2);

    for (long long int i = 3 ; i * i <= 65000 ; i += 2) 
    {
        if (numeros[i]) // É primo
        {
            for (long long int j = i * i ; j <= 65000 ; j += i)
                numeros[j] = false;
        }
    }

    for (int i = 3 ; i <= 65000 ; i += 2)
    {
        if (numeros[i])
            primos.push_back(i);
    }
}

bool eDivisivel(int n, int m)
{
    for (std::vector<int>::size_type i = 0 ; i < primos.size() && primos[i] * primos[i] <= m ; i++)
    {
        if (m % primos[i] == 0) // Esse fator existe no m. Consequentemente, existe no n!.
        {
            int nAntes = n; // Iremos usar o n à frente, não podemos modificá-lo.
            int contagemExpoenteNFatorial = 0, contagemExpoenteM = 0; // Contagem desse fator primo em n! e m

            while (m % primos[i] == 0) // Fatora o número e incrementa a contagem do expoente
            {
                m /= primos[i];
                contagemExpoenteM++;
            }

            while (nAntes) // Fatora o n para obter a quantidade desse fator primo em n!
            {
                nAntes /= primos[i];

                /* O quociente anterior é o número de vezes que o fator primo ocorre entre o n dessa iteração e a potência do primo mais inferior ao n atual. */

                contagemExpoenteNFatorial += nAntes; 
            }

            if (contagemExpoenteNFatorial < contagemExpoenteM) // Há mais fatores em m do que em n, não há como dividir
                return false;
        }
    }

    if (m > 1 && n < m) // Se m é maior que 1 e n é menor que m, m é primo que não consta em n!
        return false;

    return true;
}

int main()
{
    int n, m;

    iniciaCrivo();

    while (std::cin >> n && std::cin >> m)
    {
        if (eDivisivel(n, m))
            std::cout << m << " divides " << n << "!" << std::endl;

        else
            std::cout << m << " does not divide " << n << "!" << std::endl;
    }

    return 0;
}
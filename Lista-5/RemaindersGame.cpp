#include <iostream>
#include <algorithm>

/*
    Pelo teorema chinês do resto, um conjunto de equações modulares em vários módulos da forma x == a_i mod c_i
    pode ser reduzido a uma equação x == a mod n, onde n é o produto de todos os c_i.
    Como, nesse caso, temos o n e temos as equações e os c_i's, basta fazer a seguinte análise:
    c_i divide x - a_i pela definição de congruência.
    Dessa forma, se o mdc(k, mmc(c1, c2, ..., c_n)) for maior ou igual a k, então Arya consegue descobrir a resposta.
    O que dizemos é que k divide x - a_i para todo c_i.

    Pela propriedade do mdc, mdc(k, mmc(c1, c2, ..., cn)) = mmc(mdc(c1, k), mdc(c2, k), ..., mdc(c_n, k)).
    Devemos lembrar que o mmc/mdc são associativos.
    E, ainda, mmc(a, b) * mdc(a, b) = a * b.

    Ao chegarmos ao final de todos os c_i dados, basta verificar se o mdc (= mmc) é divisível por k.
*/

int main()
{
    long long int n, k, mmc = 1, mdcInterno, numeroAuxiliar;

    std::cin >> n >> k;

    for (int i = 0 ; i < n ; i++)
    {
        std::scanf("%lld", &numeroAuxiliar);

        mdcInterno = std::__gcd(numeroAuxiliar, k);
        mmc = mmc * mdcInterno / std::__gcd(mmc, mdcInterno);
    }   

    if (mmc >= k)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}
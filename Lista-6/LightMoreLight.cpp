#include <iostream>
#include <cmath>

/*
    Precisamos apenas analisar apenas o último interruptor.
    Claramente, como ele só tem dois estados e esses são alterados
    se o identificador do interruptor é divisível por um número,
    basta ver se ele tem uma quantidade ímpar de divisores, já
    que as lâmpadas estão desligadas e somente ao acionar o interruptor
    uma quantidade ímpar de vezes é que ele fica ligado.
    Como isso é custoso demais para um número grande, podemos fazer
    a seguinte análise.

    Na fatoração de um número, se todos os expoentes são pares, esse número tem uma quantidade ímpar de divisores.
    Isso ocorre porque, pelo lema do número de divisores, devemos pegar os expoentes da fatoração, somar 1 a cada e multiplicar.
    Logo, teremos 2*i + 1 em cada membro, onde i é um número tal que multiplicado por 2 forneça o expoente do fator primo.
    Dessa forma, a quantidade de divisores será ímpar.

    Consequentemente, todos os fatores primos tem uma quantidade par se, e somente se,
    ao obtermos a raiz quadrada, todos os expoentes serão inteiros.

    Portanto, dado um n, se obtermos a raiz quadrada dele e multiplicarmos ela por ela mesmo
    e resultar no n, esse número tem uma quantidade ímpar de divisores. Assim, a última lâmpada
    estará ligada.
*/

int main()
{
    unsigned int n;

    while (std::cin >> n && n)
    {
        unsigned int quadrado = static_cast<unsigned int>(std::sqrt(n));

        if (quadrado * quadrado == n)
            std::cout << "yes" << std::endl;

        else
            std::cout << "no" << std::endl;
    }

    return 0;
}
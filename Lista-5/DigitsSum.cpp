#include <iostream>

/*
    Como o primeiro número é o 9, podemos perceber que somente ao adicionarmos mais um dígito
    teremos um número com a propriedade dada.
    Portanto, se dividirmos por 10, iremos verificar a quantidade de números com essa propriedade.
    Entretanto, se o número é reduzido a 9 no módulo 10, ele irá ter a propriedade.
*/

int main()
{
    int numCasos;
    std::cin >> numCasos;

    while (numCasos--)
    {
        int numero, resposta;

        std::cin >> numero;

        resposta = numero / 10;

        if (numero % 10 == 9)
            resposta++;

        std::cout << resposta << std::endl;
    }

    return 0;
}
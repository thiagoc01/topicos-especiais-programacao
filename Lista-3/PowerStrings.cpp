#include <iostream>
#include <string>
#include <cmath>

/*
    Esse problema é uma aplicação do algoritmo KMP.
    Entretanto, não sabemos com o que vamos realizar a construção da tabela de salto do algoritmo.
    Logo, o primeiro padrão encontrado será o padrão utilizado para procura no texto.
    Isso pode ser feito utilizando o tamanho do subtexto encontrado até ali.
    Enquanto encontrarmos caracteres diferentes inicialmente, esse será nosso subtexto
    que deve servir como parâmetro de concatenação. Com isso, aumentamos o tamanho do subtexto
    enquanto encontrarmos as diferenças.
    A partir daí, tudo que vem depois é reduzido ao tamanho do subtexto, através do operador de módulo.
    Pegamos a posição e reduzimos ao equivalente no tamanho do texto. 
    Dessa forma, podemos casar os caracteres do padrão.
    Qualquer diferença daí em diante irá diminuir a potência em um cada vez que percorremos uma 
    quantidade de índices maior que o tamanho do subtexto.

    Após percorrer o texto, devemos analisar os resultados da seguinte forma.
    Se dividirmos o tamanho do texto em partes do tamanho do subtexto e esse resultado for diferente de 0,
    então não obtivemos a concatenação em forma de exponenciação de um padrão.
    Caso contrário, a string está perfeitamente dividida.
*/

    
    
int main()
{
    std::string entrada;

    std::cin >> entrada;

    while (entrada != ".")
    {
        int i = 1, tamanhoSubTexto = 1, tamanhoTexto = entrada.length();

        while (i < tamanhoTexto)
        {
            while (entrada[i] != entrada[i % tamanhoSubTexto])
                tamanhoSubTexto++;

            i++;
        }
        

        if (tamanhoTexto % tamanhoSubTexto)
            std::cout << 1 << std::endl;
        
        else
            std::cout << (int) std::ceil(tamanhoTexto / tamanhoSubTexto) << std::endl;

        std::cin >> entrada;
    }

    return 0;
}
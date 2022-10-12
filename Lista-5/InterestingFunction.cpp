#include <iostream>

/*
    Os números estão no sistema decimal.
    Ao somar um, temos certeza que mudamos um dígito.
    Logo, de 1 a n, teremos n mudanças.
    Entretanto, por não ser possível guardar 10 na unidade,
    temos a subida de 1 na soma.
    Podemos fazer o seguinte: se dividirmos o número por 10,
    iremos calcular o número de vezes em que houve a subida de 1
    até aquele número.
    Ou seja, os algarismos adjacentes que mudaram.
    Mas essa subida de 1 pode afetá-los.
    Logo, iremos realizar esse procedimento até o n ser 0.
    Os resultados são incrementados ao mínimo de mudanças, que é n.
    A soma total indica o número de algarismos que mudaram.
    
    Se realizarmos esse cálculo anterior para o l e r e subtrairmos,
    iremos encontrar exatamente a quantidade de mudanças para ir de um
    até o outro.
*/

int retornaQuantidadeAlgarismosAlterados(int n)
{
    int resultado = n;
    
    while (n != 0)
    {
        n /= 10;
        
        resultado += n;
    }
    
    return resultado;
}

int main()
{
    int numCasos;
    
    std::cin >> numCasos;
    
    while (numCasos--)
    {
        int l, r;
        
        std::cin >> l >> r;
        
        std::cout << retornaQuantidadeAlgarismosAlterados(r) - retornaQuantidadeAlgarismosAlterados(l) << std::endl;
    }

    return 0;
}
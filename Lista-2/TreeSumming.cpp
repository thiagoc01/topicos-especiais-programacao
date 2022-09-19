#include <iostream>
#include <string>

/*
    Para esse problema, basta realizar uma busca em profundidade até achar uma folha.
    Uma folha, nesse caso, é quando não encontramos um número dos dois lados de um nó ao descer na árvore.
    A cada nó, somamos a quantidade até ali.
    Quando chegarmos em uma folha, verificamos se a soma total é o número desejado.
*/

bool realizaParse(int somaTotal, const int& numObjetivo, bool& achouResultado, char &c)
{
    std::string stringNumero; // Acumula o número da entrada numa string
    int numero; // Número do nó
    bool haRamoEsquerda, haRamoDireita; // Analisa se há ramo à esquerda ou direita
    bool eNegativo = false;   

    while (c == '\n' || c == ' ')
        c = std::getchar();

    if (c == '(')
    {
        while (c = std::getchar())
        {
            if (c >= '0' && c <= '9') // Se houver dígito, coloca na string auxiliar
                stringNumero += c;
            
            else
            {
                if (c == '-') // Numero é negativo
                    eNegativo = true;
                else
                    break; // Qualquer outra coisa, sai do loop
            }            
        }

        while (c == '\n' || c == ' ')
            c = std::getchar();

        if (stringNumero.empty()) // Se a string está vazia, não há ramo desse lado
            return false;        

        numero = std::stoi(stringNumero); // Transforma a string para inteiro, visando obter o inteiro do nó

        if (eNegativo)
            numero *= -1;

        haRamoEsquerda = realizaParse(somaTotal + numero, numObjetivo, achouResultado, c); // Busca em profundidade para esquerda

        while ( (c = std::getchar()) != '('); 

        haRamoDireita = realizaParse(somaTotal + numero, numObjetivo, achouResultado, c); // Busca em profundidade para direita

        while ( (c = std::getchar()) != ')'); 

        if (haRamoEsquerda == false && haRamoDireita == false) // Se ambos os ramos não existem, essa é uma folha
        {
            if (somaTotal + numero == numObjetivo) // Se esse o número desse nó com a soma total até aqui é o número, achamos o caminho do enunciado
                achouResultado = true;
        }

        return true; 
    }

    return false;  
}

int main()
{
    int num;
    char c;
    bool achouResultado = false;

    while (scanf("%d", &num) == 1)
    {
        c = std::getchar();
        realizaParse(0, num, achouResultado, c);

        if (!achouResultado)
            std::cout << "no" << std::endl;
        else
            std::cout << "yes" << std::endl;

        achouResultado = false;
    }

    return 0;
}
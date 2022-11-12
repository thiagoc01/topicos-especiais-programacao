#include <iostream>
#include <string>
#include <vector>
#include <limits.h>

/*
    Cada lâmpada é acionada por 5 interruptores. O interruptor da própria luz, um de cima ou de baixo e um de cada lado.
    Podemos notar que os interruptores da primeira fileira e da última têm um a menos de opção, já que ou de cima ou de baixo
    não estão disponíveis.
    
    Podemos fazer o seguinte, testar todas as possibilidades para a primeira fileira e testar os botões com base nessa combinação.
    Para gerar as combinações, podemos fazer uma DFS na primeira fileira modificada. Descemos até a última coluna da primeira fileira
    e testamos a combinação. Depois, acionamos o botão e testamos novamente. Cada volta da recursão será uma nova combinação.
    Por serem 10 nós, claramente temos 2^10 filhos criados.

    O teste é feito da seguinte forma: se o interruptor adjacente ao verificado na linha anterior está ligado, nós apertamos o botão, já que
    essa é a única forma de modificarmos o estado da primeira fileira. Caso contrário, não fazemos nada.

    Para que o teste da combinação seja válido, a última fileira deve estar inteira apagada, já que, pelo mesmo motivo da primeira,
    a última fileira só pode ser modificada pela fileira 9. Logo, se alguma lâmpada ficou acesa, não é possível que, com a combinação testada,
    seja possível desligar todas as lâmpadas.

    Como queremos a menor quantidade, basta trocar o resultado final quando o resultado do teste for menor.
*/

#define DIMENSAO 10

std::vector<std::vector<bool>> painel = std::vector<std::vector<bool>>(DIMENSAO);

int apertos = INT_MAX; 

void apertaBotao(int i, int j)
{
    painel[i][j] = !painel[i][j];

    if (i - 1 >= 0)
        painel[i - 1][j] = !painel[i - 1][j];
    
    if (i + 1 <= DIMENSAO - 1)
        painel[i + 1][j] = !painel[i + 1][j];

    if (j - 1 >= 0)
        painel[i][j - 1] = !painel[i][j - 1];

    if (j + 1 <= DIMENSAO - 1)
        painel[i][j + 1] = !painel[i][j + 1];
}

void testa(int apertosTeste)
{
    std::vector<std::pair<int, int>> v; // Guarda os botões que foram apertados

    for (int i = 1 ; i < DIMENSAO ; i++)
    {
        for (int j = 0 ; j < DIMENSAO ; j++)
        {
            if (painel[i - 1][j]) // Luz ligada
            {
                apertosTeste++;
                apertaBotao(i, j);
                v.push_back({i, j});
            }
        }
    }

    for (int i = 0 ; i < DIMENSAO ; i++)
    {
        if (painel[DIMENSAO - 1][i])
        {
            for (const auto & r : v)
                apertaBotao(r.first, r.second);
                
            return;
        }
    }

    for (const auto & r : v)
        apertaBotao(r.first, r.second);

    if (apertosTeste < apertos)
        apertos = apertosTeste;
}

void criaCombinacao(int j, int apertosTeste)
{
    // Chegamos no último botão. Testamos a combinação. Depois apertamos o botão para a outra possibilidade e testamos novamente.

    if (j == DIMENSAO - 1) 
    {
        testa(apertosTeste);

        apertaBotao(0, j);
        
        testa(apertosTeste + 1);

        apertaBotao(0, j);        
    }

    else // Ainda estamos na linha 1, desce na árvore
    {
        criaCombinacao(j + 1, apertosTeste);

        apertaBotao(0, j);

        criaCombinacao(j + 1, apertosTeste + 1);

        apertaBotao(0, j);
    }
}

int main()
{
    std::string entrada;

    std::cin >> entrada;

    for (int i = 0 ; i < DIMENSAO ; i++)
        painel[i] = std::vector<bool>(DIMENSAO);

    while (entrada != "end")
    {
        char c;

        for (int i = 0 ; i < DIMENSAO ; i++)
        {
            for (int j = 0 ; j < DIMENSAO ; j++)
            {
                std::cin >> c;

                if (c == '#')
                    painel[i][j] = false;                    
                
                else
                    painel[i][j] = true;
            }
        }

        criaCombinacao(0, 0);

        if (apertos != INT_MAX)
            std::cout << entrada << " " << apertos << std::endl;
        else
            std::cout << entrada << " " << -1 << std::endl;

        apertos = INT_MAX;
        
        std::cin >> entrada;
    }

    return 0;
}
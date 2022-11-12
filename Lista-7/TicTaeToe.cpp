#include <iostream>
#include <vector>

#define DIMENSAO 3

/*
    A verificação ocorre por contradição.

    Se a contagem de X é igual a O, então ocorreu empate ou O venceu.
    Se isso ocorre, nenhuma das possibilidades de vitória do jogo pode conter X.
    Logo, se testarmos todas as possibilidades em que X vence e não encontrarmos alguma,
    o jogo é válido.
    Essa análise é análoga para a vitória de X.

    O outro caso é o que O aparece mais vezes. Isso é um absurdo porque X começa o jogo.
*/

std::vector<std::vector<char>> tabuleiro = std::vector<std::vector<char>>(3);

bool verificaValidade(const char& perdedor)
{
    if (tabuleiro[0][0] == perdedor && tabuleiro[0][1] == perdedor && tabuleiro[0][2] == perdedor)
        return false;
    
    if (tabuleiro[1][0] == perdedor && tabuleiro[1][1] == perdedor && tabuleiro[1][2] == perdedor)
        return false;

    if (tabuleiro[2][0] == perdedor && tabuleiro[2][1] == perdedor && tabuleiro[2][2] == perdedor)
        return false;

    if (tabuleiro[0][0] == perdedor && tabuleiro[1][0] == perdedor && tabuleiro[2][0] == perdedor)
        return false;

    if (tabuleiro[0][1] == perdedor && tabuleiro[1][1] == perdedor && tabuleiro[2][1] == perdedor)
        return false;

    if (tabuleiro[0][2] == perdedor && tabuleiro[1][2] == perdedor && tabuleiro[2][2] == perdedor)
        return false;

    if (tabuleiro[0][0] == perdedor && tabuleiro[1][1] == perdedor && tabuleiro[2][2] == perdedor)
        return false;

    if (tabuleiro[0][2] == perdedor && tabuleiro[1][1] == perdedor && tabuleiro[2][0] == perdedor)
        return false;

    return true;
}

void iniciaTabuleiro()
{
    for (int i = 0 ; i < DIMENSAO ; i++)
        tabuleiro[i] = std::vector<char>(3);
}

int main()
{
    long long int numCasos;
    
    std::cin >> numCasos;    

    while (numCasos--)
    {
        bool eValido;

        short int contagemX = 0, contagemO = 0;

        iniciaTabuleiro();

        for (short int i = 0 ; i < DIMENSAO ; i++)
        {
            for (short int j = 0 ; j < DIMENSAO ; j++)
            {
                char c;
                
                std::cin >> c;

                if (c == 'X')
                {
                    tabuleiro[i][j] = 'X';
                    contagemX++;
                }

                else if (c == 'O')
                {
                    tabuleiro[i][j] = 'O';
                    contagemO++;
                }

                else
                    tabuleiro[i][j] = '.';           
            }
        }

        if (contagemX == contagemO) // Empate ou O venceu. X não pode aparecer em nenhuma linha inteiramente.
            eValido = verificaValidade('X');

        else if (contagemX == contagemO + 1) // X venceu. 0 não pode aparecer em nenhuma linha inteiramente.
            eValido = verificaValidade('O');
        
        else // Caso em que há mais O que X, impossível.
            eValido = false;

        if (eValido)
            std::cout << "yes" << std::endl;

        else
            std::cout << "no" << std::endl;
    }

    return 0;

}

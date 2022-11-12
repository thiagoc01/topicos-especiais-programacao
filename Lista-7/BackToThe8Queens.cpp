#include <iostream>
#include <vector>
#include <limits.h>

/*
    O problema funciona com busca em profundidade.
    Todas as combinações devem ser analisadas e uma configuração até uma certa coluna a ser analisada
    depende das posições das outras damas, o que caracteriza um backtracking, padrão de uma busca em profundidade.

    Como as damas estão nas colunas, só podemos mover para cima ou baixo, ou seja, colocá-las em linhas diferentes.

    Para cada linha, iremos verificar se, naquela célula específica, a dama pode ser colocada.

    A verificação consiste em ver se não há uma dama na mesma linha ou na mesma diagonal.
    
    Cada vez que voltamos da recursão, verificamos se obtemos uma quantidade menor de movimentos e alteramos a variável.

    O vetor linhasDamas guarda as linhas que recebemos da entrada, para verificar se alteramos a posição da dama.
    O vetor posicaoFinalDama guarda o tabuleiro com as modificações.
*/

#define NUM_DAMAS 8

int linhasDamas[NUM_DAMAS + 1];
int posicaoFinalDama[NUM_DAMAS + 1];

/* Verifica se não há ataque lateral ou na diagonal, já que as colunas são individuais. */

bool verificaPosicao(short int linha, short int coluna)
{
    for (short int i = 1 ; i < coluna ; i++) // Para todas as damas
    {
        if (linha == posicaoFinalDama[i]) // Se a linha a ser verificada tiver uma dama, haverá choque lateral
            return false;
        
        if (std::abs(linha - posicaoFinalDama[i]) == std::abs(coluna - i)) // Choque na diagonal
            return false;
    }

    return true;
}

int retornaQuantidadeMovimentos(short int coluna)
{
    if (coluna == 9) // Verificamos todas as colunas
        return 0;

    int numMovimentos = INT_MAX - 1;

    for (short int i = 1 ; i < 9 ; i++) // Para todas as linhas, iremos verificar qual delas a dama pode ser colocada.
    {
        if (verificaPosicao(i, coluna)) // A posição para mover a dama é válida, iremos colocá-la nessa célula.
        {
            posicaoFinalDama[coluna] = i;

            if (i == linhasDamas[coluna]) // Se a posição que a dama irá se mover for a que ela já esta, não somamos um aos movimentos totais.
                numMovimentos = std::min(numMovimentos, retornaQuantidadeMovimentos(coluna + 1));
            
            else
                numMovimentos = std::min(numMovimentos, 1 + retornaQuantidadeMovimentos(coluna + 1));
        }
    }

    return numMovimentos;
}

int main()
{
    short int casos = 1;

    while (std::cin >> linhasDamas[1])
    {
        for (int i = 2 ; i <= NUM_DAMAS ; i++)
            std::cin >> linhasDamas[i];

        std::cout << "Case " << casos++ <<  ": " << retornaQuantidadeMovimentos(1) << std::endl;
    }

    return 0;
}
#include <iostream>
#include <vector>

int retornaMaiorNumero(int a, int b, int c)
{
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int retornaVotosVitoria(int n, int max)
{
    return n == max ? 0 : max - n + 1;
}

int retornaVotosVitoriaEmpate(int n, int max)
{
    return n == max ? 1 : max - n + 1;
}

int main()
{
    int numCasos;
    std::vector<std::vector<int>> votosCasos;

    std::cin >> numCasos;

    while (numCasos > 0)
    {
        int votosA, votosB, votosC, maiorVotos;

        std::cin >> votosA;
        std::cin >> votosB;
        std::cin >> votosC;

        maiorVotos = retornaMaiorNumero(votosA, votosB, votosC);

        if ((maiorVotos == votosA && maiorVotos == votosB) || (maiorVotos == votosA && maiorVotos == votosC) || (maiorVotos == votosB && maiorVotos == votosC))
            votosCasos.push_back( std::vector<int>{retornaVotosVitoriaEmpate(votosA, maiorVotos), retornaVotosVitoriaEmpate(votosB, maiorVotos), retornaVotosVitoriaEmpate(votosC, maiorVotos)});
        
        else
            votosCasos.push_back( std::vector<int>{retornaVotosVitoria(votosA, maiorVotos), retornaVotosVitoria(votosB, maiorVotos), retornaVotosVitoria(votosC, maiorVotos)});

        
        numCasos--;
    }

    for (const auto& votos : votosCasos)
    {
        std::cout << votos[0] << " " << votos[1] << " " << votos[2] << std::endl;
    }

    return 0;
}
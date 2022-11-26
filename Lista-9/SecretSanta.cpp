#include <iostream>
#include <vector>

/*
    A ideia é baseada em fluxo de um vértice.
    Cada vértice deve ter uma unidade de fluxo.
    Se um vértice possui mais de um, precisamos deslocar essa unidade para outro sem.
    Logo, procuramos pelo primeiro vértice sem fluxo e utilizamos esse para troca com outro
    que possui fluxo maior que 1. Antes da troca, precisamos verificar
    se não estamos trocando um vértice com ele mesmo para não haver erro de contagem.

    O primeiro vértice a ser encontrado que não contenha fluxo deve começar do sentido contrário
    da iteração, já que queremos a maximização.
*/


int main()
{
    int numCasos;

    std::cin >> numCasos;

    while (numCasos--)
    {
        int n, desejosAtendidos, atualSemDesejos;
        
        std::cin >> n;

        std::vector<int> desejos = std::vector<int>(n + 1);
        std::vector<int> solicitacoes = std::vector<int>(n + 1, 0);

        desejosAtendidos = n;
        atualSemDesejos = n;

        for (int i = 1 ; i <= n ; i++)
        {
            int a;

            std::cin >> a;

            solicitacoes[a]++;
            desejos[i] = a;
        }

        for (int i = 1 ; i <= n ; i++)
        {
            while (solicitacoes[atualSemDesejos] != 0)
                atualSemDesejos--;

            if (solicitacoes[desejos[i]] > 1)
            {
                if (i == atualSemDesejos)
                    continue;               
               
                solicitacoes[desejos[i]]--;
                desejos[i] = atualSemDesejos;
                solicitacoes[atualSemDesejos]++;
                
                desejosAtendidos--;
            }
        }

        std::cout << desejosAtendidos << std::endl;

        for (int i = 1 ; i <= n ; i++)
            std::cout << desejos[i] << " ";

        std::cout << std::endl;
    }

    return 0;
}

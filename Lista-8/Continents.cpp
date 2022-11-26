#include <iostream>
#include <vector>
#include <string>

/*
    Basta realizar uma busca simples no mapa.
    Ela funciona visitando cada célula enquanto não for uma porção de água,
    o que indica que ali encerrou o continente para aquele sentido da busca.
    Como qualquer porção de terra adjacente é continente, a busca deve continuar para o norte, sul,
    leste e oeste. Como solicitado pelo problema, ao alcançar as laterais limites do mapa, colocamos o índice em
    n - 1 ou 0, dependendo de qual lado estamos.
    
    Ao fim de uma busca em um continente, verificamos se o resultado obtido é maior do que o atual.

    Primeiro, visitamos o continente inteiro para não ser contabilizado, caso esse seja o maior ou maior que qualquer outro.
*/

std::vector<std::string> mapa;
std::vector<std::vector<bool>> jaFoiVisitada;
char terra; // Caractere escolhido para ser terra
short int m, n;

void realizaProcura(short int i, short int j, int& soma)
{
    /* Os dois if's a seguir são os casos em que chegamos no canto do mapa e devemos contornar. */

    if (j < 0)
        j = n - 1;

    if (j >= n)
        j = 0;

    if (i < 0 || i >= m) // Chegamos no fim na parte vertical, encerramos.
        return;

    /*
        A procura deve ser feita para todos os lados de uma porção de terra,
        já que o problema diz que qualquer região adjacente é considerada parte do continente.
    */

    if (mapa[i][j] == terra && !jaFoiVisitada[i][j])
    {
        jaFoiVisitada[i][j] = true;
        soma++;
        realizaProcura(i, j + 1, soma);
        realizaProcura(i, j - 1, soma);
        realizaProcura(i + 1, j, soma);
        realizaProcura(i - 1, j, soma);
    }
}

int main()
{
    while (std::cin >> m)
    {
        short int x, y;
        int quantidade = 0;

        jaFoiVisitada = std::vector<std::vector<bool>>();

        std::cin >> n;

        for (short int i = 0 ; i < m ; i++)
        {
            std::string linha;

            std::cin >> linha;

            mapa.push_back(linha);

            jaFoiVisitada.push_back(std::vector<bool>(n, false));
        }
        
        std::cin >> x >> y;

        terra = mapa[x][y]; // Caracteres para terra e água variam. A posição inicial é sempre solo.

        int inutil; // Apenas para ser possível chamar a função no caso de verificação do continente inicial.

        realizaProcura(x, y, inutil); // O continente dele deve ser desconsiderado.

        for (short int i = 0 ; i < m ; i++)
        {
            for (short int j = 0 ; j < n ; j++)
            {
                int soma = 0;

                if (jaFoiVisitada[i][j] || mapa[i][j] != terra)  // Região já conhecida ou é água.
                    continue;

                realizaProcura(i, j, soma);

                if (soma > quantidade)
                    quantidade = soma;
            }
        }

        std::cout << quantidade << std::endl;

        mapa.clear();
        jaFoiVisitada.clear();
    }

    return 0;
}
#include <iostream>
#include <vector>

int main()
{
    short int n, h, l, r;
    std::vector<short int> horariosParaDormir;
    std::vector<std::vector<short int>> contagemHorariosBons;

    std::cin >> n >> h >> l >> r;

    horariosParaDormir = std::vector<short int>(n + 1);

    for (short int i = 1 ; i <= n ; i++)
        std::cin >> horariosParaDormir[i];

    contagemHorariosBons = std::vector<std::vector<short int>>(n + 2, std::vector<short int>(h + 1));

    for (short int i = 0 ; i < h ; i++)
        contagemHorariosBons[n + 1][i] = 0;

    for (short int i = n ; i >= 1 ; i--)
    {
        for (short int j = 0 ; j < h ; j++)
        {
            short int escolha1 = (j + horariosParaDormir[i]) % h;
            short int boaEscolha1 = l <= escolha1 && escolha1 <= r ? 1 : 0;

            contagemHorariosBons[i][j] = contagemHorariosBons[i + 1][escolha1] + boaEscolha1;

            short int escolha2 = (j + horariosParaDormir[i] - 1) % h;
            short int boaEscolha2 = l <= escolha2 && escolha2 <= r ? 1 : 0;

            contagemHorariosBons[i][j] = std::max(contagemHorariosBons[i][j], static_cast<short int>(contagemHorariosBons[i + 1][escolha2] + boaEscolha2));
        }
    }

    std::cout << contagemHorariosBons[1][0];

    return 0;
}
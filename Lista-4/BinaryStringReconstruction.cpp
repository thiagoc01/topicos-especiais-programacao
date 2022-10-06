#include <iostream>
#include <string>

/*
    Para reconstruir a string, vamos usar a contrapositiva dos critérios.
    Uma condicional é equivalente à contrapositiva, ou seja, p->q <=> !q->!p
    Logo, para ambos os critérios:

    1) s[i] != 1 -> !(existe w_i-x && w_i-x == 1) <=> s[i] == 0 -> !existe w_i-x || w_i-x == 0
    2) s[i] != 1 -> !(existe w_i+x && w_i+x == 1) <=> s[i] == 0 -> !existe w_i+x || w_i+x == 0

    Supondo que s[i] == 0. Para que a condicional seja verdade, precisamos que o lado direito também seja.
    Como as posições necessariamente devem existir, então a negação é falsa.
    Logo, as posições na string original devem ser iguais a 0 para que o || seja verdade.

    Portanto, reconstruímos a string w.

    Depois, para verificar se a string é resultante, a ida e a volta dos critérios devem valer.
    Logo, p -> q && q -> p.

    Como construímos a string w baseada em p -> q (via contrapositiva), iremos testar q -> p.

    Ou seja, se s[i] == 1, então as posições devem ser válidas e w na posição dada deve ser igual a 1.
    Se encontrarmos uma disparidade, então a string não pode ser reconstruída.
*/

int main()
{
    int numCasos;
    std::cin >> numCasos;

    while (numCasos--)
    {
        std::string s, w;
        int x;
        bool existeString = true;

        std::cin >> s >> x;

        const int tamString = s.size();

        w = std::string(tamString, '1');

        for (int i = 0 ; i < tamString ; i++)
        {
            if (s[i] == '0')
            {
                if (i - x >= 0)
                    w[i - x] = '0';
                if (i + x < tamString)
                    w[i + x] = '0';
            }
        }

        for (int i = 0 ; i < tamString ; i++)
        {
            if (s[i] == '1')
            {
                if (!(i - x >= 0 && w[i - x] == '1') && !(i + x < tamString && w[i + x] == '1'))
                {
                    existeString = false;
                    break;
                }
            }
        }

        existeString ? std::cout << w << std::endl : std::cout << -1 << std::endl;
    }

    return 0;
}
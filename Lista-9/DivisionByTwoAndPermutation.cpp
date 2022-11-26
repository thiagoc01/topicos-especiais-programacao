#include <iostream>
#include <vector>

/*
    Basta dividir cada valor por 2 enquanto for maior que n ou caso ele tenha sido utilizado.
    Pois, se foi utilizado, precisamos ver se é possível atingir um valor menor para obter
    a permutação.
    Caso haja o resultado de 0, tivemos um caso em que o número precisa ser dividido, mas não pode ser feito
    porque as opções disponíveis já foram obtidas. Logo, é impossível.
*/
     
#define QTD_MAX 51

std::vector<bool> utilizado;
    
int main()
{
    int numCasos;

    std::cin >> numCasos;

    while (numCasos--)
    {
        int n;
        bool ePossivel = true;
        utilizado = std::vector<bool>(QTD_MAX, false);

        std::cin >> n;

        for (int i = 0 ; i < n ; i++)
        {
            int a;

            std::cin >> a;

            while (a >= 1 && (a > n || utilizado[a]))
                a /= 2;
            
            if (a == 0)
                ePossivel = false;

            utilizado[a] = true;
        }

        if (ePossivel)
            std::cout << "YES" << std::endl;

        else
            std::cout << "NO" << std::endl;
    }

    return 0;	
}
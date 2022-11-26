#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

/*
    Como as ruas são conectadas, basta obter as coordenadas para calcular a distância.
    Após calcular a distância total, multiplicamos por 2 (pois as ruas são limpas em ambos os sentidos),
    dividimos por 20 pela fórmula da velocidade média (velocidade do trator ao limpar).
    Iremos obter as horas. Passamos para minutos e arredondamos para cima.
    Para obter as horas, basta dividir por 60 novamente e para obter os minutos basta realizar o módulo do número
    por 60 para obter os minutos.
*/

int main()
{
    int numCasos;
    std::string entrada;

    std::cin >> numCasos;    
    
    std::getline(std::cin, entrada);

    while (numCasos--)
    {       
        double distancia = 0.0, horas;
        double x1, y1, x2, y2;
        long long int minutos;

        std::getline(std::cin, entrada);

        while (std::getline(std::cin, entrada) && !entrada.empty())
        {
            std::stringstream buffer = std::stringstream(entrada);

            buffer >> x1 >> y1 >> x2 >> y2;
            
            distancia += std::hypot(x2 - x1, y2 - y1);
        }

        distancia /= 1000; // Distância está em metros

        horas = distancia * 2 / 20; // Velocidade média = distância / tempo

        minutos = static_cast<long long int>(std::round(horas * 60));

        std::cout << minutos / 60 << ":" << std::setfill('0') << std::setw(2) << minutos % 60 << std::endl;

        if (numCasos)
            std::cout << std::endl;
    }

    return 0;
}
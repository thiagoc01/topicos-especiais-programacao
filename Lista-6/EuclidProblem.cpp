#include <iostream>

long long int mdc, X, Y;

void aplicaEuclidesEstendido(const long long int a, const long long int b)
{
    if (b == 0)
    { 
        mdc = a;
        X = 1;
        Y = 0;

        return;
    } 

    aplicaEuclidesEstendido(b, a % b); 

    long long int xAntigo = X; 

    X = Y;

    Y = (xAntigo - ((a / b) * Y)); 
}

int main()
{
    long long int a, b;

    while (std::cin >> a && std::cin >> b)
    {
        aplicaEuclidesEstendido(a, b);

        std::cout << X << " " << Y << " " << mdc << std::endl;
    }

    return 0;
}
#include <iostream>
#include <vector>

/*
    Como os vértices são visitados em ordem crescente, se um número consecutivo
    é maior que o anterior, necessariamente ele criará um novo ramo na árvore (exceto entre o vértice 1 e o segundo).
    Caso contrário, continuamos no ramo atual.
*/

class Vertice
{
    protected:
        int id;
        int altura;      

    public:
        Vertice(const int& id, const int& altura)
        {
            this->id = id;
            this->altura = altura;
        }

        Vertice()
        {

        }

        int getID() const
        {
            return id;
        }

        int getAltura() const
        {
            return altura;
        }
};

class Grafo
{
    private:
        std::vector<Vertice> vertices;

    public:
        Grafo (int n)
        {
            int menorAltura = 1; // Posição do vértice de menor altura
            int v;

            std::cin >> v;

            vertices.push_back(Vertice(0, 0));
            vertices.push_back(Vertice(1, 0));

            for (int i = 2 ; i <= n ; i++)
            {
                std::cin >> v;

                if (vertices[i - 1].getID() > v)
                    menorAltura++;
                    
                vertices.push_back(Vertice(v, vertices[menorAltura].getAltura() + 1));
            }

            std::cout << vertices[n].getAltura() << std::endl;            
        }
};

int main()
{
    short int numCasos;

    std::cin >> numCasos;

    while (numCasos--)
    {
        int n;

        std::cin >> n;

        Grafo g = Grafo(n);
    }

    return 0;
}
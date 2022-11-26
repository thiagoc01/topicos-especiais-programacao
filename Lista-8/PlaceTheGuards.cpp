#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

/*
    O problema é de bipartição de grafo.

    Como dois vértices adjacentes não podem ter um guarda em cada um,
    basta realizar uma bipartição das ruas e esquinas.
    Se não for possível realizar isso, o problema não tem solução.

    Depois, para descobrir a quantidade de guardas, verificamos o tamanho das componentes.
    A componente de menor tamanho será a quantidade de guardas, já que queremos o mínimo de guardas.
*/

#define PART1 1
#define PART2 2
#define NAO_VISITADO 3

class Vertice
{
    protected:
        int id;
        short int cor;
        std::set<Vertice *> vizinhos;          

    public:
        Vertice(const int& id)
        {
            this->id = id;
            cor = NAO_VISITADO;
        }

        Vertice()
        {

        }

        int getID() const
        {
            return id;
        }

        void adicionaVizinho(Vertice*& v)
        {
            vizinhos.insert(v);
        }

        std::set<Vertice *>& retornaVizinhos()
        {
            return vizinhos;
        }

        short int retornaCor() const
        {
            return cor;
        }

        void setaCor(const int& cor)
        {
            this->cor = cor;
        }
};

class Grafo
{
    private:
        std::map<int, Vertice *> vertices;	

    public:
        Grafo (int n)
        {
            for (int i = 0 ; i < n ; i++)
                vertices.insert(std::make_pair(i, new Vertice(i)));     
        }

        void adicionaAresta(const int& id1, const int& id2)
        {
            Vertice *v = vertices.at(id1), *w = vertices.at(id2);
			
            v->adicionaVizinho(w);
        }

        bool BFS(Vertice*& v, short int& numeroGuardas)
        {
            std::queue<Vertice *> fila;
            bool eBipartido = true;
            std::vector<int> particoes = std::vector<int>(3, 0);

            v->setaCor(PART1);
            particoes[PART1]++;

            fila.push(v);

            while (!fila.empty() && eBipartido)
            {
                Vertice *u = fila.front();
                fila.pop();

                for (auto& w : u->retornaVizinhos())
                {
                    if (w->retornaCor() == u->retornaCor()) // Vértices adjacentes na mesma partição. Absurdo para grafo bipartido
                    {
                        eBipartido = false;
                        break;
                    }

                    if (w->retornaCor() == NAO_VISITADO)
                    {
                        if (u->retornaCor() == PART1) // Vértice verificado está na partição 1, seu adjacente vai para a segunda partição.
                        {    
                            w->setaCor(PART2);
                            particoes[PART2]++;
                        }

                        else // Análogo ao anterior
                        {
                            w->setaCor(PART1);
                            particoes[PART1]++;
                        }

                        fila.push(w);
                    }
                }
            }

            numeroGuardas += std::max(1, std::min(particoes[PART1], particoes[PART2])); // Se o vértice é desconexo, tem que ter pelo menos um guarda.

            return eBipartido;
        }

        ~Grafo()
        {
            std::for_each(vertices.begin(), vertices.end(), [](std::map<int, Vertice *>::value_type& p) { delete p.second; });
        }

        std::map<int, Vertice *>& retornaVertices()
        {
            return vertices;
        }
};

int main()
{
    short int numCasos;

    std::cin >> numCasos;

    while (numCasos--)
    {
        short int numVertices, numArestas, numeroGuardas = 0;
        bool eBipartido = true;
        std::map<int, Vertice *> vertices;

        std::cin >> numVertices >> numArestas;

        Grafo g = Grafo(numVertices);

        while (numArestas--)
        {
            short int f, t;

            std::cin >> f >> t;

            g.adicionaAresta(f, t);
            g.adicionaAresta(t, f);
        }

        vertices = g.retornaVertices();

        for (auto& v : vertices)
        {
            if (!eBipartido) // Não há por que continuar
                break;

            if (v.second->retornaCor() != NAO_VISITADO) // Vértice já colorido
                continue;

            eBipartido = g.BFS(v.second, numeroGuardas);            
        }

        if (eBipartido)
            std::cout << numeroGuardas << std::endl;

        else
            std::cout << -1 << std::endl;
    }

    return 0;
}
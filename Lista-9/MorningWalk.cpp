#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

/*
    Aplicação direta para detectar se existe um caminho euleriano em um grafo.
    Basta criar os vértices e as arestas e verificar se existe caminho euleriano.
*/

class Vertice
{
    protected:
        int id;
        bool visitado;
        std::vector<Vertice *> vizinhos;          

    public:
        Vertice(const int& id)
        {
            this->id = id;
            visitado = false;
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
            vizinhos.push_back(v);
        }

        std::vector<Vertice *>& retornaVizinhos()
        {
            return vizinhos;
        }

        bool retornaVisitado() const
        {
            return visitado;
        }

        void setaVisitado()
        {
            this->visitado = true;
        }

        int retornaGrauVertice() const
        {
            return vizinhos.size();
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
            w->adicionaVizinho(v);
        }

        void DFS(Vertice*& v)
        {
            v->setaVisitado();

            for (Vertice* u : v->retornaVizinhos())
            {
                if (u->retornaVisitado() == false)
                    DFS(u);
            }
        }

        bool verificaConexidade()
        {
            bool existeComponenteConexa = false;

            for (auto& v : vertices)
            {
                if (v.second->retornaGrauVertice() != 0) // Não se pode começar a busca em um vértice de grau 0
                {
                    existeComponenteConexa = true;
                    DFS(v.second);
                    break;
                }
            }

            if (!existeComponenteConexa) // Não há arestas
                return false;

            for (const auto& v : vertices)
            {
                if (v.second->retornaVisitado() == false && v.second->retornaGrauVertice() != 0)
                    return false;
                    
            }

            return true;
        }

        bool eEuleriano()
        {		
            for (const auto& v: vertices)
            {
                if (v.second->retornaGrauVertice() % 2 == 1) 
                    return false; // Grafo com vértice de grau ímpar                
            }

            if (!verificaConexidade()) 
                return false; // Grafo desconexo                
            
            return true;
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
    short int numVertices, numEstradas;
    std::string entrada;

    while (std::cin >> numVertices && std::cin >> numEstradas)
    {
        Grafo g(numVertices);
        
        for (short int i = 0 ; i < numEstradas ; i++)
        {
            short int u, v;

            std::cin >> u >> v;
            g.adicionaAresta(u, v);
        }

        if (g.eEuleriano())
            std::cout << "Possible" << std::endl;
        
        else
            std::cout << "Not Possible" << std::endl;
    }

    return 0;
}
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>

/*
    Esse problema é de ordenação topológica.
    A cada par de string que vem em sequência na entrada, comparamos posição por posição.
    Se em uma dada posição duas letras diferem, marcamos que ambas são usadas e adicionamos uma aresta
    da que vem na primeira string para a segunda. Isso indica que a outra vem antes no alfabeto.
    Realizando a ordenação topológica, encontramos a ordenação do alfabeto.
*/

#define NUM_LETRAS_ALFABETO 26

std::vector<bool> apareceLetra = std::vector<bool>(NUM_LETRAS_ALFABETO, false);
std::vector<int> alfabetoOrdenado;

class Vertice
{
    protected:
        int id;
        bool visitado; 
        std::set<Vertice *> vizinhos;          

    public:
        Vertice(const int& id)
        {
            this->id = id;
            visitado = false;
        }

        Vertice()
        {

        }

        bool foiVisitado() const
        {
            return visitado;
        }

        void setaVisitado()
        {
            visitado = true;
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

        int retornaGrauSaida() const
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
            for (int i = 1 ; i <= n ; i++)
                vertices.insert(std::make_pair(i, new Vertice(i)));     
        }

        void adicionaAresta(const int& id1, const int& id2)
        {
            Vertice *v = vertices.at(id1), *w = vertices.at(id2);
			
            v->adicionaVizinho(w);
        }

        void DFS(Vertice*& v)
        {
            v->setaVisitado();

            for (auto u : v->retornaVizinhos())
            {
                if (!u->foiVisitado())
                    DFS(u);
            }

            alfabetoOrdenado.push_back(v->getID());
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
    std::string atual, proxima;

    Grafo grafo = Grafo(NUM_LETRAS_ALFABETO);
    std::map<int, Vertice *> vertices;

    std::cin >> atual;

    while (std::cin >> proxima && proxima != "#")
    {
        for (int i = 0 ; i < atual.length() && i < proxima.length() ; i++)
        {
            if (atual[i] != proxima[i]) // Achamos a letra que difere
            {
                /* Somamos 1 porque as diferenças retornam distância. Porém, os IDs são a posição no alfabeto. */

                int posicaoLetraAtualAlfabeto = static_cast<int>(atual[i] - 'A');
                int posicaoLetraProximaAlfabeto = static_cast<int>(proxima[i] - 'A');

                apareceLetra[posicaoLetraAtualAlfabeto] = true;
                apareceLetra[posicaoLetraProximaAlfabeto] = true;

                grafo.adicionaAresta(posicaoLetraAtualAlfabeto + 1, posicaoLetraProximaAlfabeto + 1);

                break; // Basta uma diferença para encerrar a procura
            }
        }
        
        atual = std::string(proxima);
    }

    vertices = grafo.retornaVertices();

    for (auto v : vertices)
    {
        if (!v.second->foiVisitado() && apareceLetra[v.second->getID() - 1])
            grafo.DFS(v.second);
    }

    for (auto iterador = alfabetoOrdenado.rbegin() ; iterador != alfabetoOrdenado.rend() ; iterador++)
        std::cout << static_cast<char>('A' + *iterador - 1);

    std::cout << std::endl;
      

    return 0;
}
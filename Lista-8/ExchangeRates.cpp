#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

/*
    O problema consiste em encontrar relações entre produtos.
    Ele pode ser modelado como um grafo, onde cada nó é um produto, uma aresta é oriunda
    do comando '!' e as quantidades são os pesos das arestas.

    Quando não temos uma informação direta, precisamos realizar uma busca no grafo para
    criar adjacências entre cada componente.

    Isso pode ser feito através de uma busca em profundidade que recebe dois nós, onde o primeiro nó
    é fixado, sendo o produto 1 e o segundo são todos os nós do grafo.

    Se houver uma adjacência entre dois produtos, iremos usá-la para juntar componentes não-conexas
    através da adjacência do segundo produto com seus vizinhos.

    Para encontrar a taxa de câmbio, basta obter cada quantidade e realizar uma regra de três, onde o produto
    que conecta o produto da entrada com o da busca é o intermediário.

    Basicamente:

    P12   P32
    --- = --- <=> P12 * P23 = P21 * P32
    P21   P23

    Obtemos o mdc (para redução) entre as quantidades do produto intermediário com o produto da entrada e do produto de busca.
    Reduzimos ambas para uma fração irredutível.
    Daí, fazemos a multiplicação.
    E criaremos a aresta, representando a equivalência transitiva.

    Ao final da construção das conexões, verificamos se existe uma adjacência entre os dois produtos.
    Se sim, imprimos a quantidade. Caso contrário, não há informação suficiente para deduzir a taxa.
*/

class Vertice
{
    protected:
        std::string produto;
        std::unordered_map<Vertice *, int> vizinhos;          

    public:
        Vertice(const std::string& produto)
        {
            this->produto = std::string(produto);
        }

        Vertice()
        {

        }

        void adicionaVizinho(Vertice*& v, const int& quantidade)
        {
            vizinhos.insert({v, quantidade});
        }

        std::unordered_map<Vertice *, int>& retornaVizinhos()
        {
            return vizinhos;
        }

        std::string retornaProduto() const
        {
            return produto;
        }
};

class Grafo
{
    private:
        std::unordered_map<std::string, Vertice *> vertices;	

    public:
        Grafo ()
        {

        }

        void adicionaVertice(const std::string& produto)
        {
            if (vertices.find(produto) == vertices.end())
                vertices.insert({produto, new Vertice(produto)});
        }

        void adicionaAresta(const std::string& p1, const std::string& p2, const int& quantidade1, const int& quantidade2)
        {
            Vertice *v = vertices.at(p1), *w = vertices.at(p2);
			int mdc = std::__gcd(quantidade1, quantidade2); // Deseja-se a quantidade reduzida para os termos mais baixos, até para prevenir overflow.

            v->adicionaVizinho(w, quantidade1 / mdc);
            w->adicionaVizinho(v, quantidade2 / mdc);
        }

        void DFS(Vertice*& v, Vertice*& u)
        {
            for (auto& w : vertices)
            {
                /* 
                    Não devemos fazer a operação no próprio produto,
                    nem se o produto u (intermediário) não possui adjacência com o transitivo (produto 3)
                    e nem se o produto da entrada possui adjacência com o transitivo (já que existe uma taxa de câmbio se isso ocorre).
                */

                if (w.second != v && (u->retornaVizinhos().find(w.second) != u->retornaVizinhos().end()) && (v->retornaVizinhos().find(w.second) == v->retornaVizinhos().end()))
                {
                    /* Obtemos as equivalências. */

                    int quantidadeP12 = v->retornaVizinhos().find(u)->second;
                    int quantidadeP21 = u->retornaVizinhos().find(v)->second;
                    int quantidadeP23 = u->retornaVizinhos().find(w.second)->second;
                    int quantidadeP32 = w.second->retornaVizinhos().find(u)->second;

                    int mdc = std::__gcd(quantidadeP21, quantidadeP23); // Realizamos o MDC para reduzir a fração.

                    int quantidadeP23Reduzida = quantidadeP23 / mdc;
                    int quantidadeP21Reduzida = quantidadeP21 / mdc;

                    /* A taxa de câmbio transitiva é a regra de três entre a taxa do produto 2 com 1 e produto 2 com 3. */
                    adicionaAresta(v->retornaProduto(), w.second->retornaProduto(), quantidadeP12 * quantidadeP23Reduzida, quantidadeP32 * quantidadeP21Reduzida);

                    DFS(v, w.second); // Continua a busca nos filhos do produto 3.
                }
            }
        }

        ~Grafo()
        {
            std::for_each(vertices.begin(), vertices.end(), [](std::unordered_map<std::string, Vertice *>::value_type& p) { delete p.second; });
        }

		std::unordered_map<std::string, Vertice *>& retornaVertices()
		{
			return vertices;
        }
};

int main()
{
    std::string comando, igual, item1, item2; // igual : guarda o '='
    int qtdItem1, qtdItem2;
    Grafo g;

    std::cin >> comando;

    while (comando != ".")
    {
        if (comando == "!")
        {
            std::cin >> qtdItem1 >> item1 >> igual >> qtdItem2 >> item2;

            g.adicionaVertice(item1);
            g.adicionaVertice(item2);

            g.adicionaAresta(item1, item2, qtdItem1, qtdItem2);
        }

        else
        {
            std::cin >> item1 >> igual >> item2;
            std::unordered_map<std::string, Vertice *> vertices;
            Vertice *p1, *p2;

            /* Caso não tenham sido adicionadas equivalências para um dos produtos. */

            g.adicionaVertice(item1);
            g.adicionaVertice(item2);

            vertices = g.retornaVertices();

            p1 = vertices.at(item1); // Obtém o vértice do produto 1
            p2 = vertices.at(item2); // Análogo ao anterior

            std::unordered_map<Vertice *, int> vizinhosProduto1 = p1->retornaVizinhos();

            for (auto& v : vertices) // Calcula as taxas pelas componentes
            {
                if (vizinhosProduto1.find(v.second) != vizinhosProduto1.end()) // Vértice v e produto 1 possui uma relação de preço
                    g.DFS(p1, v.second);            
            }

            vizinhosProduto1 = p1->retornaVizinhos();

            if (vizinhosProduto1.find(p2) != vizinhosProduto1.end())
				std::cout << vizinhosProduto1.find(p2)->second << " " << item1 << " = " << p2->retornaVizinhos().find(p1)->second << ' ' << item2 << std::endl;
			else
				std::cout << "? " << item1 << " = " << "? " << item2 << std::endl;
        }

        std::cin >> comando;
    }

    return 0;
}
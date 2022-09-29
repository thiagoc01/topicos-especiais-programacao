#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>

/*
    O programa modela um grafo e seus vértices. Para realizarmos a soma com base na distância, basta realizar uma busca em profundidade,
    limitada a distância dada. Para cada vizinho, iremos até a distância dada. Depois, voltamos decrementando o contador para ir para o próximo vizinho,
    até que todos os vizinhos do vértice solicitado tenham sido visitados.
    Ao visitar, somamos o valor solicitado.
*/

class NoListaLigada
{
    private:
        int valor;
        NoListaLigada *proxNo;

    public:
        NoListaLigada()
        {
            proxNo = nullptr;
            valor = 0;
        }

        NoListaLigada(int valor, NoListaLigada *proxNo)
        {
            this->proxNo = proxNo;
            this->valor = valor;
        }

        void setaProxNo(NoListaLigada*& no)
        {
            proxNo = no;
        }

        void setaValor(int& valor)
        {
            this->valor = valor;
        }

        int retornaValor() const
        {
            return valor;
        }

        NoListaLigada *retornaProximoNo()
        {
            return proxNo;
        }
};

class ListaLigada
{
    private:
        NoListaLigada *lista;

    public:
        ListaLigada()
        {
            lista = nullptr;
        }

        void insereNoCabeca(NoListaLigada* no)
        {
            if (lista == nullptr)
                lista = no;

            else
            {
                no->setaProxNo(lista);
                lista = no;
                
            }
        }

        void insereNoFinal(NoListaLigada* no)
        {
            if (lista != nullptr)
            {
                NoListaLigada *aux = lista;

                while (aux->retornaProximoNo() != nullptr)
                {
                    aux = aux->retornaProximoNo();
                }
                aux->setaProxNo(no);
            }

            else
                lista = no;
            
            
        }

        void printLista()
        {
            NoListaLigada *no = lista;

            while (no != nullptr)
            {
                std::cout << no->retornaValor() << " ";
                no = no->retornaProximoNo();
            }
        }

        void deletaNos()
        {
            NoListaLigada *no = lista;
            NoListaLigada *del = lista;

            while (no != nullptr)
            {
                del = no;
                no = no->retornaProximoNo();
                delete del;
            }

        }

};

class VerticeUnico
{
    protected:
        int id;
        bool visitado;        

    public:
        VerticeUnico(const int& id)
        {
            this->id = id;
            visitado = false;
        }

        VerticeUnico()
        {

        }

        bool operator ==(const VerticeUnico && obj) const
        {
            if (id == obj.id)
                return true;
            else
                return false;
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
};



class HashVertice 
{
    public:    
        int operator()(VerticeUnico && v) const
        {
            return std::hash<int>()(v.getID());
        }
};
 

class Vertice : public VerticeUnico
{
    private:
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
        ListaLigada lista;		

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

		void DFS()
        {
            for (auto& v : vertices)
            {
                if (!(v.second->foiVisitado()))
                    visitadorDFS(v.second);
            }
        }
        
        void visitadorDFS(Vertice*& v)
        {
            v->setaVisitado();

            for (Vertice* u: v->retornaVizinhos())
            {
                if (!(u->foiVisitado()))
                    visitadorDFS(u);
            }
            NoListaLigada *no = new NoListaLigada(v->getID(), nullptr);
            lista.insereNoCabeca(no);
        }

        void imprimeListaOrdenada()
        {
            lista.printLista();
            std::cout << std::endl;
        }

        void liberaLista()
        {
            lista.deletaNos();
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
    int numTarefas, numDependencias;

    std::cin >> numTarefas;
    std::cin >> numDependencias;    

    while (!(numTarefas == 0 && numDependencias == 0))
    {
        Grafo tarefas = Grafo(numTarefas);

        for (int i = 0 ; i < numDependencias ; i++)
        {
            int tarefa1, tarefa2;

            std::cin >> tarefa1;
            std::cin >> tarefa2;

            tarefas.adicionaAresta(tarefa1, tarefa2);

        }

        tarefas.DFS();
        tarefas.imprimeListaOrdenada();
        tarefas.liberaLista();

        std::cin >> numTarefas;
        std::cin >> numDependencias;        
    }

    
    

    return 0;
}
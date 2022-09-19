#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <vector>

/*
    O programa modela um grafo e seus vértices. Para realizarmos a soma com base na distância, basta realizar uma busca em profundidade,
    limitada a distância dada. Para cada vizinho, iremos até a distância dada. Depois, voltamos decrementando o contador para ir para o próximo vizinho,
    até que todos os vizinhos do vértice solicitado tenham sido visitados.
    Ao visitar, somamos o valor solicitado.
*/

class BitTree
{
	private:
		std::vector<int> arvore;
		
		int numVertices;
	
		int proximoElemento(int x)
		{
			return x & (-x);
		}
 
	public:
	
		BitTree(int numVertices)
		{
			this->numVertices = numVertices;
			arvore.resize(numVertices, 0);			
		}

		BitTree()
		{

		}
	
		void atualizaArvore(int indiceInicial, int valor)
		{
			for (int i = indiceInicial ; i < numVertices ; i += proximoElemento(i))
				arvore[i] += valor;
		}
	
		int retornaValor(int indiceVertice)
		{
			int soma = 0;

			for (int i = indiceVertice ; i > 0 ; i -= proximoElemento(i))
				soma += arvore[i];
			
			return soma;
		}
};

class VerticeUnico
{
    protected:
        int id, valor;        

    public:
        VerticeUnico(const int& id)
        {
            this->id = id;
            valor = 0;
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

        int retornaValor() const
        {
            return valor;
        }

        void adicionaValor(const int& valor)
        {
            this->valor += valor;
        }

        int getID() const
        {
            return id;
        }            
};



class HashVertice 
{
    public:    
        static uint64_t splitmix64(uint64_t x)
        {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30))
                * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27))
                * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }
    
        int operator()(VerticeUnico && v) const
        {
            static const uint64_t random
                = std::chrono::steady_clock::now()
                    .time_since_epoch()
                    .count();
            return splitmix64(v.getID() + random);
        }
};
 

class Vertice : public VerticeUnico
{
    private:
        std::unordered_set<Vertice *> vizinhos;         

    public:
        Vertice(const int& id)
        {
            this->id = id;
            valor = 0;
        }

        Vertice()
        {

        }

        void adicionaVizinho(Vertice*& v)
        {
            vizinhos.insert(v);
        }

        std::unordered_set<Vertice *>& retornaVizinhos()
        {
            return vizinhos;
        }

        void adicionaValor(const int& valor)
        {
            this->valor += valor;
        }          
};



class Grafo
{
    private:
		std::vector<int> ramificacao;
		std::vector<int> profundidade;
        std::unordered_map<int, Vertice *> vertices;
		

    public:
        Grafo (int n)
        {
            for (int i = 1 ; i <= n ; i++)
                vertices.insert(std::make_pair(i, new Vertice(i)));

			profundidade.resize(n+1);
			ramificacao.resize(n+1);      
        }

        void adicionaAresta(const int& id1, const int& id2)
        {
            Vertice *v = vertices.at(id1), *w = vertices.at(id2);
			
            v->adicionaVizinho(w);
            w->adicionaVizinho(v);         
        }

        void imprimeValorVertice(const int& id)
        {
            Vertice *vertice = vertices.at(id);

            std::cout << vertice->retornaValor() << std::endl;
        }

        bool eFolha(Vertice* v)
        {
            return v->retornaVizinhos().size() == 1;
        }


        void imprimeVizinhos()
        {
            for (auto v = vertices.begin() ; v != vertices.end() ; v++)
            {
                std::cout << v->first << " ";
                for (const auto& u : v->second->retornaVizinhos())
                    std::cout << u->getID() << " ";
                std::cout << std::endl;
            }
        }

        void imprimeValoresGrafo()
        {
            static int iteracao = 1;
            std::cout << "Iteracao " <<iteracao << std::endl;
            iteracao++;
            for (auto v = vertices.begin() ; v != vertices.end() ; v++)
                std::cout << v->first << " " << v->second->retornaValor() << std::endl;
        }

		int DFS(const int& id, Vertice*& v, int distancia, int ramificacao)
		{			
			this->profundidade[v->getID()] = distancia;
			this->ramificacao[v->getID()] = ramificacao;
			int numVerticesRamificacao = 1;

			for (Vertice* u : v->retornaVizinhos())
			{
				if (u->getID() != id)
					numVerticesRamificacao += DFS(v->getID(), u, distancia + 1, ramificacao);
					
			}

			return numVerticesRamificacao;
		}

        ~Grafo()
        {
            std::for_each(vertices.begin(), vertices.end(), [](std::unordered_map<int, Vertice *>::value_type& p) { delete p.second; });
        }

		std::unordered_map<int, Vertice *>& retornaVertices()
		{
			return vertices;
		}		

		std::vector<int>& retornaProfundidades()
		{
			return profundidade;
		}

		std::vector<int>& retornaRamificacao()
		{
			return ramificacao;
		}
};

int main()
{
    int numNos, numReq, maiorRamificacao = 0;
	std::unordered_set<Vertice *> vizinhosRaiz;

    std::cin >> numNos;
    std::cin >> numReq;
	std::vector<BitTree> bitTree;	
    Grafo arvore = Grafo(numNos);
	

    for (int i = 0 ; i < numNos - 1 ; i++)
    {		
        int id1, id2;
        std::cin >> id1;
        std::cin >> id2;
        arvore.adicionaAresta(id1, id2);
    }
	
	vizinhosRaiz = arvore.retornaVertices().at(1)->retornaVizinhos();
	bitTree.resize(vizinhosRaiz.size() + 1);
	arvore.retornaProfundidades()[1] = 1;	

	auto itVizinhos = vizinhosRaiz.begin();
	int ramificacao = 1;

	/*
		Inicialmente, iremos construir uma Bit tree para cada ramificação, e vamos incluir a raiz como se fosse membro de cada uma.
		Começamos a contar a ramificação a partir do 1.
	*/

	for (auto v : vizinhosRaiz)
	{		
		int tamRamificacao = arvore.DFS(1, v, 2, ramificacao) + 1; // A DFS retorna o número de vértices na ramificação, incluindo a raiz.
		bitTree[ramificacao] = BitTree(tamRamificacao + 1); // A BitTree é sempre o número de vértices + 1;

		/* 
			No caso em que iremos modificar as outras ramificações , ou seja, que a distância é maior que a altura do vértice, precisamos de uma árvore auxiliar
			que tem os valores baseados na profundidade da ramificação.
			Logo, ela deve ser construída com base no número de vértices da maior ramificação, pois ela irá abranger qualquer ramificação, já que ela
			será a cota superior.
		*/

		maiorRamificacao = std::max(tamRamificacao + 1, maiorRamificacao);
		ramificacao++; // Visitamos todos os vértices dessa ramificação, iremos para a próxima
	}

	bitTree[0] = BitTree(maiorRamificacao + 1); // Criamos a Bit tree para o cálculo de valores com base na profundidade

	std::vector<int> profundidades = arvore.retornaProfundidades(); // Retorna informações de profundidade dos vértices
	std::vector<int> ramificacoes = arvore.retornaRamificacao(); // Retorna informações das ramificações para cada vértice
	
    for (int i = 0 ; i < numReq ; i++)
    {
        int tipoReq, vertice;

        std::cin >> tipoReq;
		std::cin >> vertice;

		std::unordered_map<int, Vertice *> verticesGrafo = arvore.retornaVertices(); // Vértices da árvore
		
		
		int profundidadeVertice = profundidades[verticesGrafo.at(vertice)->getID()]; // Recebe a informação da profundidade do vértice
		int ramificacaoVertice = ramificacoes[verticesGrafo.at(vertice)->getID()]; // Recebe a informação de qual ramificação esse vértice está

        if (tipoReq == 0)
        {
            int valor, distancia;
            
            std::cin >> valor;
            std::cin >> distancia;
			
			/* 
				Calcula o número de vértices que estão fora da ramificação, para o caso em que distância é maior que a profundidade.
				Se o resultado do primeiro argumento for maior que 0, então iremos sair da ramificação (desconsiderando a raiz).
				Esse cálculo irá fornecer a profundidade do vértice que será alterado.
				Se o valor for 0, então não iremos sair da ramificação.
				A base do cálculo é tomar a distância e diminuir da profundidade. Se iremos sair da ramificação, esse valor já irá ser maior que 0.
				Somando 1 iremos desconsiderar a raiz e somando 1 iremos para a última profundidade do vértice que irá receber o valor a ser somado.
			*/

            int profundidadeVerticeForaRamificacao = std::max(distancia - profundidadeVertice + 1 + 1, 0);

			/*
				Devido à propriedade da Bit tree, a soma efetuada nas potências de 2 irá se propagar por todos os vértices.
				Com isso, iremos somar o valor nas profundidades com valor igual a uma potência de 2.
				Logo em seguida, se formos para outra ramificação, iremos corrigir essa soma nas profundidades que não devem receber esse valor, somando o oposto.
				Basta tomar o cálculo anterior e somar um, já que ele indicará a última profundidade a receber o valor de soma.
			*/

			bitTree[0].atualizaArvore(1, valor);
			bitTree[0].atualizaArvore(profundidadeVerticeForaRamificacao + 1, -valor);		

			/*
				Se o vértice solicitado não é a raiz, então devemos somar o valor nas ramificações.
				Se não sairmos da ramificação, a subtração entre profundidade do vértice e distância será maior ou igual a 1.
				Com isso, esse valor será maior que o primeiro cálculo, que será igual a 1 nesse caso.
				Logo, iremos somar o valor no vértice na distância dada, para que ele seja afetado e propague para os demais.
				Caso a distância seja maior que a profundidade, isso fará com que profundidadeVerticeForaRamificacao seja maior que 1.
				Assim, o segundo valor será negativo.
				Portanto, esse será o caso de somar o valor de forma que ele se propague por todos os vértices da ramificação
				que estejam relacionados com as profundidades que não devem receber o valor.
				Devemos fazer isso porque os vértices que devem receber o valor na ramificação serão afetados erroneamente,
				devido ao calculo de correção feito anteriormente para a profundidade deles.
				Assim, eles terão o valor a ser somado descontado, quando deveriam recebê-lo.
				Podemos evitar isso simplesmente somando o que foi retirado a partir do vértice da profundidade imediatamente abaixo da última que recebe o valor de soma.

				E, ainda, como no primeiro cálculo distribuimos o valor para todas as ramificações, precisamos retirar o valor somado
				para os vértices abaixo da distância dada para a soma, somando o oposto do valor.
			*/

			if (vertice != 1)
			{
				bitTree[ramificacaoVertice].atualizaArvore(std::max(profundidadeVerticeForaRamificacao + 1, profundidadeVertice - distancia), valor);			
				bitTree[ramificacaoVertice].atualizaArvore(profundidadeVertice + distancia + 1, -valor);				
        	}
		}

        else
        {
            int valorVertice;
			
			valorVertice = bitTree[0].retornaValor(profundidadeVertice); // O valor do vértice relacionado às somas na profundidade dele

            if (vertice != 1) // Se o vértice não é a raiz, iremos obter os valores somados para o vértice de uma ramificação especificamente
                valorVertice += bitTree[ramificacaoVertice].retornaValor(profundidadeVertice);
            
			std::cout << valorVertice << std::endl;
		}       
    }

    return 0;
}
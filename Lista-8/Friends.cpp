#include <iostream>
#include <vector>

/*
    O problema é a aplicação básica de union find.
    Cada pessoa é um conjunto unitário e, obviamente, todos disjuntos.
    Cada amizade fornecida pela entrada é uma união de conjuntos.
    A transitividade da amizade é dada colocando o novo amigo no conjunto do outro amigo.

    Basta realizar as operações de UNION a cada linha recebida e no final verificar qual conjunto é o maior.    
*/

class Pessoa
{
    private:
        short int id;
        Pessoa *amigo;
        int tamanho;

    public:

        Pessoa (short int id)
        {
            this->id = id;
            tamanho = 1;
        }

        Pessoa ()
        {

        }

        short int retornaId() const
        {
            return id;
        }
        
        Pessoa*& retornaAmigo()
        {
            return amigo;
        }

        int retornaTamanho() const
        {
            return tamanho;
        }

        void setaId(const int& id)
        {
            this->id = id;
        }

        void setaAmigo(Pessoa* amigo)
        {
           this->amigo = amigo;
        }

        void setaTamanho(const int& tamanho)
        {
            this->tamanho += tamanho;
        }
};

Pessoa *achaAmigo(Pessoa** x) // Caminho por comprenssão
{
    if ((*x)->retornaAmigo() != *x)
        (*x)->setaAmigo(achaAmigo(&(*x)->retornaAmigo()));

    return (*x)->retornaAmigo();
}

void adicionaAmigo(Pessoa *p1, Pessoa *p2)
{
    auto amigoP1 = achaAmigo(&p1); // Acha o conjunto de p1
    auto amigoP2 = achaAmigo(&p2); // Acha o conjunto de p2
    
    if (amigoP1 == amigoP2)
        return;

    if (amigoP1->retornaTamanho() < amigoP2->retornaTamanho()) // O conjunto 2 tem mais elementos, 1 se juntará a ele
    {
        amigoP1->setaAmigo(amigoP2->retornaAmigo());
        amigoP2->setaTamanho(amigoP1->retornaTamanho());
    }

    else // O conjunto 1 tem mais elementos, 2 se juntará a ele
    {
        amigoP2->setaAmigo(amigoP1->retornaAmigo());
        amigoP1->setaTamanho(amigoP2->retornaTamanho());
    }
}

int main()
{
    unsigned int numCasos;

    std::cin >> numCasos;

    while (numCasos--)
    {
        short int n;
        int m;
        std::vector<Pessoa> pessoas;

        std::cin >> n >> m;

        pessoas = std::vector<Pessoa>(n);

        for (short int i = 0 ; i < n ; i++)
        {
            pessoas[i] = Pessoa(i + 1);
            pessoas[i].setaAmigo(&pessoas[i]);
        }

        for (int i = 0 ; i < m ; i++)
        {
            short int p1, p2;

            std::cin >> p1 >> p2;

            adicionaAmigo(&pessoas[p1 - 1], &pessoas[p2 - 1]);
        }

        int maior = pessoas[0].retornaTamanho();

        for (const auto& p : pessoas)
        {
            if (p.retornaTamanho() > maior)
                maior = p.retornaTamanho();
        }

        std::cout << maior << std::endl;
    }

    return 0;
}

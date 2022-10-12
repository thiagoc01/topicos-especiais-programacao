'''
    O problema é um caso de aplicação da fórmula de Euler para grafos planares,
    F = E - V + 2.
    Entretanto, como as arestas se cruzam, não podemos aplicá-la diretamente.
    Mas podemos repartir as arestas para podermos realizar a aplicação.
    Duas arestas se cruzam em um ponto e esse é considerado um vértice interior.
    Notemos que, ao colocar um novo ponto na borda, esse se conectará
    com os demais pontos. Para criar novas áreas, não podemos alinhar
    esse ponto com um ponto já existente e uma interseção de
    outras duas retas. Caso contrário, não teríamos o número máximo de áreas.

    Vamos repartir a figura em um grafo de uma forma que não haja cruzamentos de arestas.

    Existem vértices na borda e no interior resultantes das interseções das arestas.
    Temos n vértices na borda. Os vértices do interior se dão por uma combinação
    de 4 vértices da borda, já que duas criam uma aresta e precisamos de duas arestas
    para essa interseção, o novo ponto.
    Logo, como podemos escolher 4 pontos dos n vértices, a quantidade total de vértices
    no interior é obtida pela combinação de n em grupos de 4.
    Assim, o total de vértices é n + n! / ((n - 4)! * 4!).

    Vamos analisar as arestas.
    Uma aresta é criada ao conectar dois pontos.
    Logo, realizando a combinação de n em grupos de 2, obtemos a quantidade total.
    No entanto, os vértices interiores são criados pela conexão de 2 arestas, que são
    oriundas de 4 vértices. Com isso, um vértice interior resulta em 2 arestas.
    E como podemos escolher 4 vértices dos n totais, temos 2 * combinação de n em grupos de 4
    arestas criadas pelos vértices interiores.
    Além desses 2 grupos, temos os arcos entre os vértices exteriores. Por ser um círculo,
    existem n arestas dessas.
    Finalmente, o total de arestas é n + (n! / ((n - 2)! * 2!)) + (2 * (n! / ((n - 4)! * 4!))).

    Substituindo o número de vértices e arestas na fórmula dada e simplificando, temos:

    F = (n! / ((n - 2)! * 2!)) + (n! / ((n - 4)! * 4!)) + 2

    Porém, esse cálculo inclui a face externa ao círculo.
    Subtraindo um, obtemos:

    F = (n! / ((n - 2)! * 2!)) + (n! / ((n - 4)! * 4!)) + 1
      = (n * (n - 1) / 2) + ((n * (n - 1) * (n - 2) * (n - 3)) / 24) + 1

    Essa equação fornece o número máximo de divisões do problema.
'''

numCasos = int(input())

for i in range(numCasos):
    n = int(input())
    print(int(n*(n - 1)*(n - 2)*(n - 3) // 24 + n*(n - 1) // 2 + 1))
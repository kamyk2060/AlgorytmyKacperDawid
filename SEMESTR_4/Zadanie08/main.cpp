// main.cpp - zadanie 8.1: algorytm Dijkstry

#include "graph.hpp"
#include "dijkstra.hpp"
#include <cassert>
#include <iostream>

void test_prosty_graf() {
    std::cout << "=== Test 1: prosty graf ===" << std::endl;

    //   (0) --1--> (1) --2--> (2)
    //    |                      ^
    //    +----------4-----------+
    //
    // Z 0 do 2 sa 2 drogi: bezposrednio (waga 4) lub przez 1 (waga 1+2=3)
    Graph g(3, true);
    g.add_edge(0, 1, 1.0);
    g.add_edge(1, 2, 2.0);
    g.add_edge(0, 2, 4.0);

    Dijkstra<int, Graph> d(g);
    d.run(0);

    assert(d.distance[0] == 0);
    assert(d.distance[1] == 1);
    assert(d.distance[2] == 3); // krotsza droga przez 1, nie 4!

    std::cout << "Sciezka 0 -> 2: ";
    d.print_path(0, 2);
    std::cout << " (dystans " << d.distance[2] << ")" << std::endl;
    std::cout << "Test 1 PASSED" << std::endl;
}

void test_graf_nieskierowany() {
    std::cout << "\n=== Test 2: graf nieskierowany ===" << std::endl;

    //   (0) --5-- (1) --3-- (2)
    //
    // Krawedzie dzialaja w obie strony.
    Graph g(3, false);
    g.add_edge(0, 1, 5.0);
    g.add_edge(1, 2, 3.0);

    Dijkstra<int, Graph> d(g);
    d.run(0);

    assert(d.distance[0] == 0);
    assert(d.distance[1] == 5);
    assert(d.distance[2] == 8); // 5+3

    std::cout << "Dystanse od 0: 0=" << d.distance[0]
              << ", 1=" << d.distance[1]
              << ", 2=" << d.distance[2] << std::endl;
    std::cout << "Test 2 PASSED" << std::endl;
}

void test_nieosiagalny() {
    std::cout << "\n=== Test 3: wierzcholek nieosiagalny ===" << std::endl;

    //   (0) --1--> (1)     (2)  <- wierzcholek 2 izolowany
    //
    Graph g(3, true);
    g.add_edge(0, 1, 1.0);

    Dijkstra<int, Graph> d(g);
    d.run(0);

    assert(d.distance[0] == 0);
    assert(d.distance[1] == 1);
    assert((d.distance[2] == Dijkstra<int, Graph>::INF));

    std::cout << "Sciezka 0 -> 2: ";
    d.print_path(0, 2);
    std::cout << std::endl;
    std::cout << "Test 3 PASSED" << std::endl;
}

// przykladowy graf n=10
void zadanie_81() {
    std::cout << "\n=== Zadanie 8.1: graf n=10 ===" << std::endl;

    Graph g(10, true);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 2);
    g.add_edge(2, 1, 1);
    g.add_edge(1, 3, 5);
    g.add_edge(2, 4, 4);
    g.add_edge(3, 4, 2);
    g.add_edge(4, 6, 1);
    g.add_edge(6, 7, 2);
    g.add_edge(6, 8, 2);
    g.add_edge(7, 9, 1);
    g.add_edge(8, 9, 3);

    Dijkstra<int, Graph> d(g);
    d.run(0);

    std::cout << "\nNajkrotsze sciezki z wierzcholka 0:" << std::endl;
    for (int v = 0; v < 10; v++) {
        std::cout << "  do " << v << ": ";
        d.print_path(0, v);
        if (d.distance[v] != Dijkstra<int, Graph>::INF)
            std::cout << " (dystans " << d.distance[v] << ")";
        std::cout << std::endl;
    }

    // sprawdzamy ze 0 jest korzeniem, a 1 jest osiagalny krotsza droga
    assert(d.distance[0] == 0);
    assert(d.distance[1] == 3); // przez 2: 0->2->1 = 2+1 = 3, nie bezposrednio (4)

    std::cout << "\nZadanie 8.1 PASSED" << std::endl;
}

int main() {
    test_prosty_graf();
    test_graf_nieskierowany();
    test_nieosiagalny();
    zadanie_81();

    std::cout << "\n=== WSZYSTKIE TESTY PASSED ===" << std::endl;
    return 0;
}
#include "graph.hpp"
#include "connected.hpp"
#include <cassert>
#include <iostream>
#include <vector>

void test_graf_spojny() {
    std::cout << "=== Test grafu spojnego (1 skladowa) ===" << std::endl;

    // 0 - 1 - 2
    //     |
    //     3 - 4
    Graph g(5);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(3, 4);

    ConnectedComponents<int, Graph> cc(g);
    cc.run();

    // wszystkie wierzchołki w tej samej składowej
    assert(cc.ncc == 1);
    for (int v = 0; v < 5; v++)
        assert(cc.component[v] == 0);

    std::cout << "Liczba skladowych: " << cc.ncc << std::endl;
    std::cout << "Test PASSED" << std::endl;
}

void test_graf_bez_krawedzi() {
    std::cout << "\n=== Test grafu bez krawedzi (n skladowych) ===" << std::endl;

    // 4 izolowane wierzchołki
    Graph g(4);

    ConnectedComponents<int, Graph> cc(g);
    cc.run();

    // każdy wierzchołek to osobna składowa
    assert(cc.ncc == 4);

    std::cout << "Liczba skladowych: " << cc.ncc << std::endl;
    std::cout << "Test PASSED" << std::endl;
}

void test_dwie_skladowe() {
    std::cout << "\n=== Test grafu z 2 skladowymi ===" << std::endl;

    // składowa A: 0 - 1 - 2
    // składowa B: 3 - 4
    Graph g(5);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(3, 4);

    ConnectedComponents<int, Graph> cc(g);
    cc.run();

    assert(cc.ncc == 2);
    // wierzchołki 0, 1, 2 w tej samej składowej
    assert(cc.component[0] == cc.component[1]);
    assert(cc.component[1] == cc.component[2]);
    // wierzchołki 3, 4 w tej samej składowej
    assert(cc.component[3] == cc.component[4]);
    // ale składowa A != składowa B
    assert(cc.component[0] != cc.component[3]);

    std::cout << "Liczba skladowych: " << cc.ncc << std::endl;
    std::cout << "Test PASSED" << std::endl;
}

void zadanie_71() {
    std::cout << "\n=== Zadanie 7.1: spojne skladowe grafu niespojnego n=10 ==="
              << std::endl;

    // graf niespojny z n=10, 3 spojne skladowe:
    //
    // skladowa A (trojkat + ogon):  0 - 1 - 2 - 0, 2 - 3
    // skladowa B (sciezka):         4 - 5 - 6 - 7
    // skladowa C (para + izolowany): 8 - 9, wierzcholek (juz brak - n=10)
    //
    Graph g(10);

    // skladowa A: trojkat 0-1-2 z ogonem do 3
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(0, 2);
    g.add_edge(2, 3);

    // skladowa B: sciezka 4-5-6-7
    g.add_edge(4, 5);
    g.add_edge(5, 6);
    g.add_edge(6, 7);

    // skladowa C: para 8-9
    g.add_edge(8, 9);

    std::cout << "\nGraf:" << std::endl;
    g.display();

    ConnectedComponents<int, Graph> cc(g);
    cc.run();

    std::cout << "\nLiczba spojnych skladowych: " << cc.ncc << std::endl;
    assert(cc.ncc == 3);

    // wypisujemy przynaleznosc kazdego wierzcholka
    std::cout << "\nPrzynaleznosc wierzcholkow do skladowych:" << std::endl;
    for (int v = 0; v < 10; v++) {
        std::cout << "  wierzcholek " << v
                  << " -> skladowa " << cc.component[v] << std::endl;
    }

    // grupujemy wierzcholki wedlug skladowych
    std::cout << "\nSkladowe:" << std::endl;
    std::vector< std::vector<int> > skladowe(cc.ncc);
    for (int v = 0; v < 10; v++) {
        skladowe[cc.component[v]].push_back(v);
    }
    for (int i = 0; i < cc.ncc; i++) {
        std::cout << "  skladowa " << i << ": { ";
        for (int v : skladowe[i]) std::cout << v << " ";
        std::cout << "}" << std::endl;
    }

    std::cout << "\nZadanie 7.1 PASSED" << std::endl;
}

int main() {
    test_graf_spojny();
    test_graf_bez_krawedzi();
    test_dwie_skladowe();
    zadanie_71();

    std::cout << "\n=== WSZYSTKIE TESTY PASSED ===" << std::endl;
    return 0;
}

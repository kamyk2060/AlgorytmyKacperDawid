// main.cpp - testy ADT GRAPH (macierz sąsiedztwa, graf bez wag)

#include "graph.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

void test_edge() {
    std::cout << "=== Test klasy Edge ===" << std::endl;

    Edge<int> e1(0, 1);
    Edge<int> e2(0, 1, 2.5);
    Edge<int> e3(e1); // konstruktor kopiujący

    // domyślna waga
    assert(e1.weight == 1.0);
    assert(e2.weight == 2.5);

    // konstruktor kopiujący
    assert(e3.source == 0 && e3.target == 1 && e3.weight == 1.0);

    // operator ==, !=
    assert(e1 == e3);
    assert(e1 != e2);

    // operator ~ (odwrócenie krawędzi)
    Edge<int> e4 = ~e2;
    assert(e4.source == 1 && e4.target == 0 && e4.weight == 2.5);

    // operator przypisania
    Edge<int> e5(9, 9);
    e5 = e1;
    assert(e5 == e1);

    // operator wypisywania
    std::cout << "Krawedz e2: " << e2 << std::endl;

    std::cout << "Test klasy Edge PASSED" << std::endl;
}

void test_graf_nieskierowany() {
    std::cout << "\n=== Test grafu nieskierowanego ===" << std::endl;

    Graph g(5); // 5 wierzchołków: 0,1,2,3,4

    // sprawdzenie podstawowych właściwości
    assert(g.v() == 5);
    assert(g.e() == 0);
    assert(!g.is_directed());

    // sprawdzenie wierzchołków
    assert(g.has_node(0));
    assert(g.has_node(4));
    assert(!g.has_node(5));
    assert(!g.has_node(-1));

    // dodawanie krawędzi
    g.add_edge(0, 1);
    g.add_edge(0, 3);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);

    assert(g.e() == 5);

    // istnienie krawędzi (nieskierowany - obie strony)
    assert(g.has_edge(0, 1));
    assert(g.has_edge(1, 0));
    assert(g.has_edge(2, 3));
    assert(g.has_edge(3, 2));
    assert(!g.has_edge(0, 4));
    assert(!g.has_edge(1, 4));

    // wagi (graf bez wag - 0 lub 1)
    assert(g.weight(0, 1) == 1.0);
    assert(g.weight(0, 4) == 0.0);

    // stopnie wierzchołków
    assert(g.degree(0) == 2); // sąsiedzi: 1, 3
    assert(g.degree(1) == 2); // sąsiedzi: 0, 2
    assert(g.degree(2) == 2); // sąsiedzi: 1, 3
    assert(g.degree(3) == 3); // sąsiedzi: 0, 2, 4
    assert(g.degree(4) == 1); // sąsiad: 3

    // test z Edge
    Edge<int> krawedz(1, 4);
    assert(!g.has_edge(krawedz));
    g.add_edge(krawedz);
    assert(g.has_edge(krawedz));
    assert(g.has_edge(1, 4));
    assert(g.has_edge(4, 1));
    assert(g.e() == 6);

    // usuwanie krawędzi
    g.del_edge(0, 1);
    assert(!g.has_edge(0, 1));
    assert(!g.has_edge(1, 0));
    assert(g.e() == 5);

    // usuwanie krawędzi przez Edge
    Edge<int> do_usuniecia(2, 3);
    g.del_edge(do_usuniecia);
    assert(!g.has_edge(2, 3));
    assert(!g.has_edge(3, 2));
    assert(g.e() == 4);

    // usuwanie wierzchołka (usunięcie krawędzi incydentnych)
    g.del_node(3);
    assert(!g.has_edge(0, 3));
    assert(!g.has_edge(3, 4));

    g.display();

    // czyszczenie grafu
    g.clear();
    assert(g.e() == 0);
    assert(g.v() == 5);

    std::cout << "Wszystkie testy grafu nieskierowanego PASSED" << std::endl;
}

void test_graf_skierowany() {
    std::cout << "\n=== Test grafu skierowanego ===" << std::endl;

    Graph g(4, true);

    assert(g.v() == 4);
    assert(g.e() == 0);
    assert(g.is_directed());

    // dodawanie krawędzi skierowanych
    g.add_edge(0, 1);
    g.add_edge(0, 3);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);

    assert(g.e() == 5);

    // krawędź skierowana istnieje tylko w jedną stronę
    assert(g.has_edge(0, 1));
    assert(!g.has_edge(1, 0));
    assert(g.has_edge(2, 3));
    assert(!g.has_edge(3, 2));

    // stopnie wejściowe i wyjściowe (jak w przykładzie z instrukcji)
    assert(g.outdegree(0) == 2);
    assert(g.indegree(0) == 1);
    assert(g.outdegree(1) == 1);
    assert(g.indegree(1) == 1);
    assert(g.outdegree(2) == 2);
    assert(g.indegree(2) == 1);
    assert(g.outdegree(3) == 0);
    assert(g.indegree(3) == 2);

    // test z Edge
    Edge<int> krawedz(1, 3);
    g.add_edge(krawedz);
    assert(g.has_edge(1, 3));
    assert(!g.has_edge(3, 1));
    assert(g.e() == 6);

    // usuwanie krawędzi skierowanej
    g.del_edge(0, 1);
    assert(!g.has_edge(0, 1));
    assert(g.e() == 5);

    // usuwanie wierzchołka
    g.del_node(2);
    assert(!g.has_edge(1, 2));
    assert(!g.has_edge(2, 0));
    assert(!g.has_edge(2, 3));
    assert(g.e() == 2); // zostały: 0->3, 1->3

    g.display();

    g.clear();
    assert(g.e() == 0);

    std::cout << "Wszystkie testy grafu skierowanego PASSED" << std::endl;
}

void test_graf_pelny() {
    std::cout << "\n=== Test grafu pelnego K4 ===" << std::endl;

    Graph g(4);
    for (int u = 0; u < 4; u++)
        for (int w = u + 1; w < 4; w++)
            g.add_edge(u, w);

    assert(g.e() == 6); // K4 ma 4*3/2 = 6 krawędzi
    for (int u = 0; u < 4; u++)
        assert(g.degree(u) == 3);

    g.display();

    std::cout << "Test grafu pelnego PASSED" << std::endl;
}

void test_podwojne_dodawanie() {
    std::cout << "\n=== Test podwojnego dodawania ===" << std::endl;

    Graph g(3);
    g.add_edge(0, 1);
    g.add_edge(0, 1); // dodanie tej samej krawędzi ponownie
    assert(g.e() == 1); // nadal 1 krawędź (macierz: 0/1)

    std::cout << "Test podwojnego dodawania PASSED" << std::endl;
}

void test_node_iterator() {
    std::cout << "\n=== Test NodeIterator ===" << std::endl;

    Graph g(5);
    std::vector<int> wierzcholki;
    for (auto it = g.node_begin(); it != g.node_end(); ++it)
        wierzcholki.push_back(*it);

    assert(wierzcholki.size() == 5);
    for (int i = 0; i < 5; i++)
        assert(wierzcholki[i] == i);

    std::cout << "Test NodeIterator PASSED" << std::endl;
}

void test_edge_iterator_nieskierowany() {
    std::cout << "\n=== Test EdgeIterator (nieskierowany) ===" << std::endl;

    // graf nieskierowany z instrukcji:
    // 0-1, 0-2, 0-3, 1-2, 2-3
    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(0, 3);
    g.add_edge(1, 2);
    g.add_edge(2, 3);

    assert(g.e() == 5);

    std::vector<Edge<int>> krawedzie;
    for (auto it = g.edge_begin(); it != g.edge_end(); ++it)
        krawedzie.push_back(*it);

    // powinno być 5 krawędzi (nieskierowany - każda raz)
    assert((int)krawedzie.size() == 5);

    std::cout << "Krawedzie (nieskierowany): ";
    for (const auto& e : krawedzie)
        std::cout << e << " ";
    std::cout << std::endl;

    std::cout << "Test EdgeIterator (nieskierowany) PASSED" << std::endl;
}

void test_edge_iterator_skierowany() {
    std::cout << "\n=== Test EdgeIterator (skierowany) ===" << std::endl;

    // graf skierowany z instrukcji:
    // 0->1, 0->3, 1->2, 2->0, 2->3
    Graph g(4, true);
    g.add_edge(0, 1);
    g.add_edge(0, 3);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);

    assert(g.e() == 5);

    std::vector<Edge<int>> krawedzie;
    for (auto it = g.edge_begin(); it != g.edge_end(); ++it)
        krawedzie.push_back(*it);

    assert((int)krawedzie.size() == 5);

    std::cout << "Krawedzie (skierowany): ";
    for (const auto& e : krawedzie)
        std::cout << e << " ";
    std::cout << std::endl;

    std::cout << "Test EdgeIterator (skierowany) PASSED" << std::endl;
}

void test_adjacent_iterator() {
    std::cout << "\n=== Test AdjacentIterator ===" << std::endl;

    // graf nieskierowany: 0-1, 0-2, 0-3, 1-2, 2-3
    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(0, 3);
    g.add_edge(1, 2);
    g.add_edge(2, 3);

    // sąsiedzi wierzchołka 0: {1, 2, 3}
    std::vector<int> sasiedzi_0;
    for (auto it = g.adj_begin(0); it != g.adj_end(0); ++it)
        sasiedzi_0.push_back(*it);
    assert(sasiedzi_0.size() == 3);
    assert(sasiedzi_0[0] == 1);
    assert(sasiedzi_0[1] == 2);
    assert(sasiedzi_0[2] == 3);

    // sąsiedzi wierzchołka 1: {0, 2}
    std::vector<int> sasiedzi_1;
    for (auto it = g.adj_begin(1); it != g.adj_end(1); ++it)
        sasiedzi_1.push_back(*it);
    assert(sasiedzi_1.size() == 2);
    assert(sasiedzi_1[0] == 0);
    assert(sasiedzi_1[1] == 2);

    // sąsiedzi wierzchołka 3: {0, 2}
    std::vector<int> sasiedzi_3;
    for (auto it = g.adj_begin(3); it != g.adj_end(3); ++it)
        sasiedzi_3.push_back(*it);
    assert(sasiedzi_3.size() == 2);
    assert(sasiedzi_3[0] == 0);
    assert(sasiedzi_3[1] == 2);

    std::cout << "Sasiedzi wierzcholka 0: ";
    for (int s : sasiedzi_0) std::cout << s << " ";
    std::cout << std::endl;

    std::cout << "Sasiedzi wierzcholka 1: ";
    for (int s : sasiedzi_1) std::cout << s << " ";
    std::cout << std::endl;

    std::cout << "Test AdjacentIterator PASSED" << std::endl;
}

void test_adjacent_iterator_skierowany() {
    std::cout << "\n=== Test AdjacentIterator (skierowany) ===" << std::endl;

    // graf skierowany: 0->1, 0->3, 1->2, 2->0, 2->3
    Graph g(4, true);
    g.add_edge(0, 1);
    g.add_edge(0, 3);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(2, 3);

    // sąsiedzi (wychodzące) wierzchołka 0: {1, 3}
    std::vector<int> sasiedzi_0;
    for (auto it = g.adj_begin(0); it != g.adj_end(0); ++it)
        sasiedzi_0.push_back(*it);
    assert(sasiedzi_0.size() == 2);
    assert(sasiedzi_0[0] == 1);
    assert(sasiedzi_0[1] == 3);

    // sąsiedzi wierzchołka 3: brak (outdegree = 0)
    std::vector<int> sasiedzi_3;
    for (auto it = g.adj_begin(3); it != g.adj_end(3); ++it)
        sasiedzi_3.push_back(*it);
    assert(sasiedzi_3.size() == 0);

    std::cout << "Sasiedzi wierzcholka 0 (skierowany): ";
    for (int s : sasiedzi_0) std::cout << s << " ";
    std::cout << std::endl;

    std::cout << "Test AdjacentIterator (skierowany) PASSED" << std::endl;
}

void test_pusty_graf() {
    std::cout << "\n=== Test pustego grafu (iteratory) ===" << std::endl;

    Graph g(3);

    // brak krawędzi - EdgeIterator powinien być pusty
    int ile_krawedzi = 0;
    for (auto it = g.edge_begin(); it != g.edge_end(); ++it)
        ile_krawedzi++;
    assert(ile_krawedzi == 0);

    // brak sąsiadów
    int ile_sasiadow = 0;
    for (auto it = g.adj_begin(0); it != g.adj_end(0); ++it)
        ile_sasiadow++;
    assert(ile_sasiadow == 0);

    std::cout << "Test pustego grafu PASSED" << std::endl;
}

int main() {
    test_edge();
    test_graf_nieskierowany();
    test_graf_skierowany();
    test_graf_pelny();
    test_podwojne_dodawanie();
    test_node_iterator();
    test_edge_iterator_nieskierowany();
    test_edge_iterator_skierowany();
    test_adjacent_iterator();
    test_adjacent_iterator_skierowany();
    test_pusty_graf();

    std::cout << "\n=== WSZYSTKIE TESTY PASSED ===" << std::endl;
    return 0;
}
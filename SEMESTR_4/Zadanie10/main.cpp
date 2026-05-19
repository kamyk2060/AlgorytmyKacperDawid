
#include "graph.hpp"
#include "transitive.hpp"
#include <cassert>
#include <iostream>

// Test 1: prosty graf
void test_prosty_graf() {
    std::cout << "=== Test 1: prosty graf ===" << std::endl;

    //   (0) --> (1) --> (2)
    //
    // Z 0 mozna dojsc do 1 i 2 (przez 1).
    // Z 1 mozna dojsc do 2.
    // Z 2 nie mozna nigdzie.
    Graph g(3, true);
    g.add_edge(0, 1, 1.0);
    g.add_edge(1, 2, 1.0);

    TransitiveClosure<Graph> tc(g);
    tc.run();
    tc.wypisz();

    // przekatna zawsze true
    assert(tc.T[0][0] == true);
    assert(tc.T[1][1] == true);
    assert(tc.T[2][2] == true);

    // sciezki istniejace
    assert(tc.T[0][1] == true); // bezposrednia krawedz
    assert(tc.T[0][2] == true); // przez 1
    assert(tc.T[1][2] == true); // bezposrednia

    // sciezki nieistniejace
    assert(tc.T[1][0] == false);
    assert(tc.T[2][0] == false);
    assert(tc.T[2][1] == false);

    std::cout << "Test 1 PASSED" << std::endl;
}

// Test 2: graf z cyklem
void test_cykl() {
    std::cout << "\n=== Test 2: graf z cyklem ===" << std::endl;

    //   (0) --> (1) --> (2)
    //    ^               |
    //    +---------------+
    //
    // Cykl 0 -> 1 -> 2 -> 0
    // Z kazdego wierzcholka mozna dojsc do kazdego!
    Graph g(3, true);
    g.add_edge(0, 1, 1.0);
    g.add_edge(1, 2, 1.0);
    g.add_edge(2, 0, 1.0);

    TransitiveClosure<Graph> tc(g);
    tc.run();
    tc.wypisz();

    // wszystkie pary maja sciezki
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            assert(tc.T[i][j] == true);

    std::cout << "Test 2 PASSED" << std::endl;
}


// Zadanie 10.1 - przykladowy graf n=10
void zadanie_101() {
    std::cout << "\n=== Zadanie 10.1: graf n=10 ===" << std::endl;

    // graf skierowany, n=10
    Graph g(10, true);
    g.add_edge(0, 1, 1.0);
    g.add_edge(0, 2, 1.0);
    g.add_edge(2, 1, 1.0);
    g.add_edge(1, 3, 1.0);
    g.add_edge(2, 4, 1.0);
    g.add_edge(3, 4, 1.0);
    g.add_edge(3, 5, 1.0);
    g.add_edge(4, 6, 1.0);
    g.add_edge(5, 8, 1.0);
    g.add_edge(6, 7, 1.0);
    g.add_edge(6, 8, 1.0);
    g.add_edge(7, 9, 1.0);
    g.add_edge(8, 9, 1.0);

    std::cout << "\nGraf:" << std::endl;
    g.display();

    TransitiveClosure<Graph> tc(g);
    tc.run();

    std::cout << std::endl;
    tc.wypisz();

    std::cout << std::endl;
    tc.wypisz_pary_sciezek();

    // przekatna zawsze true
    for (int i = 0; i < 10; i++)
        assert(tc.T[i][i] == true);

    // z 0 mozna dojsc wszedzie (graf "rozchodzi sie" z 0)
    for (int j = 0; j < 10; j++)
        assert(tc.T[0][j] == true);

    // z 9 (lisc) nie mozna nigdzie poza siebie
    for (int j = 0; j < 10; j++) {
        if (j == 9)
            assert(tc.T[9][j] == true);
        else
            assert(tc.T[9][j] == false);
    }

    std::cout << "\nZadanie 10.1 PASSED" << std::endl;
}

int main() {
    test_prosty_graf();
    test_cykl();
    zadanie_101();

    std::cout << "\n=== WSZYSTKIE TESTY PASSED ===" << std::endl;
    return 0;
}

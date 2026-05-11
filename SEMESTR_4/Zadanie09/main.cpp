
#include "graph.hpp"
#include "floyd_warshall.hpp"
#include <cassert>
#include <iostream>

// Test 1: prosty graf, sprawdzamy podstawowe odleglosci
void test_prosty_graf() {
    std::cout << "=== Test 1: prosty graf ===" << std::endl;

    //   (0) --1--> (1) --2--> (2)
    //    |                      ^
    //    +----------4-----------+
    //
    // najkrotsza droga 0->2: przez 1 (1+2=3), nie bezposrednio (4)
    Graph g(3, true);
    g.add_edge(0, 1, 1.0);
    g.add_edge(1, 2, 2.0);
    g.add_edge(0, 2, 4.0);

    FloydWarshall<Graph> fw(g);
    fw.run();
    fw.wypisz_dystanse();

    assert(fw.Distance[0][0] == 0);
    assert(fw.Distance[0][1] == 1);
    assert(fw.Distance[0][2] == 3); // przez 1
    assert(fw.Distance[1][2] == 2);
    // graf skierowany - z 2 nie da sie nigdzie dojsc
    assert((fw.Distance[2][0] == FloydWarshall<Graph>::inf()));

    std::cout << "Test 1 PASSED" << std::endl;
}

// Test 2: graf nieskierowany - sciezki dzialaja w obie strony
void test_graf_nieskierowany() {
    std::cout << "\n=== Test 2: graf nieskierowany ===" << std::endl;

    //   (0) --5-- (1) --3-- (2)
    Graph g(3, false);
    g.add_edge(0, 1, 5.0);
    g.add_edge(1, 2, 3.0);

    FloydWarshall<Graph> fw(g);
    fw.run();
    fw.wypisz_dystanse();

    assert(fw.Distance[0][2] == 8);
    assert(fw.Distance[2][0] == 8); 
    assert(fw.Distance[0][1] == 5);
    assert(fw.Distance[1][0] == 5);

    std::cout << "Test 2 PASSED" << std::endl;
}

// Test 3: wierzcholek nieosiagalny
void test_nieosiagalny() {
    std::cout << "\n=== Test 3: wierzcholek nieosiagalny ===" << std::endl;

    //   (0) --1--> (1)     (2)  <- izolowany
    Graph g(3, true);
    g.add_edge(0, 1, 1.0);

    FloydWarshall<Graph> fw(g);
    fw.run();
    fw.wypisz_dystanse();

    assert(fw.Distance[0][1] == 1);
    assert((fw.Distance[0][2] == FloydWarshall<Graph>::inf()));
    assert((fw.Distance[1][2] == FloydWarshall<Graph>::inf()));
    assert(fw.Distance[0][0] == 0);
    assert(fw.Distance[2][2] == 0);

    std::cout << "Test 3 PASSED" << std::endl;
}

// Zadanie 9.2 - przykladowy graf n=10
void zadanie_92() {
    std::cout << "\n=== Zadanie 9.2: graf n=10 ===" << std::endl;

    // graf skierowany wazony, n=10
    Graph g(10, true);
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 2);
    g.add_edge(2, 1, 1);
    g.add_edge(1, 3, 5);
    g.add_edge(2, 4, 4);
    g.add_edge(3, 4, 2);
    g.add_edge(3, 5, 3);
    g.add_edge(4, 6, 1);
    g.add_edge(5, 8, 2);
    g.add_edge(6, 7, 2);
    g.add_edge(6, 8, 3);
    g.add_edge(7, 9, 1);
    g.add_edge(8, 9, 2);

    std::cout << "\nGraf:" << std::endl;
    g.display();

    FloydWarshall<Graph> fw(g);
    fw.run();

    std::cout << std::endl;
    fw.wypisz_dystanse();

    // kilka znanych odleglosci
    assert(fw.Distance[0][1] == 3); // przez 2: 0->2->1 = 2+1 = 3
    assert(fw.Distance[0][2] == 2); // bezposrednio
    assert(fw.Distance[0][9] != FloydWarshall<Graph>::inf());

    // przekatna - dystans do siebie zawsze 0
    for (int i = 0; i < 10; i++)
        assert(fw.Distance[i][i] == 0);

    std::cout << "\nZadanie 9.2 PASSED" << std::endl;
}

int main() {
    test_prosty_graf();
    test_graf_nieskierowany();
    test_nieosiagalny();
    zadanie_92();

    std::cout << "\n=== WSZYSTKIE TESTY PASSED ===" << std::endl;
    return 0;
}
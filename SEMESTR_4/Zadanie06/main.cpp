
#include "graph.hpp"
#include "topsort.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>

// weryfikacja sortowania topologicznego
// dla każdej krawędzi (u,v) sprawdzamy czy u występuje przed v
void weryfikuj_topsort(Graph& g, const std::vector<int>& sorted_nodes) {
    assert((int)sorted_nodes.size() == g.v());

    // tworzymy mapę: wierzchołek -> pozycja w posortowanym ciągu
    std::unordered_map<int, int> idx;
    for (int i = 0; i < g.v(); ++i)
        idx[sorted_nodes[i]] = i;

    // dla każdej krawędzi (u,v): idx[u] < idx[v]
    for (auto it = g.edge_begin(); it != g.edge_end(); ++it) {
        int u = (*it).source;
        int v = (*it).target;
        assert(idx[u] < idx[v]);
    }
}



void test_topsort_maly() {
    std::cout << "=== Test topsort na malym dagu ===" << std::endl;

    // dag z instrukcji:
    //   0 -> 1 -> 2
    //   | \       ^
    //   v  v      |
    //   3 -> 4 -> 5
    Graph g(6, true);
    g.add_edge(0, 1);
    g.add_edge(0, 3);
    g.add_edge(0, 4);
    g.add_edge(1, 2);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    g.add_edge(5, 2);

    std::vector<int> sorted_nodes = topsort_dfs<int, Graph>(g);

    std::cout << "Posortowane: ";
    for (int v : sorted_nodes) std::cout << v << " ";
    std::cout << std::endl;

    weryfikuj_topsort(g, sorted_nodes);

    std::cout << "Test PASSED" << std::endl;
}

void test_topsort_sciezka() {
    std::cout << "\n=== Test topsort na sciezce ===" << std::endl;

    // 0 -> 1 -> 2 -> 3 -> 4
    Graph g(5, true);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);

    std::vector<int> sorted_nodes = topsort_dfs<int, Graph>(g);

    std::cout << "Posortowane: ";
    for (int v : sorted_nodes) std::cout << v << " ";
    std::cout << std::endl;

    // dla ścieżki jedyne sortowanie to 0,1,2,3,4
    for (int i = 0; i < 5; i++)
        assert(sorted_nodes[i] == i);

    weryfikuj_topsort(g, sorted_nodes);

    std::cout << "Test PASSED" << std::endl;
}

void test_topsort_bez_krawedzi() {
    std::cout << "\n=== Test topsort bez krawedzi ===" << std::endl;

    // graf bez krawędzi — każda permutacja jest poprawna
    Graph g(4, true);

    std::vector<int> sorted_nodes = topsort_dfs<int, Graph>(g);

    assert((int)sorted_nodes.size() == 4);
    weryfikuj_topsort(g, sorted_nodes);

    std::cout << "Posortowane: ";
    for (int v : sorted_nodes) std::cout << v << " ";
    std::cout << std::endl;

    std::cout << "Test PASSED" << std::endl;
}

void test_topsort_cykl() {
    std::cout << "\n=== Test wykrywania cyklu ===" << std::endl;

    // cykl: 0 -> 1 -> 2 -> 0
    Graph g(3, true);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);

    bool wykryto_cykl = false;
    try {
        topsort_dfs<int, Graph>(g);
    } catch (const std::runtime_error& e) {
        wykryto_cykl = true;
        std::cout << "Zlapano wyjatek: " << e.what() << std::endl;
    }

    assert(wykryto_cykl);
    std::cout << "Test PASSED" << std::endl;
}

void zadanie_61() {
    std::cout << "\n=== Zadanie 6.1: topsort dagu n=10 ===" << std::endl;

    // dag z 10 wierzchołków reprezentujący zależności zadań
    // 
    //
    //   0 -> 2 -> 5 -> 8
    //   |    |    ^    |
    //   v    v    |    v
    //   1 -> 3 -> 6 -> 9
    //        |    ^
    //        v    |
    //        4 -> 7
    //
    Graph g(10, true);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 3);
    g.add_edge(2, 5);
    g.add_edge(3, 4);
    g.add_edge(3, 6);
    g.add_edge(4, 7);
    g.add_edge(5, 8);
    g.add_edge(6, 5);
    g.add_edge(6, 9);
    g.add_edge(7, 6);
    g.add_edge(8, 9);

    std::cout << "\nDag:" << std::endl;
    g.display();

    std::vector<int> sorted_nodes = topsort_dfs<int, Graph>(g);

    std::cout << "\nSortowanie topologiczne: ";
    for (int v : sorted_nodes) std::cout << v << " ";
    std::cout << std::endl;

    // weryfikacja: dla każdej krawędzi (u,v), u jest przed v
    weryfikuj_topsort(g, sorted_nodes);

    std::cout << "\nZadanie 6.1 PASSED" << std::endl;
}

int main() {
    test_topsort_maly();
    test_topsort_sciezka();
    test_topsort_bez_krawedzi();
    test_topsort_cykl();
    zadanie_61();

    std::cout << "\n=== WSZYSTKIE TESTY PASSED ===" << std::endl;
    return 0;
}

// main.cpp - zadanie 5.1: BFS na grafie spójnym n=10

#include "graph.hpp"
#include "bfs.hpp"
#include <cassert>
#include <iostream>

void test_bfs_maly() {
    std::cout << "=== Test BFS na malym grafie ===" << std::endl;

    //   0 --- 1 --- 2
    //   |           |
    //   3 --- 4 --- 5
    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(0, 3);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    g.add_edge(2, 5);

    BFS<int, Graph> bfs(g);
    bfs.run(0);

    assert(bfs.preorder[0] == 0);
    assert((int)bfs.preorder.size() == 6);
    assert(bfs.distance[0] == 0);
    assert(bfs.distance[1] == 1);
    assert(bfs.distance[3] == 1);
    assert(bfs.distance[2] == 2);
    assert(bfs.distance[4] == 2);
    assert(bfs.distance[5] == 3);
    assert(bfs.parent[0] == -1);
    assert(bfs.parent[1] == 0);
    assert(bfs.parent[3] == 0);

    std::cout << "Test BFS na malym grafie PASSED" << std::endl;
}

void zadanie_51() {
    std::cout << "\n=== Zadanie 5.1: BFS na grafie spojnym n=10 ===" << std::endl;

    // graf spójny, 10 wierzchołków, 13 krawędzi
    //
    //   0 --- 1 --- 2 --- 3
    //   |     |     |     |
    //   4 --- 5 --- 6 --- 7
    //          \         /
    //           8 --- 9
    //
    Graph g(10);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(0, 4);
    g.add_edge(1, 5);
    g.add_edge(2, 6);
    g.add_edge(3, 7);
    g.add_edge(4, 5);
    g.add_edge(5, 6);
    g.add_edge(6, 7);
    g.add_edge(5, 8);
    g.add_edge(8, 9);
    g.add_edge(7, 9);

    std::cout << "\nGraf:" << std::endl;
    g.display();

    BFS<int, Graph> bfs(g);
    bfs.run(0);

    // graf spójny — BFS powinien odwiedzić wszystkie 10 wierzchołków
    assert((int)bfs.preorder.size() == 10);

    std::cout << "\nKolejnosc odkrywania (preorder): ";
    for (int w : bfs.preorder) std::cout << w << " ";
    std::cout << std::endl;

    std::cout << "\nOdleglosci od wierzcholka 0:" << std::endl;
    for (int w = 0; w < 10; w++)
        std::cout << "  d(0," << w << ") = " << bfs.distance[w] << std::endl;

    std::cout << "\nDrzewo BFS (rodzice):" << std::endl;
    for (int w = 0; w < 10; w++) {
        if (bfs.parent[w] == -1)
            std::cout << "  " << w << " <- korzen" << std::endl;
        else
            std::cout << "  " << w << " <- " << bfs.parent[w] << std::endl;
    }

    std::cout << "\nNajkrotsze sciezki od 0:" << std::endl;
    for (int w = 0; w < 10; w++) {
        std::cout << "  0 -> " << w << ": ";
        bfs.print_path(0, w);
        std::cout << " (dl. " << bfs.distance[w] << ")" << std::endl;
    }

    std::cout << "\nZadanie 5.1 PASSED" << std::endl;
}

// graf niespójny — dwie składowe, run() bez argumentu
void test_bfs_niespojny() {
    std::cout << "\n=== Test BFS na grafie niespojnym ===" << std::endl;

    // składowa A: 0 - 1 - 2
    // składowa B: 3 - 4
    // wierzchołek 5 izolowany
    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(3, 4);

    BFS<int, Graph> bfs(g);
    bfs.run(); // bez argumentu — bada cały graf

    // wszystkie 6 wierzchołków odwiedzonych (3 składowe)
    assert((int)bfs.preorder.size() == 6);

    // odległości wewnątrz składowej A
    assert(bfs.distance[0] == 0);
    assert(bfs.distance[1] == 1);
    assert(bfs.distance[2] == 2);

    // składowa B — osobny korzeń
    assert(bfs.distance[3] == 0);
    assert(bfs.distance[4] == 1);

    // wierzchołek izolowany — sam jest swoją składową
    assert(bfs.distance[5] == 0);
    assert(bfs.parent[5] == -1);

    std::cout << "Preorder: ";
    for (int w : bfs.preorder) std::cout << w << " ";
    std::cout << std::endl;

    std::cout << "Test BFS na grafie niespojnym PASSED" << std::endl;
}

// graf skierowany — krawędzie działają tylko w jedną stronę
void test_bfs_skierowany() {
    std::cout << "\n=== Test BFS na grafie skierowanym ===" << std::endl;

    // 0 -> 1 -> 2
    // |         ^
    // +-> 3 ->--+
    Graph g(4, true);
    g.add_edge(0, 1);
    g.add_edge(0, 3);
    g.add_edge(1, 2);
    g.add_edge(3, 2);

    BFS<int, Graph> bfs(g);
    bfs.run(0);

    assert((int)bfs.preorder.size() == 4);
    assert(bfs.distance[0] == 0);
    assert(bfs.distance[1] == 1);
    assert(bfs.distance[3] == 1);
    assert(bfs.distance[2] == 2); // 0->1->2 lub 0->3->2

    // wsteczna krawędź nie istnieje — z 2 nie da się dojść do 0
    BFS<int, Graph> bfs2(g);
    bfs2.run(2);
    assert((int)bfs2.preorder.size() == 1); // z 2 nie ma żadnych krawędzi wychodzących
    assert(bfs2.distance[0] == -1); // nieosiągalny

    std::cout << "Test BFS na grafie skierowanym PASSED" << std::endl;
}

// graf — pojedynczy wierzchołek bez krawędzi
void test_bfs_jeden_wierzcholek() {
    std::cout << "\n=== Test BFS na jednym wierzcholku ===" << std::endl;

    Graph g(1);

    BFS<int, Graph> bfs(g);
    bfs.run(0);

    assert((int)bfs.preorder.size() == 1);
    assert(bfs.preorder[0] == 0);
    assert(bfs.distance[0] == 0);
    assert(bfs.parent[0] == -1);

    std::cout << "Test BFS na jednym wierzcholku PASSED" << std::endl;
}

// ścieżka liniowa — odległości rosną o 1
void test_bfs_sciezka() {
    std::cout << "\n=== Test BFS na sciezce liniowej ===" << std::endl;

    // 0 - 1 - 2 - 3 - 4
    Graph g(5);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 4);

    BFS<int, Graph> bfs(g);
    bfs.run(0);

    for (int w = 0; w < 5; w++) {
        assert(bfs.distance[w] == w); // d(0,w) = w
        if (w > 0)
            assert(bfs.parent[w] == w - 1); // rodzic w = w-1
    }

    std::cout << "Sciezka 0 -> 4: ";
    bfs.print_path(0, 4);
    std::cout << std::endl;

    std::cout << "Test BFS na sciezce liniowej PASSED" << std::endl;
}

// cykl — BFS nie wchodzi w nieskończoną pętlę
void test_bfs_cykl() {
    std::cout << "\n=== Test BFS na cyklu ===" << std::endl;

    // 0 - 1 - 2 - 3 - 0 (cykl C4)
    Graph g(4);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 0);

    BFS<int, Graph> bfs(g);
    bfs.run(0);

    assert((int)bfs.preorder.size() == 4); // nie zapętlił się
    assert(bfs.distance[0] == 0);
    assert(bfs.distance[1] == 1);
    assert(bfs.distance[2] == 2);
    assert(bfs.distance[3] == 1); // 0-3 bezpośrednio, nie 0-1-2-3

    std::cout << "Test BFS na cyklu PASSED" << std::endl;
}

int main() {
    test_bfs_maly();
    test_bfs_niespojny();
    test_bfs_skierowany();
    test_bfs_jeden_wierzcholek();
    test_bfs_sciezka();
    test_bfs_cykl();
    zadanie_51();

    std::cout << "\n=== WSZYSTKIE TESTY PASSED ===" << std::endl;
    return 0;
}
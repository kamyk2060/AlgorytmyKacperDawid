// graph.hpp - ADT GRAPH na bazie macierzy sąsiedztwa (graf bez wag)

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "basegraph.hpp"
#include "iterator.hpp"
#include <vector>
#include <cassert>

class Graph : public BaseGraph<int> {
    bool directed; // czy graf jest skierowany
    std::vector< std::vector<int> > adj_matrix; // macierz sąsiedztwa
public:
    // Alokacja macierzy kwadratowej nxn, wypełnionej zerami.
    Graph(int n, bool directed = false) : directed(directed) {
        adj_matrix = std::vector< std::vector<int> >(n, std::vector<int>(n, 0));
    }

    ~Graph() { clear(); }

    // czy graf jest skierowany, O(1)
    bool is_directed() const override { return directed; }

    // liczba wierzchołków grafu, O(1)
    int v() const override { return adj_matrix.size(); }

    // liczba krawędzi grafu, O(n^2)
    int e() const override {
        int counter = 0;
        for (int u = 0; u < v(); u++)
            for (int w = 0; w < v(); w++)
                counter += adj_matrix[u][w];
        return (directed ? counter : counter / 2);
    }

    // liczba sąsiadów wierzchołka u (tylko graf nieskierowany), O(n)
    int degree(int u) override {
        assert(!directed);
        int counter = 0;
        for (int w = 0; w < v(); w++)
            counter += adj_matrix[u][w];
        return counter;
    }

    // liczba krawędzi wchodzących do u, O(n)
    int indegree(int u) override {
        int counter = 0;
        for (int w = 0; w < v(); w++)
            counter += adj_matrix[w][u]; // kolumna u
        return counter;
    }

    // liczba krawędzi wychodzących z u, O(n)
    int outdegree(int u) override {
        int counter = 0;
        for (int w = 0; w < v(); w++)
            counter += adj_matrix[u][w]; // wiersz u
        return counter;
    }

    // dodanie wierzchołka (w macierzy sąsiedztwa wierzchołki już istnieją)
    void add_node(int u) override {
        assert(0 <= u && u < v());
    }

    // usunięcie wierzchołka - usuwamy krawędzie O(n)
    void del_node(int u) override {
        for (int w = 0; w < v(); w++) {
            adj_matrix[u][w] = 0;
            adj_matrix[w][u] = 0;
        }
    }

    // sprawdzenie czy wierzchołek istnieje, O(1)
    bool has_node(int u) const override {
        return (0 <= u && u < v());
    }

    // wstawienie krawędzi (u,w), O(1)
    void add_edge(int u, int w, float weight = 1.0) override {
        (void)weight; // graf bez wag, ignorujemy wagę
        assert(0 <= u && u < v());
        assert(0 <= w && w < v());
        adj_matrix[u][w] = 1;
        if (!directed)
            adj_matrix[w][u] = 1;
    }

    // wstawienie krawędzi z obiektu Edge, O(1)
    void add_edge(Edge<int> edge) override {
        add_edge(edge.source, edge.target, edge.weight);
    }

    // usunięcie krawędzi (u,w), O(1)
    void del_edge(int u, int w) override {
        assert(0 <= u && u < v());
        assert(0 <= w && w < v());
        adj_matrix[u][w] = 0;
        if (!directed)
            adj_matrix[w][u] = 0;
    }

    // usunięcie krawędzi z obiektu Edge, O(1)
    void del_edge(Edge<int> edge) override {
        del_edge(edge.source, edge.target);
    }

    // test istnienia krawędzi, O(1)
    bool has_edge(int u, int w) const override {
        return adj_matrix[u][w] == 1;
    }

    // test istnienia krawędzi z obiektu Edge, O(1)
    bool has_edge(Edge<int> edge) const override {
        return adj_matrix[edge.source][edge.target] == 1;
    }

    // waga krawędzi (0 lub 1 dla grafu bez wag), O(1)
    float weight(int u, int w) const override {
        return adj_matrix[u][w];
    }

    // waga krawędzi z obiektu Edge, O(1)
    float weight(Edge<int> edge) const override {
        return adj_matrix[edge.source][edge.target];
    }

    // usunięcie wszystkich krawędzi, O(n^2)
    void clear() override {
        for (int u = 0; u < v(); u++)
            for (int w = 0; w < v(); w++)
                adj_matrix[u][w] = 0;
    }

    // wypisanie macierzy sąsiedztwa, O(n^2)
    void display() const override {
        std::cout << (directed ? "Graf skierowany" : "Graf nieskierowany");
        std::cout << ", wierzcholki: " << v()
                  << ", krawedzie: " << e() << std::endl;
        std::cout << "Macierz sasiedztwa:" << std::endl;
        for (int u = 0; u < v(); u++) {
            for (int w = 0; w < v(); w++)
                std::cout << adj_matrix[u][w] << " ";
            std::cout << std::endl;
        }
    }

    // dostęp do macierzy dla iteratorów (friend nie jest potrzebny)
    int get_adj(int u, int w) const { return adj_matrix[u][w]; }

    // --- iteratory ---
    NodeIterator node_begin() { return NodeIterator(this, 0); }
    NodeIterator node_end() { return NodeIterator(this, v()); }

    EdgeIterator edge_begin() { return EdgeIterator(this); }
    EdgeIterator edge_end() { return EdgeIterator(this, v(), 0); }

    AdjacentIterator adj_begin(int r) { return AdjacentIterator(this, r); }
    AdjacentIterator adj_end(int r) { return AdjacentIterator(this, r, v()); }
};

// --- definicje metod iteratorów (potrzebują pełnej definicji Graph) ---

// EdgeIterator - szuka następnej krawędzi od bieżącej pozycji
inline void EdgeIterator::find_next() {
    int n = graph->v();
    while (row < n) {
        while (col < n) {
            if (graph->get_adj(row, col) == 1) {
                // dla grafu nieskierowanego bierzemy krawędź tylko raz (row <= col)
                if (graph->is_directed() || row <= col)
                    return;
            }
            ++col;
        }
        ++row;
        col = 0;
    }
    // koniec - ustawiamy na pozycję end
    row = n;
    col = 0;
}

// EdgeIterator - konstruktor begin
inline EdgeIterator::EdgeIterator(const Graph* g)
    : graph(g), row(0), col(0) {
    find_next(); // szukamy pierwszej krawędzi
}

// EdgeIterator - konstruktor end
inline EdgeIterator::EdgeIterator(const Graph* g, int r, int c)
    : graph(g), row(r), col(c) {}

// EdgeIterator - operator dereferencji
inline Edge<int> EdgeIterator::operator*() const {
    return Edge<int>(row, col, graph->get_adj(row, col));
}

// AdjacentIterator - szuka następnego sąsiada
inline void AdjacentIterator::find_next() {
    int n = graph->v();
    while (pos < n) {
        if (graph->get_adj(src, pos) == 1)
            return;
        ++pos;
    }
}

// AdjacentIterator - konstruktor begin
inline AdjacentIterator::AdjacentIterator(const Graph* g, int r)
    : graph(g), src(r), pos(0) {
    find_next(); // szukamy pierwszego sąsiada
}

// AdjacentIterator - konstruktor end
inline AdjacentIterator::AdjacentIterator(const Graph* g, int r, int p)
    : graph(g), src(r), pos(p) {}

#endif // GRAPH_HPP
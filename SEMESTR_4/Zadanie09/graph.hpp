// graph.hpp - ADT GRAPH na bazie macierzy sasiedztwa (graf wazony)

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "basegraph.hpp"
#include "iterator.hpp"
#include <vector>
#include <cassert>

class Graph : public BaseGraph<int> {
    bool directed; // czy graf jest skierowany
    // macierz sasiedztwa: adj_matrix[u][v] = waga krawedzi (u,v)
    // 0.0 oznacza brak krawedzi
    std::vector< std::vector<float> > adj_matrix;
public:
    // konstruktor: macierz n x n wypelniona zerami
    Graph(int n, bool directed = false) : directed(directed) {
        adj_matrix = std::vector< std::vector<float> >(n, std::vector<float>(n, 0.0f));
    }

    ~Graph() { clear(); }

    bool is_directed() const override { return directed; }
    int v() const override { return adj_matrix.size(); }

    // liczba krawedzi - skanujemy cala macierz, O(n^2)
    int e() const override {
        int counter = 0;
        for (int u = 0; u < v(); u++)
            for (int w = 0; w < v(); w++)
                if (adj_matrix[u][w] != 0.0f)
                    counter++;
        return (directed ? counter : counter / 2);
    }

    // stopien (liczba sasiadow) - tylko dla nieskierowanego, O(n)
    int degree(int u) override {
        assert(!directed);
        int counter = 0;
        for (int w = 0; w < v(); w++)
            if (adj_matrix[u][w] != 0.0f)
                counter++;
        return counter;
    }

    // liczba krawedzi wchodzacych do u, O(n) - skanujemy kolumne u
    int indegree(int u) override {
        int counter = 0;
        for (int w = 0; w < v(); w++)
            if (adj_matrix[w][u] != 0.0f)
                counter++;
        return counter;
    }

    // liczba krawedzi wychodzacych z u, O(n) - skanujemy wiersz u
    int outdegree(int u) override {
        int counter = 0;
        for (int w = 0; w < v(); w++)
            if (adj_matrix[u][w] != 0.0f)
                counter++;
        return counter;
    }

    // dodanie wierzcholka (0..n-1 juz istnieja)
    void add_node(int u) override { assert(0 <= u && u < v()); }

    // usuniecie wierzcholka - zerujemy wiersz i kolumne, O(n)
    void del_node(int u) override {
        for (int w = 0; w < v(); w++) {
            adj_matrix[u][w] = 0.0f;
            adj_matrix[w][u] = 0.0f;
        }
    }

    bool has_node(int u) const override {
        return (0 <= u && u < v());
    }

    // dodanie krawedzi z waga, O(1)
    // waga 0 jest zarezerwowana na "brak krawedzi"
    void add_edge(int u, int w, float weight = 1.0) override {
        assert(0 <= u && u < v());
        assert(0 <= w && w < v());
        assert(weight != 0.0f);
        adj_matrix[u][w] = weight;
        if (!directed)
            adj_matrix[w][u] = weight;
    }

    void add_edge(Edge<int> edge) override {
        add_edge(edge.source, edge.target, edge.weight);
    }

    // usuniecie krawedzi - wstawiamy 0, O(1)
    void del_edge(int u, int w) override {
        assert(0 <= u && u < v());
        assert(0 <= w && w < v());
        adj_matrix[u][w] = 0.0f;
        if (!directed)
            adj_matrix[w][u] = 0.0f;
    }

    void del_edge(Edge<int> edge) override {
        del_edge(edge.source, edge.target);
    }

    // test istnienia krawedzi, O(1)
    bool has_edge(int u, int w) const override {
        return adj_matrix[u][w] != 0.0f;
    }

    bool has_edge(Edge<int> edge) const override {
        return has_edge(edge.source, edge.target);
    }

    // waga krawedzi, O(1)
    float weight(int u, int w) const override {
        return adj_matrix[u][w];
    }

    float weight(Edge<int> edge) const override {
        return weight(edge.source, edge.target);
    }

    // usuniecie wszystkich krawedzi (wierzcholki zostaja)
    void clear() override {
        for (int u = 0; u < v(); u++)
            for (int w = 0; w < v(); w++)
                adj_matrix[u][w] = 0.0f;
    }

    // wypisanie macierzy sasiedztwa
    void display() const override {
        std::cout << (directed ? "Graf skierowany" : "Graf nieskierowany");
        std::cout << ", wierzcholki: " << v()
                  << ", krawedzie: " << e() << std::endl;
        std::cout << "Macierz sasiedztwa (wagi):" << std::endl;
        std::cout << "    ";
        for (int w = 0; w < v(); w++)
            std::cout << w << "    ";
        std::cout << std::endl;
        for (int u = 0; u < v(); u++) {
            std::cout << u << " [ ";
            for (int w = 0; w < v(); w++)
                std::cout << adj_matrix[u][w] << "  ";
            std::cout << "]" << std::endl;
        }
    }

    // dostep do macierzy dla iteratorow
    float get_weight(int u, int w) const { return adj_matrix[u][w]; }

    // --- iteratory ---
    NodeIterator node_begin() { return NodeIterator(this, 0); }
    NodeIterator node_end() { return NodeIterator(this, v()); }

    EdgeIterator edge_begin() { return EdgeIterator(this); }
    EdgeIterator edge_end() { return EdgeIterator(this, v(), 0); }

    AdjacentIterator adj_begin(int u) { return AdjacentIterator(this, u); }
    AdjacentIterator adj_end(int u) { return AdjacentIterator(this, u, v()); }
};

// definicje metod iteratorow

// EdgeIterator::find_next() - skanuje macierz szukajac niezerowych komorek
// najpierw przesuwa sie z biezacej pozycji (++col), potem szuka
// dla nieskierowanego: bierze krawedz tylko raz (row <= col)
inline void EdgeIterator::find_next() {
    int n = graph->v();
    ++col;
    while (row < n) {
        while (col < n) {
            if (graph->get_weight(row, col) != 0.0f) {
                if (graph->is_directed() || row <= col)
                    return;
            }
            ++col;
        }
        ++row;
        col = 0;
    }
    // koniec - pozycja end
    row = n;
    col = 0;
}

// EdgeIterator - konstruktor begin
// startujemy z col = -1, find_next() po ++col zacznie od (0, 0)
inline EdgeIterator::EdgeIterator(const Graph* g)
    : graph(g), row(0), col(-1) {
    find_next();
}

// EdgeIterator - konstruktor end
inline EdgeIterator::EdgeIterator(const Graph* g, int r, int c)
    : graph(g), row(r), col(c) {}

// EdgeIterator - operator dereferencji
// zwraca krawedz (row, col, waga)
inline Edge<int> EdgeIterator::operator*() const {
    return Edge<int>(row, col, graph->get_weight(row, col));
}

// AdjacentIterator::find_next() - skanuje wiersz src szukajac niezerowych
// najpierw przesuwa pos, potem pomija zera
inline void AdjacentIterator::find_next() {
    int n = graph->v();
    ++pos;
    while (pos < n && graph->get_weight(src, pos) == 0.0f)
        ++pos;
}

// AdjacentIterator - konstruktor begin
// startujemy z pos = -1, find_next() znajdzie pierwszego sasiada
inline AdjacentIterator::AdjacentIterator(const Graph* g, int r)
    : graph(g), src(r), pos(-1) {
    find_next();
}

// AdjacentIterator - konstruktor end
inline AdjacentIterator::AdjacentIterator(const Graph* g, int r, int p)
    : graph(g), src(r), pos(p) {}

#endif // GRAPH_HPP

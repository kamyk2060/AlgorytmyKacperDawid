// graph.hpp - ADT GRAPH na bazie listy sąsiedztwa (graf bez wag)

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "basegraph.hpp"
#include "iterator.hpp"
#include <vector>
#include <algorithm>
#include <cassert>

class Graph : public BaseGraph<int> {
    bool directed; // czy graf jest skierowany
    std::vector< std::vector<int> > adj_list; // lista sąsiedztwa
public:
    // Powstaje wektor z 'n' pustymi wektorami.
    Graph(int n, bool directed = false) : directed(directed) {
        adj_list = std::vector< std::vector<int> >(n);
    }

    ~Graph() { clear(); }

    // czy graf jest skierowany, O(1)
    bool is_directed() const override { return directed; }

    // liczba wierzchołków grafu, O(1)
    int v() const override { return adj_list.size(); }

    // liczba krawędzi grafu, O(n)
    int e() const override {
        int counter = 0;
        for (const auto& vec : adj_list)
            counter += vec.size();
        return (directed ? counter : counter / 2);
    }

    // stopień wierzchołka (rozmiar jego listy sąsiedztwa), O(1)
    int degree(int u) override { return adj_list[u].size(); }

    // liczba krawędzi wchodzących do u, O(n + m)
    // trzeba przeszukać listy sąsiedztwa WSZYSTKICH wierzchołków
    int indegree(int u) override {
        int counter = 0;
        for (int w = 0; w < v(); w++) {
            for (int sasiad : adj_list[w]) {
                if (sasiad == u)
                    counter++;
            }
        }
        return counter;
    }

    // liczba krawędzi wychodzących z u, O(1)
    int outdegree(int u) override { return adj_list[u].size(); }

    // dodanie wierzchołka (wierzchołki 0..n-1 już istnieją)
    void add_node(int u) override {
        assert(0 <= u && u < v());
    }

    // usunięcie wierzchołka — usuwamy krawędzie incydentne
    // 1) czyścimy listę sąsiedztwa u
    // 2) usuwamy u z list sąsiedztwa wszystkich innych wierzchołków
    void del_node(int u) override {
        adj_list[u].clear(); // usuwamy krawędzie wychodzące z u
        for (int w = 0; w < v(); w++) {
            // usuwamy wszystkie wystąpienia u z listy wierzchołka w
            auto& vec = adj_list[w];
            vec.erase(std::remove(vec.begin(), vec.end(), u), vec.end());
        }
    }

    // sprawdzenie czy wierzchołek istnieje, O(1)
    bool has_node(int u) const override {
        return (0 <= u && u < v());
    }

    // wstawienie krawędzi (u,w), O(n) bo sprawdzamy czy już istnieje
    void add_edge(int u, int w, float weight = 1.0) override {
        (void)weight; // graf bez wag, ignorujemy
        assert(0 <= u && u < v());
        assert(0 <= w && w < v());
        // dodajemy tylko jeśli krawędź jeszcze nie istnieje
        if (!has_edge(u, w)) {
            adj_list[u].push_back(w);
            if (!directed)
                adj_list[w].push_back(u);
        }
    }

    // wstawienie krawędzi z obiektu Edge, O(n)
    void add_edge(Edge<int> edge) override {
        add_edge(edge.source, edge.target, edge.weight);
    }

    // usunięcie krawędzi (u,w), O(n)
    void del_edge(int u, int w) override {
        assert(0 <= u && u < v());
        assert(0 <= w && w < v());
        auto& vec_u = adj_list[u];
        vec_u.erase(std::remove(vec_u.begin(), vec_u.end(), w), vec_u.end());
        if (!directed) {
            auto& vec_w = adj_list[w];
            vec_w.erase(std::remove(vec_w.begin(), vec_w.end(), u), vec_w.end());
        }
    }

    // usunięcie krawędzi z obiektu Edge, O(n)
    void del_edge(Edge<int> edge) override {
        del_edge(edge.source, edge.target);
    }

    // test istnienia krawędzi (u,w), O(deg(u))
    bool has_edge(int u, int w) const override {
        const auto& vec = adj_list[u];
        return std::find(vec.begin(), vec.end(), w) != vec.end();
    }

    // test istnienia krawędzi z obiektu Edge
    bool has_edge(Edge<int> edge) const override {
        return has_edge(edge.source, edge.target);
    }

    // waga krawędzi — 1.0 jeśli istnieje, 0.0 jeśli nie
    float weight(int u, int w) const override {
        return has_edge(u, w) ? 1.0 : 0.0;
    }

    // waga krawędzi z obiektu Edge
    float weight(Edge<int> edge) const override {
        return weight(edge.source, edge.target);
    }

    // usunięcie wszystkich krawędzi (wierzchołki zostają)
    void clear() override {
        for (auto& vec : adj_list)
            vec.clear();
    }

    // wypisanie listy sąsiedztwa
    void display() const override {
        std::cout << (directed ? "Graf skierowany" : "Graf nieskierowany");
        std::cout << ", wierzcholki: " << v()
                  << ", krawedzie: " << e() << std::endl;
        std::cout << "Lista sasiedztwa:" << std::endl;
        for (int u = 0; u < v(); u++) {
            std::cout << u << ": ";
            for (int w : adj_list[u])
                std::cout << w << " ";
            std::cout << std::endl;
        }
    }

    // dostęp do listy sąsiedztwa dla iteratorów
    const std::vector<int>& get_adj_list(int u) const { return adj_list[u]; }

    // --- iteratory ---
    NodeIterator node_begin() { return NodeIterator(this, 0); }
    NodeIterator node_end() { return NodeIterator(this, v()); }

    EdgeIterator edge_begin() { return EdgeIterator(this); }
    EdgeIterator edge_end() { return EdgeIterator(this, v(), 0); }

    AdjacentIterator adj_begin(int u) {
        return AdjacentIterator(this, u, 0);
    }
    AdjacentIterator adj_end(int u) {
        return AdjacentIterator(this, u, adj_list[u].size());
    }
};

// ---------------------------------------------------------------
// definicje metod iteratorów (potrzebują pełnej definicji Graph)
// ---------------------------------------------------------------

// EdgeIterator::find_next() — przesuwa się z bieżącej pozycji
// na NASTĘPNĄ krawędź w liście sąsiedztwa.
// Najpierw robi krok naprzód (++col_idx), potem szuka.
// Dla grafu nieskierowanego: krawędź (u,w) liczymy raz — tylko gdy u <= w.
inline void EdgeIterator::find_next() {
    int n = graph->v();
    ++col_idx; // przesuwamy się z bieżącej pozycji
    while (row < n) {
        const auto& lista = graph->get_adj_list(row);
        int rozmiar = lista.size();
        while (col_idx < rozmiar) {
            int sasiad = lista[col_idx];
            // dla nieskierowanego: bierzemy krawędź tylko raz (row <= sasiad)
            if (graph->is_directed() || row <= sasiad)
                return; // znaleziono następną krawędź
            ++col_idx;
        }
        ++row;
        col_idx = 0;
    }
    // koniec — pozycja end
    row = n;
    col_idx = 0;
}

// EdgeIterator — konstruktor begin
// Startujemy z col_idx = -1, żeby find_next() po ++col_idx zaczął od 0.
inline EdgeIterator::EdgeIterator(const Graph* g)
    : graph(g), row(0), col_idx(-1) {
    find_next(); // szukamy pierwszej krawędzi
}

// EdgeIterator — konstruktor end
inline EdgeIterator::EdgeIterator(const Graph* g, int r, int c)
    : graph(g), row(r), col_idx(c) {}

// EdgeIterator — operator dereferencji
inline Edge<int> EdgeIterator::operator*() const {
    int sasiad = graph->get_adj_list(row)[col_idx];
    return Edge<int>(row, sasiad);
}

// AdjacentIterator — konstruktor
inline AdjacentIterator::AdjacentIterator(const Graph* g, int r, int p)
    : graph(g), src(r), pos(p) {}

// AdjacentIterator — operator dereferencji
inline int AdjacentIterator::operator*() const {
    return graph->get_adj_list(src)[pos];
}

#endif // GRAPH_HPP

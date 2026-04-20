// iterator.hpp - iteratory dla grafu (lista sąsiedztwa)

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "edge.hpp"

// abstrakcyjna klasa bazowa iteratora
template <typename T>
class Iterator {
public:
    Iterator() = default;
    ~Iterator() = default;
    virtual T operator*() const = 0;
};

// deklaracja wyprzedzająca klasy Graph
class Graph;

// ---------------------------------------------------------------
// iterator po wierzchołkach grafu (0, 1, ..., n-1)
// ---------------------------------------------------------------
class NodeIterator : public Iterator<int> {
    const Graph* graph;
    int pos; // bieżący wierzchołek
public:
    NodeIterator(const Graph* g, int p) : graph(g), pos(p) {}

    NodeIterator& operator++() {
        ++pos;
        return *this;
    }

    NodeIterator operator++(int) {
        NodeIterator tmp = *this;
        ++pos;
        return tmp;
    }

    int operator*() const override {
        return pos;
    }

    bool operator==(const NodeIterator& other) const {
        return (graph == other.graph && pos == other.pos);
    }

    bool operator!=(const NodeIterator& other) const {
        return !(*this == other);
    }
};

// ---------------------------------------------------------------
// iterator po krawędziach grafu
// Przechodzi po wierszach listy sąsiedztwa (row),
// a w każdym wierszu po elementach listy (col_idx).
// ---------------------------------------------------------------
class EdgeIterator : public Iterator<Edge<int>> {
    const Graph* graph;
    int row;      // bieżący wierzchołek-źródło
    int col_idx;  // indeks w liście sąsiedztwa wierzchołka row

    void find_next(); // przesuwa się na NASTĘPNĄ krawędź

public:
    EdgeIterator(const Graph* g);                       // begin
    EdgeIterator(const Graph* g, int r, int c);         // end

    EdgeIterator& operator++() {
        find_next();
        return *this;
    }

    EdgeIterator operator++(int) {
        EdgeIterator tmp = *this;
        find_next();
        return tmp;
    }

    Edge<int> operator*() const override;

    bool operator==(const EdgeIterator& other) const {
        return (graph == other.graph && row == other.row
                && col_idx == other.col_idx);
    }

    bool operator!=(const EdgeIterator& other) const {
        return !(*this == other);
    }
};

// ---------------------------------------------------------------
// iterator po sąsiadach wierzchołka
// ---------------------------------------------------------------
class AdjacentIterator : public Iterator<int> {
    const Graph* graph;
    int src;     // wierzchołek, którego sąsiadów iterujemy
    int pos;     // indeks w liście sąsiedztwa wierzchołka src

public:
    AdjacentIterator(const Graph* g, int r, int p);

    AdjacentIterator& operator++() {
        ++pos;
        return *this;
    }

    AdjacentIterator operator++(int) {
        AdjacentIterator tmp = *this;
        ++pos;
        return tmp;
    }

    int operator*() const override;

    bool operator==(const AdjacentIterator& other) const {
        return (graph == other.graph && src == other.src && pos == other.pos);
    }

    bool operator!=(const AdjacentIterator& other) const {
        return !(*this == other);
    }
};

#endif // ITERATOR_HPP

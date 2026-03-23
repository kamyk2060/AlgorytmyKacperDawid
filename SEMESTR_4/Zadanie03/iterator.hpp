// iterator.hpp - iteratory dla grafu

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

// iterator po wierzchołkach grafu
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

// iterator po krawędziach grafu
class EdgeIterator : public Iterator<Edge<int>> {
    const Graph* graph;
    int row; // bieżący wiersz (source)
    int col; // bieżąca kolumna (target)

    void find_next(); // szuka następnej krawędzi w macierzy

public:
    EdgeIterator(const Graph* g);                   // begin
    EdgeIterator(const Graph* g, int r, int c);     // end

    EdgeIterator& operator++() {
        ++col;
        find_next();
        return *this;
    }

    EdgeIterator operator++(int) {
        EdgeIterator tmp = *this;
        ++col;
        find_next();
        return tmp;
    }

    Edge<int> operator*() const override;

    bool operator==(const EdgeIterator& other) const {
        return (graph == other.graph && row == other.row && col == other.col);
    }

    bool operator!=(const EdgeIterator& other) const {
        return !(*this == other);
    }
};

// iterator po sąsiadach wierzchołka
class AdjacentIterator : public Iterator<int> {
    const Graph* graph;
    int src; // wierzchołek, którego sąsiadów iterujemy
    int pos; // bieżący kandydat na sąsiada

    void find_next(); // szuka następnego sąsiada

public:
    AdjacentIterator(const Graph* g, int r);           // begin
    AdjacentIterator(const Graph* g, int r, int p);    // end

    AdjacentIterator& operator++() {
        ++pos;
        find_next();
        return *this;
    }

    AdjacentIterator operator++(int) {
        AdjacentIterator tmp = *this;
        ++pos;
        find_next();
        return tmp;
    }

    int operator*() const override {
        return pos;
    }

    bool operator==(const AdjacentIterator& other) const {
        return (graph == other.graph && src == other.src && pos == other.pos);
    }

    bool operator!=(const AdjacentIterator& other) const {
        return !(*this == other);
    }
};

#endif // ITERATOR_HPP

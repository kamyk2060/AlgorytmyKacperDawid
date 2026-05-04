// iterator.hpp - iteratory dla grafu wazonego na macierzy sasiedztwa

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "edge.hpp"

template <typename T>
class Iterator {
public:
    Iterator() = default;
    ~Iterator() = default;
    virtual T operator*() const = 0;
};

// deklaracja wyprzedzajaca klasy Graph
class Graph;

// iterator po wierzcholkach grafu (0, 1, ..., n-1)
class NodeIterator : public Iterator<int> {
    const Graph* graph;
    int pos; // biezacy wierzcholek
public:
    NodeIterator(const Graph* g, int p) : graph(g), pos(p) {}

    NodeIterator& operator++() { ++pos; return *this; }
    NodeIterator operator++(int) { NodeIterator tmp = *this; ++pos; return tmp; }

    int operator*() const override { return pos; }

    bool operator==(const NodeIterator& other) const {
        return (graph == other.graph && pos == other.pos);
    }
    bool operator!=(const NodeIterator& other) const { return !(*this == other); }
};

// iterator po krawedziach grafu — zwraca Edge<int> z waga
// skanuje macierz szukajac niezerowych komorek
class EdgeIterator : public Iterator<Edge<int>> {
    const Graph* graph;
    int row;     // biezacy wiersz 
    int col;     // biezaca kolumna 

    void find_next(); // przesuwa sie na NASTEPNA krawedz

public:
    EdgeIterator(const Graph* g);                   // begin
    EdgeIterator(const Graph* g, int r, int c);     // end

    EdgeIterator& operator++() { find_next(); return *this; }
    EdgeIterator operator++(int) { EdgeIterator tmp = *this; find_next(); return tmp; }

    Edge<int> operator*() const override;

    bool operator==(const EdgeIterator& other) const {
        return (graph == other.graph && row == other.row && col == other.col);
    }
    bool operator!=(const EdgeIterator& other) const { return !(*this == other); }
};

// iterator po sasiadach wierzcholka — zwraca numer sasiada
class AdjacentIterator : public Iterator<int> {
    const Graph* graph;
    int src;     // wierzcholek, ktorego sasiadow iterujemy
    int pos;     // biezaca kolumna w wierszu src

    void find_next(); // przesuwa pos na NASTEPNEGO sasiada

public:
    AdjacentIterator(const Graph* g, int r);          // begin
    AdjacentIterator(const Graph* g, int r, int p);   // end

    AdjacentIterator& operator++() { find_next(); return *this; }
    AdjacentIterator operator++(int) { AdjacentIterator tmp = *this; find_next(); return tmp; }

    int operator*() const override { return pos; }

    bool operator==(const AdjacentIterator& other) const {
        return (graph == other.graph && src == other.src && pos == other.pos);
    }
    bool operator!=(const AdjacentIterator& other) const { return !(*this == other); }
};

#endif // ITERATOR_HPP

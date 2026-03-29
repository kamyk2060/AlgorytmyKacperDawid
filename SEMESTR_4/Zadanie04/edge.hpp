// edge.hpp - klasa krawędzi grafu

#ifndef EDGE_HPP
#define EDGE_HPP

#include <iostream>

template <typename T>
class Edge {
public:
    T source;
    T target;
    float weight;

    Edge(T s, T t, float w = 1.0) : source(s), target(t), weight(w) {}
    ~Edge() {}

    // konstruktor kopiujący
    Edge(const Edge& edge) : source(edge.source), target(edge.target),
        weight(edge.weight) {}

    // operator negacji bitowej - odwraca krawędź
    Edge operator~() const { return Edge(target, source, weight); }

    // operator przypisania
    Edge& operator=(const Edge& other) {
        if (this != &other) {
            source = other.source;
            target = other.target;
            weight = other.weight;
        }
        return *this;
    }

    // operator wypisywania
    friend std::ostream& operator<<(std::ostream& os, const Edge& edge) {
        os << "(" << edge.source << ", " << edge.target
           << ", " << edge.weight << ")";
        return os;
    }

    // operatory porównania
    bool operator==(const Edge& edge) const {
        return (source == edge.source && target == edge.target
                && weight == edge.weight);
    }

    bool operator!=(const Edge& edge) const {
        return !(*this == edge);
    }
};

#endif // EDGE_HPP

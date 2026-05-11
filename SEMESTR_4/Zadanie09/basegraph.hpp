// basegraph.hpp - abstrakcyjna klasa bazowa grafu

#ifndef BASEGRAPH_HPP
#define BASEGRAPH_HPP

#include "edge.hpp"

template <typename T>
class BaseGraph {
public:
    BaseGraph() = default;
    ~BaseGraph() = default;
    virtual bool is_directed() const = 0;
    virtual int v() const = 0;
    virtual int e() const = 0;
    virtual int degree(T u) = 0;
    virtual int indegree(T u) = 0;
    virtual int outdegree(T u) = 0;
    virtual void add_node(T u) = 0;
    virtual void del_node(T u) = 0;
    virtual bool has_node(T u) const = 0;
    virtual void add_edge(T u, T w, float weight = 1.0) = 0;
    virtual void add_edge(Edge<T> edge) = 0;
    virtual void del_edge(T u, T w) = 0;
    virtual void del_edge(Edge<T> edge) = 0;
    virtual bool has_edge(T u, T w) const = 0;
    virtual bool has_edge(Edge<T> edge) const = 0;
    virtual float weight(T u, T w) const = 0;
    virtual float weight(Edge<T> edge) const = 0;
    virtual void clear() = 0;
    virtual void display() const = 0;
};

#endif // BASEGRAPH_HPP

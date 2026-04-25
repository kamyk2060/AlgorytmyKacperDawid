
#ifndef CONNECTED_HPP
#define CONNECTED_HPP

#include <queue>
#include <unordered_map>
#include <cassert>

template <typename T, typename G>
class ConnectedComponents {
    G& graph;
    std::unordered_map<T, bool> visited;
public:
    // tablica numerów składowych: component[u] = numer składowej wierzchołka u
    std::unordered_map<T, int> component;
    int ncc; // liczba spójnych składowych 

    ConnectedComponents(G& g) : graph(g), ncc(0) {
        // algorytm działa tylko dla grafów nieskierowanych
        assert(!graph.is_directed());

        // inicjalizacja — wszystkie wierzchołki WHITE (nieodwiedzone)
        for (auto n_it = graph.node_begin();
             n_it != graph.node_end();
             ++n_it) {
            visited[*n_it] = false;
        }
    }

    ~ConnectedComponents() = default;

    // procedura główna — dla każdego nieodwiedzonego wierzchołka
    // uruchamia BFS i zwiększa licznik składowych
    void run() {
        for (auto n_it = graph.node_begin();
             n_it != graph.node_end();
             ++n_it) {
            if (!visited[*n_it]) {
                visit(*n_it);
                ncc++;
            }
        }
    }

    // BFS od wierzchołka s - odwiedza całą jego składową
    void visit(T s) {
        visited[s] = true;
        component[s] = ncc; 

        std::queue<T> Q;
        Q.push(s);

        while (!Q.empty()) {
            T u = Q.front();
            Q.pop();

            // iteracja po sąsiadach u
            for (auto a_it = graph.adj_begin(u);
                 a_it != graph.adj_end(u);
                 ++a_it) {
                T w = *a_it;
                if (!visited[w]) {
                    visited[w] = true;
                    component[w] = ncc; 
                    Q.push(w);
                }
            }
        }
    }
};

#endif // CONNECTED_HPP

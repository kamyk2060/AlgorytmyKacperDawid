
#ifndef TOPSORT_HPP
#define TOPSORT_HPP

#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>

// kolory wierzchołków (zgodnie z Cormenem)
enum Color { WHITE, GREY, BLACK };

// DFSVisit z wykrywaniem krawędzi wstecznej (cyklu)
// wierzchołek u -> L w postorder (dodajemy po zbadaniu wszystkich potomków)
template <typename T, typename G>
void dfs_visit_topsort(G& graph, T u,
                       std::unordered_map<T, Color>& color,
                       std::vector<T>& L) {
    color[u] = GREY;

    // iteracja po sąsiadach u
    for (auto a_it = graph.adj_begin(u); a_it != graph.adj_end(u); ++a_it) {
        T v = *a_it;
        if (color[v] == WHITE) {
            dfs_visit_topsort(graph, v, color, L);
        } else if (color[v] == GREY) {
            // krawędź wsteczna -> graf NIE jest dagiem (ma cykl)
            throw std::runtime_error("Graf ma cykl - nie jest dagiem");
        }
    }

    color[u] = BLACK;
    L.push_back(u); // post_action(u): L.append(u)
}

// algorytm Tarjana sortowania topologicznego
// działa tylko dla dagów (grafów skierowanych acyklicznych)
// zwraca wektor wierzchołków w porządku topologicznym
// rzuca std::runtime_error jeśli graf ma cykl
template <typename T, typename G>
std::vector<T> topsort_dfs(G& graph) {
    std::unordered_map<T, Color> color;
    std::vector<T> L; // lista wierzchołków w kolejności postorder

    // inicjalizacja — wszystkie wierzchołki WHITE
    for (auto n_it = graph.node_begin(); n_it != graph.node_end(); ++n_it) {
        color[*n_it] = WHITE;
    }

    // DFS z każdego nieodwiedzonego wierzchołka
    for (auto n_it = graph.node_begin(); n_it != graph.node_end(); ++n_it) {
        if (color[*n_it] == WHITE) {
            dfs_visit_topsort(graph, *n_it, color, L);
        }
    }

    // odwracamy L — postorder odwrócony to sortowanie topologiczne
    std::reverse(L.begin(), L.end());

    return L;
}

#endif // TOPSORT_HPP

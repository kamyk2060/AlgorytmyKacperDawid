
#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <unordered_map>
#include <limits>
#include <iostream>

template <typename T, typename G>
class Dijkstra {
    G& graph;
public:
    std::unordered_map<T, T> parent;       // drzewo najkrotszych sciezek
    std::unordered_map<T, float> distance; // odleglosc od zrodla
    std::unordered_map<T, bool> visited;   // zbior S - wierzcholki przetworzone

    static constexpr float INF = std::numeric_limits<float>::infinity();
    static constexpr T NONE = T(-1);

    // Krok 1 
    Dijkstra(G& g) : graph(g) {
        for (auto n_it = graph.node_begin();
             n_it != graph.node_end();
             ++n_it) {
            distance[*n_it] = INF;
            parent[*n_it] = NONE;
            visited[*n_it] = false;
        }
    }

    ~Dijkstra() = default;

    // uruchomienie algorytmu Dijkstry od wierzcholka s
    void run(T s) {
        distance[s] = 0;
        parent[s] = s; 

        int n = graph.v();

        // Krok 2 
        // wykonujemy n iteracji - w kazdej przetwarzamy jeden wierzcholek
        for (int i = 0; i < n; i++) {
            // znajdujemy wierzcholek u z najmniejszym distance[u] 
            T u = NONE;
            float min_dist = INF;
            for (auto n_it = graph.node_begin();
                 n_it != graph.node_end();
                 ++n_it) {
                T v = *n_it;
                if (!visited[v] && distance[v] < min_dist) {
                    min_dist = distance[v];
                    u = v;
                }
            }

            // jesli nie ma osiagalnych - koniec
            if (u == NONE) break;

            // przetwarzamy u (dodajemy do zbioru S)
            visited[u] = true;

            // relaksacja krawedzi wychodzacych z u
            for (auto a_it = graph.adj_begin(u);
                 a_it != graph.adj_end(u);
                 ++a_it) {
                T w = *a_it;
                float waga = graph.weight(u, w);
                float alt = distance[u] + waga;

                if (alt < distance[w]) {
                    distance[w] = alt;
                    parent[w] = u;
                }
            }
        }
    }

    // wypisanie najkrotszej sciezki ze zrodla s do t (rekurencyjnie)
    void print_path(T s, T t) const {
        if (distance.at(t) == INF) {
            std::cout << "brak sciezki z " << s << " do " << t;
            return;
        }
        if (s == t) {
            std::cout << s;
        } else {
            print_path(s, parent.at(t));
            std::cout << " -> " << t;
        }
    }
};

#endif // DIJKSTRA_HPP
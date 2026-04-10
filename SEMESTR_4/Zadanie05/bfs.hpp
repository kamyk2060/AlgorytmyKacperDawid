// bfs.hpp - przeszukiwanie wszerz (Breadth-First Search)

#ifndef BFS_HPP
#define BFS_HPP

#include <vector>
#include <queue>
#include <unordered_map>

template <typename T, typename G> // typ wierzchołka, typ grafu
class BFS {
    G& graph;
    std::unordered_map<T, bool> visited; // odwiedzony
public:
    std::vector<T> preorder;   // kolejność odkrywania 
    std::vector<T> postorder;  // kolejność przetwarzania 
    std::unordered_map<T, T> parent;     // drzewo BFS (rodzic każdego wierzchołka)
    std::unordered_map<T, int> distance; // odległość od źródła (w przeskokach)

    BFS(G& g) : graph(g) {
        for (auto n_it = graph.node_begin(); n_it != graph.node_end(); ++n_it) {
            visited[*n_it] = false;
            distance[*n_it] = -1; // -1 oznacza nieskończoność
            parent[*n_it] = -1;   // -1 oznacza brak rodzica
        }
    }

    ~BFS() = default;

    // uruchomienie BFS
    // jeśli podano wierzchołek startowy — badamy jedną składową spójną
    // jeśli nie — badamy cały graf (wszystkie składowe)
    void run(T u = T()) {
        if (u != T()) {
            visit(u);
        } else {
            for (auto n_it = graph.node_begin();
                 n_it != graph.node_end();
                 ++n_it) {
                if (!visited[*n_it])
                    visit(*n_it);
            }
        }
    }

    // BFSVisit — przeszukiwanie wszerz od wierzchołka s
    void visit(T s) {
        visited[s] = true;
        parent[s] = -1;    // korzeń nie ma rodzica
        distance[s] = 0;
        preorder.push_back(s); // pre_action(s)

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
                    preorder.push_back(w);         // pre_action(w)
                    parent[w] = u;
                    distance[w] = distance[u] + 1;
                    Q.push(w);
                }
            }
            postorder.push_back(u); // post_action(u)
        }
    }

    // wypisanie najkrótszej ścieżki z s do t (rekurencyjnie)
    void print_path(T s, T t) const {
        if (s == t) {
            std::cout << s;
        } else if (parent.at(t) == -1) {
            std::cout << "brak sciezki";
        } else {
            print_path(s, parent.at(t));
            std::cout << " -> " << t;
        }
    }
};

#endif // BFS_HPP

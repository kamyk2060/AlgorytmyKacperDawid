
#ifndef TRANSITIVE_HPP
#define TRANSITIVE_HPP

#include <vector>
#include <iostream>

template <typename G>
class TransitiveClosure {
    G& graph;
public:
    // T[i][j] = true jesli istnieje sciezka z i do j
    std::vector< std::vector<bool> > T;

    TransitiveClosure(G& g) : graph(g) {}

    ~TransitiveClosure() = default;

    // Algorytm Floyda-Warshalla z operacjami logicznymi
    // Idea: T[i][j]^(k) = true jesli istnieje sciezka z i do j,
    //       ktorej wewnetrzne wierzcholki naleza do {0, 1, ..., k}
    void run() {
        int n = graph.v();

        // T^(0): macierz poczatkowa
        // T[i][j] = true gdy i == j lub istnieje krawedz (i,j)
        T = std::vector< std::vector<bool> >(n, std::vector<bool>(n, false));
        for (int i = 0; i < n; i++) {
            T[i][i] = true; // do siebie zawsze istnieje sciezka (dlugosci 0)
            for (auto a_it = graph.adj_begin(i);
                 a_it != graph.adj_end(i);
                 ++a_it) {
                int j = *a_it;
                T[i][j] = true;
            }
        }

        // glowna petla - dla kazdego dopuszczalnego wierzcholka posredniego k
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    T[i][j] = T[i][j] || (T[i][k] && T[k][j]);
                }
            }
        }
    }

    // wypisanie macierzy domkniecia przechodniego
    void wypisz() const {
        int n = T.size();
        std::cout << "Macierz domkniecia przechodniego T[i][j]:" << std::endl;
        std::cout << "      ";
        for (int j = 0; j < n; j++)
            std::cout << j << "  ";
        std::cout << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "  " << i << " [ ";
            for (int j = 0; j < n; j++)
                std::cout << (T[i][j] ? "1" : ".") << "  ";
            std::cout << "]" << std::endl;
        }
    }

    // wypisanie par (i,j) dla ktorych istnieje sciezka z i do j (i != j)
    void wypisz_pary_sciezek() const {
        int n = T.size();
        std::cout << "Pary (i,j) z istniejaca sciezka z i do j:" << std::endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && T[i][j]) {
                    std::cout << "  " << i << " ~> " << j << std::endl;
                }
            }
        }
    }
};

#endif // TRANSITIVE_HPP

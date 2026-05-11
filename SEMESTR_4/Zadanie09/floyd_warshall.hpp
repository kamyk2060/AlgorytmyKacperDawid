
#ifndef FLOYD_WARSHALL_HPP
#define FLOYD_WARSHALL_HPP

#include <vector>
#include <limits>
#include <stdexcept>
#include <iostream>

template <typename G>
class FloydWarshall {
    G& graph;
public:
    // Distance[i][j] = najkrotsza odleglosc z i do j
    std::vector< std::vector<float> > Distance;

    // INF jako funkcja statyczna
    static float inf() { return std::numeric_limits<float>::infinity(); }

    FloydWarshall(G& g) : graph(g) {}

    ~FloydWarshall() = default;

    // budowa macierzy wag z grafu (poczatkowa macierz D)
    // D[i][j] = 0    dla i == j
    // D[i][j] = w    dla krawedzi (i,j) z waga w
    // D[i][j] = INF  gdy brak krawedzi
    std::vector< std::vector<float> > zbuduj_weight() {
        int n = graph.v();
        std::vector< std::vector<float> > D(n, std::vector<float>(n, inf()));
        for (int i = 0; i < n; i++) {
            D[i][i] = 0;
            for (auto a_it = graph.adj_begin(i);
                 a_it != graph.adj_end(i);
                 ++a_it) {
                int j = *a_it;
                D[i][j] = graph.weight(i, j);
            }
        }
        return D;
    }

    // Algorytm Floyda-Warshalla
    // D[i][j]^(k) = najkrotsza sciezka z i do j, ktorej wszystkie
    // Rekurencja: D[i][j]^(k) = min{ D[i][j]^(k-1), D[i][k]^(k-1) + D[k][j]^(k-1) }
    void run() {
        int n = graph.v();

        // poczatkowa macierz D = macierz wag
        std::vector< std::vector<float> > D = zbuduj_weight();

        // glowna petla algorytmu - wewnetrzny wierzcholek k
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    // unikamy INF + cokolwiek (zeby nie bylo NaN)
                    if (D[i][k] != inf() && D[k][j] != inf()) {
                        float przez_k = D[i][k] + D[k][j];
                        if (przez_k < D[i][j]) {
                            D[i][j] = przez_k;
                        }
                    }
                }
            }
        }

        // sprawdzenie cykli o ujemnej wadze
        for (int i = 0; i < n; i++) {
            if (D[i][i] < 0) {
                throw std::runtime_error("Wykryto cykl o ujemnej wadze!");
            }
        }

        Distance = D;
    }

    // wypisanie macierzy odleglosci
    void wypisz_dystanse() const {
        int n = Distance.size();
        std::cout << "Macierz najkrotszych odleglosci D[i][j]:" << std::endl;
        std::cout << "      ";
        for (int j = 0; j < n; j++)
            std::cout << j << "    ";
        std::cout << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "  " << i << " [ ";
            for (int j = 0; j < n; j++) {
                if (Distance[i][j] == inf())
                    std::cout << "INF  ";
                else
                    std::cout << Distance[i][j] << "    ";
            }
            std::cout << "]" << std::endl;
        }
    }
};

#endif 

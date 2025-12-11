#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void BubbleSort(std::vector<T> &arr, int first, int last) {
    bool swapped;
    for (int i = first; i < last - 1; i++) {
        swapped = false;
        for (int j = first; j < last - (i - first) - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // Jeśli w danej iteracji nie było żadnej zamiany, tablica jest już posortowana
        if (!swapped) {
            break;
        }
    }
}

int main() {
    std::vector<int> x {64, 23, 87, 12, 45, 91, 3, 78, 56, 34, 29, 67, 41, 5, 88, 19, 72, 95, 11, 50};    
    std::vector<double> y {6.4, 2.3, 8.7, 1.2, 4.5, 9.1, 0.3, 7.8, 5.6, 3.4, 2.9, 6.7, 4.1, 0.5, 8.8, 1.9, 7.2, 9.5, 1.1, 5.0};  
    
    // BubbleSort test
    std::vector<int> x_bubble = x;
    std::vector<double> y_bubble = y;
    
    BubbleSort(x_bubble, 0, x_bubble.size());
    BubbleSort(y_bubble, 0, y_bubble.size());

    std::cout << "BubbleSort int > ";
    for (int i : x_bubble) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    std::cout << "BubbleSort double > ";
    for (double i : y_bubble) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Test uporządkowania
    bool is_x_sorted = std::is_sorted(x_bubble.begin(), x_bubble.end());
    bool is_y_sorted = std::is_sorted(y_bubble.begin(), y_bubble.end());
    
    std::cout << "Vector x is sorted: " << (is_x_sorted ? "YES" : "NO") << std::endl;
    std::cout << "Vector y is sorted: " << (is_y_sorted ? "YES" : "NO") << std::endl;
    
    return 0;
}
#include <iostream>
#include <vector>


template<typename T>
void BubbleSort(int first, int last, std::vector<T> &x) {
    T temp {};
    for (int i = first; i < last; i++) {
        for (int j = i + 1; j < last; j++) {
            if (x[i] > x[j]) {
                temp = x[j];
                x[j] = x[i];
                x[i] = temp;
            }
        }
    }
}



int main() {
    std::vector<int> x {64, 23, 87, 12, 45, 91, 3, 78, 56, 34, 29, 67, 41, 5, 88, 19, 72, 95, 11, 50};    
    std::vector<double> y {6.4, 2.3, 8.7, 1.2, 4.5, 9.1, 0.3, 7.8, 5.6, 3.4, 2.9, 6.7, 4.1, 0.5, 8.8, 1.9, 7.2, 9.5, 1.1, 5.0};  
    
    // BubbleSort test
    std::vector<int> x_bubble = x;
    std::vector<double> y_bubble = y;
    
    BubbleSort(0, x_bubble.size(), x_bubble);
    BubbleSort(0, y_bubble.size(), y_bubble);

    std::cout << "BubbleSort int > ";
    for (int i : x_bubble) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "BubbleSort double > ";
    for (double i : y_bubble) {
        std::cout << i << " ";
    }
    
    return 0;
}
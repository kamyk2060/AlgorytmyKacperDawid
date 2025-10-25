#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void Merge(std::vector<T> &LeftArray, std::vector<T> &RightArray, std::vector<T> &x, int start);

template<typename T>
void MergeSort(int first, int last, std::vector<T> &x) {
    int length = last - first;

    if (length <= 1) {
        return;
    }

    int middle = first + length / 2;  
    std::vector<T> LeftArray(middle - first);
    std::vector<T> RightArray(last - middle);

    // Kopiowanie lewej części
    for (int i = 0; i < int(LeftArray.size()); i++) {
        LeftArray[i] = x[first + i];
    }
    
    // Kopiowanie prawej części
    for (int i = 0; i < int(RightArray.size()); i++) {
        RightArray[i] = x[middle + i];
    }
    
    // REKURENCJA - zachowanie spójności interfejsu
    MergeSort(0, LeftArray.size(), LeftArray);
    MergeSort(0, RightArray.size(), RightArray);
    Merge(LeftArray, RightArray, x, first);
}

template<typename T>
void Merge(std::vector<T> &LeftArray, std::vector<T> &RightArray, std::vector<T> &x, int start) {
    int LeftSize = LeftArray.size(); 
    int RightSize = RightArray.size(); 
    int i = start;
    int l = 0;
    int r = 0;

    while (l < LeftSize && r < RightSize) {
        if (LeftArray[l] <= RightArray[r]) {  
            x[i] = LeftArray[l];
            i++;
            l++;
        } else {
            x[i] = RightArray[r];
            i++;
            r++;
        }
    }

    while (l < LeftSize) {
        x[i] = LeftArray[l];
        i++;
        l++;
    }
    while (r < RightSize) {
        x[i] = RightArray[r];
        i++;
        r++;
    }
}

int main() {
    // MergeSort test
    std::vector<int> x_merge = {5, -2, 64, 23, 87, 12, 45, 91, 3, 78, 56, 34, 29, 67, 41, 5, 88, 19, 72, 95, 11, 50};    
    std::vector<double> y_merge = {6.4, 2.3, 8.7, 1.2, 4.5, 9.1, 0.3, 7.8, 5.6, 3.4, 2.9, 6.7, 4.1, 0.5, 8.8, 1.9, 7.2, 9.5, 1.1, 5.0};  

    // Test 1: Sortowanie całych tablic
    std::vector<int> x_test1 = x_merge;  
    std::vector<double> y_test1 = y_merge;  

    MergeSort(0, x_test1.size(), x_test1);
    MergeSort(0, y_test1.size(), y_test1);

    std::cout << "MergeSort int (cala tablica) > ";
    for (int i : x_test1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    std::cout << "MergeSort double (cala tablica) > ";
    for (double i : y_test1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Test 2: Sortowanie częściowe
    std::vector<int> x_test2 = x_merge;
    MergeSort(3, 8, x_test2);  // Sortowanie fragmentu od indeksu 3 do 8

    std::cout << "MergeSort int (indeksy 3-8) > ";
    for (int i : x_test2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Test uporządkowania
    bool is_x_sorted = std::is_sorted(x_test1.begin(), x_test1.end());
    bool is_y_sorted = std::is_sorted(y_test1.begin(), y_test1.end());
    bool is_x_partial_sorted = std::is_sorted(x_test2.begin() + 3, x_test2.begin() + 8);

    std::cout << "Vector x sorted: " << (is_x_sorted ? "YES" : "NO") << std::endl;
    std::cout << "Vector y sorted: " << (is_y_sorted ? "YES" : "NO") << std::endl;
    std::cout << "Vector x (partial 3-8) sorted: " << (is_x_partial_sorted ? "YES" : "NO") << std::endl;

    return 0;
}
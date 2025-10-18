#include <iostream>
#include <vector>

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
        if (LeftArray[l] < RightArray[r]) {
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

    std::vector<int> x_merge_test = x_merge;  
    std::vector<double> y_merge_test = y_merge;  

    MergeSort(3, x_merge_test.size(), x_merge_test);
    MergeSort(0, y_merge_test.size(), y_merge_test);

    std::cout << "MergeSort int (od indeksu 3) > ";
    for (int i : x_merge_test) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "MergeSort double > ";
    for (double i : y_merge_test) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
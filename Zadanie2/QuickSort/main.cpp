#include <iostream>
#include <vector>

int Partition(std::vector<int> &arr, int start, int end) {
    int pivot = arr[end];
    int i = start - 1;

    for (int j = start; j <= end - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    i++;
    int temp = arr[i];
    arr[i] = arr[end];
    arr[end] = temp;

    return i;
}

void QuickSort(std::vector<int> &arr, int start, int end) {
    if (end <= start) {  
        return;
    }

    int pivot = Partition(arr, start, end);
    QuickSort(arr, start, pivot - 1);
    QuickSort(arr, pivot + 1, end);
}

int main(int argc, char const *argv[])
{
    std::vector<int> arr{2, 8, 9, 10, 4, 7, 675, 54, 6, 2, 4};

    QuickSort(arr, 0, arr.size() - 1);  

    for (auto i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
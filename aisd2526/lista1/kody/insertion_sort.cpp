#include <vector>
#include <algorithm>
using namespace std;

struct Counter { int comparisons = 0; int assignments = 0; };

void insertionSort(vector<int>& arr, Counter& c) {
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i]; c.assignments++;
        int j = i - 1;
        while (j >= 0 && arr[j] > key) { c.comparisons++; arr[j+1] = arr[j]; c.assignments++; j--; }
        if(j>=0) c.comparisons++;
        arr[j+1] = key; c.assignments++;
    }
}

// zliczamy wszystkie porównania i przypisania
void insertionSortDouble(vector<int>& arr, Counter& c) {
    size_t i = 0;
    while(i+1 < arr.size()){
        // porównanie dwóch elementów do wstawienia
        c.comparisons++;
        if(arr[i] > arr[i+1]) { swap(arr[i], arr[i+1]); c.assignments += 3; }
        int key1 = arr[i], key2 = arr[i+1]; c.assignments += 2;
        int j = i - 1;
        while(j >= 0 && arr[j] > key2) { c.comparisons++; arr[j+2] = arr[j]; c.assignments++; j--; }
        if(j>=0) c.comparisons++;
        arr[j+1] = key1; arr[j+2] = key2; c.assignments += 2;
        i += 2;
    }
    // wstawienie ostatniego elementu
    if(i < arr.size()) {
        int key = arr[i]; c.assignments++;
        int j = i-1;
        while(j >= 0 && arr[j] > key) { c.comparisons++; arr[j+1] = arr[j]; c.assignments++; j--; }
        if(j>=0) c.comparisons++;
        arr[j+1] = key; c.assignments++;
    }
}

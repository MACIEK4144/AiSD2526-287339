#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

struct Counter { int comparisons = 0; int assignments = 0; };

void insertionSort(vector<int>& arr, Counter& c);
void insertionSortDouble(vector<int>& arr, Counter& c);
void mergeSort(vector<int>& arr, int left, int right, Counter& c);
void merge3(vector<int>& arr, int left, int right, Counter& c);
void heapSort(vector<int>& arr, Counter& c);
void heapSortTernary(vector<int>& arr, Counter& c);

// generowanie losowej tablicy
void generateRandomVector(vector<int>& arr, int size) {
    arr.clear();
    for (int i = 0; i < size; i++)
        arr.push_back(rand() % 10000);
}

int main() {
    srand(time(nullptr));
    vector<int> sizes = {100, 500, 1000};
    vector<int> original, arr;

    cout << "Rozmiar | Algorytm | Porownania | Przypisania\n";
    cout << "---------------------------------------------\n";

    for (int n : sizes) {
        generateRandomVector(original, n);

        arr = original; Counter c;
        insertionSort(arr, c);
        cout << n << " | InsertionSort | " << c.comparisons << " | " << c.assignments << "\n";

        arr = original; c = Counter();
        insertionSortDouble(arr, c);
        cout << n << " | InsertionSortDouble | " << c.comparisons << " | " << c.assignments << "\n";

        arr = original; c = Counter();
        mergeSort(arr, 0, n - 1, c);
        cout << n << " | MergeSort | " << c.comparisons << " | " << c.assignments << "\n";

        arr = original; c = Counter();
        merge3(arr, 0, n - 1, c);
        cout << n << " | MergeSort3 | " << c.comparisons << " | " << c.assignments << "\n";

        arr = original; c = Counter();
        heapSort(arr, c);
        cout << n << " | HeapSort | " << c.comparisons << " | " << c.assignments << "\n";

        arr = original; c = Counter();
        heapSortTernary(arr, c);
        cout << n << " | HeapSortTernary | " << c.comparisons << " | " << c.assignments << "\n";
    }

    return 0;
}

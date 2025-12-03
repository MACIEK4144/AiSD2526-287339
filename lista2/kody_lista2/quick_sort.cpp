#include <utility>
#include <algorithm>
#include <cstdlib>

using namespace std;

extern long long comp_count;
extern long long assign_count;
long long& get_porownania();
long long& get_przypisania();
void increment_porownania();
void increment_przypisania();

void swap_arr(int arr[], int i, int j) {
    if (i != j) {
        std::swap(arr[i], arr[j]);
        increment_przypisania();
        increment_przypisania();
        increment_przypisania();
    }
}

int partition_classic(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    increment_przypisania();

    for (int j = low; j <= high - 1; j++) {
        increment_porownania();
        if (arr[j] <= pivot) {
            i++;
            swap_arr(arr, i, j);
        }
    }
    swap_arr(arr, i + 1, high);
    return (i + 1);
}

void quick_sort_classic(int arr[], int low, int high) {
    increment_porownania();
    if (low < high) {
        int pi = partition_classic(arr, low, high);
        quick_sort_classic(arr, low, pi - 1);
        quick_sort_classic(arr, pi + 1, high);
    }
}

std::pair<int, int> partition_dual_pivot(int arr[], int low, int high) {
    increment_porownania();
    if (arr[low] > arr[high]) {
        swap_arr(arr, low, high);
    }

    int p1 = arr[low];
    int p2 = arr[high];
    increment_przypisania();
    increment_przypisania();

    int l = low + 1;
    int g = high - 1;
    int k = l;

    while (k <= g) {
        increment_porownania();
        increment_porownania();
        if (arr[k] < p1) {
            swap_arr(arr, k, l);
            l++;
        } else {
            increment_porownania();
            if (arr[k] > p2) {
                swap_arr(arr, k, g);
                g--;
                k--;
            }
        }
        k++;
    }

    swap_arr(arr, low, l - 1);
    swap_arr(arr, high, g + 1);

    return {l - 1, g + 1};
}

void quick_sort_dual_pivot(int arr[], int low, int high) {
    increment_porownania();
    if (low < high) {
        std::pair<int, int> pivots = partition_dual_pivot(arr, low, high);
        quick_sort_dual_pivot(arr, low, pivots.first - 1);
        quick_sort_dual_pivot(arr, pivots.first + 1, pivots.second - 1);
        quick_sort_dual_pivot(arr, pivots.second + 1, high);
    }
}

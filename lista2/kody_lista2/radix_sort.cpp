#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

extern long long comp_count;
extern long long assign_count;
long long& get_porownania();
long long& get_przypisania();
void increment_porownania();
void increment_przypisania();

int find_min(int arr[], int size) {
    if (size == 0) return 0;
    int min_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) min_val = arr[i];
    }
    return min_val;
}

int find_max_abs(int arr[], int size) {
    if (size == 0) return 0;
    int max_abs = 0;
    for (int i = 0; i < size; i++) {
        int abs_val = std::abs(arr[i]);
        if (abs_val > max_abs) max_abs = abs_val;
    }
    return max_abs;
}

void counting_sort_radix(int arr[], int size, long long exp, int base) {
    if (size <= 0) return;

    int* output = new int[size];
    std::vector<int> count(base, 0);

    for (int i = 0; i < size; i++) {
        int digit = (arr[i] / exp) % base;
        count[digit]++;
        increment_przypisania();
    }

    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
        increment_przypisania();
    }

    for (int i = size - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % base;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
        increment_przypisania();
        increment_przypisania();
    }

    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
        increment_przypisania();
    }

    delete[] output;
}

void radix_sort(int arr[], int size, int base) {
    if (size <= 1) return;

    int min_val = find_min(arr, size);
    int max_abs = find_max_abs(arr, size);
    int shift = (min_val < 0) ? -min_val : 0;

    int* shifted_arr = new int[size];

    for (int i = 0; i < size; i++) {
        shifted_arr[i] = arr[i] + shift;
        increment_przypisania();
    }

    long long exp = 1;
    while (max_abs / exp > 0) {
        counting_sort_radix(shifted_arr, size, exp, base);
        exp *= base;
    }

    for (int i = 0; i < size; i++) {
        arr[i] = shifted_arr[i] - shift;
        increment_przypisania();
    }

    delete[] shifted_arr;
}

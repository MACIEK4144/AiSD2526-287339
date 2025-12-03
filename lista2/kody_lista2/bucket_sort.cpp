#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

extern long long comp_count;
extern long long assign_count;
long long& get_porownania();
long long& get_przypisania();
void increment_porownania();
void increment_przypisania();

void bucket_insertion_sort(std::vector<int>& bucket) {
    for (size_t i = 1; i < bucket.size(); ++i) {
        int key = bucket[i];
        increment_przypisania();
        int j = i - 1;

        increment_porownania();
        while (j >= 0) {
            increment_porownania();
            if (bucket[j] > key) {
                bucket[j + 1] = bucket[j];
                increment_przypisania();
                j = j - 1;
            } else {
                break;
            }
        }
        bucket[j + 1] = key;
        increment_przypisania();
    }
}


void bucket_sort(int arr[], int size, int num_buckets) {
    if (size <= 1) return;

    int min_val = arr[0];
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        increment_porownania();
        if (arr[i] < min_val) min_val = arr[i];
        increment_porownania();
        if (arr[i] > max_val) max_val = arr[i];
    }

    long long range = (long long)max_val - min_val;
    if (range == 0) range = 1;

    std::vector<std::vector<int>> buckets(num_buckets);

    for (int i = 0; i < size; i++) {
        double normalized = (double)(arr[i] - min_val) / range;
        int bucket_index = (int)(normalized * num_buckets);

        if (bucket_index >= num_buckets) bucket_index = num_buckets - 1;
        if (bucket_index < 0) bucket_index = 0;

        buckets[bucket_index].push_back(arr[i]);
        increment_przypisania();
    }

    for (int i = 0; i < num_buckets; i++) {
        bucket_insertion_sort(buckets[i]);
    }

    int index = 0;
    for (int i = 0; i < num_buckets; i++) {
        for (int val : buckets[i]) {
            arr[index++] = val;
            increment_przypisania();
        }
    }
}

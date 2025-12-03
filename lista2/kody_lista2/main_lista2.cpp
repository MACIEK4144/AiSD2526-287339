#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <utility>

using namespace std;

long long comp_count = 0;
long long assign_count = 0;

long long& get_porownania() { return comp_count; }
long long& get_przypisania() { return assign_count; }
void reset_liczniki() { comp_count = 0; assign_count = 0; }
void increment_porownania() { comp_count++; }
void increment_przypisania() { assign_count++; }

void quick_sort_classic(int arr[], int low, int high);
void quick_sort_dual_pivot(int arr[], int low, int high);

void radix_sort(int arr[], int size, int base);
void bucket_sort(int arr[], int size, int num_buckets);

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class MyList {
public:
    Node* head;
    MyList() : head(nullptr) {}

    ~MyList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
    }

    void append(int val) {
        Node* new_node = new Node(val);
        if (head == nullptr) {
            head = new_node;
            return;
        }
        Node* last = head;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = new_node;
    }

    static MyList from_array(int arr[], int size) {
        MyList list;
        for (int i = 0; i < size; ++i) {
            list.append(arr[i]);
        }
        return list;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
};

void insertion_sort_list(MyList& list);


void generate_random_array(int arr[], int size, int min_val, int max_val) {
    for (int i = 0; i < size; ++i) {
        arr[i] = min_val + (rand() % (max_val - min_val + 1));
    }
}

void test_sort_array(const char* name, int arr_to_sort[], int size,
                     void (*sort_func)(int[], int, int) = nullptr,
                     int param = 0) {

    int* temp_arr = new int[size];
    copy(arr_to_sort, arr_to_sort + size, temp_arr);

    reset_liczniki();
    clock_t start = clock();

    if (name == "Bucket_Sort") {
        bucket_sort(temp_arr, size, param);
    } else {
        sort_func(temp_arr, 0, size - 1);
    }

    clock_t end = clock();
    double time_taken = double(end - start) / CLOCKS_PER_SEC;

    cout << setiosflags(ios::left) << setw(20) << name
         << " | Rozmiar: " << setw(7) << size
         << " | Porownania: " << setw(15) << get_porownania()
         << " | Przypisania: " << setw(15) << get_przypisania()
         << " | Czas: " << fixed << setprecision(6) << time_taken << " s" << endl;

    delete[] temp_arr;
}

void test_radix(const char* name, int arr_to_sort[], int size, int base) {
    int* temp_arr = new int[size];
    copy(arr_to_sort, arr_to_sort + size, temp_arr);

    reset_liczniki();
    clock_t start = clock();

    radix_sort(temp_arr, size, base);

    clock_t end = clock();
    double time_taken = double(end - start) / CLOCKS_PER_SEC;

    cout << setiosflags(ios::left) << setw(20) << name
         << " | Rozmiar: " << setw(7) << size
         << " | Porownania: " << setw(15) << get_porownania()
         << " | Przypisania: " << setw(15) << get_przypisania()
         << " | Czas: " << fixed << setprecision(6) << time_taken << " s" << endl;

    delete[] temp_arr;
}

void test_insertion_sort(int arr_to_sort[], int size) {
    MyList list = MyList::from_array(arr_to_sort, size);

    reset_liczniki();
    clock_t start = clock();

    insertion_sort_list(list);

    clock_t end = clock();
    double time_taken = double(end - start) / CLOCKS_PER_SEC;

    cout << setiosflags(ios::left) << setw(20) << "Insertion_List"
         << " | Rozmiar: " << setw(7) << size
         << " | Porownania: " << setw(15) << get_porownania()
         << " | Przypisania: " << setw(15) << get_przypisania()
         << " | Czas: " << fixed << setprecision(6) << time_taken << " s" << endl;
}

int main() {
    srand(time(0));

    const int SIZES[] = {1000, 5000, 10000, 20000, 50000, 100000};
    const int MIN_VAL = -10000;
    const int MAX_VAL = 10000;

    cout << setiosflags(ios::left) << setw(20) << "ALGORYTM"
         << " | Rozmiar | Porownania" << setw(5) << ""
         << " | Przypisania" << setw(3) << ""
         << " | Czas [s]" << endl;
    cout << "----------------------------------------------------------------------------------------\n";


    for (int size : SIZES) {
        int* data = new int[size];

        generate_random_array(data, size, MIN_VAL, MAX_VAL);

        cout << "\n--- TESTY DLA N = " << size << " ---\n";

        test_sort_array("QuickSort_C", data, size, quick_sort_classic);

        test_sort_array("QuickSort_DP", data, size, quick_sort_dual_pivot);

        test_sort_array("Bucket_Sort", data, size, nullptr, (int)sqrt(size));

        test_radix("Radix_B10", data, size, 10);
        test_radix("Radix_B256", data, size, 256);

        if (size <= 50000) {
            test_insertion_sort(data, size);
        }

        delete[] data;
    }

    return 0;
}

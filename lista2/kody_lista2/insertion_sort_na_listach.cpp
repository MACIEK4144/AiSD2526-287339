extern long long comp_count;
extern long long assign_count;
long long& get_porownania();
long long& get_przypisania();
void increment_porownania();
void increment_przypisania();

struct Node { int data; Node* next; Node(int val) : data(val), next(nullptr) {} };
class MyList {
public:
    Node* head;
    MyList() : head(nullptr) {}
    ~MyList();
    void append(int val);
    static MyList from_array(int arr[], int size);
    void print() const;
};


void insertion_sort_list(MyList& list) {
    if (list.head == nullptr || list.head->next == nullptr) {
        return;
    }

    Node* sorted = nullptr;
    Node* current = list.head;

    while (current != nullptr) {
        Node* next_node = current->next;

        Node* curr_sorted = sorted;
        Node* prev_sorted = nullptr;

        increment_porownania();
        while (curr_sorted != nullptr) {
            increment_porownania();
            if (current->data < curr_sorted->data) {
                break;
            }
            prev_sorted = curr_sorted;
            curr_sorted = curr_sorted->next;
        }

        if (prev_sorted == nullptr) {
            current->next = sorted;
            increment_przypisania();
            sorted = current;
            increment_przypisania();
        } else {
            current->next = prev_sorted->next;
            increment_przypisania();
            prev_sorted->next = current;
            increment_przypisania();
        }

        current = next_node;
    }
    list.head = sorted;
    increment_przypisania();
}

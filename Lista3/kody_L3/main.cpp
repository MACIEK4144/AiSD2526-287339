#include <iostream>
#include <vector>
#include <map>
#include <chrono>
using namespace std;
using namespace chrono;

int cutRodNaive(const vector<int>&, int);
int cutRodMemo(const vector<int>&, int, vector<int>&);
int cutRodBottomUp(const vector<int>&, int, vector<int>&);

string lcsMemo(const string&, const string&);
string lcsIter(const string&, const string&);

vector<pair<int,int>> activityRecursive(vector<pair<int,int>>);
vector<pair<int,int>> activityIterative(vector<pair<int,int>>);
vector<pair<int,int>> activityDP(vector<pair<int,int>>);
vector<pair<int,int>> activityDPStartSorted(vector<pair<int,int>>);

map<char,string> huffman(const map<char,long long>&);

void printCuts(const vector<int>& s, int n) {
    while (n > 0) {
        cout << s[n] << " ";
        n -= s[n];
    }
    cout << endl;
}

void printActivities(const vector<pair<int,int>>& a) {
    for (auto& x : a)
        cout << "(" << x.first << "," << x.second << ") ";
    cout << endl;
}

int main() {
    cout << "========== CUT ROD ==========\n";
    vector<int> p = {1,5,8,9,10,17,17,20};
    vector<int> s1(9), s2(9);

    cout << "Naive: " << cutRodNaive(p,4) << endl;
    cout << "Memo: " << cutRodMemo(p,4,s1) << " | ";
    printCuts(s1,4);
    cout << "Bottom-Up: " << cutRodBottomUp(p,4,s2) << " | ";
    printCuts(s2,4);

    cout << "\n========== LCS ==========\n";
    cout << lcsMemo("ABCBDAB","BDCABA") << endl;
    cout << lcsIter("ABCBDAB","BDCABA") << endl;

    cout << "\n====== ACTIVITY SELECTOR ======\n";
    vector<pair<int,int>> acts = {
        {1,4},{3,5},{0,6},{5,7},{3,9},{5,9},{6,10},{8,11}
    };

    printActivities(activityRecursive(acts));
    printActivities(activityIterative(acts));
    printActivities(activityDP(acts));
    printActivities(activityDPStartSorted(acts));

    cout << "\n========== HUFFMAN ==========\n";
    map<char,long long> f = {
        {'a',5},{'b',9},{'c',12},{'d',13},{'e',16},{'f',45}
    };

    auto codes = huffman(f);
    for (auto& x : codes)
        cout << x.first << " -> " << x.second << endl;

    cout << "\n=== PERFORMANCE TESTS ===\n";
    vector<int> prices(100);
    for (int i = 0; i < 100; i++) prices[i] = i+1;

    for (int n : {20,30,40}) {
        vector<int> s(n+1);
        auto t1 = high_resolution_clock::now();
        cutRodMemo(prices,n,s);
        auto t2 = high_resolution_clock::now();
        auto t3 = high_resolution_clock::now();
        cutRodBottomUp(prices,n,s);
        auto t4 = high_resolution_clock::now();
        cout << "n=" << n
             << " memo=" << duration_cast<microseconds>(t2-t1).count()
             << " bu=" << duration_cast<microseconds>(t4-t3).count()
             << endl;
    }

    string a(500,'A'), b(500,'A');
    auto l1 = high_resolution_clock::now();
    lcsIter(a,b);
    auto l2 = high_resolution_clock::now();
    cout << "LCS 500x500: "
         << duration_cast<milliseconds>(l2-l1).count() << " ms\n";

    vector<pair<int,int>> big;
    for (int i = 0; i < 2000; i++)
        big.push_back({i,i+1});

    auto a1 = high_resolution_clock::now();
    activityIterative(big);
    auto a2 = high_resolution_clock::now();
    auto a3 = high_resolution_clock::now();
    activityDP(big);
    auto a4 = high_resolution_clock::now();

    cout << "Activity greedy=" << duration_cast<microseconds>(a2-a1).count()
         << " DP=" << duration_cast<microseconds>(a4-a3).count() << endl;

    return 0;
}



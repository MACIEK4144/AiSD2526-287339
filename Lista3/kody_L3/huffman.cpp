#include <queue>
#include <map>
#include <vector>
#include <string>
using namespace std;

struct Node {
    long long f;
    char c;
    vector<Node*> ch;
    Node(long long f, char c = '\0') : f(f), c(c) {}
};

struct Cmp {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

void gen(Node* n, const string& s, map<char,string>& out) {
    if (n->ch.empty()) {
        out[n->c] = s;
        return;
    }
    for (int i = 0; i < n->ch.size(); i++)
        gen(n->ch[i], s + char('0'+i), out);
}

void del(Node* n) {
    for (auto x : n->ch) del(x);
    delete n;
}

map<char,string> huffman(const map<char,long long>& freq) {
    priority_queue<Node*, vector<Node*>, Cmp> pq;
    for (auto& x : freq)
        pq.push(new Node(x.second, x.first));

    const int k = 3;
    while (pq.size() > 1) {
        int take = min(k, (int)pq.size());
        Node* n = new Node(0);
        for (int i = 0; i < take; i++) {
            auto t = pq.top(); pq.pop();
            n->ch.push_back(t);
            n->f += t->f;
        }
        pq.push(n);
    }

    map<char,string> res;
    Node* root = pq.top();
    gen(root, "", res);
    del(root);
    return res;
}



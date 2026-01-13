#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int,int>> activityRecursiveAux(const vector<pair<int,int>>& a, int i, int last) {
    if (i == a.size()) return {};
    if (a[i].first >= last) {
        auto r = activityRecursiveAux(a, i+1, a[i].second);
        r.insert(r.begin(), a[i]);
        return r;
    }
    return activityRecursiveAux(a, i+1, last);
}

vector<pair<int,int>> activityRecursive(vector<pair<int,int>> a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) {
        return x.second < y.second;
    });
    return activityRecursiveAux(a, 0, 0);
}

vector<pair<int,int>> activityIterative(vector<pair<int,int>> a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) {
        return x.second < y.second;
    });

    vector<pair<int,int>> res;
    int last = 0;
    for (auto& x : a) {
        if (x.first >= last) {
            res.push_back(x);
            last = x.second;
        }
    }
    return res;
}

vector<pair<int,int>> activityDP(vector<pair<int,int>> a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) {
        return x.second < y.second;
    });

    int n = a.size();
    vector<int> dp(n,1), p(n,-1);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j].second <= a[i].first && dp[j]+1 > dp[i]) {
                dp[i] = dp[j]+1;
                p[i] = j;
            }

    int idx = max_element(dp.begin(), dp.end()) - dp.begin();
    vector<pair<int,int>> res;
    while (idx != -1) {
        res.push_back(a[idx]);
        idx = p[idx];
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<pair<int,int>> activityDPStartSorted(vector<pair<int,int>> a) {
    sort(a.begin(), a.end(), [](auto& x, auto& y) {
        return x.first < y.first;
    });

    int n = a.size();
    vector<int> dp(n,1), p(n,-1);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j].second <= a[i].first && dp[j]+1 > dp[i]) {
                dp[i] = dp[j]+1;
                p[i] = j;
            }

    int idx = max_element(dp.begin(), dp.end()) - dp.begin();
    vector<pair<int,int>> res;
    while (idx != -1) {
        res.push_back(a[idx]);
        idx = p[idx];
    }
    reverse(res.begin(), res.end());
    return res;
}






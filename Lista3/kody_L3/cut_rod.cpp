#include <vector>
#include <climits>
using namespace std;

int cutRodNaive(const vector<int>& p, int n) {
    if (n == 0) return 0;
    int best = INT_MIN;
    for (int i = 1; i <= n; i++)
        best = max(best, p[i-1] + cutRodNaive(p, n - i));
    return best;
}

int cutRodMemoAux(const vector<int>& p, int n, vector<int>& dp, vector<int>& s) {
    if (dp[n] != -1) return dp[n];
    int best = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int val = p[i-1] + cutRodMemoAux(p, n - i, dp, s);
        if (val > best) {
            best = val;
            s[n] = i;
        }
    }
    dp[n] = best;
    return best;
}

int cutRodMemo(const vector<int>& p, int n, vector<int>& s) {
    vector<int> dp(n+1, -1);
    dp[0] = 0;
    return cutRodMemoAux(p, n, dp, s);
}

int cutRodBottomUp(const vector<int>& p, int n, vector<int>& s) {
    vector<int> dp(n+1, 0);
    for (int j = 1; j <= n; j++) {
        int best = INT_MIN;
        for (int i = 1; i <= j; i++) {
            if (p[i-1] + dp[j-i] > best) {
                best = p[i-1] + dp[j-i];
                s[j] = i;
            }
        }
        dp[j] = best;
    }
    return dp[n];
}



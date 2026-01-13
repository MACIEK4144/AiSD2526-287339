#include <vector>
#include <string>
using namespace std;

int lcsMemoLen(const string& a, const string& b, int i, int j,
               vector<vector<int>>& dp) {
    if (i == 0 || j == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (a[i-1] == b[j-1])
        dp[i][j] = 1 + lcsMemoLen(a,b,i-1,j-1,dp);
    else
        dp[i][j] = max(lcsMemoLen(a,b,i-1,j,dp),
                       lcsMemoLen(a,b,i,j-1,dp));
    return dp[i][j];
}

string lcsMemo(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
    lcsMemoLen(a,b,n,m,dp);

    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) {
            res = a[i-1] + res;
            i--; j--;
        } else if (dp[i-1][j] >= dp[i][j-1])
            i--;
        else
            j--;
    }
    return res;
}

string lcsIter(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1,0));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) {
            res = a[i-1] + res;
            i--; j--;
        } else if (dp[i-1][j] >= dp[i][j-1])
            i--;
        else
            j--;
    }
    return res;
}




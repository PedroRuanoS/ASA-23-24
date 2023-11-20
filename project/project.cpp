#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxValue(int X, int Y, const vector<int>& a, const vector<int>& b, const vector<int>& p, int n) {
    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    for (int x = 1; x <= X; x++) {
        for (int y = 1; y <= Y; y++) {
            for (int k = 0; k < n; k++) {
                if (x >= a[k] && y >= b[k]) {
                    dp[x][y] = max(dp[x][y], dp[x - a[k]][y - b[k]] + p[k]);
                }       
            }
        }

    }
    return dp[X][Y];
}

int main() {
    int X, Y, n;
    cin >> X >> Y;
    cin >> n;
    vector<int> a(n), b(n), p(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> p[i];
    }

    cout << maxValue(X, Y, a, b, p, n) << endl;

    return 0;
}

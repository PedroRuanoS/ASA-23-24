#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxValue(int X, int Y, const vector<int>& a, const vector<int>& b, const vector<int>& p, int n) {
    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    for (int x = 1; x <= X; x++) {
        for (int y = 1; y <= Y; y++) {
            // Check each type of piece
            for (int i = 0; i < n; i++) {
                if (x >= a[i] && y >= b[i]) {
                    dp[x][y] = max(dp[x][y], dp[x - a[i]][y - b[i]] + p[i]);
                }
                if (x >= b[i] && y >= a[i]) {
                    dp[x][y] = max(dp[x][y], dp[x - b[i]][y - a[i]] + p[i]);
                }
            }

            // Optimize cuts along dimensions
            if (x > 1) {
                for (int cut = 1; cut <= x / 2; cut++) {
                    dp[x][y] = max(dp[x][y], dp[cut][y] + dp[x - cut][y]);
                }
            }
            if (y > 1) {
                for (int cut = 1; cut <= y / 2; cut++) {
                    dp[x][y] = max(dp[x][y], dp[x][cut] + dp[x][y - cut]);
                }
            }
        }
    }

    return dp[X][Y];
}

int main() {
    int X, Y, n;
    cin >> X >> Y >> n;
    vector<int> a(n), b(n), p(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> p[i];
    }

    cout << maxValue(X, Y, a, b, p, n) << endl;
    return 0;
}
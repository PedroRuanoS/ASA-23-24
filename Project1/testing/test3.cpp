#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxValue(int X, int Y, const vector<int>& a, const vector<int>& b, const vector<int>& p, int n) {
    // Swap dimensions to ensure X is always less than or equal to Y
    if (X > Y) {
        swap(X, Y);
    }

    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    for (int x = 0; x <= X; x++) {
        for (int y = x; y <= Y; y++) {  // Start y from x to avoid redundant computations
            for (int i = 0; i < n; i++) {
                if (x >= a[i] && y >= b[i]) {
                    dp[x][y] = max(dp[x][y], dp[x - a[i]][y] + p[i]);
                }
                if (x >= b[i] && y >= a[i]) {
                    dp[x][y] = max(dp[x][y], dp[x - b[i]][y] + p[i]);
                }
            }

            for (int cut = 1; cut < x; cut++) {
                dp[x][y] = max(dp[x][y], dp[cut][y] + dp[x - cut][y]);
            }
            for (int cut = 1; cut < y; cut++) {
                dp[x][y] = max(dp[x][y], dp[x][cut] + dp[x][y - cut]);
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

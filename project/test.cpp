#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Função para calcular o valor máximo de maneira iterativa
int maxValue(int X, int Y, const vector<int>& a, const vector<int>& b, const vector<int>& p, int n) {
    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    for (int x = 0; x <= X; x++) {
        for (int y = 0; y <= Y; y++) {
            for (int i = 0; i < n; i++) {
                // Tenta colocar a peça na orientação original
                if (x >= a[i] && y >= b[i]) {
                    dp[x][y] = max(dp[x][y], p[i] + dp[x - a[i]][y] + dp[a[i]][y - b[i]]);
                }
                // Tenta colocar a peça na orientação rotacionada
                if (x >= b[i] && y >= a[i]) {
                    dp[x][y] = max(dp[x][y], p[i] + dp[x - b[i]][y] + dp[b[i]][y - a[i]]);
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

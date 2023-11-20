#include <iostream>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

// Função para calcular o valor máximo
int dfs(int remaining_X, int remaining_Y, const vector<int>& a, const vector<int>& b, const vector<int>& p, int n, map<pair<int, int>, int>& memo) {
    // Verifica se o resultado já foi computado
    if (memo.find({remaining_X, remaining_Y}) != memo.end()) {
        return memo[{remaining_X, remaining_Y}];
    }

    int max_value = 0;
    for (int i = 0; i < n; ++i) {
        // Tenta colocar a peça na orientação original
        if (remaining_X >= a[i] && remaining_Y >= b[i]) {
            int value = p[i] + dfs(remaining_X - a[i], remaining_Y, a, b, p, n, memo)
                              + dfs(a[i], remaining_Y - b[i], a, b, p, n, memo);
            max_value = max(max_value, value);
        }
        // Tenta colocar a peça na orientação rotacionada
        if (remaining_X >= b[i] && remaining_Y >= a[i]) {
            int value = p[i] + dfs(remaining_X - b[i], remaining_Y, a, b, p, n, memo)
                              + dfs(b[i], remaining_Y - a[i], a, b, p, n, memo);
            max_value = max(max_value, value);
        }
    }

    // Armazena o resultado no cache
    memo[{remaining_X, remaining_Y}] = max_value;
    return max_value;
}

// Função para iniciar o cálculo do valor máximo
int maxValue(int X, int Y, const vector<int>& a, const vector<int>& b, const vector<int>& p, int n) {
    map<pair<int, int>, int> memo;
    return dfs(X, Y, a, b, p, n, memo);
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

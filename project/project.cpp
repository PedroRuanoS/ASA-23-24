#include <iostream>
#include <vector>
#include <map>
#include <tuple>
using namespace std;

// Função para calcular o valor máximo
int dfs(int remainingX, int remainingY, const vector<int>& a, const vector<int>& b, const vector<int>& p, int n, map<pair<int, int>, int>& memo) {
    // Verifica se o resultado já foi computado
    if (memo.find({remainingX, remainingY}) != memo.end()) {
        return memo[{remainingX, remainingY}];
    }

    int max_value = 0;
    for (int i = 0; i < n; ++i) {
        // Tenta colocar a peça na orientação original
        if (remainingX >= a[i] && remainingY >= b[i]) {
            int value = p[i] + dfs(remainingX - a[i], remainingY, a, b, p, n, memo)
                              + dfs(a[i], remainingY - b[i], a, b, p, n, memo);
            max_value = max(max_value, value);
        }
        // Tenta colocar a peça na orientação rotacionada
        if (remainingX >= b[i] && remainingY >= a[i]) {
            int value = p[i] + dfs(remainingX - b[i], remainingY, a, b, p, n, memo)
                              + dfs(b[i], remainingY - a[i], a, b, p, n, memo);
            max_value = max(max_value, value);
        }
    }

    // Armazena o resultado no cache
    memo[{remainingX, remainingY}] = max_value;
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

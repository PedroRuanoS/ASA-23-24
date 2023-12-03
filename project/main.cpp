/*
*   1º Projeto ASA 2023/2024
*
*   Alunos:
*       Pedro Silveira - 106642
*       Gonçalo Aleixo - 106900
*
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int maxValue(vector<vector<int>>& matrix, int X, int Y) {
    int maxVal = 0;

    for (int x = 1; x <= X; x++) {
        for (int y = 1; y <= Y; y++) {
            int maxCurrentXY = 0;
            for (int i = 1; i <= x/2; i++) {
                maxCurrentXY = max(maxCurrentXY, matrix[i][y] + matrix[x-i][y]);
            }
            for (int j = 1; j <= y/2; j++) {
                maxCurrentXY = max(maxCurrentXY, matrix[x][j] + matrix[x][y-j]);
            }
            matrix[x][y] = max(matrix[x][y], maxCurrentXY);
            maxVal = max(maxVal, matrix[x][y]);
        }
    }

    return maxVal;
}

int main() {
    int X, Y, n;
    scanf("%d %d %d", &X, &Y, &n);

    vector<vector<int>> matrix(X + 1, vector<int>(Y + 1, 0));

    for (int i = 0; i < n; i++) {
        int a, b, p;
        scanf("%d %d %d", &a, &b, &p);
        if (a <= X && b <= Y) {
            matrix[a][b] = max(matrix[a][b], p);
        }
        if (b <= X && a <= Y) {
            matrix[b][a] = max(matrix[b][a], p);
        }
    }

    printf("%d\n", maxValue(matrix, X, Y));
    return 0;
}

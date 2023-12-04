/*
   1º Projeto ASA 2023/2024

   Autores:
       Pedro Silveira - 106642
       Gonçalo Aleixo - 106900

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int maxValue(vector<vector<int>>& allValues, int X, int Y) {

    for (int x = 1; x <= X; x++) {
        for (int y = 1; y <= Y; y++) {
            int maxCurrentXY = 0;
            for (int i = 1; i <= x/2; i++) {
                maxCurrentXY = max(maxCurrentXY, allValues[i][y] + allValues[x-i][y]);
            }
            for (int j = 1; j <= y/2; j++) {
                maxCurrentXY = max(maxCurrentXY, allValues[x][j] + allValues[x][y-j]);
            }
            allValues[x][y] = max(allValues[x][y], maxCurrentXY);
        }
    }
    
    return allValues[X][Y];
}

int main() {
    int X, Y, n;
    scanf("%d %d %d", &X, &Y, &n);

    vector<vector<int>> allValues(X + 1, vector<int>(Y + 1, 0));

    for (int i = 0; i < n; i++) {
        int a, b, p;
        scanf("%d %d %d", &a, &b, &p);
        if (a <= X && b <= Y) {
            allValues[a][b] = max(allValues[a][b], p);
        }
        if (b <= X && a <= Y) {
            allValues[b][a] = max(allValues[b][a], p);
        }
    }

    printf("%d\n", maxValue(allValues, X, Y));
    return 0;
}

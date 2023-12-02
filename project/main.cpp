#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

// Function to compute the maximum value
int maxValue(vector<vector<int>>& matrix, int X, int Y) {
    int maxVal = 0;

    // Outer loops for dimensions X and Y
    for (int x = 1; x <= X; x++) {
        for (int y = 1; y <= Y; y++) {
            int maxForCurrentXY = 0;

            // First inner loop (horizontal cuts)
            for (int i = 1; i <= x / 2; i++) {
                maxForCurrentXY = max(maxForCurrentXY, matrix[i][y] + matrix[x - i][y]);
            }

            // Second inner loop (vertical cuts)
            for (int j = 1; j <= y / 2; j++) {
                maxForCurrentXY = max(maxForCurrentXY, matrix[x][j] + matrix[x][y - j]);
            }

            // Update the matrix with the maximum value found for the current x, y
            matrix[x][y] = max(matrix[x][y], maxForCurrentXY);
            // Update the overall maximum value
            maxVal = max(maxVal, matrix[x][y]);
        }
    }

    return maxVal;
}

int main() {
    int X, Y, n;
    scanf("%d %d %d", &X, &Y, &n);

    // Create and initialize the matrix
    vector<vector<int>> matrix(X + 1, vector<int>(Y + 1, 0));

    // Process each piece and update the matrix
    for (int i = 0; i < n; i++) {
        int a, b, p;
        scanf("%d %d %d", &a, &b, &p);
        // Ensure the piece fits in the slab in both orientations
        if (a <= X && b <= Y) {
            matrix[a][b] = max(matrix[a][b], p);
        }
        if (b <= X && a <= Y) {
            matrix[b][a] = max(matrix[b][a], p);
        }
    }

    // Calculate and print the maximum value
    printf("%d\n", maxValue(matrix, X, Y));

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Segment Tree implementation for range maximum query
class SegmentTree {
private:
    vector<int> tree;
    int n;

    void buildTree(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            buildTree(arr, 2 * node, start, mid);
            buildTree(arr, 2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

    int queryTree(int node, int start, int end, int L, int R) {
        if (R < start || end < L) {
            return 0; // Represents a null value
        }
        if (L <= start && end <= R) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int p1 = queryTree(2 * node, start, mid, L, R);
        int p2 = queryTree(2 * node + 1, mid + 1, end, L, R);
        return max(p1, p2);
    }

    void updateTree(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                updateTree(2 * node, start, mid, idx, val);
            } else {
                updateTree(2 * node + 1, mid + 1, end, idx, val);
            }
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

public:
    SegmentTree(int size) : n(size) {
        tree.resize(4 * size, 0);
    }

    void build(const vector<int>& arr) {
        buildTree(arr, 1, 0, n - 1);
    }

    int query(int L, int R) {
        return queryTree(1, 0, n - 1, L, R);
    }

    void update(int idx, int val) {
        updateTree(1, 0, n - 1, idx, val);
    }
};

int maxValue(int X, int Y, map<pair<int, int>, int>& pieceValues) {
    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));
    SegmentTree segTreeX(X + 1), segTreeY(Y + 1);

    for (int x = 1; x <= X; ++x) {
        for (int y = 1; y <= Y; ++y) {
            if (pieceValues.find({x, y}) != pieceValues.end()) {
                dp[x][y] = pieceValues[{x, y}];
            }

            int bestHorizontalCut = x > 1 ? segTreeX.query(1, x - 1) : 0;
            int bestVerticalCut = y > 1 ? segTreeY.query(1, y - 1) : 0;

            dp[x][y] = max({dp[x][y], bestHorizontalCut, bestVerticalCut});

            segTreeX.update(x, dp[x][y]);
            segTreeY.update(y, dp[x][y]);
        }
    }

    return dp[X][Y];
}

int main() {
    int X, Y, n;
    cin >> X >> Y >> n;

    map<pair<int, int>, int> pieceValues;
    for (int i = 0; i < n; ++i) {
        int w, h, v;
        cin >> w >> h >> v;
        pieceValues[{w, h}] = max(pieceValues[{w, h}], v);
    }

    cout << maxValue(X, Y, pieceValues) << endl;
    return 0;
}

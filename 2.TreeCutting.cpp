#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int n;

// 1. Replaced C-style array (int dp[1001][1001]) with STL vector
vector<vector<int>> dp;

int solve(vector<vector<int>> &trees, int treeVal, int pos) {
    if (treeVal == 0) {
        return n - pos;
    }

    if (dp[treeVal][pos] != -1) {
        return dp[treeVal][pos];
    }

    if (trees[treeVal].empty()) {
        return dp[treeVal][pos] = solve(trees, treeVal - 1, pos);
    }

    vector<int> &line = trees[treeVal];
    int t = line.size();
    int cost = INT_MAX;

    int L = line.front();
    int R = line.back();

    if (pos < L) {
        int dist = R - pos;
        int nPos = R;

        int curr = t + dist + solve(trees, treeVal - 1, nPos);
        cost = min(cost, curr);
    } else if (pos > R) {
        int dist = pos - L;
        int nPos = L;

        int curr = t + dist + solve(trees, treeVal - 1, nPos);
        cost = min(cost, curr);
    } else {
        int dist1 = (pos - L) + (R - L);
        int nPos1 = R;
        int curr1 = t + dist1 + solve(trees, treeVal - 1, nPos1);

        int dist2 = (R - pos) + (R - L);
        int nPos2 = L;
        int curr2 = t + dist2 + solve(trees, treeVal - 1, nPos2);

        cost = min({cost, curr1, curr2});
    }

    return dp[treeVal][pos] = cost;
}

int main(int argc, char const *argv[]) {
    int testCases;
    cin >> testCases;

    for (int t = 1; t <= testCases; t++) {
        cin >> n;

        vector<vector<int>> trees(1001);
        
        // 2. Replaced memset(dp, -1, sizeof(dp)) with STL vector assignment
        dp.assign(1001, vector<int>(1001, -1));

        int a;
        for (int i = 0; i < n; i++) {
            cin >> a;
            if (a > 0)
                trees[a].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            cin >> a;
            if (a > 0)
                trees[a].push_back(i);
        }

        for (int i = 0; i < 1001; i++) {
            if (trees[i].empty()) {
                continue;
            }
            sort(trees[i].begin(), trees[i].end());
        }

        int minCost = solve(trees, 1000, 0);
        cout << "#" << t << " " << minCost << endl;
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <deque>
#include <utility>
#include <climits>

using namespace std;

// 0-1 BFS using std::pair instead of a custom struct
int getMinFrogJumps(int n, const vector<vector<int>>& mat, pair<int, int> src, pair<int, int> dest) {
    // If the starting or ending positions are blocked (0), it's impossible.
    if (mat[src.first][src.second] == 0 || mat[dest.first][dest.second] == 0) {
        return -1;
    }

    // Initialize distance matrix with "infinity"
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    
    // Deque stores pairs of coordinates (row, col)
    deque<pair<int, int>> dq;

    // Start at the source
    dq.push_back(src);
    dist[src.first][src.second] = 0;

    // Direction arrays: Right, Left, Down, Up
    int row_offset[] = {0, 0, 1, -1};
    int col_offset[] = {1, -1, 0, 0};

    while (!dq.empty()) {
        pair<int, int> curr = dq.front();
        int r = curr.first;
        int c = curr.second;
        dq.pop_front();

        // Optional: Early exit if we reached the destination
        if (r == dest.first && c == dest.second) {
            return dist[r][c];
        }

        // Explore all 4 neighbors
        for (int i = 0; i < 4; i++) {
            int newRow = r + row_offset[i];
            int newCol = c + col_offset[i];

            // Check boundaries and whether the spot is valid (1)
            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && mat[newRow][newCol] == 1) {
                
                // Horizontal moves (row offset is 0) cost 0. Vertical moves cost 1.
                int jumpCost = (row_offset[i] == 0) ? 0 : 1;

                // Relaxation step: If we found a strictly cheaper path
                if (dist[r][c] + jumpCost < dist[newRow][newCol]) {
                    dist[newRow][newCol] = dist[r][c] + jumpCost;

                    // 0-1 BFS routing: 0-cost to the front, 1-cost to the back
                    if (jumpCost == 0) {
                        dq.push_front({newRow, newCol});
                    } else {
                        dq.push_back({newRow, newCol});
                    }
                }
            }
        }
    }
    
    // Return -1 if the destination was never reached
    return (dist[dest.first][dest.second] == INT_MAX) ? -1 : dist[dest.first][dest.second]; 
}

int main() {
    // Fast I/O for competitive programming style inputs
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Read the grid
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }

    // Read source and destination as pairs
    pair<int, int> src, dest;
    cin >> src.first >> src.second >> dest.first >> dest.second;

    // Calculate and print
    int minCost = getMinFrogJumps(n, mat, src, dest);
    cout << minCost << "\n";

    return 0;
}
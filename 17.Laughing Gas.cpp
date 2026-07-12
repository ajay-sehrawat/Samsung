#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Array to easily iterate over the 4 adjacent directions (Up, Down, Right, Left)
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void solve(int case_num) {
    int cols, rows;
    // Read number of columns and rows
    cin >> cols >> rows;

    // Use STL vector for dynamic 2D grid allocation (0-based indexing)
    vector<vector<int>> grid(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> grid[i][j];
        }
    }

    int start_col, start_row;
    cin >> start_col >> start_row;
    
    // Convert 1-based input coordinates to 0-based for the vector
    start_col -= 1;
    start_row -= 1;

    // Queue stores pairs of {{row, col}, current_time}
    queue<pair<pair<int, int>, int>> q;
    
    // Push the starting coordinate at time = 0
    q.push({{start_row, start_col}, 0});
    grid[start_row][start_col] = 2; // Mark as visited to avoid processing it again

    int max_time = 1;

    // Standard BFS Loop
    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        int r = current.first.first;
        int c = current.first.second;
        int current_time = current.second;

        // Keep track of the maximum time reached
        max_time = max(max_time, current_time);

        // Check all 4 adjacent directions
        for (int i = 0; i < 4; ++i) {
            int nr = r + dx[i];
            int nc = c + dy[i];

            // If the neighbor is within grid bounds and has uninfected people (1)
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                grid[nr][nc] = 2; // Mark as visited immediately
                q.push({{nr, nc}, current_time + 1});
            }
        }
    }

    // Print result format as requested
    cout << "Case #" << case_num << "\n";
    cout << max_time<< "\n";
}

int main() {
    int T;
    if (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            solve(t);
        }
    }
    return 0;
}
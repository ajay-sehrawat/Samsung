#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Lookup tables to check if a pipe type (0 to 7) has an opening in a specific direction.
// Index 0 represents no pipe (type 0).
bool can_up[8]    = {false, true, true, false, true, false, false, true};
bool can_down[8]  = {false, true, true, false, false, true, true, false};
bool can_left[8]  = {false, true, false, true, false, false, true, true};
bool can_right[8] = {false, true, false, true, true, true, false, false};

void solve() {
    int n, m, r, c, l;
    cin >> n >> m >> r >> c >> l;
    
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    
    // If the starting location has no pipe, or length is 0, we can't explore anything
    if (grid[r][c] == 0 || l == 0) {
        cout << 0 << "\n";
        return;
    }
    
    vector<vector<int>> dist(n, vector<int>(m, 0));
    queue<pair<int, int>> q;
    
    // Initialize starting point
    q.push({r, c});
    dist[r][c] = 1;
    int result = 1;
    
    // BFS traversal
    while (!q.empty()) {
        auto [curr_r, curr_c] = q.front();
        q.pop();
        
        // If the current distance has reached the endoscope's length limit, stop expanding
        if (dist[curr_r][curr_c] >= l) continue;
        
        int type = grid[curr_r][curr_c];
        
        // Check UP
        if (curr_r > 0 && dist[curr_r - 1][curr_c] == 0) {
            int next_type = grid[curr_r - 1][curr_c];
            // Current pipe must be able to go UP, and target pipe must be able to go DOWN
            if (can_up[type] && can_down[next_type]) {
                dist[curr_r - 1][curr_c] = dist[curr_r][curr_c] + 1;
                q.push({curr_r - 1, curr_c});
                result++;
            }
        }
        
        // Check DOWN
        if (curr_r < n - 1 && dist[curr_r + 1][curr_c] == 0) {
            int next_type = grid[curr_r + 1][curr_c];
            if (can_down[type] && can_up[next_type]) {
                dist[curr_r + 1][curr_c] = dist[curr_r][curr_c] + 1;
                q.push({curr_r + 1, curr_c});
                result++;
            }
        }
        
        // Check LEFT
        if (curr_c > 0 && dist[curr_r][curr_c - 1] == 0) {
            int next_type = grid[curr_r][curr_c - 1];
            if (can_left[type] && can_right[next_type]) {
                dist[curr_r][curr_c - 1] = dist[curr_r][curr_c] + 1;
                q.push({curr_r, curr_c - 1});
                result++;
            }
        }
        
        // Check RIGHT
        if (curr_c < m - 1 && dist[curr_r][curr_c + 1] == 0) {
            int next_type = grid[curr_r][curr_c + 1];
            if (can_right[type] && can_left[next_type]) {
                dist[curr_r][curr_c + 1] = dist[curr_r][curr_c] + 1;
                q.push({curr_r, curr_c + 1});
                result++;
            }
        }
    }
    
    cout << result << "\n";
}

int main() {
    // Optimize standard I/O operations for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
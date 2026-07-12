#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve() {
    int n;
    cin >> n;
    
    // Use std::vector instead of variable-length arrays
    // Read the grid as a vector of strings for easier input handling
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    // Force start and end to '0' as per the original problem logic
    grid[0][0] = '0';
    grid[n - 1][n - 1] = '0';

    // dp table stores pairs: {max_score, number_of_paths}
    // We initialize max_score to -1 (meaning unreachable) and paths to 0
    // Using 'long long' for paths prevents integer overflow on larger grids
    vector<vector<pair<int, long long>>> dp(n, vector<pair<int, long long>>(n, {-1, 0}));

    // Base case: We are at the start. Score is 0, and there is 1 way to be here.
    dp[0][0] = {0, 1};

    // Direction arrays for Right, Down, and Diagonal Right-Down
    int dx[] = {0, 1, 1};
    int dy[] = {1, 0, 1};

    // Process every cell in the grid from top-left to bottom-right
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            
            // If it's an obstacle, or we haven't reached this cell yet, skip it.
            if (grid[i][j] == 'x' || dp[i][j].first == -1) {
                continue;
            }

            // Try all 3 possible moves from the current cell
            for (int d = 0; d < 3; d++) {
                int next_i = i + dx[d];
                int next_j = j + dy[d];

                // Check if the next cell is inside the grid and is not an obstacle
                if (next_i < n && next_j < n && grid[next_i][next_j] != 'x') {
                    
                    int points = grid[next_i][next_j] - '0';
                    int new_score = dp[i][j].first + points;

                    // Case 1: We found a strictly better score for the next cell
                    if (new_score > dp[next_i][next_j].first) {
                        dp[next_i][next_j].first = new_score;
                        dp[next_i][next_j].second = dp[i][j].second; // Overwrite ways
                    } 
                    // Case 2: We found a path that ties with the current best score
                    else if (new_score == dp[next_i][next_j].first) {
                        dp[next_i][next_j].second += dp[i][j].second; // Accumulate ways
                    }
                }
            }
        }
    }

    // Check if the destination is still -1 (unreachable)
    if (dp[n - 1][n - 1].first == -1) {
        cout << "0 0\n";
    } else {
        cout << dp[n - 1][n - 1].first << " " << dp[n - 1][n - 1].second << "\n";
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// The 8 possible moves for the piece (Knight's move)
int mv[8][2] = {{-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}};

void solve(int t) {
    int n, m, r1, c1, r2, c2;
    cin >> n >> m >> r1 >> c1 >> r2 >> c2;

    // A 2D vector to store the minimum moves to reach each cell.
    // Initialized with -1 to indicate unvisited cells.
    // We use (n + 1) and (m + 1) because the problem uses 1-based indexing.
    vector<vector<int>> dist(n + 1, vector<int>(m + 1, -1));
    
    // Queue stores pairs of (x, y) coordinates
    queue<pair<int, int>> q;

    // Start by pushing the initial position into the queue
    q.push({r1, c1});
    dist[r1][c1] = 0; // It takes 0 moves to reach the starting position

    int steps = -1;

    // Standard Breadth-First Search (BFS)
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // If we reach the target piece, record the steps and stop searching
        if (x == r2 && y == c2) {
            steps = dist[x][y];
            break;
        }

        // Try all 8 possible moves
        for (int k = 0; k < 8; k++) {
            int nx = x + mv[k][0];
            int ny = y + mv[k][1];

            // If the move is inside board boundaries and hasn't been visited yet
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && dist[nx][ny] == -1) {
                // The distance to the new cell is the distance to the current cell + 1
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    // Output the formatted result
    cout << "Case #" << t << "\n";
    cout << steps << "\n";
}

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        for (int t = 1; t <= T; t++) {
            solve(t);
        }
    }
    return 0;
}
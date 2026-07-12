#include <iostream>
#include <climits>
#include <vector>
#include <cmath>     // For std::abs
#include <algorithm> // For std::min

using namespace std;

// Replaced raw arrays with STL vectors
vector<int> x(20), y(20);
int n, ans;

// The custom abs() function was removed; we now use std::abs from <cmath>

int dist(int i, int j) { // Calc dist between 2 points
    int x1 = x[i], x2 = x[j];
    int y1 = y[i], y2 = y[j];
    
    return (std::abs(x1 - x2) + std::abs(y1 - y2));
}

// Renamed the parameter 'x' to 'curr' to avoid shadowing the global vector 'x'
// Passed the visited vector by reference (&)
void optimalPath(int curr, vector<bool>& visited, int nodes, int value) {
    if (n == nodes) { // If number of nodes equal n then set value of answer
        ans = min(ans, value + dist(curr, n + 1));
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            optimalPath(i, visited, nodes + 1, value + dist(curr, i)); // Dfs call
            visited[i] = false;
        }
    }
}

int main() {
    int tCases;
    cin >> tCases; // For testcases
    for (int i = 0; i < tCases; i++) {
        ans = INT_MAX; // Set ans to max value
        cin >> n;
        cin >> x[0] >> y[0] >> x[n+1] >> y[n+1]; // Input destination and source x,y coordinates
        for (int j = 1; j <= n; j++) { // Input drop off location coordinates
            cin >> x[j] >> y[j];
        }
        
        // Replaced Variable-Length Array (VLA) with an STL vector initialized to false
        vector<bool> visited(n + 2, false);
        
        optimalPath(0, visited, 0, 0);
        cout << "#" << i + 1 << " " << ans << "\n";
    }
    return 0;
}
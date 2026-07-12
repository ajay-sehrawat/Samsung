/*
Mr. Lee has to travel various offices abroad to assist branches of each place.
... (Problem description omitted for brevity) ...
*/
#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

int N, result;

// Updated signature to take STL vectors by reference
void minCostMrLee(const vector<vector<int>>& arr, vector<bool>& visited, int count, int cost, int src) {
    // Base Case
    if (count == N - 1) {
        /* Corner Case if no path exists from last city */
        if (arr[src][0] != 0)
            result = min(result, cost + arr[src][0]);
        return;
    }
    
    // Main Case
    for (int i = 0; i < N; i++) {
        if (!visited[i] && arr[src][i] != 0) {
            visited[i] = true;
            minCostMrLee(arr, visited, count + 1, cost + arr[src][i], i);
            visited[i] = false;
        }
    }
}

int main() {
    // Optimize standard I/O operations for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        cin >> N;
        
        // Replace raw double pointer array with a 2D vector
        vector<vector<int>> arr(N, vector<int>(N));
        
        // Replace raw boolean pointer with a 1D vector initialized to false
        vector<bool> visited(N, false);
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> arr[i][j];
            }
        }
        
        result = INT_MAX;    
        visited[0] = true;
        
        minCostMrLee(arr, visited, 0, 0, 0);
        
        result != INT_MAX ? cout << result << "\n" : cout << "-1\n";
    }
    return 0;
}
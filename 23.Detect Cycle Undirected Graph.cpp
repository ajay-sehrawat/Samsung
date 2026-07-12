#include <iostream>
#include <vector>
using namespace std;

// DFS function to detect and print the cycle
bool dfs(int node, int parent, vector<vector<int>>& adj, vector<bool>& vis, int& cycleStart) {
    vis[node] = true;
    
    // Iterate through all adjacent nodes using a range-based for loop
    for (auto it : adj[node]) {
        // If the adjacent node is not visited, recursively call DFS
        if (!vis[it]) {
            if (dfs(it, node, adj, vis, cycleStart)) {
                // Backtracking: Print the cycle path
                if (cycleStart == node) {
                    cout << node << " ";
                    cycleStart = -1; // Cycle complete
                } 
                else if (cycleStart != -1) {
                    cout << node << " ";
                }
                return true;
            }
        }
        // If it is visited AND it's not the parent, a cycle is detected
        else if (it != parent) {
            cout << node << " ";    
            cycleStart = it;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    // Assuming 0-based indexing for nodes based on your original code
    cin >> n >> m;
    
    // STL Adjacency List: O(V + E) space instead of O(V^2)
    vector<vector<int>> adj(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }
    
    // Visited array using STL vector
    vector<bool> vis(n, false);
    int cycleStart = -1;
    
    // Striver standard: Always loop through nodes to handle disconnected components
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (dfs(i, -1, adj, vis, cycleStart)) {
                // If a cycle is found in this component, stop searching
                break; 
            }
        }
    }
    
    return 0;
}
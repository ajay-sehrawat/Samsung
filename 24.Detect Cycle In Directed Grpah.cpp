#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// DFS function for Directed Graph Cycle Detection
bool dfs(int node, vector<vector<int>>& adj, vector<bool>& vis, vector<bool>& pathVis, vector<int>& parent, int& cycleStart, int& cycleEnd) {
    vis[node] = true;
    pathVis[node] = true;

    // Traverse all directed neighbors
    for (auto it : adj[node]) {
        // If unvisited, set parent and go deeper
        if (!vis[it]) {
            parent[it] = node;
            if (dfs(it, adj, vis, pathVis, parent, cycleStart, cycleEnd)) {
                return true;
            }
        } 
        // If visited AND on the current path, we found a directed cycle!
        else if (pathVis[it]) {
            cycleStart = it;   // The node where the cycle loops back
            cycleEnd = node;   // The node that connects back to cycleStart
            return true;
        }
    }

    // Backtrack: remove node from the current path
    pathVis[node] = false;
    return false;
}

int main() {
    // Optimize standard I/O operations for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    // CSES problems typically use 1-based indexing
    if (!(cin >> n >> m)) return 0;

    // STL Adjacency List: O(V + E) space
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // Directed edge only u -> v
    }

    vector<bool> vis(n + 1, false);
    vector<bool> pathVis(n + 1, false);
    vector<int> parent(n + 1, -1);
    
    int cycleStart = -1;
    int cycleEnd = -1;

    // Check all components for a cycle
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            if (dfs(i, adj, vis, pathVis, parent, cycleStart, cycleEnd)) {
                break; // Stop at the first detected cycle
            }
        }
    }

    // Output formatting specific to CSES Round Trip II
    if (cycleStart == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        vector<int> cycle;
        cycle.push_back(cycleStart);
        
        // Trace backwards from the end of the cycle to the start
        for (int v = cycleEnd; v != cycleStart; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycleStart); // Complete the loop
        
        // Reverse to print in forward order
        reverse(cycle.begin(), cycle.end());

        cout << cycle.size() << "\n";
        for (int node : cycle) {
            cout << node << " ";
        }
        cout << "\n";
    }

    return 0;
}
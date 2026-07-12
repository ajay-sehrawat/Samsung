#include <iostream>
#include <vector>
#include <utility> // This is the standard library for std::pair

using namespace std;

void solveTestCases() {
    int nodes, edges, time;
    cin >> nodes >> edges >> time;

    // Adjacency List using std::pair. 
    // It is a vector of vectors, where the inner vector holds pairs of <int, double>
    // Pair meaning: <Destination Node, Probability>
    vector<vector<pair<int, double>>> adj(nodes + 1);

    for (int i = 0; i < edges; i++) {
        int from, to;
        double prob;
        cin >> from >> to >> prob;
        
        // We insert a pair into the list for the 'from' node
        adj[from].push_back({to, prob});
    }

    // This vector tracks the probability of being at each node at the CURRENT time
    vector<double> currentProb(nodes + 1, 0.0);
    
    // The doctor always starts at division 1 with 100% probability (1.0)
    currentProb[1] = 1.0;

    // BFS Level-by-Level simulation
    while (time > 0) {
        
        // This vector calculates where the doctor will be after the NEXT 10 minutes
        vector<double> nextProb(nodes + 1, 0.0);

        // Go through every node to see where the doctor can currently be
        for (int u = 1; u <= nodes; u++) {
            
            // If there is a chance the doctor is currently at division 'u'
            if (currentProb[u] > 0.0) {
                
                // Look at all connected divisions for node 'u'
                for (pair<int, double> edge : adj[u]) {
                    
                    // With std::pair, we extract the values using .first and .second
                    int nextNode = edge.first;
                    double pathProb = edge.second;
                    
                    // Add the calculated probability to the next node
                    nextProb[nextNode] += currentProb[u] * pathProb;
                }
            }
        }

        // The 10 minutes have passed. 
        time -= 10;
        
        // Our 'next' probabilities now become our 'current' probabilities for the next loop
        currentProb = nextProb;
    }

    // Time is up! Find the division with the highest probability
    double maxProb = 0.0;
    int bestDivision = 0;

    for (int i = 1; i <= nodes; i++) {
        if (currentProb[i] > maxProb) {
            maxProb = currentProb[i];
            bestDivision = i;
        }
    }

    cout << bestDivision << " " << maxProb << "\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solveTestCases();
    }
    return 0;
}

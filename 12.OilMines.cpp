#include <iostream>
#include <climits>
#include <vector>
#include <algorithm> // Added for std::min and std::max
using namespace std;

int companies, mines, ANS;

// Custom MIN and MAX functions removed; using std::min and std::max instead.

void calculateOilMines(int i, vector<int>& oilMines, vector<bool>& visited, int minV, int maxV, int sum,
                        int nodes, int &ANS){
    // Base Case
    if(visited[i]){
        int newMin = min(sum, minV);
        int newMax = max(sum, maxV);

        if(nodes == companies - 1){
            ANS = min(ANS, newMax - newMin);
        }
        return;
    }

    // Main Case
    visited[i] = true;
    int j = (i + 1) % mines;

    calculateOilMines(j, oilMines, visited, minV, maxV, sum + oilMines[i], nodes, ANS);

    int newMin = min(sum, minV);
    int newMax = max(sum, maxV);

    calculateOilMines(j, oilMines, visited, newMin, newMax, oilMines[i], nodes + 1, ANS);

    visited[i] = false;
    return;
}

int main() {
    int t;
    cin >> t;
    while(t--){
        cin >> companies >> mines;
        
        // Replaced manual memory allocation (new int[]) with STL vectors
        vector<int> oilMines(mines);
        vector<bool> visited(mines, false);

        for(int i=0; i<mines; i++){
            cin >> oilMines[i];
            // visited[i] = false is handled by the vector constructor above
        }
            
        ANS = INT_MAX;    
        for(int i=0; i<mines; i++)
            calculateOilMines(i, oilMines, visited, INT_MAX, INT_MIN, 0, 0, ANS);  

        cout << ANS << endl;        
    }
    return 0;
}
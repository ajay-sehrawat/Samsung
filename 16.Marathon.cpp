#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A simple struct to hold our pace data cleanly
struct Pace {
    int time;
    int energy;
};

int main() {
    // Optimize standard I/O operations
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int testCase = 1; testCase <= t; testCase++) {
        int D, H;
        cin >> D >> H;

        // Use STL vector to store the 5 paces
        vector<Pace> paces(5);
        for (int i = 0; i < 5; i++) {
            int minv, sec, energy;
            cin >> minv >> sec >> energy;
            // Convert everything to seconds immediately for easier math
            paces[i] = {minv * 60 + sec, energy}; 
        }

        // dp[d][h] stores the minimum time to run 'd' kilometers using EXACTLY 'h' energy.
        // We use an arbitrarily large number (1e9) to represent "impossible states".
        const int INF = 1e9;
        
        // Create a 2D STL vector initialized to INF
        vector<vector<int>> dp(D + 1, vector<int>(H + 1, INF));
        
        // Base case: Running 0 km takes 0 time and consumes 0 energy.
        dp[0][0] = 0;

        // Build the DP table
        for (int d = 1; d <= D; d++) {              // For every kilometer to run
            for (int h = 0; h <= H; h++) {          // For every possible energy state
                for (const auto& p : paces) {       // Try every pace for this 1 km stretch
                    
                    // If we have enough energy for this pace, and the previous state was valid
                    if (h >= p.energy && dp[d - 1][h - p.energy] != INF) {
                        dp[d][h] = min(dp[d][h], dp[d - 1][h - p.energy] + p.time);
                    }
                }
            }
        }

        // Find the absolute minimum time to finish distance D using ANY energy <= H
        int minTime = INF;
        for (int h = 0; h <= H; h++) {
            minTime = min(minTime, dp[D][h]);
        }

        // Output the result in the required format
        cout << "#" << testCase << " " << minTime / 60 << " " << minTime % 60 << "\n";
    }

    return 0;
}
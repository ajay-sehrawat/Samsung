#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Global variables to store the best answer and raw prices for the current testcase
int max_profit;
int d_price, e_price;

// Recursive function to try all valid combinations of configurations
void solve_configs(int index, int types_used, int current_D, int current_E, int current_F, int current_profit, const vector<vector<int>>& configs) {
    
    // At any state, we can calculate the profit if we stop building right now 
    // and just sell the remaining raw CPUs and Memory chips.
    int final_profit = current_profit + (current_D * d_price) + (current_E * e_price);
    max_profit = max(max_profit, final_profit);

    // Base Case: If we have evaluated all configurations or we've reached the limit of 3 distinct types
    if (index >= configs.size() || types_used == 3) {
        return;
    }

    // Choice 1: Skip this configuration completely and move to the next one
    solve_configs(index + 1, types_used, current_D, current_E, current_F, current_profit, configs);

    // Choice 2: Try building this configuration 1 time, 2 times, 3 times... etc.
    int req_D = configs[index][0];
    int req_E = configs[index][1];
    int req_F = configs[index][2];
    int sell_price = configs[index][3];

    int build_count = 1;
    
    while (true) {
        int total_D = req_D * build_count;
        int total_E = req_E * build_count;
        int total_F = req_F * build_count;

        // Check if we have enough raw materials to build 'build_count' units
        if (current_D >= total_D && current_E >= total_E && current_F >= total_F) {
            
            // Recurse: Move to next index, increase types_used by exactly 1, and subtract materials
            solve_configs(
                index + 1, 
                types_used + 1, 
                current_D - total_D, 
                current_E - total_E, 
                current_F - total_F, 
                current_profit + (sell_price * build_count), 
                configs
            );
            
            // Increment to try building one more of this exact same configuration
            build_count++; 
        } 
        else {
            // We ran out of materials to build any more of this configuration
            break; 
        }
    }
}

int main() {
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;
    
    for (int case_num = 1; case_num <= t; ++case_num) {
        int D, E, F;
        cin >> D >> E >> F >> d_price >> e_price;
        
        int n;
        cin >> n;
        
        // configs will hold 'n' rows and 4 columns (req_D, req_E, req_F, sell_price)
        vector<vector<int>> configs(n, vector<int>(4));
        for (int i = 0; i < n; ++i) {
            cin >> configs[i][0] >> configs[i][1] >> configs[i][2] >> configs[i][3];
        }
        
        max_profit = 0;
        
        // Start from index 0, using 0 types so far, with full inventory and 0 initial profit
        solve_configs(0, 0, D, E, F, 0, configs);
        
        // Output exactly in the requested format
        cout << "Case #" << case_num << "\n" << max_profit << "\n";
    }
    
    return 0;
}
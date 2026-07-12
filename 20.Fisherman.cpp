#include <iostream>
using namespace std;

/*
=========================================================
PROBLEM STATEMENT: Fishing Spots Allocation
=========================================================
Description:
There are N fishing spots arranged in a straight line, numbered 
from 1 to N. There are 3 gates, each located at a specific 
fishing spot, with a certain number of fishermen waiting.

When a gate opens, fishermen enter and occupy the closest 
available empty spots. The distance walked is calculated as:
Distance = |Spot - Gate| + 1

Fishermen always choose the closest empty spot. If there is a tie 
(an empty spot to the left and right at the exact same distance) 
AND there is only one fisherman left to place from that gate, 
the fisherman can choose EITHER spot. 

Objective:
Find the minimum total distance walked by all fishermen across 
all possible gate opening orders and tie-breaking choices.

Input Details:
- Total number of fishing spots (N).
- For each of the 3 gates: Gate position and number of fishermen.

Output Details:
- A single integer representing the minimum total distance.
=========================================================
*/

// --- Global Variables ---
int N;
int gate_pos[4];       // Positions of the 3 gates (1-indexed)
int fishermen_cnt[4];  // Number of fishermen at the 3 gates (1-indexed)
bool visited_gate[4];  // Keeps track of which gates have been opened
bool spot_occupied[105]; // Keeps track of which fishing spots are taken
int min_total_distance;

// --- Recursive Function to explore all combinations ---
void solve(int gates_opened, int current_dist) {
    // Optimization: If our current distance is already worse than the best 
    // answer we've found so far, stop exploring this path.
    if (current_dist >= min_total_distance) {
        return; 
    }

    // Base Case: If all 3 gates have been opened, check if we found a new minimum
    if (gates_opened == 3) {
        if (current_dist < min_total_distance) {
            min_total_distance = current_dist;
        }
        return;
    }

    // Try opening each of the 3 gates
    for (int i = 1; i <= 3; i++) {
        if (!visited_gate[i]) {
            // 1. Mark this gate as visited
            visited_gate[i] = true;

            int pos = gate_pos[i];
            int f = fishermen_cnt[i];
            
            // Save the current state of the fishing spots before we place fishermen.
            // We need this so we can easily "undo" our placements later (backtracking).
            bool temp_spots[105];
            for (int s = 1; s <= N; s++) {
                temp_spots[s] = spot_occupied[s];
            }

            int added_dist = 0;
            bool branched = false;

            // 2. Place the fishermen by checking distances starting from 0 up to N
            for (int d = 0; d <= N; d++) {
                int left_spot = pos - d;
                int right_spot = pos + d;
                
                // Check if the spots are within bounds and empty
                bool left_valid = (left_spot >= 1 && !spot_occupied[left_spot]);
                bool right_valid = (right_spot <= N && !spot_occupied[right_spot]);

                if (d == 0) {
                    // Distance 0 means the exact spot where the gate is
                    if (left_valid && f > 0) {
                        spot_occupied[pos] = true;
                        added_dist += 1;
                        f--;
                    }
                } else {
                    // TIE BREAKER: Two valid spots at the same distance, but only 1 fisherman left!
                    if (left_valid && right_valid && f == 1) {
                        
                        // Path A: Put the last fisherman in the Left spot
                        spot_occupied[left_spot] = true;
                        solve(gates_opened + 1, current_dist + added_dist + d + 1);
                        spot_occupied[left_spot] = false; // Undo Path A
                        
                        // Path B: Put the last fisherman in the Right spot
                        spot_occupied[right_spot] = true;
                        solve(gates_opened + 1, current_dist + added_dist + d + 1);
                        spot_occupied[right_spot] = false; // Undo Path B
                        
                        branched = true; // We handled the next steps inside the branches
                        break; 
                    } 
                    // Normal Placement: No tie-breaker needed, greedily take available spots
                    else {
                        if (left_valid && f > 0) {
                            spot_occupied[left_spot] = true;
                            added_dist += (d + 1);
                            f--;
                        }
                        if (right_valid && f > 0) {
                            spot_occupied[right_spot] = true;
                            added_dist += (d + 1);
                            f--;
                        }
                    }
                }
                
                // If all fishermen for this gate are placed, stop searching outward
                if (f == 0) {
                    break; 
                }
            }

            // 3. Move to the next gate (only if we didn't branch due to a tie-breaker)
            if (!branched) {
                solve(gates_opened + 1, current_dist + added_dist);
            }

            // 4. Backtrack: Restore the spots and gate status so the next loop iteration starts clean
            for (int s = 1; s <= N; s++) {
                spot_occupied[s] = temp_spots[s];
            }
            visited_gate[i] = false;
        }
    }
}

int main() {
    // Initialization
    N = 10;
    min_total_distance = 999999;
    
    for (int i = 1; i <= N; i++) {
        spot_occupied[i] = false;
    }
    for (int i = 1; i <= 3; i++) {
        visited_gate[i] = false;
    }

    // Input Data (1-based indexing for the 3 gates)
    gate_pos[1] = 4;
    fishermen_cnt[1] = 5;

    gate_pos[2] = 6;
    fishermen_cnt[2] = 2;

    gate_pos[3] = 10;
    fishermen_cnt[3] = 2;

    // Start recursion: 0 gates opened, 0 current distance
    solve(0, 0);

    // Output Result
    cout << min_total_distance << endl;

    return 0;
}
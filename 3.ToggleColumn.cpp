#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

void solve(int testcase) {
    int r, c, k;
    cin >> r >> c >> k;

    // Maps a row string to its frequency count
    unordered_map<string, int> row_frequency;
    int max_all_ones = 0;

    for (int i = 0; i < r; i++) {
        string current_row = "";
        int zeros_count = 0;
        
        for (int j = 0; j < c; j++) {
            char val;
            cin >> val;
            current_row += val; // Build the string representation of the row
            
            if (val == '0') {
                zeros_count++;
            }
        }

        // Rule 1: We must have enough flips to target all 0s (zeros_count <= k)
        // Rule 2: Leftover flips must be even to cancel themselves out ((k - zeros_count) % 2 == 0)
        if (zeros_count <= k && (k - zeros_count) % 2 == 0) {
            
            row_frequency[current_row]++; // Increment the count of this specific row pattern
            
            // Keep track of the maximum frequency found so far
            max_all_ones = max(max_all_ones, row_frequency[current_row]);
        }
    }

    cout << "#" << testcase << " " << max_all_ones << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; i++) {
            solve(i);
        }
    }
    return 0;
}
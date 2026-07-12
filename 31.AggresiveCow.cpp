#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// This function checks if it is possible to place 'c' cows 
// with at least 'mid' distance between any two of them.
// We pass the vector by reference (&) so we don't waste time copying it.
bool check(int mid, int n, int c, const vector<int>& a) {
    int cows_placed = 1;      // We always place the first cow in the first stall
    int last_pos = a[0];      // Keep track of where we placed the last cow
    
    for (int i = 1; i < n; i++) {
        // If the distance from the last placed cow is at least 'mid'
        if (a[i] - last_pos >= mid) {
            cows_placed++;        // Place another cow
            last_pos = a[i];      // Update the position of the last placed cow
            
            // If we successfully placed all cows, this distance 'mid' works!
            if (cows_placed == c) {
                return true;
            }
        }
    }
    
    // If the loop finishes and we couldn't place all cows, 'mid' is too big
    return false;
}

void solve() {
    int n, c;
    cin >> n >> c;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Step 1: Sort the array so we can place cows from left to right
    sort(a.begin(), a.end());

    // Step 2: Binary search on the answer
    int l = 1;                        // Minimum possible distance
    int r = a[n-1] - a[0];            // Maximum possible distance (ends of the array)
    int ans = 1;                      // Variable to store our best valid answer
    
    while (l <= r) {
        int mid = l + (r - l) / 2;
        
        if (check(mid, n, c, a)) {
            ans = mid;     // This distance works, save it!
            l = mid + 1;   // Now try to find a BIGGER distance
        } else {
            r = mid - 1;   // This distance failed, we must try a SMALLER distance
        }
    }

    cout << ans << '\n';
}

int main() {
    // Fast I/O for Codeforces
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
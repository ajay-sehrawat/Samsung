#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to calculate points gained when balloon 'k' is popped LAST 
// between the boundaries 'left' and 'right'.
int calculatePoints(const vector<int>& A, int left, int right, int k) {
    int n = A.size();
    
    // Rule 4: No left, no right (it is the absolute last balloon)
    if (left == -1 && right == n) {
        return A[k];
    }
    // Rule 3: No left exists, only right
    if (left == -1) {
        return A[right];
    }
    // Rule 2: No right exists, only left
    if (right == n) {
        return A[left];
    }
    // Rule 1: Both left and right exist
    return A[left] * A[right];
}

// Top-Down DP function
int solve(const vector<int>& A, int left, int right, vector<vector<int>>& memo) {
    // Base case: There are no balloons left to pop strictly between left and right
    if (left + 1 == right) {
        return 0;
    }

    // Memoization check: +1 is used because 'left' can be -1. 
    // This maps our indices safely from 0 to n+1.
    if (memo[left + 1][right + 1] != -1) {
        return memo[left + 1][right + 1];
    }

    int maxCoins = 0;

    // Try making every balloon in the range (left, right) the LAST one to pop
    for (int k = left + 1; k < right; ++k) {
        
        // Solve for the left chunk
        int leftSide = solve(A, left, k, memo);
        
        // Solve for the right chunk
        int rightSide = solve(A, k, right, memo);
        
        // Points for popping k itself as the last balloon in this range
        int currentPop = calculatePoints(A, left, right, k);

        // Maximize the total
        int total = leftSide + rightSide + currentPop;
        maxCoins = max(maxCoins, total);
    }

    // Save and return the result
    return memo[left + 1][right + 1] = maxCoins;
}

// Wrapper function to initialize memoization table
int getMaxScore(vector<int>& A) {
    int n = A.size();
    
    // Create a 2D vector initialized with -1. 
    // Size is (n + 2) x (n + 2) to safely handle the -1 and n boundaries.
    vector<vector<int>> memo(n + 2, vector<int>(n + 2, -1));

    // We want to pop everything strictly between index -1 and index n
    return solve(A, -1, n, memo);
}

int main() {
    // Input-1
    vector<int> A1 = {1, 2, 3, 4};
    cout << "Output for Input-1: " << getMaxScore(A1) << "\n"; // Expected: 20

    // Input-2
    vector<int> A2 = {1, 0, 2, 3, 0, 4};
    cout << "Output for Input-2: " << getMaxScore(A2) << "\n"; // Expected: 34

    return 0;
}
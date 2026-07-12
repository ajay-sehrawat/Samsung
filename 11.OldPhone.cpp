#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Special constants so our code is easy to read.
const int EMPTY = -9999999; 
const int INVALID = -8888888; // Used to handle division by zero errors

// Global variables to store the inputs for the current test case
int max_touches;
int target_val;
int min_touches;

vector<int> working_digits;
vector<int> working_ops;

// A simple helper function to do the math. 
// 1 = Add, 2 = Subtract, 3 = Multiply, 4 = Divide
int doMath(int left, int right, int op) {
    if (op == 1) return left + right;
    if (op == 2) return left - right;
    if (op == 3) return left * right;
    if (op == 4) {
        if (right == 0) return INVALID; // You can't divide by zero!
        return left / right;
    }
    return 0;
}

// ---------------------------------------------------------
// The core logic: Mimics a human typing on a calculator
// ---------------------------------------------------------
void useCalculator(int display, int saved, int pending_op, int touches) {
    
    // Stop exploring if we ran out of allowed touches
    if (touches > max_touches) return;

    // --- CHECK IF WE WON ---

    // Scenario 1: We hit the '=' button right now. 
    // (We must have a pending operation and a number on the display to do this).
    if (pending_op != 0 && display != EMPTY) {
        int final_result = doMath(saved, display, pending_op);
        
        if (final_result == target_val) {
            // We succeeded! Update our record. 
            // We add +1 to touches because hitting the '=' button costs 1 touch.
            min_touches = min(min_touches, touches + 1); 
        }
    }

    // Scenario 2: We typed the number perfectly without needing math! (e.g., typing "18")
    if (pending_op == 0 && display == target_val) {
        min_touches = min(min_touches, touches);
    }

    // --- TRY PRESSING BUTTONS ---

    // Move A: Try pressing a Digit (0-9)
    for (int digit : working_digits) {
        int next_display;
        
        if (display == EMPTY) {
            next_display = digit; // Start a new number
        } else {
            next_display = (display * 10) + digit; // Append to screen: 4 then 5 makes 45
        }
        
        // Recurse (simulate pressing the button)
        useCalculator(next_display, saved, pending_op, touches + 1);
    }

    // Move B: Try pressing an Operator (+, -, *, /)
    // You can only press an operator if there is actually a number on the screen.
    if (display != EMPTY) {
        for (int op : working_ops) {
            
            int next_saved = display; 
            
            // If we ALREADY had a pending operation (like typing 5 + 3 + ... )
            // Calculate the 5 + 3 first before moving on!
            if (pending_op != 0) {
                next_saved = doMath(saved, display, pending_op);
            }
            
            // As long as we didn't cause a divide-by-zero error, keep going.
            if (next_saved != INVALID) {
                // The display becomes EMPTY because we are ready to type the next number.
                useCalculator(EMPTY, next_saved, op, touches + 1);
            }
        }
    }
}

int main() {
    int testcases;
    if (!(cin >> testcases)) return 0;
    
    int count = 1;
    while (testcases--) {
        int n, m;
        cin >> n >> m >> max_touches;
        
        // Reset for the new test case
        min_touches = 9999999; 
        working_digits.clear();
        working_ops.clear();
        
        // Read working digits
        for (int i = 0; i < n; i++) {
            int digit;
            cin >> digit;
            working_digits.push_back(digit);
        }
        
        // Read working operations
        for (int i = 0; i < m; i++) {
            int op;
            cin >> op;
            working_ops.push_back(op);
        }
        
        cin >> target_val;
        
        // Start playing with the calculator! 
        // Display is EMPTY, Saved is 0, No pending Op (0), Touches used = 0
        useCalculator(EMPTY, 0, 0, 0);
        
        // Output the result
        cout << "#" << count << ": ";
        if (min_touches == 9999999) {
            cout << -1 << endl; // Impossible to reach the target
        } else {
            cout << min_touches << endl;
        }
        count++;
    }
    
    return 0;
}
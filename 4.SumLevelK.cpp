#include <iostream>
#include <string>
#include <cctype> // For isdigit()

using namespace std;

int main() {
    int target_depth;
    string tree_str;
    
    cin >> target_depth >> tree_str;
    
    int current_depth = -1; 
    long long total_sum = 0;
    
    for (int i = 0; i < tree_str.length(); i++) {
        
        if (tree_str[i] == '(') {
            // Going one level deeper into the tree
            current_depth++;
        } 
        else if (tree_str[i] == ')') {
            // Coming back up one level
            current_depth--;
        } 
        else {
            // We found a number (starts with a digit or a minus sign)
            int sign = 1;
            long long num = 0;
            
            // Check for negative numbers
            if (tree_str[i] == '-') {
                sign = -1;
                i++; // Move to the first digit
            }
            
            // Build the number digit by digit
            while (i < tree_str.length() && isdigit(tree_str[i])) {
                num = (num * 10) + (tree_str[i] - '0');
                i++; // Move to the next character
            }
            
            // The while loop stops when it hits a non-digit (like a '(' or ')').
            // We need to step back by 1 so the outer for-loop doesn't skip it.
            i--; 
            
            num *= sign; // Apply the negative sign if it had one
            
            // If we are at the correct depth, add it to our sum
            if (current_depth == target_depth) {
                total_sum += num;
            }
        }
    }
    
    cout << total_sum << endl;
    return 0;
}
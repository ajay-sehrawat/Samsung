#include <iostream>
#include <vector>

using namespace std;

// We pass white_count and blue_count by reference (&) so the function can update the actual variables
void cut_paper(const vector<vector<int>>& grid, int row, int col, int size, int& white_count, int& blue_count) {
    
    // 1. Record the color of the very first cell in our current boundary
    int first_color = grid[row][col];
    bool is_mixed = false;

    // 2. Check if all cells in this specific boundary match the first_color
    for (int i = row; i < row + size; ++i) {
        for (int j = col; j < col + size; ++j) {
            if (grid[i][j] != first_color) {
                is_mixed = true;
                break; 
            }
        }
        if (is_mixed) break; // Optimization: stop checking immediately if a mismatch is found
    }

    // 3. If colors are mixed, divide the paper into 4 smaller quadrants
    if (is_mixed) {
        int half = size / 2;
        
        // Recursive calls for each of the 4 new smaller pieces
        cut_paper(grid, row, col, half, white_count, blue_count);               // Top-Left
        cut_paper(grid, row, col + half, half, white_count, blue_count);        // Top-Right
        cut_paper(grid, row + half, col, half, white_count, blue_count);        // Bottom-Left
        cut_paper(grid, row + half, col + half, half, white_count, blue_count); // Bottom-Right
    } 
    // 4. If all cells are the exact same color, we have one solid piece!
    else {
        if (first_color == 0) {
            white_count++;
        } else {
            blue_count++;
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
        int n;
        cin >> n;

        // Use a 2D std::vector instead of raw arrays to prevent memory leaks and variable length array issues
        vector<vector<int>> grid(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
            }
        }

        int white_pieces = 0;
        int blue_pieces = 0;

        // Start checking from the top-left corner (0,0) with the full size of the grid (n)
        cut_paper(grid, 0, 0, n, white_pieces, blue_pieces);

        // Output exactly as required
        cout << "Case #" << case_num << "\n";
        cout << white_pieces << " " << blue_pieces << "\n";
    }

    return 0;
}
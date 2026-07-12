#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

// Passed by reference so the local copy in findMaxPoints gets updated
void updateMatrix(int row, vector<vector<char>>& matrix) {
    if (row < 0) {
        return;
    }
    int upLimit = max(0, row - 4);
    for (int i = row; i >= upLimit; i--) {
        for (int j = 0; j <= 4; j++) {
            if (matrix[i][j] == '2') {
                matrix[i][j] = '0';
            }
        }
    }
}

// Passed by value so each recursive branch has its own state of the board
int findMaxPoints(int row, int col, int bombs, vector<vector<char>> matrix) {
    if (row <= 0 || col < 0 || col >= 5) {
        return 0;
    }
    
    int answer = 0;
    
    // Move up
    if (row > 0 && matrix[row - 1][col] != '2') {
        answer = max(answer, (matrix[row - 1][col] == '1' ? 1 : 0) + findMaxPoints(row - 1, col, bombs, matrix));
    }
    // Move up-left
    if (col > 0 && row > 0 && matrix[row - 1][col - 1] != '2') {
        answer = max(answer, (matrix[row - 1][col - 1] == '1' ? 1 : 0) + findMaxPoints(row - 1, col - 1, bombs, matrix));
    }
    // Move up-right
    if (col < 4 && row > 0 && matrix[row - 1][col + 1] != '2') {
        answer = max(answer, (matrix[row - 1][col + 1] == '1' ? 1 : 0) + findMaxPoints(row - 1, col + 1, bombs, matrix));
    }

    // Use bomb if no other safe moves exist
    if (answer == 0 && bombs > 0) {
        updateMatrix(row - 1, matrix);
        answer = findMaxPoints(row, col, bombs - 1, matrix);
    }

    return answer;
}

int main() {
    int t, row;
    cin >> t;
    int tNo = 0;
    
    while (t--) {
        cin >> row;
        
        // Initialize a 2D vector of size `row` x 5
        vector<vector<char>> matrix(row, vector<char>(5));
        
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < 5; j++) {
                cin >> matrix[i][j];
            }
        }
        
        tNo++;
        // Starting position: row = N, col = 2 (center), bombs = 1
        cout << "#" << tNo << " : " << findMaxPoints(row, 2, 1, matrix) << endl;        
    }
    return 0;
}
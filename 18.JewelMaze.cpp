#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int n, ans;

bool isValid(int i, int j) {
   return (i >= 0 && i < n && j >= 0 && j < n);
}

// Passed by const reference to avoid unnecessary copying
void printMatrix(const vector<vector<int>>& arr) {
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < n; j++)
           cout << arr[i][j] << " ";
       cout << endl;
   }
}

int dirX[] = {1, 0, -1, 0};
int dirY[] = {0, 1, 0, -1};

// Vectors passed by reference to maintain state across recursive calls
void jewelMaze(const vector<vector<int>>& maze, int x, int y, int value, vector<vector<int>>& visited, vector<vector<int>>& path) {
   if (x == n - 1 && y == n - 1) {
       if (value >= ans) {
           ans = value;
          
           for (int i = 0; i < n; i++) {
               for (int j = 0; j < n; j++) {
                   if (visited[i][j]) {
                       path[i][j] = 3;
                   } else {
                       path[i][j] = maze[i][j];
                   }
               }
           }
       }
       return;
   }

   for (int i = 0; i < 4; i++) {
       int newX = x + dirX[i];
       int newY = y + dirY[i];
      
       if (isValid(newX, newY)) {
           if (visited[newX][newY] == 0 && maze[newX][newY] == 0) {
               visited[newX][newY] = 1;
               jewelMaze(maze, newX, newY, value, visited, path);
               visited[newX][newY] = 0;
           }
          
           if (visited[newX][newY] == 0 && maze[newX][newY] == 2) {
               visited[newX][newY] = 1;
               jewelMaze(maze, newX, newY, value + 1, visited, path);
               visited[newX][newY] = 0;
           }
       }
   }
}

int main() {
   int t;
   if (!(cin >> t)) return 0;
  
   while (t--) {
       cin >> n;
      
       // Initializing 2D vectors of size N x N with default value 0
       vector<vector<int>> maze(n, vector<int>(n, 0));
       vector<vector<int>> visited(n, vector<int>(n, 0));
       vector<vector<int>> path(n, vector<int>(n, 0));

       // Input Maze
       for (int i = 0; i < n; i++) {
           for (int j = 0; j < n; j++) {
               cin >> maze[i][j];
               // Visited and Path vectors are already initialized to 0 above
           }
       }
      
       ans = INT_MIN;
      
       int sX = 0, sY = 0;
       visited[sX][sY] = 1;
      
       if (maze[sX][sY] == 2)
           jewelMaze(maze, sX, sY, 1, visited, path);
       else
           jewelMaze(maze, sX, sY, 0, visited, path);
          
       cout << "Jewel collected : " << ans << endl;
       cout << "Path traversed --> " << endl;
       printMatrix(path);
      
       cout << endl;
   }
   return 0;
}

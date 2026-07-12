#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INT_MAX 100000 // Kept from your original code

// Global variables just like your original code
int xb, yb, xt, yt;

// Changed dp from a 2D array pointer to a const vector reference
int fun(const vector<vector<int>>& dp, int N, int M, int k){
	int msum = INT_MAX;
	for(int i=0; i<=N-k; i++){
		for(int j=0; j<=M-k; j++){
            // O(1) query to get sinkholes in a k x k square
			int sum = dp[i+k][j+k] - dp[i+k][j] - dp[i][j+k] + dp[i][j];
			
            if(sum < msum){
				msum = sum;
				if(msum <= 1){
					xb = i + k;
					yb = j + 1;
					xt = i + 1;
					yt = j + k;
				}
			}
		}
	}
	return msum;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
    // Added loop to handle multiple test cases as required by the problem
    int T;
    if (!(cin >> T)) return 0;

    for (int t = 1; t <= T; t++) {
        /* input */
        int N, M;
        cin >> N >> M;
        
        // REPLACED: int A[N][M];
        // STL vector automatically handles memory on the heap and initializes all values to 0
        vector<vector<int>> A(N, vector<int>(M, 0));
        
        int K;
        cin >> K;
        for(int i=0; i<K; i++){
            int x, y;
            cin >> x >> y;
            A[x-1][y-1] = 1;
        }
        
        // REPLACED: int dp[1001][1001];
        // Created dynamically sized vector based on N+1 and M+1, fully initialized to 0
        vector<vector<int>> dp(N + 1, vector<int>(M + 1, 0));
        
        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + A[i-1][j-1];
            }
        }
        
        /* applying binary search */
        int l = 1, r = min(M, N);
        int ones;
        while(l < r){
            int mid = (l + r) / 2;
            ones = fun(dp, N, M, mid);
            
            // if no. of ones > 1 means we need to decrease the submatrix size 
            if(ones > 1){
                r = mid;
            }
            // else increase the submatrix size
            else{
                l = mid + 1;
            }
        }
        
        /* output */
        cout << "#" << t << " " << xb << " " << yb << " " << xt << " " << yt << "\n";
    }
	return 0;
}
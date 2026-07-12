#include <iostream>
#include <vector>
#include <algorithm> // Required for std::max

using namespace std;

int maxCoins(vector<int>& nums) {
    /* O(n^3) Time and O(n^2) Space */
    int size = nums.size();
    if(size == 0)
        return 0;
        
    int i, j, k;
    
    // STL 2D Vector initialized to 0
    vector< vector<int> > dp(size, vector<int>(size, 0));
       
    for(int len = 1; len <= size; len++){
        for(i = 0; i <= size - len; i++){
            j = len + i - 1;
            for(k = i; k <= j; k++){ 
                /* Left/Right Value has default 1 but holds prev and after balloon value if k is in middle */
                int leftValue  = 1;
                int rightValue = 1;
                    
                if(i != 0)
                    leftValue  = nums[i-1];
                if(j != size-1)
                    rightValue = nums[j+1];
                        
                /* Before and After - current k balloon is last to burst select the left side and right side to burst */
                int before = 0;
                int after  = 0;
                    
                if(i != k)
                    before = dp[i][k-1];
                if(j != k)
                    after  = dp[k+1][j];
                    
                dp[i][j] = max(dp[i][j], 
                         leftValue * nums[k] * rightValue + before + after);
            }   
        }
    }    
    return dp[0][size-1];
}
int main() {
    int siz;
    cin >> siz;
    
    // Replaced VLA with std::vector for dynamic sizing
    vector<int> A(siz);
    for (int i = 0; i < siz; i++) {
        cin >> A[i];
    }

    int ans = maxCoins(A);
    cout << ans << endl;
    return 0;
}
//Solution 1 - Recrsive 
#include <iostream>
using namespace std;

void solve(int a[], vector<int> &vis, int p1, int p2, int n, int &ans){
    if(p1 == p2){
        if(p1 > ans){
            ans = p1;
        }
    }


    for(int i=0 ; i<n ; ++i){
        if(vis[i] == 0){
            vis[i] = 1;
            solve(a, vis, p1 + a[i], p2, n, ans);          // Try putting it on Pillar 1
            solve(a, vis, p1, p2 + a[i], n, ans);          // Try putting it on Pillar 2
            vis[i] = 0;
        }
    }
}

int main(){
    int n;
    cin>>n;
    int a[n];

    for(int i=0 ; i<n ; ++i){
        cin>>a[i];
    }

    vector<int> vis(n,0);
    int ans = -1;
    solve(a,vis,0,0,n,ans);

    cout<<ans;
}


//Solution 2 - Iterative 
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    
    for(int i = 0 ; i < n ; ++i){
        cin >> a[i];
    }

    int ans = -1;
    
    // Calculate 3^n (Total number of combinations)
    long long total_combinations = pow(3, n);

    // Loop through every single combination
    for(long long i = 0; i < total_combinations; ++i) {
        int p1 = 0;
        int p2 = 0;
        
        // We use a temporary variable to extract base-3 digits
        long long temp = i; 

        for(int j = 0; j < n; ++j) {
            int choice = temp % 3;
            temp /= 3; 

            if(choice == 1) {
                p1 += a[j];        // Put piece 'j' on Pillar 1
            } else if(choice == 2) {
                p2 += a[j];        // Put piece 'j' on Pillar 2
            }
            // If choice == 0, we do nothing (the piece is left on the ground)
        }

        // After placing all pieces for this combination, check if they are equal
        if(p1 == p2) {
            if(p1 > ans) {
                ans = p1;
            }
        }
    }

    // The problem statement expects 0 if no valid combination is found
    if (ans == -1) {
        ans = 0;
    }

    cout << ans << endl;
    return 0;
}
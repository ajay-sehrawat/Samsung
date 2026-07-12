#include <iostream>
#include <vector> // Include vector
using namespace std;

// Pass the vector by constant reference to avoid copying
int numberOminous(int a, int b, int k, const vector<int>& delNos) {
    int count = 0;
    for(int i = a; i <= b; i++){
        int temp = i;
        int digitArray[10] = {0};

        if (temp == 0) 
        {
            digitArray[0]++; 
        } 
        else 
        {
            while(temp > 0) {
                digitArray[temp % 10]++;
                temp /= 10;
            }
        }
        
        int rougeK = 0;
        // You can use the vector's size() instead of passing 'n' separately
        for(int j = 0; j < delNos.size(); j++){ 
            rougeK += digitArray[delNos[j]];
        }

        if(rougeK < k){
            count++;
        }
    }
    return count;
}

int main() {
    int a, b, k, n;
    cin >> a >> b >> k;
    cin >> n;
    
    // Create a vector of size 'n'
    vector<int> delNos(n); 
    for(int i = 0; i < n; i++){
        cin >> delNos[i];
    }

    cout << numberOminous(a, b, k, delNos) << "\n";

    return 0;
}
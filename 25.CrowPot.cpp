#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<int> overflow(n);
    for( int i=0; i<n; i++ )
        cin>>overflow[i];
    int k;
    cin>>k;

    sort(overflow.begin(),overflow.end());
    int noStones = 0;

    for( int i=0; i<k; i++ )
        noStones += overflow[i];

    noStones = noStones + (n-k)*overflow[k-1];
    cout<<noStones;
}
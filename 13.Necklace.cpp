#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int solve(string s, int n)
{
    unordered_map<int, int> mpp;
    mpp[0] = -1;
    int balance = 0;
    int maxLen = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'R')
        {
            balance--;
        }
        else
        {
            balance++;
        }

        if (mpp.find(balance) != mpp.end())
        {
            if (i >= n && mpp[balance] < n)
            {
                int len = i - mpp[balance];
                maxLen = max(maxLen, len);
            }
        }
        else
        {
            mpp[balance] = i;
        }
    }
    return s.length() - maxLen;
}

int main(int argc, char const *argv[])
{
    int testCases;
    cin >> testCases;

    for (int i = 0; i < testCases; i++)
    {
        int n;
        string s;
        cin >> n;
        cin >> s;

        int res = solve(s, n);
        cout << "#" << i << " " << res << endl;
    }
    return 0;
}
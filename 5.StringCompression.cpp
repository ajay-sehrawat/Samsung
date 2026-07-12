#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

void mergeAlpha(const string& str) {
    // std::map automatically keeps keys sorted in alphabetical order
    map<char, int> charCounts;

    for (size_t i = 0; i < str.length(); i++) { 
    char letter = str[i];
    i++;
    
    int count = 0;
    while (i < str.length() && isdigit(str[i])) {
        count = (count * 10) + (str[i] - '0');
        i++;
    }
    i--; // Now this is necessary again!
    
    charCounts[letter] += count; 
}

    // Range-based for loop to cleanly iterate through the map
    for (const auto& pair : charCounts) {
        cout << pair.first << " " << pair.second << " ";
    }
    cout << endl;
}

int main() {
    string s;
    // Safely read into a dynamically sized std::string
    if (cin >> s) {
        mergeAlpha(s);
    }
    return 0;
}
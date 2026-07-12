#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // For std::pair

using namespace std;

// Cross product to find the turn direction
// .first is our X coordinate, .second is our Y coordinate
long long crossProduct(pair<long long, long long> O, 
                       pair<long long, long long> A, 
                       pair<long long, long long> B) {
    return (A.first - O.first) * (B.second - O.second) - 
           (A.second - O.second) * (B.first - O.first);
}

void solve() {
    int n;
    cin >> n;
    
    // Using pair explicitly for the points
    vector<pair<long long, long long>> points(n);
    
    for (int i = 0; i < n; i++) {
        // We read directly into .first (X) and .second (Y)
        cin >> points[i].first >> points[i].second;
    }

    if (n < 3) {
        cout << -1 << "\n";
        return;
    }

    // Step 1: Sort points from left to right. 
    // std::pair automatically sorts by .first (X), then by .second (Y) if tied!
    sort(points.begin(), points.end());

    // Step 2: Remove duplicates. std::pair automatically knows how to check for equality.
    points.erase(unique(points.begin(), points.end()), points.end());
    
    if (points.size() < 3) {
        cout << -1 << "\n";
        return;
    }

    // Step 3: Build the Convex Hull
    // Using pair explicitly for the hull
    vector<pair<long long, long long>> hull;

    // Build the Lower Hull
    for (int i = 0; i < points.size(); i++) {
        while (hull.size() >= 2 && crossProduct(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    // Build the Upper Hull
    int lower_hull_size = hull.size();
    for (int i = points.size() - 2; i >= 0; i--) {
        while (hull.size() > lower_hull_size && crossProduct(hull[hull.size()-2], hull.back(), points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    hull.pop_back();

    if (hull.size() < 3) {
        cout << -1 << "\n";
        return;
    }

    // Step 4: Sort lexicographically for the required output format
    sort(hull.begin(), hull.end());

    // Step 5: Print the formatted result
    for (int i = 0; i < hull.size(); i++) {
        cout << hull[i].first << " " << hull[i].second;
        if (i != hull.size() - 1) {
            cout << ", ";
        }
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
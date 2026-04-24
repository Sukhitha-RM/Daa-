#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

// Solve TSP using DP + Bitmask
int tsp(int mask, int pos, vector<vector<int>> &dist, vector<vector<int>> &dp) {
    int n = dist.size();
    
    // Base Case: All cities visited, return to start (city 0)
    if (mask == (1 << n) - 1) {
        return dist[pos][0];
    }

    // Memoization check
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int ans = INF;
    for (int city = 0; city < n; city++) {
        // If city has not been visited yet
        if (!(mask & (1 << city))) {
            int newAns = dist[pos][city] + tsp(mask | (1 << city), city, dist, dp);
            ans = min(ans, newAns);
        }
    }
    
    return dp[mask][pos] = ans;
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    if (!(cin >> n) || n <= 1) {
        cout << "Invalid number of cities." << endl;
        return 1;
    }

    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter distance matrix (row by row):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(cin >> dist[i][j])) {
                return 1;
            }
        }
    }

    // dp table size: 2^n states for mask, n states for current position
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));

    int result = tsp(1, 0, dist, dp);
    cout << "Minimum TSP cost: " << result << endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to solve 0-1 Knapsack using DP
int knapsack(int W, const vector<int>& wt, const vector<int>& val) {
    int n = wt.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid number of items.\n";
        return 1;
    }

    cout << "Enter knapsack capacity: ";
    if (!(cin >> W) || W < 0) {
        cout << "Invalid capacity.\n";
        return 1;
    }

    vector<int> wt(n), val(n);
    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++) {
        if (!(cin >> wt[i]) || wt[i] < 0) {
            cout << "Invalid weight.\n";
            return 1;
        }
    }

    cout << "Enter values of items: ";
    for (int i = 0; i < n; i++) {
        if (!(cin >> val[i]) || val[i] < 0) {
            cout << "Invalid value.\n";
            return 1;
        }
    }

    cout << "Maximum value in knapsack = " << knapsack(W, wt, val) << endl;
    return 0;
}

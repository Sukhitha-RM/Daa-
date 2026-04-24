#include <iostream>
#include <vector>

using namespace std;

bool isSubsetSum(const vector<int>& set, int target) {
    int n = set.size();
    // dp[i][j] will be true if there is a subset of 
    // set[0..i-1] with sum equal to j
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // Base case: If sum is 0, then answer is true (empty subset)
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;

    // Fill the table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (j < set[i - 1]) {
                // Current element is greater than the sum, exclude it
                dp[i][j] = dp[i - 1][j];
            } else {
                // Include or exclude the current element
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - set[i - 1]];
            }
        }
    }

    return dp[n][target];
}

int main() {
    vector<int> set = {3, 34, 4, 12, 5, 2};
    int sum = 9;

    if (isSubsetSum(set, sum))
        cout << "Found a subset with given sum" << endl;
    else
        cout << "No subset with given sum" << endl;

    return 0;
}

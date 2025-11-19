#include <iostream>
using namespace std;

int knapsackDP(int W, int wt[], int val[], int n) {

    // dynamic 2D array
    int** dp = new int*[n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = new int[W + 1];
    }

    // initialize dp table with 0
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = 0;
        }
    }

    // DP logic
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    int result = dp[n][W];

    // free memory
    for (int i = 0; i <= n; i++) {
        delete[] dp[i];
    }
    delete[] dp;

    return result;
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    int wt[n], val[n];
    cout << "Enter weight and value of each item:\n";
    for (int i = 0; i < n; i++) {
        cin >> wt[i] >> val[i];
    }

    cout << "Enter capacity of knapsack: ";
    cin >> W;

    cout << "Maximum value = " << knapsackDP(W, wt, val, n) << endl;

    return 0;
}

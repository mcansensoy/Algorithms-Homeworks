#include "the3.h"

// DO NOT CHANGE ABOVE THIS LINE!
// you may implement helper functions below

int find_min_cost(const std::vector<std::vector<int>>& costs, int N) {
    std::vector<std::vector<int>> dp(N - 1, std::vector<int>(6, 1e9));

    for (int j = 0; j < 6; ++j) {
        dp[0][j] = costs[0][j];
    }

    for (int i = 1; i < N - 1; ++i) {
        dp[i][0] = costs[i][0] + std::min(std::min(std::min(dp[i - 1][0], dp[i - 1][2]), 
                                                   dp[i - 1][3]), 
                                          std::min(dp[i - 1][4], dp[i - 1][5]));
                                          
        dp[i][1] = costs[i][1] + std::min(std::min(std::min(dp[i - 1][1], dp[i - 1][2]), 
                                                   dp[i - 1][3]), 
                                          std::min(dp[i - 1][4], dp[i - 1][5]));
                                          
        dp[i][2] = costs[i][2] + std::min(std::min(dp[i - 1][0], dp[i - 1][1]), 
                                          std::min(dp[i - 1][4], dp[i - 1][5]));
                                          
        dp[i][3] = costs[i][3] + std::min(std::min(dp[i - 1][0], dp[i - 1][1]), 
                                          std::min(dp[i - 1][4], dp[i - 1][5]));
                                          
        dp[i][4] = costs[i][4] + std::min(std::min(dp[i - 1][0], dp[i - 1][1]), 
                                          std::min(dp[i - 1][2], dp[i - 1][3]));
                                          
        dp[i][5] = costs[i][5] + std::min(std::min(dp[i - 1][0], dp[i - 1][1]), 
                                          std::min(dp[i - 1][2], dp[i - 1][3]));
    }

    int min_cost = dp[N - 2][0];
    for (int j = 1; j < 6; ++j) {
        min_cost = std::min(min_cost, dp[N - 2][j]);
    }

    return min_cost;
}

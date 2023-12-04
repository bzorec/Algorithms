#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct Island {
    int x, y, t; // x and y coordinates, time to explore
};

class Solution {
public:
    vector<long long> exploreIslands(int N, int M, int K, vector<Island>& islands) {
        vector<vector<long long>> dp(N + 1, vector<long long>(M + 1, LLONG_MAX));
        vector<long long> result;

        dp[1][1] = 0;

        for (int i = 1; i <= N; ++i) {
            vector<long long> A(M + 1, LLONG_MAX);
            vector<long long> RESULT(M + 1, LLONG_MAX);
            A[0] = 0;

            for (int j = 1; j <= M; ++j) {
                A[j] = min(A[j - 1] + 3, RESULT[j - 1] + 3);
                RESULT[j] = min(RESULT[j], A[j] + islands[i - 1].t);
            }

            for (int j = M - 1; j >= 1; --j) {
                A[j] = min(A[j], RESULT[j + 1] + 3);
                RESULT[j] = min(RESULT[j], A[j] + islands[i - 1].t);
            }

            for (int j = 1; j <= M; ++j) {
                dp[i][j] = RESULT[j];
            }
        }

        for (int i = 0; i < K; ++i) {
            result.push_back(dp[N][islands[i].y]);
        }

        return result;
    }
};

int main() {
    Solution solution;

    // Input data
    int N = 4, M = 4, K = 5;
    vector<Island> islands = {
        {1, 3, 1},
        {1, 2, 9},
        {2, 3, 5},
        {3, 2, 6},
        {4, 3, 2}
    };

    vector<long long> result = solution.exploreIslands(N, M, K, islands);

    // Output the result
    for (long long res : result) {
        cout << res << " ";
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct Island {
    int x, y, t; // x and y coordinates, time to explore
};
// class Solution {
// public:
//     int minPathSum(vector<vector<int>>& grid) {
//         //Fast I/O in C++
//         ios_base::sync_with_stdio(false);
//         cin.tie(NULL);
//         
//         int rows = grid.size();
//         if(rows==0)
//             return 0;
//         int cols = grid[0].size();
//         vector<vector<int>> dp(rows,vector<int>(cols,0));
//         int i,j;
//         
//         dp[0][0] = grid[0][0];  //1st element is starting point
//         //Fill 1st row
//         for(i=1;i<cols;++i)
//             dp[0][i] = dp[0][i-1] + grid[0][i];
//         
//         //Fill 1st Col
//         for(i=1;i<rows;++i)
//             dp[i][0] = dp[i-1][0] + grid[i][0];
//         
//         //Now fill the rest of the cell
//         for(i=1;i<rows;++i)
//         {
//             for(j=1;j<cols;++j)
//                 dp[i][j] = grid[i][j] + min(dp[i-1][j],dp[i][j-1]);
//         }
//         return dp[rows-1][cols-1];
//     }
// };
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

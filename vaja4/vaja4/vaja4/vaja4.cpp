#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Island {
    int x;
    int y;
    long long t;
};

vector<long long> minSumPath(const vector<Island>& islands, int n, int m, const int k) {
    // Create a 2D table to store intermediate results
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, INT_MAX));

    dp[0][0] = 0;
    
    // Fill the table using tabulation
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            // Option 1: Move forward
            auto val1 = dp[i][j];
            auto val2 = (i == 1) ? islands[i - 1].y - i + islands[i - 1].t : dp[i - 1][j] + 1 + islands[i - 1].t;
            dp[i][j] = min(val1, val2);

            // Option 2: Move backward
            if (j > 0) {
                auto val1 = dp[i][j];
                auto val2 = dp[i][j - 1] + (abs(islands[i].y - islands[i - 1].y) + 1) + islands[i - 1].t;
                dp[i][j] = min(val1, val2);
            }

            // Option 3: Move upward if in the first or last column
            if (j > 0 && (i == 1 || i == n)) {
                auto val1 = dp[i][j];
                auto val2 = dp[i - 1][j - 1] + (abs(islands[i - 1].y - islands[i].y) + 1) + islands[i - 1].t;
                dp[i][j] = min(val1, val2);
            }
        }
    }


    // Extract the result from the last row of the table
    vector<long long> resultPath(k);

    for (int j = 0; j < k; ++j) {
        long long minTime = INT_MAX;
        for (int i = 0; i <= n; ++i) {
            minTime = min(minTime, dp[j][i]);
        }
        resultPath[j] = minTime;
    }

    return resultPath;
}

int main(int argc, char* argv[]) {

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    // Example usage
    int N, M, K;
    inputFile >> N >> M >> K;

    // Input island positions and exploration times
    vector<Island> islands(K);
    for (int i = 0; i < K; ++i) {
        inputFile >> islands[i].x >> islands[i].y >> islands[i].t;
    }

    // Check if vector islands has enough elements
    if (islands.size() < K) {
        cerr << "Error: Insufficient elements in the islands vector." << endl;
        return 1;
    }

    // Calculate the minimum sum path using tabulation
    vector<long long> resultPath = minSumPath(islands,N,M, K);

    // Output the result path
    for (int time : resultPath) {
        cout << time << " ";
    }
    return 0;
}

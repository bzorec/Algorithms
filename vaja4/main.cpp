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

vector<long long> minSumPath(const vector<Island>&islands, int n, int m, const int k) {
    // Create a 2D table to store intermediate results
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, INT_MAX));


    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    dp[0][0] = 0;

    // TODO fix the movment checks not calculation the moves correctly
    // Fill the table using tabulation
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            // Option 1: Enter a new row in column y=1
            auto val1 = dp[i][j];
            auto val2 = dp[i - 1][j] + 1 + islands[i - 1].t;
            dp[i][j] = min(val1, val2);

            // Option 2: Enter the next row again in column y=1
            if (j > 0) {
                auto val1 = dp[i][j];
                auto val2 = dp[i][j - 1] + 1 + islands[i - 1].y - islands[i - 2].y + islands[i - 1].t;
                dp[i][j] = min(val1, val2);
            }

            // Option 3: Enter the next row in the column y=M
            if (j > 0) {
                auto val1 = dp[i][j];
                auto val2 = dp[i - 1][j - 1] + 1 + islands[i - 2].y + islands[i - 1].t;
                dp[i][j] = min(val1, val2);
            }

            // Option 4: Enter the new row in the column y=M
            val1 = dp[i][j];
            val2 = dp[i - 1][j] + 1 + islands[i - 2].y + islands[i - 1].t;
            dp[i][j] = min(val1, val2);
        }
    }

    // Extract the result from the last row of the table
    vector<long long> resultPath(k + 1);
    for (int i = 0; i < k; i++) {
        resultPath[i] = INT_MAX;
    }

    // TODO fix the result how to put into the new array
    for (int j = 0; j <= k; ++j) {
        auto result = (dp[n][j]);
        resultPath[j] = result;
    }

    return resultPath;
}

int main() {
    const string filename = "test.txt";

    ifstream inputFile(filename);
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

    // Calculate the minimum sum path using dynamic programming
    // Output the result path
    for (const vector<long long> resultPath = minSumPath(islands, N, M, K); const long long time: resultPath) {
        cout << time << " ";
    }

    return 0;
}

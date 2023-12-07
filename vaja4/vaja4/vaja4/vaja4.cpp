#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct island
{
	int x;
	int y;
	long long t;
};

int abs_diff(const int x, const int y)
{
	return (x > y) ? x - y : y - x;
}

vector<long long> min_sum_path(const vector<island>& islands, const int n, const int m, const int k)
{
	// Create a 2D table to store intermediate results
	vector dp(k + 1, vector<long long>(k + 1, LLONG_MAX - 1));

	dp[0][0] = 0;

	// Fill the table using tabulation
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j <= k; ++j)
		{
			// Option 1: Move forward
			auto left1 = dp[i][j];
			auto right1 = dp[i - 1][j] + (abs_diff(islands[i].y, islands[i - 1].y) + 1) + islands[i - 1].t;
			dp[i][j] = min(left1, right1);

			// Option 2: Move backward
			if (j > 0)
			{
				auto left2 = dp[i][j];
				auto right2 = dp[i][j - 1] + (abs_diff(islands[i].y, islands[i - 1].y) + 1) + islands[i - 1].t;
				dp[i][j] = min(left2, right2);
			}

			// Option 3: Move upward if in the first or last column
			if (j > 0 && (i == 1 || i == n))
			{
				auto left3 = dp[i][j];
				auto right3 = dp[i - 1][j - 1] + (abs_diff(islands[i - 1].y, islands[i].y) + 1) + islands[i - 1].t;
				dp[i][j] = min(left3, right3);
			}

			// Initialize the first column of the dp table to 0
			for (int l = 1; l <= k; ++l)
			{
				dp[0][l] = 0;
			}
		}
	}

	// Extract the result path
	vector<long long> result_path(k + 1);

	for (int j = 0; j < k; ++j)
	{
		long long min_time = INT_MAX;
		for (int i = 0; i <= n; ++i)
		{
			min_time = min(min_time, dp[j][i]);
		}
		result_path[j] = min_time;
	}

	return result_path;
}


int main(int argc, char* argv[])
{
	ifstream input_file(argv[1]);
	if (!input_file.is_open())
	{
		cerr << "Error opening the file!" << '\n';
		return 1;
	}

	// Example usage
	int n, m, k;
	input_file >> n >> m >> k;

	// Input island positions and exploration times
	vector<island> islands(k);
	for (int i = 0; i < k; ++i)
	{
		input_file >> islands[i].x >> islands[i].y >> islands[i].t;
	}

	// Check if vector islands has enough elements
	if (islands.size() < k)
	{
		cerr << "Error: Insufficient elements in the islands vector." << '\n';
		return 1;
	}

	// Calculate the minimum sum path using tabulation

	// Output the result path
	for (const vector<long long> result_path = min_sum_path(islands, n, m, k); const long long time : result_path)
	{
		cout << time << " ";
	}

	return 0;
}

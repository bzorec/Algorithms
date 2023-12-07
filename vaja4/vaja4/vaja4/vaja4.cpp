#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct island
{
	int x_cord;
	int y_cord;
	int research_time;
};

vector<int> result;

bool compareIslands(const island& a, const island& b)
{
	// Sort by x_cord and then by y_cord
	if (a.x_cord == b.x_cord)
		return a.y_cord < b.y_cord;
	return a.x_cord < b.x_cord;
}

void new_main(const vector<island>& islands, const int n, const int m, const int k)
{
	result.resize(k + 1, INT32_MAX - 1);
	result[0] = 0;

	for (int i = 1; i <= k; ++i)
	{
		island current_island = islands[i - 1];
		int current_x = current_island.x_cord;
		int current_y = current_island.y_cord;

		for (int j = 0; j < n / 2; ++j)
		{
			// Calculate time for moving left and down:
			island down_left = current_island;
			down_left.x_cord--;
			down_left.y_cord++;
			down_left.research_time++;

			// Update the result for the new position
			result[i] = min(result[i], down_left.research_time + result[i - 1] + 2);

			// Calculate time for moving down
			island down = current_island;
			down.y_cord++;
			down.research_time++;

			result[i] = min(result[i], down.research_time + result[i - 1] + 1);

			// Calculate time for moving down and right
			island down_right = current_island;
			down_right.x_cord++;
			down_right.y_cord++;
			down_right.research_time++;

			result[i] = min(result[i], down_right.research_time + result[i - 1] + 3);

			// Calculate time for moving right
			island right = current_island;
			right.x_cord++;
			right.research_time++;

			result[i] = min(result[i], right.research_time + result[i - 1] + 1);

			// Calculate time for moving left and up
			island left_up = current_island;
			left_up.x_cord--;
			left_up.y_cord--;
			left_up.research_time++;

			result[i] = min(result[i], left_up.research_time + result[i - 1] + 4);
		}
	}

	for (int i = 1; i <= k; ++i)
	{
		cout << result[i] << " ";
	}
	cout << endl;
}

int main(const int argc, char* argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <input_file>" << '\n';
		return 1;
	}

	fstream input_file(argv[1]);
	if (!input_file.is_open())
	{
		cerr << "Error opening the file!" << '\n';
		return 1;
	}

	int n, m, k;
	input_file >> n >> m >> k;

	// Input island positions and exploration times
	vector<island> islands(k);
	for (int i = 0; i < k; ++i)
	{
		input_file >> islands[i].x_cord >> islands[i].y_cord >> islands[i].research_time;
	}

	// Sort the islands
	sort(islands.begin(), islands.end(), compareIslands);

	new_main(islands, n, m, k);

	return 0;
}

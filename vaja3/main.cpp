#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

struct cushion {
    int x, y, size;
};

int calculateMaxDrop(const vector<multiset<int>> &columns, int height) {
    int maxDrop = 0;
    for (const auto &item: columns) {
        auto it = item.begin();

        if (it == item.end()) {
            maxDrop = height;
            continue;
        }

        if (*it > maxDrop) maxDrop = *it;
    }
    return maxDrop;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Error occurred while opening the file." << endl;
        return 1;
    }

    int changes, height, width;
    file >> changes >> height >> width;

    vector<multiset<int>> columns(width);

    char symbol;
    int row;

    vector<cushion> cushions;
    cushions.reserve(changes);

    int maxDrop = 0;

    vector<int> maxDropValues;

    for (size_t i = 0; i < changes; i++) {
        file >> symbol;
        if (symbol == '+') {
            cushions.emplace_back();
            file >> cushions.back().x >> cushions.back().y >> cushions.back().size;

            cushions.back().size--;
            for (int j = cushions.back().y; j <= cushions.back().y + cushions.back().size; j++) {
                columns[j].insert(cushions.back().x);
            }
        } else {
            file >> row;
            for (int j = cushions[row - 1].y; j <= cushions[row - 1].y + cushions[row - 1].size; j++) {
                columns[j].erase(columns[j].find(cushions[row - 1].x));
            }
        }

        maxDrop = calculateMaxDrop(columns, height);
        maxDropValues.push_back(maxDrop);
    }

    for (const auto &value: maxDropValues) {
        cout << value << std::endl;
    }

    return 0;
}
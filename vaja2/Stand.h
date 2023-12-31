﻿#include <vector>
#include <algorithm>

class Stand {
public:
    int findMinimum();

    int findMaximum();

    void trim(int x);

    bool arePairsValid();

    bool anyWeights();

    void addWeight(int number);

private:
    std::vector<int> _weights;
};

int Stand::findMinimum() {
    return *std::min_element(_weights.begin(), _weights.end());
}

int Stand::findMaximum() {
    return *std::max_element(_weights.begin(), _weights.end());
}

void Stand::trim(int x) {
    _weights.erase(std::remove_if(_weights.begin(), _weights.end(), [x](int val) { return val < x + 1; }),
                   _weights.end());
}

bool Stand::arePairsValid() {
    for (size_t i = 0; i < _weights.size(); i += 2) {
        if (i + 1 < _weights.size() && _weights[i] != _weights[i + 1]) {
            return false;
        }
    }
    for (size_t i = 0; i < _weights.size(); i += 2)
        if (_weights.size() == 1)
            return false;

    return true;
}

bool Stand::anyWeights() {
    return !_weights.empty();
}

void Stand::addWeight(int number) {
    _weights.push_back(number);
}

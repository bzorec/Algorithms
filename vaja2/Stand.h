#include <vector>
#include <algorithm>

class Stand {
public:
    int findMinimum() {
        return *std::min_element(_weights.begin(), _weights.end());
    }

    int findMaximum() {
        return *std::max_element(_weights.begin(), _weights.end());
    }

    void trim(int x) {
        _weights.erase(std::remove_if(_weights.begin(), _weights.end(), [x](int val) { return val < x + 1; }),
                       _weights.end());
    }

    bool arePairsValid() {
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

    bool anyWeights() {
        return !_weights.empty();
    }

    void addWeight(int number) {
        _weights.push_back(number);
    }

    std::vector<int> getWeights() {
        return _weights;
    }

private:
    std::vector<int> _weights;
};

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include "Stand.h"

bool checkX(Stand *firstStand, Stand *secondStand, int x);

int bisect(Stand *firstStand, Stand *secondStand, int a, int b);

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Incorrect number of arguments!\n";
        return -1;
    }

    std::string filePath = argv[1];
    std::ifstream file(filePath);

    int weightPairCount, currentNumber;

    std::vector<int> weights1, weights2;

    if (!file.is_open()) {
        std::cout << "Error opening the input file.\n";
        return -1;
    }
    auto firstStand = new Stand();
    auto secondStand = new Stand();

    file >> weightPairCount;

    for (int i = 0; i < weightPairCount * 2; i++) {
        file >> currentNumber;

        if (i < weightPairCount) {
            firstStand->addWeight(currentNumber);
        } else {
            secondStand->addWeight(currentNumber);
        }
    }

    if (firstStand->anyWeights() && secondStand->anyWeights()) {
        int min = std::min(firstStand->findMinimum(), secondStand->findMinimum());
        int max = std::max(firstStand->findMaximum(), secondStand->findMaximum());

        if (checkX(firstStand, secondStand, min)) {
            std::cout << "0";
            return 0;
        }

        auto bisectResult = bisect(firstStand, secondStand, min, max);
        std::cout << bisectResult;

        return 0;
    }

    file.close();
    return 0;
}

bool checkX(Stand *firstStand, Stand *secondStand, int x) {
    auto first = *firstStand;
    auto second = *secondStand;

    first.trim(x);
    second.trim(x);

    if (!first.anyWeights() && !second.anyWeights()) {
        return true;
    }

    return first.arePairsValid() && second.arePairsValid();
}

int bisect(Stand *firstStand, Stand *secondStand, int a, int b) {
    while (b - a > 1) {
        int x = (a + b) / 2;

        bool fa = checkX(firstStand, secondStand, a);
        bool fb = checkX(firstStand, secondStand, b);
        bool fx = checkX(firstStand, secondStand, x);

        if (!fa && fb && fx) {
            b = x;
        } else if (!fa && !fx && fb) {
            a = x;
            firstStand->trim(x);
            secondStand->trim(x);
        } else {
            break;
        }
    }

    return b;
}

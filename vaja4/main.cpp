#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int main(const int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uporaba: " << argv[0] << " <vhodna_datoteka.txt>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Napaka pri odpiranju datoteke." << endl;
        return 1;
    }

    int N, M, K;
    file >> N >> M >> K;

    vector<vector<int>> islandData(K, vector<int>(3, 0));
    for (int i = 0; i < K; ++i) {
        file >> islandData[i][0] >> islandData[i][1] >> islandData[i][2];
    }

    vector<int> times(N + 1, 0); // Časi potrebnih za dosego otokov (indeksiranje od 1)
    vector<int> RESULT(K + 1, numeric_limits<int>::max()); // Polje za hranjenje minimalnega časa za raziskovanje
    vector<vector<int>> A(K + 1, vector<int>(M + 1, numeric_limits<int>::max()));
    // Tabela stanj za hranjenje minimalnega časa za raziskovanje k otokov + čas premikov v nove vrstice

    // Branje časov potrebnih za dosego otokov
    for (int i = 0; i < K; ++i) {
        times[islandData[i][0]] = islandData[i][2];
    }

    // Dinamično programiranje za premikanje med otoki v vrstici
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j <= N; ++j) {
            int moveCost = 0;
            for (int k = j + 1; k <= N; ++k) {
                moveCost += times[k];
                A[k][1] = min(A[k][1], A[j][0] + moveCost);
            }
        }
    }

    // Dinamično programiranje za celotno nalogo
    for (int k = 1; k <= K; ++k) {
        for (int i = k; i <= N; ++i) {
            RESULT[k] = min(RESULT[k], A[i][1]);
        }
    }

    // Izpis rezultatov
    for (int k = 1; k <= K; ++k) {
        cout << RESULT[k] << " ";
    }

    return 0;
}

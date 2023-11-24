#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Blazina {
public:
    int zacetek;
    int konec;
    int visina;

    Blazina(int z, int k, int v) : zacetek(z), konec(k), visina(v) {}
};

class SegmentnoDrevo {
private:
    vector<int> drevo;

public:
    explicit SegmentnoDrevo(int velikost) {
        int velikost_drevesa = 2 * pow(2, ceil(log2(velikost)));  // Zaokroži na najbližje večkratnik od 2
        drevo.resize(velikost_drevesa, 0);
    }

    void posodobi(int indeks, int zacetek, int konec, int pozicija, int vrednost) {
        if (zacetek == konec) {
            drevo[indeks] = vrednost;
            return;
        }

        int sredina = (zacetek + konec) / 2;
        int levo = 2 * indeks + 1;
        int desno = 2 * indeks + 2;

        if (pozicija <= sredina) {
            posodobi(levo, zacetek, sredina, pozicija, vrednost);
        } else {
            posodobi(desno, sredina + 1, konec, pozicija, vrednost);
        }

        drevo[indeks] = max(drevo[levo], drevo[desno]);
    }

    int vrni_najvecjo_vrednost(int indeks, int zacetek, int konec, int levi, int desni) {
        if (levi > konec || desni < zacetek) {
            return 0;
        }

        if (levi <= zacetek && desni >= konec) {
            return drevo[indeks];
        }

        int sredina = (zacetek + konec) / 2;
        int levo = 2 * indeks + 1;
        int desno = 2 * indeks + 2;

        int maksimum_levo = vrni_najvecjo_vrednost(levo, zacetek, sredina, levi, desni);
        int maksimum_desno = vrni_najvecjo_vrednost(desno, sredina + 1, konec, levi, desni);

        return max(maksimum_levo, maksimum_desno);
    }
};

void najvecja_globina_padca(int N, int V, int S, vector<string>& spremembe) {
    vector<Blazina> blazine;
    SegmentnoDrevo segmentno_drevo(S);
    int globina_padca = 0;

    for (int i = 0; i < N; ++i) {
        string sprememba = spremembe[i];

        if (sprememba[0] == 'Y') {
            int Y, X, D;
            sscanf(sprememba.c_str(), "Y%dXD%d", &Y, &D);
            X = stoi(sprememba.substr(2, sprememba.find("XD") - 2));
            Blazina nova_blazina(X, X + D, Y);
            blazine.push_back(nova_blazina);
            segmentno_drevo.posodobi(0, 0, S - 1, X, Y);
        } else if (sprememba[0] == 'K') {
            int indeks = stoi(sprememba.substr(1)) - 1;
            Blazina odstranjena_blazina = blazine[indeks];
            blazine.erase(blazine.begin() + indeks);
            segmentno_drevo.posodobi(0, 0, S - 1, odstranjena_blazina.zacetek, 0);
        }

        // Izračun največje globine padca
        int min_visina = segmentno_drevo.vrni_najvecjo_vrednost(0, 0, S - 1, 0, S - 1);
        globina_padca = V - min_visina;

        cout << globina_padca << endl;
    }
}

int main() {
    int N = 5;
    int V = 10;
    int S = 5;
    vector<string> spremembe = {"Y5XD2", "Y8XD1", "K1", "Y7XD3", "K2"};

    najvecja_globina_padca(N, V, S, spremembe);

    return 0;
}

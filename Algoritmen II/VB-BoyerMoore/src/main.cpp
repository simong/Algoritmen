#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned int uint;
typedef unsigned char uchar;

class BoyerMoore {
public:
    BoyerMoore(const uchar* pattern, uint m);
    int search(const uchar* text, uint n);

//private:
    uint d; // ASCI
    uint m;
    const uchar* pattern;

    int heuristiek_1[256];
    uint* suffix_tabel;
    uint* verschuivings_tabel;

    int heuristiek_verkeerde_karakter(const uchar* text, uint k, uint i);

    int heuristiek_juiste_suffix(uint j);
    uint bereken_suffix(const uchar* str, uint length, uint j);
};

BoyerMoore::BoyerMoore(const uchar* pattern, uint m)
        : d(256), pattern(pattern), m(m) {

    // Heuristiek 1 : Verkeerde karakter.
    // We bepalen voor ieder mogelijk karakter zijn meest rechtse voorkomen in het patroon.
    // Als het niet voorkomt in het patroon dan: -1
    for (uint i = 0; i < d; i++)
        heuristiek_1[i] = -1;

    for (uint i = 0; i < m; i++)
        heuristiek_1[pattern[i]] = i;

    // Heuristiek 2: Juiste suffix.
    suffix_tabel = new uint[m];
    for (uint j = 0; j < m; j++) {
        suffix_tabel[j] = bereken_suffix(pattern, m, j);
    }

    // Verschuivings tabel berekenen.
    // Deze heeft initieel de waarde m - s(1)
    verschuivings_tabel = new uint[m];
    for (int i = m - 1; i >= 0; i--)
        verschuivings_tabel[i] = m - suffix_tabel[0];

    // v[i] berekenen
    // v[i] = minimuum van het v[i] en i + 1 - j
    for (int j = m - 1; j >= 0; j--) {
        uint i = m - suffix_tabel[j];
        verschuivings_tabel[i] = std::min(verschuivings_tabel[i], i + 1 - j);
    }
}

uint BoyerMoore::bereken_suffix(const uchar* str, uint length, uint j) {
    if (j == m - 1)
        return 0;

    unsigned int pi = suffix_tabel[j + 1];
    while (pi != 0) {
        if (str[m - pi - 1] == str[j])
            return pi + 1;
        else
            pi = suffix_tabel[m - pi + 1];
    }

    if (str[m - pi - 1] == str[j])
        return pi + 1;
    else
        return pi;
}

int BoyerMoore::heuristiek_verkeerde_karakter(const uchar* text, uint k, uint i) {
// k is de positie in de text, i is de positie in het patroon.

// Dit is de eerste (simpele) heuristiek.
// Dit zoekt de meest rechtse positie van het karakter op text[pos].
// We bepalen de verschuiving zodat er een gelijkaardig karakter ligt op text[pos]
    int j = heuristiek_1[text[k]];
    int verschuiving = i - j;

// Aangezien j (de meest rechtse index waar dit karakter voorkomt) _rechts_ van pos
// kan liggen, zou dit een negatieve (of 0) verschuiving inhouden.
// Dan verschuiven we gewoon met 1.
    if (verschuiving < 1)
        verschuiving = 1;

    std::cout << " H1: " << verschuiving;
    return verschuiving;
}

int BoyerMoore::heuristiek_juiste_suffix(uint j) {
    // We hebben suffix van lengte m - i -1 gevonden. (-1 omdat c++ zero based is, de cursus is 1-based)
    // Situaties
    std::cout << " H2: " << verschuivings_tabel[j];
    return verschuivings_tabel[j];
}

int BoyerMoore::search(const uchar* text, uint n) {

    std::vector<int> locaties;

    uint skip = 0;
    for (uint i = 0; i < n - m; i += skip) {
        skip = 0;

        // Van achter naar voor over het pattern lopen en vergelijken met overeenkomstig karakter in de text.
        for (int j = m - 1; j >= 0; j--) {
            if (text[i + j] != pattern[j]) {
                // We hebben een fout gevonden.
                int heur1 = heuristiek_verkeerde_karakter(text, i + j, i);
                int heur2 = heuristiek_juiste_suffix(j);
                std::cout << std::endl;
                skip = std::max(heur1, heur2);
                //skip = heur1;
                break;
            }
        }

        if (skip == 0) {
            // We hebben het patroon gevonden!
            locaties.push_back(i);
            return i;
        }

    }

    return -1;
}

int main() {
    const uchar text[] = "alfa beta alfa charly";
    const uchar pattern[] = "beta";

    uint n = 21;
    uint m = 4;

    BoyerMoore bm(pattern, m);

    int pos = bm.search(text, n);
    std::cout << pos;

    return 0;
}

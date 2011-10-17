//============================================================================
// Name        : Labo09-RadixSort.cpp
// Author      : Simon Gaeremynck
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <set>

#include "countingsort.h"
#include "util.h"

using namespace std;

void radix_sort_gelijke_sleutels(vector<string>& v) {
    // Zoek de lengte van de sleutels.
    int i = v[0].size();

    while (i > 0) {
        i--; // Eerst -1 omdat .size() de lengte teruggeeft...
        stringchar schar(i);
        counting_sort(v, schar, 256);
    }
}

// Blijkbaar niet het gevraagde..
// Verschillende sleutels.
void verkeerde_radix_sort(vector<string>& v) {
    // Zoek de grootste lengte
    // Om het iets performanter te maken, zouden we de lengtes in een map kunnen steken
    // Deze dalend sorteren.
    // Dan de sleutels overlopen.
    // Dan hebben we maximum even veel items.

    unsigned int len = v[0].size();
    for (unsigned int i = 0; i < v.size(); i++)
        if (v[i].size() >= len)
            len = v[i].size();

    while (len > 0) {
        len--; // Eerst -1 omdat .size() de lengte teruggeeft...
        stringchar schar(len);
        counting_sort(v, schar, 256);
    }
}

void msd_radix_sort(vector<string> &v, vector<uint> &hulp, int start, int end,
        int d, int maxLen) {

    if (d <= maxLen) {
        uint k = 256; // # aantal mogelijke tekens .. ASCII .. 256.
        stringchar convfunc(d);

        // Initialiseren
        // hulp is eerst freq-tabel
        for (uint i = 0; i < k; i++)
            hulp[i] = 0;

        // Over heel de tabel lopen en het aantal voor deze sleutel verhogen.
        // convfunc beeld T af als een uint.
        for (uint i = start; i < end; i++) {
            uint p = convfunc(v[i]);
            hulp[p]++;
        }

        // hulp wordt cumul-tabel = eindpositietabel
        // Als de tabel 4 2 3 5  7  bevat dan wordt deze
        //              4 6 9 14 21 wat de eindindexes aanduidt..
        for (uint j = 1; j < k; j++)
            hulp[j] += hulp[j - 1];

        // wegens stabiliteit van achter naar voor
        // Gebruik de hulp tabel om de index te bepalen van de elementen.
        // Iedere keer VOOR we een element plaatsen, gaat de positie in de hulptabel 1 naar beneden.
        vector<string> sorted(v.size());
        for (int i = end - 1; i >= start; i--) {
            uint p = convfunc(v[i]);
            sorted[--hulp[p]] = v[i];
        }

        // Gesorteerde tabel op v zetten.
        for (int i = 0; i < end-start; i++) {
            v[start + i] = sorted[i];
        }

        vector<uint> freq(hulp);
        vectorutil::print(freq);
        for (int i = 1; i < k; i++) {
            if (freq[i - 1] < freq[i]) {
                msd_radix_sort(v, hulp, freq[i - 1], freq[i], d + 1, maxLen);
            }
        }
    }
}

void radix_sort(vector<string> &v) {
    // Grootste lengte zoeken O(n).
    unsigned int len = v[0].size();
    for (unsigned int i = 0; i < v.size(); i++)
        if (v[i].size() >= len)
            len = v[i].size();

    vector<uint> hulp(256);
    msd_radix_sort(v, hulp, 0, v.size(), 0, len - 1);
}

template<typename F>
bool variabele_lengte_ok(const F &sortfunc) {
    std::string strings[] = { "de", "boskabouter", "liep", "al", "zingend",
            "en", "al", "springend", "in", "het", "bos" };

    uint n = sizeof(strings) / sizeof(std::string);

    std::vector<std::string> v(strings, strings + n);

    return sort_ok(sortfunc, v);
}

int main() {
    bool b = variabele_lengte_ok(radix_sort);
    if (b)
        cout << "Success!";
    else
        cout << "Failed!";
    return 0;
}

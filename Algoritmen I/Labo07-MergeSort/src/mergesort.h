/*
 * mergesort.h
 *
 *  Created on: May 28, 2011
 *      Author: simon
 */

#ifndef MERGESORT_H_
#define MERGESORT_H_

#include <vector>

/**
 * Merged de tabel [l, r[
 */
template<typename T>
void merge_sort_top_down(std::vector<T>& v, std::vector<T>& h, unsigned int l,
        unsigned int r) {
    // Stopconditie
    if (l < r) {
        // Deel de tabel in 2.
        unsigned int m = l + (r - l) / 2;
        unsigned int lengte = v.size() - 1;
        m = std::min(m, lengte);
        r = std::min(r, lengte);

        // Eigenlijk is top down merge sort een implementatie van bottom up.
        // Er wordt eerst helemaal afgedaald naar beneden en door de recursie
        // worden deze dan samengevoegd.
        merge_sort_top_down(v, h, l, m);
        merge_sort_top_down(v, h, m + 1, r);
        // De merge is [l, m[ Daarom +1 voor de recht grens..
        merge(v, h, l, m + 1, r + 1);
    }

}

template<typename T>
void merge_sort_top_down(std::vector<T>& v) {
    /*
     * Tabellen opdelen in 2, tot er maar 0 of 1 meer in zit.
     */
    std::vector<T> h;
    h.reserve(v.size());
    merge_sort_top_down(v, h, 0, v.size());
}

template<typename T>
void merge_sort_bottom_up(std::vector<T>& v) {

    /**
     * De tabel wordt gesorteerd door telkens groter wordende deeltabellen te mergen.
     * We beginnen bij deeltabellen van 1 element groot.
     *      i.e.: Het eerste met het tweede element "mergen", derde met het vierde..
     * Deeltabellen van 2 groot:
     *      i.e: Tabel 1 [1, 2] en Tabel 2 [3, 4] en deze 2 mergen
     * Repeat..
     */
    std::vector<T> h(v.size() / 2);

    //1, 2, 4, 8, 16, ..
    unsigned int k = 1;
    while (k < v.size()) {

        /**
         * We bepalen de deeltabellen
         * Tabel 1: [l, m[
         * Tabel 2: [m, r[
         * en mergen ze
         */
        for (unsigned int l = 0; l < v.size(); l += 2 * k) {
            unsigned int m = std::min(l + k, (unsigned int) v.size());
            unsigned int r = std::min(l + 2 * k, (unsigned int) v.size());
            merge(v, h, l, m, r);
        }

        k *= 2;
    }
}

template<typename T>
void merge(std::vector<T>& v, std::vector<T>& h, unsigned int l,
        unsigned int m, unsigned int r) {

    // Kopieer de linker tabel naar h
    for (unsigned int i = l; i < m; i++) {
        h[i - l] = v[i];
    }

    // Merge beide tabellen naar v.
    unsigned int i = l; // Linkse loper
    unsigned int j = m; // Rechtse loper.
    unsigned int u = l; // Loper voor gemergede tabel.

    // De eerste while loopt tot een van de tabellen leeg is.
    while (i < m && j < r) {
        if (h[i - l] < v[j]) {
            v[u] = h[i - l];
            i++;
        }
        else {
            v[u] = v[j];
            j++;
        }

        u++;
    }

    // Een van de tabellen is leeg, voeg de rest van de andere toe.
    // 2x while
    while (i < m) {
        v[u] = h[i - l];
        u++;
        i++;
    }
    while (j < r) {
        v[u] = v[j];
        u++;
        j++;
    }
}

#endif /* MERGESORT_H_ */

/*
 * sort.cpp
 *
 *  Created on: May 28, 2011
 *      Author: simon
 */

#ifndef DATUM_CPP_
#define DATUM_CPP_

#include<iostream>
#include "../mysort.h";

template<typename T, typename FUNC>
void MySort<T, FUNC>::insertion_sort(vector<T> &v, FUNC compareFunc) {

    /**
     * O(n²)
     * - ter plaatse
     * - stabiel.
     *
     * Insertion sort zal lineair door de vector lopen.
     *      ~ (for ..)
     * Voor ieder element zal dan achterwaarts tot aan het begin element
     * gelopen worden.
     *      ~ (while ..)
     * Als het vorige element groter is dan het huidig geselecteerde (h <v[j])
     * dan zal het 1 plaats opgeschoven worden. (stabiel!)
     * Als de while afgesloten is, hoeven we enkel nog het element op zijn plaats te zetten.
     * Dit moet op j+1 want we hebben j-- 1x te veel gedaan.
     */

    for (uint i = 1; i < v.size(); i++) {
        T h = v[i];
        int j = i - 1;
        while (j >= 0 && compareFunc(h, v[j])) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = h;
    }
}

template<typename T, typename FUNC>
void MySort<T, FUNC>::selection_sort(vector<T> &v, FUNC compareFunc) {

    /**
     * O(n²)
     * - ter plaatste
     * - niet stabiel
     *
     * Grootste element zoeken in vector en acteraan plaatsen. (swap)
     * Begin achteraan en loop naar het begin.
     *
     */

    for (uint i = v.size() - 1; i > 0; i--) {

        uint grootste = i;
        for (uint j = 0; j < i; j++)
            if (compareFunc(v[grootste], v[j]))
                grootste = j;

        swap(v[i], v[grootste]);
    }
}

template<typename T, typename FUNC>
void MySort<T, FUNC>::shell_sort(vector<T> &v, FUNC compareFunc) {

    /**
     * Verbetert insertion sort.
     * Insertion sort werkt enorm goed op bijna gesorteerde tabellen.
     * Daarom eerst de tabellen k-sorteren.
     *
     * Bij de laatste increment sleutel is k=1=insertion sort en is de tabel bijna correct.
     *
     * ~O(n*lg(n)^2) [ geschat ]
     */

    int INCREMENTEN[28] = { 1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929,
            16001, 36289, 64769, 146305, 260609, 587521, 1045505, 2354689,
            4188161, 9427969, 16764929, 37730305, 67084289, 150958081,
            268386305, 603906049, 1073643521 };

    int w = 27;
    int k = INCREMENTEN[w];
    while (w >= 0) {

        // Eigenlijk k-"insertion sort".
        for (uint i = k; i < v.size(); i++) {
            T h = v[i];
            int j = i - k;
            while (j >= 0 && h < v[j]) {
                v[j + k] = v[j];
                j -= k;
            }
            v[j + k] = h;
        }

        w--;
        k = INCREMENTEN[w];
    }

}

// Utilities //


template<typename T, typename FUNC>
bool MySort<T, FUNC>::is_sorted(vector<T> &v) {
    for (uint i = 1; i < v.size(); i++)
        if (v[i] < v[i - 1])
            return false;
    return true;
}

template<typename T, typename FUNC>
void MySort<T, FUNC>::print(vector<T> &v, ostream& os) {
    for (uint i = 0; i < v.size(); i++)
        os << v[i] << " ";

    os << endl;
}

#endif

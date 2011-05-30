/*
 * utils.cpp
 *
 *  Created on: May 28, 2011
 *      Author: simon
 */

#ifndef UTILS_CPP_
#define UTILS_CPP_

#include <vector>
#include "../utils.h"

using namespace std;

/**
 * Zal de vector v opvullen met n getallen.
 * De max parameter geeft aan wat de maximum waarde mag zijn.
 * Tijdsduur = 2n
 */
void vul_random(vector<int> &v, unsigned int n, int max) {
    // Opvullen met random getallen.
    for (unsigned int i = 0; i < n; i++) {
        v[i] = rand() % max;
    }

    // Getallen random verdelen.
    for (unsigned int i = 0; i < v.size(); i++) {
        int r = rand() % (n - 1);
        swap(v[i], v[r]);
    }
}

#endif

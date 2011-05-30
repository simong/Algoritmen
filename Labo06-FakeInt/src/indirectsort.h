/*
 * indirectsort.h
 *
 *  Created on: May 28, 2011
 *      Author: simon
 */

#ifndef INDIRECTSORT_H_
#define INDIRECTSORT_H_

#include<vector>
#include<algorithms>

namespace IndirectSort {

template<typename T>
struct Comparator {
    bool operator()(T* a, T* b) const {
        return *a < *b;
    }
};

template<typename T>
void sort(std::vector<T> &v) {
    // Kopier de pointers naar een vector.
    std::vector<T*> pointers(v.size());
    for (unsigned int i = 0; i < v.size(); i++) {
        pointers[i] = &(v[i]);
    }

    // Sorteer de pointers.
    Comparator<T> cmp;
    std::sort(pointers.begin(), pointers.end(), cmp);

    std::vector<T> c(v.size());
    for (unsigned int i = 0; i < pointers.size(); i++) {
        std::cout << *pointers[i] << " ";
    }

    // Hmm...
}

}

#endif /* INDIRECTSORT_H_ */

/*
 * quicksort.h
 *
 *  Created on: May 28, 2011
 *      Author: simon
 */

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include<vector>
#include"vectorutil.h"
template<typename T>
void quicksort(std::vector<T>&v, int l, int r) {

    /**
     * 2 lopers, 1 links en 1 rechts.
     * 1 pivot.
     *
     # choose pivot
     swap a[1,rand(1,n)]

     # 2-way partition
     k = 1
     for i = 2:n, if a[i] < a[1], swap a[++k,i]
     swap a[1,k]
     → invariant: a[1..k-1] < a[k] <= a[k+1..n]

     # recursive sorts
     sort a[1..k-1]
     sort a[k+1,n]

     *
     if (l < r) {
     // Kies random pivot en plaats deze vooraan.
     int pivot = l + rand() % (r - l);
     swap(v[l], v[pivot]);

     //
     int k = l;
     for (int i = l + 1; i < r; i++) {
     if (v[i] < v[l]) {
     k++;
     swap(v[k], v[i]);
     }
     }
     swap(v[l], v[k]);

     vectorutil::print(v);
     quicksort(v, l, k - 1);
     quicksort(v, k + 1, r);
     }
     */

    if (l < r) {
        T pivot = v[l];
        int i = l;
        int j = r;

        while (pivot < v[j])
            j--;

        while (i < j) {
            swap(v[i], v[j]);
            i++;
            j--;

            while (v[i] < pivot)
                i++;
            while (pivot < v[j])
                j--;
        }

        quicksort(v, l, j);
        quicksort(v, j + 1, r);
    }
}

template<typename T>
void quicksort(std::vector<T> &v) {
    quicksort(v, 0, v.size());
}

#endif /* QUICKSORT_H_ */

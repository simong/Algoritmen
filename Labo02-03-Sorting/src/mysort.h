/*
 * sort.h
 *
 *  Created on: May 28, 2011
 *      Author: simon
 */

#ifndef SORT_H_
#define SORT_H_

#include <vector>
#include <iostream>

using namespace std;
typedef unsigned int uint;

template<class T, typename FUNC>
class MySort {
public:

    // Sorting algorithms
    void insertion_sort(vector<T> &v, FUNC compareFunc);
    void selection_sort(vector<T> &v, FUNC compareFunc);
    void shell_sort(vector<T> &v, FUNC compareFunc);

    // Help methods
    bool is_sorted(vector<T> &v);
    void print(vector<T> &v, ostream& os);
};

template<class T>
struct Compare {
    bool operator()(const T a, const T b) {
        return a < b;
    }
};

#endif /* SORT_H_ */

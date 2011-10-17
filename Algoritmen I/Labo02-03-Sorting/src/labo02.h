/*
 * labo02.cpp
 *
 *  Created on: May 28, 2011
 *      Author: simon
 */

#ifndef LABO02_CPP_
#define LABO02_CPP_

#include <iostream>
#include <vector>

#include "stopwatch.h"
#include "utils.h"

#include "impl/mysort.cpp"

using namespace std;

void labo2() {
    // Vector (bijna) normaal verdeeld opvullen.
    const int AANTAL = 10000;
    vector<int> v(AANTAL);
    vul_random(v, AANTAL, 100);

    //
    // SW - BEGIN
    //
    Stopwatch sw;
    sw.start();

    // Sorteren
    Compare<int> vergelijker;
    MySort<int, Compare<int> > mySort;
    mySort.insertion_sort(v, vergelijker);

    sw.stop();
    cout << "Total time: " << sw.time_in_sec() << endl;

    // Check
    bool sorted = mySort.is_sorted(v);
    if (!sorted) {
        cout << "Not sorted." << endl;
    }
    else {
        cout << "Sorted" << endl;
    }
}

#endif

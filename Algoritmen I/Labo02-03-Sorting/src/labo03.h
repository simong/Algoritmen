/*
 * labo03.h
 *
 *  Created on: May 28, 2011
 *      Author: simon
 */

#ifndef LABO03_H_
#define LABO03_H_

#include <iostream>
#include <vector>
#include "datum.h"
#include "stopwatch.h"
#include "utils.h"

using namespace std;

void labo3() {
    Datum a(2010, 10, 10);
    Datum b(2011, 05, 28);
    Datum c(2001, 04, 18);
    Datum d(2010, 02, 22);

    vector<Datum> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(d);

    //
    // SW - BEGIN
    //
    Stopwatch sw;
    sw.start();

    // Sorteren
    Compare<Datum> vergelijker;
    MySort<Datum, Compare<Datum> > mySort;
    mySort.selection_sort(v, vergelijker);

    sw.stop();
    cout << "Total time: " << sw.time_in_sec() << endl;

    // Check
    mySort.print(v, cout);
    cout << endl;
    bool sorted = mySort.is_sorted(v);
    if (!sorted) {
        cout << "Not sorted." << endl;
    }
    else {
        cout << "Sorted" << endl;
    }
}

void labo3shellsort() {
    // Vector (bijna) normaal verdeeld opvullen.
    const int AANTAL = 10000000;
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
    mySort.shell_sort(v, vergelijker);

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

#endif /* LABO03_H_ */

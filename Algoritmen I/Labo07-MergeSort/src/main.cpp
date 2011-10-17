//============================================================================
// Name        : Labo07-MergeSort.cpp
// Author      : Simon Gaeremynck
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include "vectorutil.h"
#include "mergesort.h"

using namespace std;

int main() {
    srand(time(0));
    vector<int> v;
    vectorutil::fill_range(v, 50);
    vectorutil::shuffle(v);
    vectorutil::print(v);

    vector<int> v2 = v;
    sort(v2.begin(), v2.end());

    merge_sort_bottom_up(v);

    bool b = (v2 == v);
    //bool b = vectorutil::is_ordered(v);
    if (b)
        cout << "Success";
    else
        cout << "Failed";
    cout << endl;

    vectorutil::print(v);

    return 0;
}

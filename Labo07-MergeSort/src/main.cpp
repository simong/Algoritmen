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
    rand(time(0));
    vector<int> v;
    vectorutil::fill_range(v, 1000);
    vectorutil::shuffle(v);

    vector<int> v2 = v;
    sort(v2.begin(), v2.end());

    merge_sort(v);

    bool b = (v2 == v);
    //bool b = vectorutil::is_ordered(v);
    if (b)
        cout << "Success";
    else
        cout << "Failed";

    return 0;
}

//============================================================================
// Name        : Labo08-QuickSort.cpp
// Author      : Simon Gaeremynck
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "quicksort.h"
#include "vectorutil.h"
using namespace std;

int main() {
    srand(time(0));
    const int AANTAL = 50;
    vector<int> v(AANTAL);

    vectorutil::fill_random(v, AANTAL, 0, AANTAL);


    vectorutil::print(v);
    quicksort(v);

    vectorutil::print(v);
    bool b = vectorutil::is_ordered(v);
    if (b)
        cout << "Success";
    else
        cout << "Failed";

    return 0;
}

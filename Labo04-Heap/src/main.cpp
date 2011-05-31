//============================================================================
// Name        : Labo04-Heap.cpp
// Author      : Simon Gaeremynck
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "test/heaptest.h"
#include "vectorutil.h"
#include "heap.h"

using namespace std;

template<typename T>
struct LessComparer: public Comparer<T> {
    virtual bool operator()(const T a, const T b) {
        return a > b;
    }
};

bool sortcheck(int aantal) {
    vector<int> v1;
    vectorutil::fill_random(v1, aantal, 0, 50);
    vector<int> v2 = v1;
    std::sort(v2.begin(), v2.end());

    // Heapify de eerste vector.
    LessComparer<int> lessCmp;
    Heap<int> h(v1, lessCmp);

    // Maak vector door telkens te poppen.
    vector<int> v3;
    v3.reserve(aantal);
    while (!h.is_empty()) {
        v3.push_back(h.top());
        h.pop();
    }

    vectorutil::print(v1);
    vectorutil::print(v2);
    vectorutil::print(v3);

    return v2 == v3;

}

int main() {
    //heap_test();

    bool b = sortcheck(8);
    if (!b)
        cout << "Niet gesorteerd!";
    else
        cout << "Wel gesorteerd.";

    return 0;
}

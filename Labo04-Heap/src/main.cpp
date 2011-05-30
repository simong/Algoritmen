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

bool sortcheck(int aantal) {
    vector<int> v1;
    vectorutil::fill_random(v1, aantal, -50, 50);
    vector<int> v2 = v1;
    std::sort(v2.begin(), v2.end());

    // Heapify de eerste vector.
    Heap<int> h(aantal);
    for (int i = 0; i < v1.size(); i++)
        h.push(v1[i]);

    // Maak vector door telkens te poppen.
    vector<int> v3(v1.size());
    while (!h.is_empty()) {
        v3.push_back(h.top());
        h.pop();
    }
    return v2 == v3;

}

int main() {
    heap_test();

    bool b = sortcheck(1000);
    if (!b)
        cout << "Niet gesorteerd!";
    else
        cout << "Wel gesorteerd.";

    return 0;
}

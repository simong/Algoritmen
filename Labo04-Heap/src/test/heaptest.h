/*
 * File:   heaptest.h
 * Author: Wijnand
 *
 * Created on 22 februari 2010, 21:56
 */

#ifndef _HEAPTEST_H
#define _HEAPTEST_H

#include <iostream>

#include "../heap.cpp"
#include "simpleunittest.h"

void heap_test() {
    ut_start_check_throw()
    Heap<int> h(100);
    ut_check_equal(h.get_capacity(), 100);

    ut_check(h.is_empty());
    ut_check_equal(h.get_size(), 0);

    h.push(20);
    ut_check_equal(h.top(), 20);
    ut_check_equal(h.get_size(), 1);
    ut_check(!h.is_empty());

    h.push(10);
    ut_check_equal(h.top(), 20);
    ut_check_equal(h.get_size(), 2);
    ut_check(!h.is_empty());

    h.push(30);
    ut_check_equal(h.top(), 30);
    ut_check_equal(h.get_size(), 3);
    ut_check(!h.is_empty());

    h.push(20);
    ut_check_equal(h.top(), 30);
    ut_check_equal(h.get_size(), 4);
    ut_check(!h.is_empty());

    h.pop();
    ut_check_equal(h.top(), 20);
    ut_check_equal(h.get_size(), 3);
    ut_check(!h.is_empty());

    h.pop();
    ut_check_equal(h.top(), 20);
    ut_check_equal(h.get_size(), 2);
    ut_check(!h.is_empty());

    h.pop();
    ut_check_equal(h.top(), 10);
    ut_check_equal(h.get_size(), 1);
    ut_check(!h.is_empty());

    h.pop();
    ut_check(h.is_empty());
    ut_check_equal(h.get_size(), 0);

    h.clear();

    const int N = 10;
    // random permutatie van 0..N-1
    std::vector<int> v;
    for (int i = 0; i < N; i++)
        v.push_back(i);
    srand((unsigned int) time(0));
    std::random_shuffle(v.begin(), v.end());

    for (int i = 0; i < N; i++)
        h.push(v[i]);

    // moet N-1..0 geven
    for (int i = N - 1; i >= 0; i--) {
        ut_check_equal(h.top(), i);
        h.pop();
    }

    ut_check_didnt_throw()

    ut_start_check_throw()
    Heap<int> h(1);

    ut_start_check_throw()
    h.top();
    ut_check_did_throw(IllegalAccess)

    ut_start_check_throw()
    h.pop();
    ut_check_did_throw(IllegalAccess)

    h.push(1);
    ut_start_check_throw()
    h.push(1);
    ut_check_did_throw(CapacityExceeded)
    ut_check_didnt_throw()

    std::cout << "HEAP TEST" << std::endl;
    ut_report();
}

#endif  /* _HEAPTEST_H */


/* 
 * File:   indirectsorttest.h
 * Author: Wijnand
 *
 * Created on 7 maart 2010, 21:20
 */

#ifndef _INDIRECTSORTTEST_H
#define	_INDIRECTSORTTEST_H

#include <vector>
#include <iostream>

#include "indirectsort.h"
#include "simpleunittest.h"
#include "fakeint.h"


typedef unsigned int uint;

// fill v with values 0..n-1
void make_range(std::vector<int> &v, uint n)
{
    v.resize(0);
    v.reserve(n);
    for (uint i=0; i<n; i++)
        v.push_back(i);
}

// check whether v contains elements 0..n-1
bool is_range(std::vector<int> &v, uint n)
{
    if (v.size() != n)
        return false;
    uint i = 0;
    while (i<n && v[i]==i)
        i++;
    return i >= n;
}

// swap elements in v in a random way.
// uses rand() -> user can call srand() to initialize rnd series
template <typename T>
void rnd_shuffle(std::vector<T> &v)  // Knuth / Fisher-Yates / Durstenfeld
{
    for (uint n = v.size(); n > 1; n--)
    {
        uint k = rand()%n;  // 0 <= k <= n - 1.
        std::swap(v[k], v[n - 1]);
    }
}

template <typename T>
void print(const std::vector<T> &v)
{
    for (uint i = 0; i < v.size(); i++)
        std::cout << v[i] << ' ';
    std::cout << std::endl;
}



void test_indirect_sort()
{
    ut_start_check_throw()

        // check sorteren:

        int N = 100;
        std::vector<int> v;
        make_range(v, N);
        srand((uint)time(0));
        rnd_shuffle(v);
        IndirectSort::sort(v);
        ut_check(is_range(v, N));


        // check aantal kopieen T:

        // random case:
        N = 100;
        std::vector<FakeInt> w;
        for (int i=0; i<N; i++)
            w.push_back(rand()%100);

        FakeInt::reset();
        IndirectSort::sort(w);
        //std::sort(w.begin(), w.end());
        //FakeInt::report();
        ut_check(FakeInt::counter.n_assign + FakeInt::counter.n_copy_ctor 
                    <= 150);

        // best case:
        w.resize(0);
        for (int i=0; i<N; i++) 
            w.push_back(i);
        FakeInt::reset();
        IndirectSort::sort(w);
        //std::sort(w.begin(), w.end());
        //FakeInt::report();
        ut_check(FakeInt::counter.n_assign + FakeInt::counter.n_copy_ctor
                    == 0);

        // worst case (voor cycli):
        w.resize(0);
        for (int i=0; i<N/2; i++) {
            w.push_back(i*2+1);
            w.push_back(i*2);
        }
        FakeInt::reset();
        IndirectSort::sort(w);
        //std::sort(w.begin(), w.end());
        //FakeInt::report();
        ut_check(FakeInt::counter.n_assign + FakeInt::counter.n_copy_ctor
                    <= 150);

    ut_check_didnt_throw()

}


#endif	/* _INDIRECTSORTTEST_H */


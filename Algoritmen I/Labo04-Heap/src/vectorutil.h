/* 
 * File:   vectorutil.h
 * Author: wijnand.schepens@hogent.be
 *
 * Created on 29 december 2009
 * Updated on 14 March 2011
 */

#ifndef _VECTORUTIL_H
#define	_VECTORUTIL_H

#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <functional>   // less

namespace vectorutil
{
    using std::vector;

    typedef unsigned int uint;

    // Fill v with values 0, ..., n-1.
    void fill_range(vector<int> &v, uint n)
    {
        v.clear();
        v.reserve(n);
        for (uint i=0; i<n; i++)
            v.push_back(i);
    }

    // Convenience (return vector copy => slow!).
    vector<int> make_range(uint n)
    {
        vector<int> v;
        fill_range(v, n);
        return v;
    }

    // Fills res with values n-1, ..., 0.
    void fill_reverse_range(vector<int> &res, uint n)
    {
        res.resize(0);
        res.reserve(n);
        for (uint i=0; i<n; i++)
            res.push_back(n-1-i);
    }

    // Convenience (return vector copy => slow!).
    vector<int> make_reverse_range(uint n)
    {
        vector<int> v;
        fill_reverse_range(v, n);
        return v;
    }
    
    // Checks whether v contains elements 0, ..., n-1.
    bool is_range(vector<int> &v, uint n)
    {
        if (v.size() != n)
            return false;
        uint i = 0;
        while (i<n && v[i]==i)
            i++;
        return i >= n;
    }

	// Fills v with n random int's in range [min, max].
	// Notes: the implementation uses rand() from <cstdlib>. Therefore
	// - the user should call srand(...) to initialize random series
	// - the range (max-min+1) must not be larger than RAND_MAX (32767 on most platforms)
    void fill_random(vector<int> &v, uint n, int min, int max)
    {
        v.resize(0);
        v.reserve(n);
        int r = max-min+1;
        for (uint i=0; i<n; i++)
            v.push_back(min + std::rand()%r);
    }

    // Convenience function (return vector copy => slow!).
    vector<int> make_random(uint n, int min, int max)
    {
        vector<int> v;
        fill_random(v, n, min, max);
        return v;
    }

    // Swaps elements in v in a random way.
    // Uses rand(). Therefore
	// - user should call srand(...) to initialize rnd series
	// - v.size() must not exceed RAND_MAX !
    template <typename T>
    void shuffle(vector<T> &v)  // Knuth / Fisher-Yates / Durstenfeld
    {
        for (uint n = v.size(); n > 1; n--)
        {
            uint k = rand()%n;  // 0 <= k <= n - 1.
            T tmp = v[k];
            v[k] = v[n - 1];
            v[n - 1] = tmp;
        }
    }

    // Reverses the ordering of the elements of v (in-place):
    template <typename T>
    void reverse(vector<T> &v) {
        uint i = 0, j = v.size() - 1;
        T h;
        while (i < j) {
            h = v[i];
            v[i] = v[j];
            v[j] = h;
        }
    }

    // Fills v with copies of value:
    template <typename T>
    void fill_uniform(vector<T> &v, uint n, const T &value)
    {
        v.resize(0);
        v.reserve(n);
        for (uint i=0; i<n; i++)
            v.push_back(value);
    }

    // Convenience (return vector copy => slow!).
    template <typename T>
    vector<T> make_uniform(uint n, const T &value)
    {
        vector<T> v;
        fill_uniform(v, n, value);
        return v;
    }

    // Writes elements of v with indices in [a, b[ to std-out.
    template <typename T>
    void print(const vector<T> &v, uint a, uint b) // v[a..b[
    {
        for (uint i = a; i < b; i++)
            std::cout << v[i] << ' ';
        std::cout << std::endl;
    }

    // Writes all elements of v to std-out.
    template <typename T>
    void print(const vector<T> &v) {
        print(v, 0, v.size());
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const vector<T> &v)
    {
        for (int i=0; i<v.size(); i++)
            os << v[i] << " ";
        return os;
    }

    // Checks whether the elements in v are ordered using ordering LESS,
    // that is v[i] <= v[j] if i < j.
    template <typename T, typename LESS>
    bool is_ordered(const vector<T> &v, const LESS &is_less) {
        uint i = 1;
        while (i < v.size() && !is_less(v[i], v[i - 1]))
            i++;
        return i >= v.size();
    }

    // Checks whether the elements in v are ordered using T's natural ordering
    template <typename T>
    bool is_ordered(const vector<T> &v) {
        return is_ordered(v, std::less<T > ());
    }

    // Check whether the elements in v are strictly ordered using ordering LESS,
    // that is v[i] < v[j] if i < j
    template <typename T, typename LESS>
    bool is_strictly_ordered(const vector<T> &v, const LESS &is_less = std::less<T>()) {
        uint i = 1;
        while (i < v.size() && is_less(v[i - 1], v[i]))
            i++;
        return i >= v.size();
    }

    // Checks whether the elements in v are ordered using T's natural ordering
    template <typename T>
    bool is_strictly_ordered(const vector<T> &v) {
        return is_strictly_ordered(v, std::less<T > ());
    }


    // Convenience functions:
    template <typename T>
    void stdsort(std::vector<T> &v)
    {
        std::sort(v.begin(), v.end());
    }

    template <typename T, typename CRIT>
    void stdsortcrit(std::vector<T> &v, const CRIT &crit)
    {
        std::sort(v.begin(), v.end(), crit);
    }

    template <typename T>
    void stdstablesort(std::vector<T> &v)
    {
        std::stable_sort(v.begin(), v.end());
    }

    template <typename T, typename CRIT>
    void stdstablesortcrit(std::vector<T> &v, const CRIT &crit)
    {
        std::stable_sort(v.begin(), v.end(), crit);
    }


} // namespace

#endif	


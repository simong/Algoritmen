/* 
 * File:   sorttest.h
 * Author: wijnand.schepens@hogent.be
 *
 * Created on 14 March 2010
 */

#ifndef _SORTTEST_H
#define	_SORTTEST_H

template <typename SORTFUNC>
bool _sort_ok(const SORTFUNC &sortfunc, uint n=100)
{
	vector<int> v1;
	vectorutil::fill_random(v1, n, -50, 50);
	vector<int> v2 = v1;
	sortfunc(v1);
	std::sort(v2.begin(), v2.end());
	return v1 == v2; 
}

#define sort_ok(SORTFUNC) (_sort_ok(SORTFUNC<int>))


struct EenheidKleiner { bool operator()(int a, int b) const { return a%10 < b%10; } };
struct TientalKleiner { bool operator()(int a, int b) const { return a/10 < b/10; } };

template <typename SORTFUNC>
bool _is_stable(const SORTFUNC &sortfunc) {
    std::vector<int> v;
    vectorutil::fill_range(v, 100);
    vectorutil::shuffle(v);
    std::sort(v.begin(), v.end(), EenheidKleiner());
    sortfunc(v, TientalKleiner());
    return vectorutil::is_range(v, 100);
}

#define is_stable(SORTFUNC) (_is_stable(SORTFUNC<int, TientalKleiner>))



#endif

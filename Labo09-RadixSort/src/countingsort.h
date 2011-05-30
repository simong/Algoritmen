/*
 * File:   countingsort.h
 * Author: Wijnand
 *
 * Created on 15 maart 2010, 19:58
 */

#ifndef _COUNTINGSORT_H
#define	_COUNTINGSORT_H

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

typedef unsigned int uint;


// sorteert elementen van v (stabiel) naar w
// uint CONVFUNC(T) is conversie- of selectiefunctie: beeldt T af op i in [0, k[
// gebruikt hulptabel van grootte k
template <typename T, typename CONVFUNC>
void counting_sort(const std::vector<T> &v, const CONVFUNC &convfunc, uint k, std::vector<uint> &hulp, std::vector<T> &w)
{
    uint n = v.size();

    // Initialiseren
    // hulp is eerst freq-tabel
    for (uint i=0; i<k; i++)
        hulp[i] = 0;

    // Over heel de tabel lopen en het aantal voor deze sleutel verhogen.
    // convfunc beeld T af als een uint.
    for (uint i=0; i<n; i++)
    {
        uint p = convfunc(v[i]);
        hulp[p]++;
    }

    // hulp wordt cumul-tabel = eindpositietabel
    // Als de tabel 4 2 3 5  7  bevat dan wordt deze
    //              4 6 9 14 21 wat de eindindexes aanduidt..
    for (uint j = 1; j < k; j++)
        hulp[j] += hulp[j - 1];

    // wegens stabiliteit van achter naar voor
    // Gebruik de hulp tabel om de index te bepalen van de elementen.
    // Iedere keer VOOR we een element plaatsen, gaat de positie in de hulptabel 1 naar beneden.
    for (int i = n-1; i >= 0; i--)
    {
        uint p = convfunc(v[i]);
        w[ --hulp[p] ] = v[i];
    }
}

template <typename T, typename CONVFUNC>
void counting_sort(std::vector<T> &v, const CONVFUNC &convfunc, uint k)
{
	std::vector<uint> hulp(k);
	std::vector<T>    w(v.size());
	counting_sort(v, convfunc, k, hulp, w);
	swap(v, w);
}




#endif	/* _COUNTINGSORT_H */


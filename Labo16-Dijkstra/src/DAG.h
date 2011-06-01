/*
 * DAG.h
 *
 *  Created on: May 31, 2011
 *      Author: simon
 */

#ifndef __DAG__
#define __DAG__

#include "ggraaf.h"
#include <vector>
#include <map>

using namespace std;

template<typename T>
class DAG {
public:
    void kortste_afstand(const GewogenGraaf<GERICHT, T> &g, int van, int naar) {
        // Topologisch sorteren
        topologische_sort(g);

        //
    }

private:

    vector<int> top_volgorde;
    vector<int> ingraden;

    void topologische_sort(const GewogenGraaf<GERICHT, T> &g) {
        // Via ingraden.
        int n = g.aantal_knopen();
        // Init
        for (int i = 0; i < n; i++) {
            ingraden[i] = 0;
        }

        // Verbindingen tellen
        for (int i = 0; i < n; i++) {
            map<int, int> knoop = g[i];
            for (map<int, int>::iterator it = knoop.begin(); it != knoop.end(); it++) {
                ingraden[(*it).first]++;
            }
        }

        // Zoek initieel alle ingraad met waarde = 0;
        for (int i = 0; i < n; i++) {
            ingraden[i] = 0;
        }
    }
};

#endif

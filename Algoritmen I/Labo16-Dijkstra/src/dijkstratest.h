#include "dijkstra.h"
#include "simpleunittest.h"

#include <iostream>

using namespace std;

void test_dijkstra() {
    //	ut_start_check_throw()

    Dijkstra<double> d;

    int n = 5;
    GewogenGraaf<GERICHT, double> g(n);

    cout << "test met " << g.aantal_verbindingen() << " verbindingen" << endl;

    d.start(g, 0);
    ut_check_equal(0.0, d.afstand(0));
    ut_check_equal(d.GEEN_OUDER, d.ouder(0));
    for (int i = 1; i < n; i++) {
        ut_check_equal(d.ONEINDIG, d.afstand(i));
        ut_check_equal(d.OUDER_ONBEPAALD, d.ouder(i));
    }

    g.voeg_verbinding_toe(1, 0, 2.0);
    cout << "test met " << g.aantal_verbindingen() << " verbindingen" << endl;

    d.start(g, 0);
    ut_check_equal(0.0, d.afstand(0));
    ut_check_equal(d.GEEN_OUDER, d.ouder(0));
    for (int i = 1; i < n; i++) {
        ut_check_equal(d.ONEINDIG, d.afstand(i));
        ut_check_equal(d.OUDER_ONBEPAALD, d.ouder(i));
    }

    d.start(g, 1);
    ut_check_equal(2.0, d.afstand(0));
    ut_check_equal(1, d.ouder(0));
    ut_check_equal(0.0, d.afstand(1));
    ut_check_equal(d.GEEN_OUDER, d.ouder(1));
    for (int i = 2; i < n; i++) {
        ut_check_equal(d.ONEINDIG, d.afstand(i));
        ut_check_equal(d.OUDER_ONBEPAALD, d.ouder(i));
    }

    g.voeg_verbinding_toe(2, 1, 3.0);
    cout << "test met " << g.aantal_verbindingen() << " verbindingen" << endl;

    d.start(g, 1);
    ut_check_equal(2.0, d.afstand(0));
    ut_check_equal(1, d.ouder(0));
    ut_check_equal(0.0, d.afstand(1));
    ut_check_equal(d.GEEN_OUDER, d.ouder(1));
    for (int i = 2; i < n; i++) {
        ut_check_equal(d.ONEINDIG, d.afstand(i));
        ut_check_equal(d.OUDER_ONBEPAALD, d.ouder(i));
    }

    d.start(g, 2);
    ut_check_equal(5.0, d.afstand(0));
    ut_check_equal(1, d.ouder(0));
    ut_check_equal(3.0, d.afstand(1));
    ut_check_equal(2, d.ouder(1));
    ut_check_equal(0.0, d.afstand(2));
    ut_check_equal(d.GEEN_OUDER, d.ouder(2));
    for (int i = 3; i < n; i++) {
        ut_check_equal(d.ONEINDIG, d.afstand(i));
        ut_check_equal(d.OUDER_ONBEPAALD, d.ouder(i));
    }

    g.voeg_verbinding_toe(2, 0, 7.0);
    cout << "test met " << g.aantal_verbindingen() << " verbindingen" << endl;

    d.start(g, 2);
    ut_check_equal(5.0, d.afstand(0));
    ut_check_equal(1, d.ouder(0));
    ut_check_equal(3.0, d.afstand(1));
    ut_check_equal(2, d.ouder(1));
    ut_check_equal(0.0, d.afstand(2));
    ut_check_equal(d.GEEN_OUDER, d.ouder(2));
    for (int i = 3; i < n; i++) {
        ut_check_equal(d.ONEINDIG, d.afstand(i));
        ut_check_equal(d.OUDER_ONBEPAALD, d.ouder(i));
    }

    g.voeg_verbinding_toe(2, 3, 0.5);
    g.voeg_verbinding_toe(3, 1, 0.5);
    cout << "test met " << g.aantal_verbindingen() << " verbindingen" << endl;

    d.start(g, 2);
    ut_check_equal(3.0, d.afstand(0));
    ut_check_equal(1, d.ouder(0));
    ut_check_equal(1.0, d.afstand(1));
    ut_check_equal(3, d.ouder(1));
    ut_check_equal(0.0, d.afstand(2));
    ut_check_equal(d.GEEN_OUDER, d.ouder(2));
    ut_check_equal(0.5, d.afstand(3));
    ut_check_equal(2, d.ouder(3));
    for (int i = 4; i < n; i++) {
        ut_check_equal(d.ONEINDIG, d.afstand(i));
        ut_check_equal(d.OUDER_ONBEPAALD, d.ouder(i));
    }

    //	ut_check_didnt_throw()

    ut_report();

}

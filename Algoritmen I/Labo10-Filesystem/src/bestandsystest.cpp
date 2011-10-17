#include <iostream>

#include "Knoop.h"
#include "Map.h"
#include "File.h"

using namespace std;

struct PostSchrijfBezoeker: public KnoopBezoeker {
    virtual void operator()(const Knoop* knoop) {
    }

    virtual void pre(Knoop *knoop, int niveau) {
    }
    virtual void post(Knoop *knoop, int niveau) {
        cout << niveau << ":" << knoop->get_dirnaam() << " ";
    }
};

struct DiepteMeter: public KnoopBezoeker {
    int max_level;
    DiepteMeter() :
        max_level(0) {
    }

    virtual void operator()(const Knoop* knoop) {
    }

    virtual void pre(Knoop *n, int niveau) {
    }
    virtual void post(Knoop *n, int niveau) {
        if (niveau > max_level)
            max_level = niveau;
    }
};

struct PreOrderBezoeker: public KnoopBezoeker {
    virtual void operator()(const Knoop* knoop) {
        cout << knoop->get_dirnaam() << " ";
    }

    virtual void pre(Knoop *n, int niveau) {
    }
    virtual void post(Knoop *n, int niveau) {
    }
};

struct KnoopTeller: public KnoopBezoeker {
    int aantal;
    KnoopTeller() :
        aantal(0) {
    }

    virtual void pre(Knoop *n, int niveau) {
    }
    virtual void post(Knoop *n, int niveau) {
    }

    virtual void operator()(const Knoop* knoop) {
        aantal++;
    }
};

int main() {
    Map *wortel = new Map("");

    Map *map1 = new Map("map1");
    wortel->voegToe(map1);

    wortel->voegToe(new File("tekst1"));

    Map *map11 = new Map("map11");
    map1->voegToe(map11);

    File *t2 = new File("tekst2");
    map11->voegToe(t2);

    Map *map2 = new Map("map2");
    wortel->voegToe(map2);

    map2->voegToe(new File("tekst3"));

    cout << "PAD: " << t2->get_padnaam() << endl;

    cout << "LIJST: " << endl;
    wortel->schrijf_lijst();

    cout << "BOOM: " << endl;
    wortel->schrijf_boom();

    cout << "PRE-ORDER: ";
    PreOrderBezoeker bezoeker;
    wortel->bezoek_preorder(bezoeker);
    cout << endl;

    cout << "AANTAL: ";
    KnoopTeller cnt;
    wortel->bezoek_preorder(cnt);
    cout << cnt.aantal << endl;

    cout << "POST: ";
    PostSchrijfBezoeker psb;
    wortel->bezoek_diepte_eerst(psb);
    cout << endl;

    cout << "DIEPTE: ";
    DiepteMeter dm;
    wortel->bezoek_diepte_eerst(dm);
    cout << dm.max_level << endl;

    cout << "LEVEL-ORDER: ";
    wortel->bezoek_level_order(bezoeker);
    cout << endl;
    return 0;
}

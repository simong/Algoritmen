#ifndef __BTREE
#define __BTREE
#include "schijf.h"
#include <iostream>
#include <stack>
using std::endl;
using std::cerr;
using std::ostream;

using namespace std;

//Dit bestand bevat code en hoofdingen van
template<class T, class D, unsigned int m>
class Btree;
template<class T, class D, unsigned int m>
class Bknoop;
//betekenis m: zie cursus

template<class T, class D, unsigned int m>
class Bknoop {
    friend class Btree<T, D, m> ;
public:
    const Bknoop<T, D, m>& operator=(const Bknoop<T, D, m>& b) {
        k = b.k;
        isblad = b.isblad;
        for (unsigned int i = 0; i < k; i++) {
            sleutels[i] = b.sleutels[i];
            data[i] = b.data[i];
        }
        if (!isblad) {
            for (unsigned int i = 0; i <= k; i++) {
                index[i] = b.index[i];
            }
        }
        return *this;
    }
    T sleutels[m];
    D data[m];
    blokindex index[m + 1];
    unsigned int k;
    bool isblad;

    // Voeg een waarde tussen in de array van sleutels/data
    // Gebruik dit enkel als er voldoende plaats is!
    int insert(T key, D val, blokindex bi);
};

template<class T, class D, unsigned int m>
class Btree {
    typedef Bknoop<T, D, m> Knoop;
public:
    Btree(Schijf<Knoop>& s)
            : schijf(s) {
        wortel.k = 0;
        wortel.isblad = true;
        wortelindex = schijf.schrijf(wortel);
    }

    void put(T key, D val);
    D get(T key);

private:
    Schijf<Knoop>& schijf;
    Knoop wortel;
    blokindex wortelindex;

    // Zoekt een waarde in de sleutels van knoop die bij key past.
    // Returned de waarde.
    // path het pad waarlangs we lopen om tot aan knoop te geraken.
    D search(T key, stack<blokindex>& path);

};

template<class T, class D, unsigned int m>
void Btree<T, D, m>::put(T key, D val) {
    // De juiste knoop zoeken.
    stack<blokindex> path;
    search(key, path);

    T key_to_add = key;
    D val_to_add = val;
    blokindex bi_to_add = 0;
    bool toegevoegd = false;
    while (!toegevoegd && !path.empty()) {
        // Haal de knoop van de stack.
        blokindex bi = path.top();
        path.pop();
        Knoop knoop;
        schijf.lees(knoop, bi);

        // Toevoegen.
        if (knoop.k < m) {
            // Als er nog genoeg plaats is, voegen we hem er gewoon tussen.
            knoop.insert(key_to_add, val_to_add, bi_to_add);
            schijf.herschrijf(knoop, bi);
            toegevoegd = true;
            // Hiermee is alles opgelost!
        }

        // Bummer, de knoop zit vol.
        // We splitsen deze knoop.
        // - Nieuwe broerknoop maken met de helft van de waardes.
        // - De value toevoegen (kan ook in broer knoop zijn!)
        // - de middenste waarde omhoog schuiven.
        else {

            // Broerknoop voor de helft vullen.
            Knoop broer;
            unsigned int midden = m / 2;
            broer.k = knoop.k - midden;
            for (unsigned int i = midden; i < knoop.k; i++) {
                broer.sleutels[i - midden] = knoop.sleutels[i];
                broer.data[i - midden] = knoop.data[i];
                if (!knoop.isblad) {
                    broer.index[i - midden] = knoop.index[i];
                }
            }

            // De linkerknoop bevat nu maar de helft van zijn data/kinderen meer.
            knoop.k = midden;

            // We voegen de nieuwe waarde toe.
            // Dit kan nu perfect, want beide knopen bevatten maar de helft van hun sleutels meer.
            if (key_to_add < knoop.sleutels[midden]) {
                knoop.insert(key_to_add, val_to_add, bi_to_add);
            }
            else {
                broer.insert(key_to_add, val_to_add, bi_to_add);
            }

            // We schuiven nu de grootste waarde van het linker kind omhoog (in-order correctheid)
            key_to_add = knoop.sleutels[knoop.k - 1];
            val_to_add = knoop.data[knoop.k - 1];
            knoop.k--; // -- omdat er een sleutel verdwijnt.

            // Knopen wegschrijven
            schijf.herschrijf(knoop, bi);
            bi_to_add = schijf.schrijf(broer);
        }
    }

    if (!toegevoegd && path.empty()) {
        // We moeten de wortel splitsen, en een nieuwe wortel knoop maken.

    }

}

template<class T, class D, unsigned int m>
D Btree<T, D, m>::get(T key) {
    // De blokindex boeit hier weinig...
    stack<blokindex> path;
    return search(key, path);
}

template<class T, class D, unsigned int m>
D Btree<T, D, m>::search(T key, stack<blokindex>& path) {
    Knoop knoop;
    schijf.lees(knoop, wortelindex);
    path.push(wortelindex);
    bool gevonden = false;

    while (!gevonden) {
        unsigned int i = 0;
        while (i < knoop.k && knoop.sleutels[i] < key) {
            i++;
        }

        if (i < knoop.k) {
            // We hebben de correcte sleutel gevonden.
            if (key == knoop.sleutels[i]) {
                return knoop.data[i];
            }
            else if (knoop.isblad) {
                // we hebben niks gevonden
                return 0;
            }
            else {
                // Nog niet tot het einde geitereerd en de sleutel is ook nog niet gevonden.
                // Dit wil zeggen dat we naar het kind moeten op pos i-1 !!! (want we zijn
                // eentje verder gegaan.)

                // Knoop van de schijf lezen.
                blokindex bindex = knoop.index[i - 1];
                path.push(bindex);
                schijf.lees(knoop, bindex);

                // Heel het proces opnieuw starten.
            }
        }
        else {
            return 0;
        }
    }
}

template<class T, class D, unsigned int m>
int Bknoop<T, D, m>::insert(T key, D val, blokindex bi) {
    // Zoek waar de sl moet komen
    unsigned int j = 0;
    while (j < k && sleutels[j] < key) {
        j++;
    }

    // Schuif alles erachter 1 plaats op.
    for (unsigned int v = k; v > j; v--) {
        sleutels[v] = sleutels[v - 1];
        data[v] = data[v - 1];
        if (!isblad) {
            index[v + 1] = index[v];
        }
    }

    // Plaats de sl daar.
    sleutels[j] = key;
    data[j] = val;
    if (!isblad && bi != 0) {
        index[j + 1] = bi;
    }
    k++;
    return j;
}

#endif

#ifndef __PATRICIA_H
#define __PATRICIA_H
#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "stringmetbits.h"

using std::ostream;

struct WordCount: public std::pair<int, StringMetBits> {
    WordCount(int count, StringMetBits& w) {
        first = count;
        second = w;
    }
};

bool operator<(const WordCount& x, const WordCount& y) {
    return y.first < x.first;
}

class Pboom;

class Pknoop;

class Pboom {
    friend class Pknoop;
public:
    Pboom();

    int get(const StringMetBits& sl);
    void insert(const StringMetBits& sl);
    std::priority_queue<WordCount> top20();

private:
    Pknoop* wortel;

    Pknoop* get(Pknoop* k, const StringMetBits& sl, int index);
    Pknoop* insert(Pknoop* k, Pknoop* parent, const StringMetBits& sl, int index);
    void visit(Pknoop* knoop, std::priority_queue<WordCount>& prio, int index);
};

class Pknoop {
    friend class Pboom;
protected:
    StringMetBits sl;
    int data;
    int index;
    Pknoop* links, *rechts;
    Pknoop(const StringMetBits& _sl, const int _data, int _index)
            : sl(_sl), data(_data), index(_index) {
    }
};

Pboom::Pboom() {
    // We maken een soort dummy knoop aan.
    // Hiervan vullen we enkel de linker kind pointer in (voorlopig naar zichzelf.)
    // Hierdoor zullen we later nooit met null pointers te maken hebben. Het rechterkind van de wortel
    // is de enige nullpointer in de hele boom.
    StringMetBits leeg("");
    wortel = new Pknoop(leeg, 0, -1);
    wortel->links = wortel;
}

int Pboom::get(const StringMetBits& sl) {
    // We beginnen bij het linker kind van de wortel (aangezien daar de eerste waarde kan zitten.)
    Pknoop* knoop = get(wortel->links, sl, -1);

    // Als de zoeksleutel niet in de boom zit, kan de zoek-methode toch
    // een knoop tonen. Hier gebeurt de enige sleutel vergelijking.
    if (knoop == 0 || knoop->sl.compare(sl) != 0) {
        return 0;
    }

    // We hebben de correcte knoop gevonden..
    return knoop->data;
}

Pknoop* Pboom::get(Pknoop* k, const StringMetBits& sl, int index) {
    // Als de index in de huidige knoop kleiner of gelijk aan de meegegeven index is
    // dan hebben we ofwel een terugverbinding naar een hoger gelegen knoop ofwel een
    // verbinding naar onszelf.
    // In beide situaties heeft verder zoeken geen zin meer.
    // We bubblen terug naar de zoek(sl) methode en doen daar een sleutel vergelijking.
    if (k->index <= index) {
        return k;
    }

    // We kunnen nog verder gaan.
    if (!sl.bit(k->index)) {
        return get(k->links, sl, k->index);
    }
    else {
        return get(k->rechts, sl, k->index);
    }
}

void Pboom::insert(const StringMetBits& sl) {
    // We zoeken naar de knoop met als sleutel, de zoeksleutel.
    Pknoop* knoop = get(wortel->links, sl, -1);

    // Situatie 1: sleutel bestaat.
    if (knoop->sl.compare(sl) == 0) {
        knoop->data++;
        return;
    }

    // Situatie 2: sleutel bestaat niet.
    // We zoeken de meest links verschillende bit.
    // Dan dalen we de boom opnieuw af:
    //  - als deze index groter (of gelijk) is voegen we hem tussen (tss 2 inwendige knopen)
    //  - als er een terugverbinding is, voegen we hem tussen. (dus blad)
    int bit = knoop->sl.verschilplaats(sl);
    wortel->links = insert(wortel->links, wortel, sl, bit);
}

Pknoop* Pboom::insert(Pknoop* k, Pknoop* parent, const StringMetBits& sl, int index) {
    // if (tss 2 inwendige || blad)
    if ((k->index >= index) || (k->index <= parent->index)) {
        bool bit_waarde = sl.bit(index);
        Pknoop* nieuw = new Pknoop(sl, 1, index);
        nieuw->links = (bit_waarde) ? k : nieuw;
        nieuw->rechts = (bit_waarde) ? nieuw : k;
        return nieuw;
    }

    // Links of rechts afdalen.
    if (!sl.bit(k->index)) {
        k->links = insert(k->links, k, sl, index);
    }
    else {
        k->rechts = insert(k->rechts, k, sl, index);
    }

    return k;
}

std::priority_queue<WordCount> Pboom::top20() {
    std::priority_queue<WordCount> prio;

    // DEZ bezoeken en aan queue toevoegen.
    visit(wortel->links, prio, -1);

    return prio;
}

void Pboom::visit(Pknoop* knoop, std::priority_queue<WordCount>& prio, int index) {
    if (knoop->index > index) {
        // Toevoegen.
        WordCount p(knoop->data, knoop->sl);
        prio.push(p);
        if (prio.size() > 20) {
            prio.pop();
        }

        // Kinderen bezoeken.
        visit(knoop->links, prio, knoop->index);
        visit(knoop->rechts, prio, knoop->index);
    }
}

#endif

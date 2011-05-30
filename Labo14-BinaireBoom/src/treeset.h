#ifndef _TREESET_H
#define	_TREESET_H

#include "Knoop.h"
#include <stack>

/*
template<typename T>
class TreeSetIterator {
public:

    // De knoop wijst hier naar de wortel.
    TreeSetIterator(const Knoop<T>* k);

    //operator*: geeft de waarde
    const T operator*() const;

    //operator++: gaat naar het volgende element
    TreeSetIterator<T> operator++(); // pre
    TreeSetIterator<T> operator++(int i); // post

    //operator==, operator!=: om iteratoren te vergelijken
    bool operator==(const TreeSetIterator<T>& b);
    bool operator!=(const TreeSetIterator<T>& b);

private:
    std::stack<Knoop<T>*> st;
    void zoek_kleinste(const Knoop<T>* k) const;
};
*/


// Set-implementatie gebaseerd op binaire zoekboom.
// Gebruikt natuurlijke orde operator<(T,T).
// Geen duplicaten.
template<typename T>
class TreeSet {
public:
    TreeSet();

    ~TreeSet();

    bool contains(const T &data) const;

    void add(const T &data);

    void remove(const T& data);

    void clear();

    int size();

    T k_de_kleinste(int n) const;

    template<typename V>
    void visit(V &visitor); // bezoek alle elementen van klein naar groot,
    // en pas op elk element visitor (functie/functor) toe.

    /*
    TreeSetIterator<T> begin() {
        return TreeSetIterator<T> (wortel);
    }
    TreeSetIterator<T> end() {
        return TreeSetIterator<T> (0);
    }*/

private:
    Knoop<T>* wortel;
    int nrOfElements;
};

//////////////////////
//  TreeSetIterator //
//////////////////////
/*
template<typename T>
TreeSetIterator<T>::TreeSetIterator(const Knoop<T>* k) {
    // Zoek het kleinste element, en steek alles wat er tussen ligt op een stack.
    zoek_kleinste(k);
}

template<typename T>
void TreeSetIterator<T>::zoek_kleinste(const Knoop<T>* k) const {
    if (k != 0) {
        st.push(k);
        if (k->links != 0) {
            zoek_kleinste(k->links);
        }
    }
}

template<typename T>
const T TreeSetIterator<T>::operator*() const {
    return st.top()->data;
}

template<typename T>
TreeSetIterator<T> TreeSetIterator<T>::operator++() {
    if (!st.empty()) {
        const Knoop<T>* k = st.pop();
        if (k->rechts != 0) {
            zoek_kleinste(k->rechts);
        }
    }
    return *this;
}

template<typename T>
TreeSetIterator<T> TreeSetIterator<T>::operator++(int i) {
    if (!st.empty()) {
        const Knoop<T>* k = st.pop();
        if (k->rechts != 0) {
            zoek_kleinste(k->rechts);
        }
    }
    return *this;
}
*/

//////////////////////
//      TreeSet     //
//////////////////////


template<typename T>
TreeSet<T>::TreeSet() :
    wortel(0), nrOfElements(0) {
}

template<typename T>
TreeSet<T>::~TreeSet() {
    if (wortel != 0)
        delete wortel;
}

template<typename T>
bool TreeSet<T>::contains(const T &data) const {
    if (wortel == 0)
        return false;

    return wortel->contains(data);
}

template<typename T>
void TreeSet<T>::add(const T& x) {
    if (wortel == 0) {
        wortel = new Knoop<T> (x);
        nrOfElements++;
    }

    else if (wortel->add(x))
        nrOfElements++;
}

template<typename T>
void TreeSet<T>::clear() {
    if (wortel != 0) {
        delete wortel;
        wortel = 0;
        nrOfElements = 0;
    }
}

template<typename T>
void TreeSet<T>::remove(const T& x) {
    if (wortel != 0) {
        if (wortel->remove(x))
            nrOfElements--;
    }
}

template<typename T>
template<typename V>
void TreeSet<T>::visit(V& visitor) {
    // in-order overlopen.
    if (wortel != 0)
        wortel->visit(visitor);
}

template<typename T>
int TreeSet<T>::size() {
    return nrOfElements;
}


template<typename T>
T TreeSet<T>::k_de_kleinste(int n) const {
    if (wortel != 0)
        return wortel->k_de_kleinste(n);

    throw "Out of range (set)";
}
#endif	


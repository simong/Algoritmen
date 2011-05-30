/*
 * heap.cpp
 *
 *  Created on: May 28, 2011
 *      Author: simon
 */
#include <iostream>
#include "heap.h"

using namespace std;

template<typename T>
Heap<T>::Heap(uint capaciteit_) :
    capaciteit(capaciteit_), aantal(0) {
    data = new T[capaciteit_ + 1];
}

template<typename T>
Heap<T>::~Heap() {
    delete[] data;
}

// maak heap leeg (capiciteit blijft behouden)
template<typename T>
void Heap<T>::clear() {
    //delete[] data;
    aantal = 0;
}

template<typename T>
bool Heap<T>::is_empty() const {
    return aantal == 0;
}

template<typename T>
uint Heap<T>::get_size() const {
    return aantal;
}

template<typename T>
uint Heap<T>::get_capacity() const {
    return capaciteit;
}

// referentie naar bovenste ('grootste') element
// throw IllegalAccess indien de heap leeg is
template<typename T>
const T &Heap<T>::top() const {
    if (aantal == 0)
        throw IllegalAccess();

    return data[1];
}

// verwijder top-element
// throw IllegalAccess indien de heap leeg is
template<typename T>
void Heap<T>::pop() {
    if (aantal == 0)
        throw IllegalAccess();

    // Eerste met laatste swappen, aantal verminderen
    swap(data[1], data[aantal]);
    aantal--;

    // Boom van boven naar beneden fixen
    int k = 1;

    // Zolang er een linkerkind is checken we..
    int kindA = 2 * k;
    int kindB = kindA + 1;
    while (kindA <= aantal) {
        int sw = k;

        // Als het linkerkind groter is dan de wortel, swappen we
        if (data[k] < data[kindA])
            sw = kindA;

        // Als er een rechterkind bestaat dat groter is dan hetgeen waar we gaan mee swappen
        // Swap dan met kind rechtse kind
        if (kindB <= aantal && data[sw] < data[kindB])
            sw = kindB;

        // Swap
        if (k != sw) {
            swap(data[k], data[sw]);

            k = sw;
            kindA = 2 * k;
            kindB = kindA + 1;
        }
        else {
            break;
        }
    }

}

// voeg een element x toe
// throw CapacityExceeded indien er geen plaats meer is
template<typename T>
void Heap<T>::push(T x) {
    if (aantal == capaciteit)
        throw CapacityExceeded();

    // Achteraan toevoegen
    int k = aantal + 1;
    data[k] = x;
    aantal++;

    // Boom van beneden naar omhoog fixen.
    int ouder = k / 2;
    // Zolang dat de ouder kleiner is, swappen
    while (ouder >= 1 && data[ouder] < data[k]) {
        swap(data[ouder], data[k]);
        k = ouder;
        ouder = ouder / 2;
    }
}

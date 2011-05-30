/*
 * Knoop.h
 *
 *  Created on: May 30, 2011
 *      Author: simon
 */

#ifndef KNOOP_H_
#define KNOOP_H_

template<typename T>
class Knoop {
public:
    Knoop(const T& x);
    ~Knoop();

    bool contains(const T &x) const;
    bool add(const T& x);
    bool remove(const T& x);
    void clear();

    template<typename V>
    void visit(V& visitor);
    T k_de_kleinste(int n) const;

private:
    Knoop* links;
    Knoop* rechts;
    T data;
    bool removed;

    //template<typename U>
    //friend class TreeSetIterator;
};

//////////////////////
//     Knoop        //
//////////////////////


template<typename T>
Knoop<T>::Knoop(const T& x) :
    links(0), rechts(0), data(x), removed(false) {
}

template<typename T>
Knoop<T>::~Knoop() {
    if (links != 0)
        delete links;
    if (rechts != 0)
        delete rechts;
}

template<typename T>
void Knoop<T>::clear() {
    if (links != 0)
        delete links;
    if (rechts != 0)
        delete rechts;
}

template<typename T>
bool Knoop<T>::contains(const T &x) const {
    if (x == data && removed != true)
        return true;

    if (x < data && links != 0)
        return links->contains(x);

    else if (data < x && rechts != 0)
        return rechts->contains(x);

    return false;
}

template<typename T>
bool Knoop<T>::add(const T& x) {
    bool added = false;
    if (x < data) {
        if (links == 0) {
            links = new Knoop(x);
            added = true;
        }
        else
            added = links->add(x);
    }

    else if (data < x) {
        if (rechts == 0) {
            rechts = new Knoop(x);
            added = true;
        }
        else
            added = rechts->add(x);
    }

    if (added) {
        aantal++;
    }
    return added;
}

template<typename T>
bool Knoop<T>::remove(const T& x) {
    if (x < data && links != 0)
        return links->remove(x);
    else if (data < x && rechts != 0)
        return rechts->remove(x);

    else if (x == data)
        removed = true;

    return removed;
}

template<typename T>
template<typename V>
void Knoop<T>::visit(V& visitor) {
    if (links != 0)
        links->visit(visitor);

    if (!removed)
        visitor(data);

    if (rechts != 0)
        rechts->visit(visitor);
}

template<typename T>
T Knoop<T>::k_de_kleinste(int n) const {
    if (links != 0 && links.aantal < n)
        return links->k_de_kleinste(n);
    if (links != 0)
        n = n - links.aantal;
    n--;

    if (n == 0)
        return data; // Deze knoop

    if (rechts != 0)
        return rechts->k_de_kleinste(n);

    throw new OutOfRangeException;
}

#endif /* KNOOP_H_ */

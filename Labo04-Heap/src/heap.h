#ifndef _HEAP_H_
#define _HEAP_H_

// Binaire heap met vaste capaciteit.
//
// Bevat elementen van het type T, eventueel met duplicaten.
// De wortel (top) is grootste element.
// Steunt (enkel) op operator<(T,T)
// T wordt "klein" ondersteld ("value type")

#include<vector>

using namespace std;

typedef unsigned int uint;

struct IllegalAccess {
};

struct CapacityExceeded {
};

template<typename T>
class Heap {
public:
    // maak nieuwe (lege) heap met gegeven capaciteit
    Heap(uint capaciteit_);

    ~Heap();

    // maak heap leeg (capiciteit blijft behouden)
    void clear();

    bool is_empty() const;

    uint get_size() const;

    uint get_capacity() const;

    // referentie naar bovenste ('grootste') element
    // throw IllegalAccess indien de heap leeg is
    const T &top() const;

    // verwijder top-element
    // throw IllegalAccess indien de heap leeg is
    void pop();

    // voeg een element x toe
    // throw CapacityExceeded indien er geen plaats meer is
    void push(T x);

private:
    int capaciteit;
    T* data;
    int aantal;
};

#endif

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
struct Comparer {
    bool operator()(const T a, const T b) {
        return a > b;
    }
};

template<typename T>
class Heap {
public:
    // maak nieuwe (lege) heap met gegeven capaciteit
    Heap(uint capaciteit_);

    // Maakt een heap van een bestaande collectie
    // Voor het gemak een vector.
    Heap(std::vector<T>& v, Comparer<T>& cmp_);

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
    Comparer<T> cmp;

    // Fixed een boom waarvan de "wortel" op positie k zit.
    void fix_top_down(int k);
};

#endif

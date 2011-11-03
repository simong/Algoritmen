#include <assert.h>

#include "treap.h"

int main() {
    srand(time(0));
    const int MAX = 1000;

    Treap<int, int> treap;
    for (int i = 0; i < MAX; i++) {
        assert(treap.add(i, i));
    }
    for (int i = 0; i < MAX; i++) {
        assert(treap.contains(i));
    }

    assert(treap.contains(MAX+1) == false);

    return 0;
}

#include<algorithm>



typedef unsigned int size;


struct point {
    double* coord;
};


class Vertex {
    point p;

    Vertex *left;
    Vertex *right;
};


class KDTree {
public:
    KDTree(unsigned int k) : k(k) {

    }

    void add_vector(point *points, uint size);

private:
    unsigned int k;

    Vertex* add_vector(point *points, uint start, uint size);
};

void KDTree::add_vector(point *points, uint size) {
    // Sort it.

    // Middensten pakken.
    uint m = size / 2;

    Vertex *v = new Vertex();
    v->left = add_vector(points, 0, m);
    v->left = add_vector(points, m+1, size);
}

Vertex* KDTree::add_vector(point *points, uint start, uint size) {
    uint m = (start + size) / 2;
    if (m != size) {
        Vertex *v = new Vertex();
        v->p = points[m];

        v->left = add_vector(points, 0, m);
        v->left = add_vector(points, m+1, size);
        return v;
    }
    else {
        return 0;
    }
}

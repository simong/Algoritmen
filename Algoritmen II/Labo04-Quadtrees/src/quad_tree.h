#ifndef quad_tree_h
#define quad_tree_h

#include<vector>
#include<iostream>

struct point {
    double x;
    double y;
    point() {
    }

    point(double x, double y)
            : x(x), y(y) {
    }
};

struct vertex {
    point p;

    /*
     * -----------------------
     * |         |           |
     * |   q2    |    q1     |
     * |         |           |
     * |         |           |
     * |-----------------------
     * |         |           |
     * |   q3    |    q4     |
     * |         |           |
     * -----------------------
     *
     */

    vertex *q1;
    vertex *q2;
    vertex *q3;
    vertex *q4;
};

class quad_tree {
private:
    vertex *root;
    unsigned int max_depth;
public:
    quad_tree() {
        root = 0;
        max_depth = 0;
    }
    // Voeg een punt toe aan de boom.
    // Returned true als het punt werd toegevoegd, false als het er al in zat.
    bool add(const point &p);

    bool remove(const point &p);
    // De hoogte van deze boom. (Dus het langst mogelijke pad).
    unsigned int height();

    void write();

private:
    void depth_first(vertex* v, std::vector<point>& points);
    void write(vertex *v);
};

bool quad_tree::add(const point &p) {
    // We houden bij hoe diep we in de quadtree afdalen als we een
    // punt toevoegen. (Voor de max diepte later in O(1) te kunnen bepalen.
    unsigned int height = 0;

    // We gebruiken een pointer naar pointer.
    // Op deze manier kunnen we simpel met pointers schuiven.
    vertex **v = &root;

    // Zolang onze pointer nog altijd naar een bestaande pointer wijst,
    // zit er een punt en moeten we verder opdelen.
    while (*v != 0) {
        // We dalen af in de boom.
        height++;

        // Kijk welke regio we moeten nemen.
        if (p.x > (*v)->p.x && p.y > (*v)->p.y) {
            v = &((*v)->q1);
        }
        else if (p.x < (*v)->p.x && p.y > (*v)->p.y) {
            v = &((*v)->q2);
        }
        else if (p.x < (*v)->p.x && p.y < (*v)->p.y) {
            v = &((*v)->q3);
        }
        else if (p.x > (*v)->p.x && p.y < (*v)->p.y) {
            v = &((*v)->q4);
        }

        // Dit punt zit al in de tree.
        // We returnen gewoon false.
        else {
            return false;
        }
    }

    // We gaan een nieuwe knoop toevoegen.
    // De padlengte vergroot met 1.
    height++;

    // Misschien is dit de maximum diepte van de boom
    if (height > max_depth)
        max_depth = height;

    // Creer een nieuwe knoop.
    *v = new vertex();
    (*v)->p = p;

    return true;
}

bool quad_tree::remove(const point &p) {
    vertex **v = &root;
    // 1. We gaan eerst op zoek naar de knoop die het punt bevat.
    // 2. We zetten de vertex pointer die hier naar verwijst op 0
    // 3. We voegen alle punten opnieuw toe.

    // 1. De knoop zoeken.
    while (*v != 0 && ((*v)->p.x != p.x && (*v)->p.y != p.y)) {
        // We dalen af in de boom.
        // Kijk welke regio we moeten nemen.
        if (p.x > (*v)->p.x && p.y > (*v)->p.y) {
            v = &((*v)->q1);
        }
        else if (p.x < (*v)->p.x && p.y > (*v)->p.y) {
            v = &((*v)->q2);
        }
        else if (p.x < (*v)->p.x && p.y < (*v)->p.y) {
            v = &((*v)->q3);
        }
        else if (p.x > (*v)->p.x && p.y < (*v)->p.y) {
            v = &((*v)->q4);
        }
    }
    // Als v == 0 dan zit het punt niet in de boom
    if (*v == 0 || ((*v)->p.x != p.x && (*v)->p.y != p.y)) {
        return false;
    }

    // We hebben de knoop gevonden. en *v wijst ernaar.
    // 'v' is dus een pointer naar de pointer die naar de knoop wijst die het punt bevat.
    // Kopieer de pointer
    vertex* copy = *v;

    // 2. We verwijderen de knoop.
    *v = 0;

    // 3. Alles onder deze knoop opnieuw toevoegen.
    //    In order
    std::vector<point> points;
    depth_first(copy->q1, points);
    depth_first(copy->q2, points);
    depth_first(copy->q3, points);
    depth_first(copy->q4, points);
    for (unsigned int i = 0; i < points.size(); i++) {
        add(points[i]);
    }

    return true;
}

void quad_tree::write() {
    if (root != 0) {
        write(root);
    }
}

void quad_tree::write(vertex* v) {
    if (v != 0) {
        std::cout << v->p.x << "," << v->p.y << std::endl;
        write(v->q1);
        write(v->q2);
        write(v->q3);
        write(v->q4);
    }
}

void quad_tree::depth_first(vertex* v, std::vector<point>& points) {
    if (v != 0) {
        points.push_back(v->p);
        depth_first(v->q1, points);
        depth_first(v->q2, points);
        depth_first(v->q3, points);
        depth_first(v->q4, points);
    }
}

unsigned int quad_tree::height() {
    return max_depth;
}

#endif

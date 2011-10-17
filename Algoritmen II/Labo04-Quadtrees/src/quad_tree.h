#ifndef quad_tree_h
#define quad_tree_h

struct point {
    double x;
    double y;
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
    bool add(point &p);

    // De hoogte van deze boom. (Dus het langst mogelijke pad).
    unsigned int height();
};

bool quad_tree::add(point &p) {
    // We houden bij hoe diep we in de quadtree afdalen als we een
    // punt toevoegen. (Voor de max diepte later in O(1) te kunnen bepalen.
    unsigned int height = 0;

    // We gebruiken een pointer naar pointer.
    // Op deze manier kunnen we simpel met pointers schuiven.
    vertex **v = &root;
    
    // Zolang onze pointer nog altijd naar een bestaande pointer wijst,
    // zit er een punt en moeten we verder opdelen.
    while(*v != 0) {
        // We dalen af in de boom.
        height ++;
        
        // Kijk welke regio we moeten nemen.
        if(p.x > (*v)->p.x && p.y > (*v)->p.y) {
            v = &((*v)->q1);
        }
        else if(p.x < (*v)->p.x && p.y > (*v)->p.y) {
            v = &((*v)->q2);
        }
        else if(p.x < (*v)->p.x && p.y < (*v)->p.y) {
            v = &((*v)->q3);
        }
        else if(p.x > (*v)->p.x && p.y < (*v)->p.y) {
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
    if(height > max_depth)
        max_depth = height;
    
    // Creer een nieuwe knoop.
    *v = new vertex();
    (*v)->p = p;
    
    return true;
}

unsigned int quad_tree::height() {
    return max_depth;
}

#endif

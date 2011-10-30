#include <iostream>
#include <math.h>
#include "quad_tree.h"
#include "csv.h"

using namespace std;

point generate(unsigned int i) {
    point p;
    p.x = ((10000 - 5 * i) * cos(i * 0.25 * M_PI));
    p.y = ((10000 - 5 * i) * sin(i * 0.25 * M_PI));
    return p;
}

void genereer_test() {

    // Paar puntjes genereren
    unsigned int max = 131073;
    point punten[max];
    for (unsigned int i = 0; i < max; i++) {
        punten[i] = generate(i);
    }

    // Ze in de volgorde dat ze gegenereerd zijn in de boom toevoegen.
    CsvData volgorde_csv("volgorde.csv", '.');
    for (unsigned int i = 2; i <= max; i = i * 2) {
        quad_tree boom;
        for (unsigned int j = 0; j < i; j++) {
            boom.add(punten[j]);
        }

        vector<unsigned int> v;
        v.push_back(i);
        v.push_back(boom.height());

        volgorde_csv.voegDataToe(v);
    }

    // Randomized
    CsvData randomized_csv("randomized.csv", '.');
    srand(time(NULL));
    for (unsigned int i = 0; i < max; i++) {
        unsigned int j = rand() % max;
        swap(punten[i], punten[j]);
    }

    for (unsigned int i = 2; i <= max; i = i * 2) {
        quad_tree boom;
        for (unsigned int j = 0; j < i; j++) {
            boom.add(punten[j]);
        }

        vector<unsigned int> v;
        v.push_back(i);
        v.push_back(boom.height());
        randomized_csv.voegDataToe(v);
    }

    cout << "Done" << endl;

}


int main(int argc, const char * argv[]) {
    // genereer_test();

    point p1(10, 10);
    point p2(20, 20);
    point p3(30, 30);
    point p4(40, 40);

    quad_tree tree;
    tree.add(p1);
    tree.add(p2);
    tree.add(p3);
    tree.add(p4);

    tree.remove(p1);

    tree.write();
    cout << "Done" << std::endl;
}


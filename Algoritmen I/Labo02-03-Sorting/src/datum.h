/*
 * Datum.h
 *
 *  Created on: May 28, 2011
 *      Author: simon
 */

#ifndef DATUM_H_
#define DATUM_H_

#include<iostream>

using namespace std;

class Datum {
public:
    // Constructors
    Datum();
    Datum(int jaar_, int maand_, int dag_);
    virtual ~Datum();

    int jaar;
    int maand;
    int dag;

    bool operator<(const Datum& datum) const;
    friend ostream& operator<<(ostream& os, const Datum& d) {
        os << d.jaar << "-" << d.maand << "-" << d.dag;
        return os;
    }
};

#endif /* DATUM_H_ */

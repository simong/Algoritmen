/*
 * Datum.cpp
 *
 *  Created on: May 28, 2011
 *      Author: simon
 */

#include <ostream>

#include "../datum.h"

Datum::Datum() :
    jaar(1970), maand(01), dag(01) {

}

Datum::Datum(int jaar_, int maand_, int dag_) :
    jaar(jaar_), maand(maand_), dag(dag_) {

}

Datum::~Datum() {
}

// < operator
bool Datum::operator<(const Datum& b) const {

    if (this->jaar < b.jaar)
        return true;
    else {
        if (this->maand < b.maand)
            return true;
        else {
            if (this->dag < b.dag)
                return true;
            else
                return false;
        }
    }
}

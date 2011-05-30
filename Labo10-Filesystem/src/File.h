/*
 * Bestand.h
 *
 *  Created on: May 29, 2011
 *      Author: simon
 */

#ifndef BESTAND_H_
#define BESTAND_H_

#include "Knoop.h"
#include "Map.h"

class File: public Knoop {
public:
    File(const std::string& naam_);

    virtual bool is_map() const {
        return false;
    }
    virtual void schrijf_boom_knoop(unsigned int niveau) const;
};

#endif /* BESTAND_H_ */

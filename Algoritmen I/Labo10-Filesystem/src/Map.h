/*
 * Map.h
 *
 *  Created on: May 29, 2011
 *      Author: simon
 */

#ifndef MAP_H_
#define MAP_H_

#include<vector>
#include "Knoop.h"

class Map: public Knoop {
public:
    Map(const std::string& naam_);
    std::vector<Knoop*> kinderen;

    void voegToe(Knoop* k);
    virtual bool is_map() const {
        return true;
    }

    virtual void schrijf_boom_knoop(unsigned int niveau) const;
    void schrijf_lijst() const;
    void schrijf_boom() const;
};

#endif /* MAP_H_ */

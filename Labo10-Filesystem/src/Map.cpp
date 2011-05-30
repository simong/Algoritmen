/*
 * Map.cpp
 *
 *  Created on: May 29, 2011
 *      Author: simon
 */

#include<vector>
#include<iostream>

#include "Map.h"
#include "Knoop.h"

Map::Map(const std::string& naam_) :
    Knoop(naam_) {
}

void Map::voegToe(Knoop* k) {
    k->ouder = this;
    kinderen.push_back(k);
}

void Map::schrijf_lijst() const {
    for (unsigned int i = 0; i < kinderen.size(); i++) {
        std::cout << kinderen[i]->get_dirnaam() << std::endl;
    }
}


void Map::schrijf_boom_knoop(unsigned int niveau) const {
    schrijf_spaties(niveau);
    std::cout << get_dirnaam() << std::endl;

    // kinderen
    for (unsigned int i = 0; i < kinderen.size(); i++) {
        kinderen[i]->schrijf_boom_knoop(niveau + 1);
    }
}

void Map::schrijf_boom() const {
    schrijf_boom_knoop(0);
}

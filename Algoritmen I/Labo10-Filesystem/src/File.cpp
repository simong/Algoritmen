/*
 * Bestand.cpp
 *
 *  Created on: May 29, 2011
 *      Author: simon
 */

#include "File.h"
#include "Knoop.h"
#include<iostream>

File::File(const std::string& naam_) :
    Knoop(naam_) {
}

void File::schrijf_boom_knoop(unsigned int niveau) const {
    schrijf_spaties(niveau);
    std::cout << get_dirnaam() << std::endl;
}

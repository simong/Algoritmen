/*
 * Knoop.cpp
 *
 *  Created on: May 29, 2011
 *      Author: simon
 */

#include "Knoop.h"
#include "Map.h"
#include<iostream>
#include<queue>

Knoop::Knoop(const std::string& naam_) :
    naam(naam_), ouder(0) {
}

std::string Knoop::get_dirnaam() const {
    if (is_map()) {
        return naam + "/";
    }

    return naam;
}

std::string Knoop::get_padnaam() const {
    Knoop* parent = ouder;
    std::string pad = get_dirnaam();
    while (parent != 0) {
        pad = parent->get_dirnaam() + pad;
        parent = parent->ouder;
    }
    return pad;
}

void Knoop::schrijf_spaties(unsigned int niveau) const {
    for (unsigned int i = 0; i < niveau * 2; i++) {
        std::cout << " ";
    }
}

void Knoop::bezoek_preorder(KnoopBezoeker& bezoeker) {
    bezoeker(this);

    if (is_map()) {
        const Map* map = (Map*) this;

        for (unsigned int i = 0; i < map->kinderen.size(); i++) {
            map->kinderen[i]->bezoek_preorder(bezoeker);
        }
    }
}
void Knoop::bezoek_diepte_eerst(KnoopBezoeker& bezoeker) {
    bezoek_diepte_eerst(bezoeker, 0);
}
void Knoop::bezoek_diepte_eerst(KnoopBezoeker& bezoeker, unsigned int niveau) {

    bezoeker.pre(this, niveau);

    bezoeker(this);

    if (is_map()) {
        const Map* map = (Map*) this;
        for (unsigned int i = 0; i < map->kinderen.size(); i++) {
            map->kinderen[i]->bezoek_diepte_eerst(bezoeker, niveau + 1);
        }
    }

    bezoeker.post(this, niveau);
}

void Knoop::bezoek_level_order(KnoopBezoeker& bezoeker) {

    // Kinderen aan queue toevoegen.
    std::queue<Knoop*> wachtlijst;
    wachtlijst.push(this);

    while (!wachtlijst.empty()) {
        Knoop* k = wachtlijst.front();
        wachtlijst.pop();
        bezoeker(k);

        if (k->is_map()) {
            const Map* map = (Map*) k;
            for (unsigned int i = 0; i < map->kinderen.size(); i++) {
                wachtlijst.push(map->kinderen[i]);
            }
        }
    }
}

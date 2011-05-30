/*
 * Knoop.h
 *
 *  Created on: May 29, 2011
 *      Author: simon
 */

#include<string>

#ifndef KNOOP_H_
#define KNOOP_H_

class File;
class Map;
class Knoop;

struct KnoopBezoeker {
    virtual void pre(Knoop *n, int niveau) = 0;
    virtual void post(Knoop *n, int niveau) = 0;
    virtual void operator()(const Knoop* knoop)=0;
};

class Knoop {
public:
    Knoop(const std::string& naam_);
    std::string naam;
    Knoop* ouder;

    std::string get_padnaam() const;
    std::string get_dirnaam() const;
    virtual bool is_map() const=0;
    virtual void schrijf_boom_knoop(unsigned int niveau) const=0;

    void bezoek_preorder(KnoopBezoeker& bezoeker);
    void bezoek_diepte_eerst(KnoopBezoeker& bezoeker);
    void bezoek_level_order(KnoopBezoeker& bezoeker);

private:
    void bezoek_diepte_eerst(KnoopBezoeker& bezoeker, unsigned int niveau);
    void schrijf_spaties(unsigned int niveau) const;

    friend class File;
    friend class Map;
};

#endif /* KNOOP_H_ */

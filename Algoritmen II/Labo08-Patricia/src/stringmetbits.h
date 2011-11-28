#ifndef __STRINGMETBITS_H
#define __STRINGMETBITS_H
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>

typedef unsigned int        uint; // OS X issue


/**********************************************************************

 Class: StringMetBits

 beschrijving: klasse van strings met bitbehandelingsmogelijkheden.
 Elke StringMetBits wordt impliciet aangevuld met oneindig veel 1-bits en kan dus geen
 prefix zijn van een andere StringMetBits. Wel zou het karakter char(0) achteraan
 tot problemen leiden.
 Een StringMetBits mag dan ook het karakter char(0) niet bevatten en dit wordt gecheckt
 in de constructor, maar niet in wijzigingsoperatoren.

 ***************************************************************************/

class StringMetBits: public std::string {
public:
    StringMetBits(const std::string& str);
    StringMetBits(const StringMetBits& str);
    StringMetBits(const char* str = "");
    void check0();
    bool bit(int i) const;
    int geefAantalBits() const;
    //geeft -1 terug als strings gelijk zijn, anders plaats van meest linkse verschilbit
    int verschilplaats(const StringMetBits& sb) const;
};
StringMetBits::StringMetBits(const std::string& str)
        : std::string(str) {
    check0();
}
StringMetBits::StringMetBits(const StringMetBits& str)
        : std::string(str) {
    check0();
}

StringMetBits::StringMetBits(const char* str)
        : std::string(str) {
    check0();
}

void StringMetBits::check0() {
    for (int i = 0; i < size(); i++) {
        assert((*this)[i]!=char(0));
    }
}

bool StringMetBits::bit(int i) const {
    if (i >= size() * 8)
        return false;
    else
        return ((*this)[i / 8] & uint(1) << (7 - (i % 8)));
}

int StringMetBits::geefAantalBits() const {
    return size() * 8;
}

int StringMetBits::verschilplaats(const StringMetBits& sb) const {
    int minlengte = std::min(size(), sb.size());
    int i = 0;
    while (i < minlengte && (*this)[i] == sb[i])
        i++;
    int bitplaats = 8 * i; //plaats 1e bit in verschillend karakter
    if (i == minlengte && size() == sb.size())
        return -1;
    else {
        //while moet niet testen op overloop: er is een verschillende bit
        int bitplaats = 8 * i; //plaats 1e bit in verschillend karakter
        while (bit(bitplaats) == sb.bit(bitplaats)) {
            bitplaats++;
        }
        return bitplaats;
    }
}

#endif


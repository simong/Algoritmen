/*
 * util.cpp
 *
 *  Created on: May 29, 2011
 *      Author: simon
 */

#include<vector>
#include "vectorutil.h"

typedef unsigned int uint;

// returns unsigned ASCII-value in [0, 255]
uint ascii(char c) {
    return (uint) (unsigned char) c;
}

struct stringchar {
    uint i;
    stringchar(int i_) :
        i(i_) {
    }
    uint operator()(const std::string &s) const {
        // EDIT START
        if (i >= s.size()) {
            return 0;
        }

        // EDIT END
        return ascii(s[i]);
    }
};

bool same_length(std::vector<std::string> &v) {
    for (uint i = 1; i < v.size(); i++)
        if (v[i].size() != v[i - 1].size())
            return false;
    return true;
}

template<typename F>
bool sort_ok(const F &sortfunc, const std::vector<std::string> &v) {
    std::vector<std::string> v1(v);
    std::vector<std::string> v2(v);
    sortfunc(v1);
    std::sort(v2.begin(), v2.end());
    vectorutil::print(v1);
    vectorutil::print(v2);
    return v1 == v2;
}

template<typename F>
bool len4_ok(const F &sortfunc) {
    std::string strings[] = { "room", "velo", "room", "velg", "riep", "volk",
            "klop", "raam", "oven", "raak", "raap" };
    uint n = sizeof(strings) / sizeof(std::string);
    std::vector<std::string> v(strings, strings + n);
    return sort_ok(sortfunc, v);
}

template<typename F>
bool len3_ok(const F &sortfunc) {
    std::string strings[] = { "vel", "roo", "vel", "rie", "vol", "klo", "raa",
            "ova", "ovi", "rap" };
    uint n = sizeof(strings) / sizeof(std::string);
    std::vector<std::string> v(strings, strings + n);
    return sort_ok(sortfunc, v);
}

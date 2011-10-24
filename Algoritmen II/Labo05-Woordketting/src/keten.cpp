#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using std::min;
using std::ostream;
using std::string;
using std::vector;

class Keten {
public:
    Keten(const vector<string>& _v)
            : v(_v) {
    }

    friend ostream& operator<<(ostream& os, const Keten& k) {
        if (k.v.size() > 0) {
            os << k.v[0];
            for (int i = 1; i < k.v.size(); i++) {
                int l = min(k.v[i - 1].size(), k.v[i].size()); //l= lengte overlapping
                while (l > 0
                        && k.v[i - 1].substr(k.v[i - 1].size() - l, l)
                                != k.v[i].substr(0, l))
                    l--;
                os << k.v[i].substr(l, k.v[i].size() - l) << " ";
            }
        }
        return os;
    }
private:
    const vector<string>& v;
};

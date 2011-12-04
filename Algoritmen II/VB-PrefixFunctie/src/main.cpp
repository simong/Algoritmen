#include <iostream>
#include <string>
#include <vector>

#include "prefix.h"

using namespace std;

int main() {
    string t = "ABAAAABAAAAAAAAA";
    string p = "BAAAAAAAAA";

    string f = p + "#" + t;

    vector<unsigned int> v = prefix(f);

    cout << f << endl;
    for (unsigned int i = 0; i < v.size(); i++) {
        cout << v[i];
    }

    vector<int> matches;
    for (unsigned int i = 0; i < v.size(); i++) {
        if (v[i] == p.size())
            matches.push_back(i - 2 * p.size());
    }
    cout << endl;

    cout << t << endl;
    unsigned int spaces = 0;
    for (unsigned int i = 0; i < matches.size(); i++) {
        for (unsigned int j = matches[i] - spaces - i; j > 0; j--) {
            cout << " ";
            spaces++;
        }

        cout << "^";
    }

    cout << endl;

    return 0;
}

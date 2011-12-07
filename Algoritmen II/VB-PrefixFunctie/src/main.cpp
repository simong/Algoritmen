#include <iostream>
#include <string>
#include <vector>

#include "prefix.h"

using namespace std;


void print(vector<unsigned int>& v) {
    for (unsigned int i = 0; i < v.size(); i++)
        cout << v[i];

    cout << endl;
}

int main() {
    string p = "aabaabaaab";
    cout << p << endl;
    vector<unsigned int> prefixes = prefix(p);
    vector<unsigned int> suffixes = suffix(p);
    print(prefixes);
    print(suffixes);

    /*
     string t = "ABAAAABAAAAAAAAA";

     string f = p + "#" + t;

     vector<unsigned int> v = suffix(f);

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
     */

    return 0;
}

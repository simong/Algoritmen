#include <string>
#include <vector>

using namespace std;

int calc_prefix(std::string& s, unsigned int i, std::vector<unsigned int>& prefixes) {
    if (i == 0)
        return 0;

    int pi = prefixes[i - 1];
    while (pi != 0) {
        if (s[pi] == s[i])
            return pi + 1;
        else
            pi = prefixes[pi - 1];
    }

    if (s[pi] == s[i])
        return pi + 1;
    else
        return pi;
}

vector<unsigned int> prefix(std::string s) {
    vector<unsigned int> prefixes(s.size());

    for (unsigned int i = 0; i < s.size(); i++) {
        prefixes[i] = calc_prefix(s, i, prefixes);
    }

    return prefixes;
}

unsigned int calc_suffix(std::string& s, unsigned int i,
        std::vector<unsigned int>& suffixes) {
    if (i == s.size() - 1)
        return 0;

    unsigned int pi = suffixes[i + 1];
    while (pi != 0) {
        if (s[s.size() - pi -1] == s[i])
            return pi + 1;
        else
            pi = suffixes[s.size() - pi + 1];
    }

    if (s[s.size() - pi-1] == s[i])
        return pi + 1;
    else
        return pi;
}

vector<unsigned int> suffix(std::string s) {
    vector<unsigned int> suffixes(s.size());

    for (int i = s.size() - 1; i >= 0; i--) {
        suffixes[i] = calc_suffix(s, i, suffixes);
    }

    return suffixes;
}

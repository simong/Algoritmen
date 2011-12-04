#include <iostream>

typedef unsigned char uchar;
typedef unsigned int uint;

int d = 256; // Grootte van het alfabet: ASCI
int Q = 997; // Ons priem getal

// Via horner de hash van een string berekenen.
int hash(const uchar* str, uint m) {
    int h = 0;
    for (uint j = 0; j < m; j++)
        h = (d * h + str[j]) % Q;

    return h;
}

bool check_same(const uchar* str, uint pos, const uchar* pattern, uint m) {
    // We kijken of het stukje string dat begint op positie pos in 'str'
    // gelijk is aan het pattern.

    // Bij een Monte Carlo algoritme returnen we hier altijd true.
    // return true;

    // Bij een Las vegas algortime doen we een expliciete check.
    for (uint i = 0; i < m; i++)
        if (str[pos + i] != pattern[i])
            return false;

    return true;
}

// Zal de positie returnen waar pattern voorkomt in de text.
int search(const uchar* text, uint n, const uchar* pattern, uint m) {
    // We berekenen een hash waarde voor ons pattern.
    uint pattern_hash = hash(pattern, m);

    // We berekenen de initiele hash T1.
    uint text_hash = hash(text, m); // we berekenen een hash voor lengte m !!! (dus niet de hele haystack!)

    // Het kan zijn dat we al een match hebben..
    if (text_hash == pattern_hash && check_same(text, 0, pattern, m))
        return 0;

    // We hebben d^(m-1) % Q nodig.
    // Onderstaande for lus is niks meer dan de machtsverheffing, gemodulo'd.
    int dm = 1;
    for (uint i = 0; i < m - 1; i++)
        dm = (dm * d) % Q;

    // De eerste m karakters zijn _niet_ het pattern.
    // check al de volgende.
    for (uint i = m; i < n; i++) {
        // ipv een hash te berekenen voor _alle_ deelstrings, leiden we de hash af uit de vorige. (anders zou het O(mn) zijn)
        // 1. We trekken er het eerste karakter vooraan af.
        // 2. We tellen het nieuwe karakter erbij op.
        text_hash = (text_hash + Q - (dm * text[i - m]) % Q) % Q; //  1.
        text_hash = (text_hash * d + text[i]) % Q; //  2.

        // Vergelijk de hashes.
        if (text_hash == pattern_hash && check_same(text, i - m + 1, pattern, m))
            return i-m+1;
    }

    return -1;
}

int main() {
    const uchar text[] = "abeta beta charly alfa";
    const uchar pattern[] = "beta";

    int loc = search(text, 23, pattern, 4);
    std::cout << loc;

    return 0;
}

#include <iostream>
#include <string>
#include <queue>

#include "patricia.h"
#include "stringmetbits.h"

void test() {

    Pboom boom;

    StringMetBits s1("alfa");
    StringMetBits s2("beta");
    StringMetBits s3("delt");
    StringMetBits s4("jaja");
    StringMetBits s5("baby");

    boom.insert(s1);
    boom.insert(s1);

    boom.insert(s2);
    boom.insert(s2);
    boom.insert(s2);

    boom.insert(s3);

    boom.insert(s4);

    boom.insert(s5);
    boom.insert(s5);

    std::cout << s1 << ": " << boom.get(s1) << std::endl;
    std::cout << s2 << ": " << boom.get(s2) << std::endl;
    std::cout << s3 << ": " << boom.get(s3) << std::endl;
    std::cout << s4 << ": " << boom.get(s4) << std::endl;
    std::cout << s5 << ": " << boom.get(s5) << std::endl;
}

void lees_bijbel(Pboom& boom) {

    // Bijbel inlezen.
    std::ifstream in;
    in.open("bible.txt");
    if (!in.good()) {
        throw "Failed to read file.";
    }
    int i = 0;
    while (in.good()) {
        std::string s;
        in >> s;
        if (s != "") {
            StringMetBits smb(s);
            boom.insert(smb);
            if (s == "the") {
                i++;
            }
        }
    }

    std::cout << "the: " << i << std::endl;
}
void lees_test() {
    Pboom boom;
    lees_bijbel(boom);

    // Eerste 20 uit de boom halen.
    // In-order over de boom lopen, in prio queue steken (op aantal)
    // en als er > dan 20 in steken, poppen.

    std::priority_queue<WordCount> prio = boom.top20();
    for (unsigned int i = prio.size(); i > 0; i--) {
        std::pair<int, StringMetBits> p = prio.top();
        std::cout << i << ". " << p.second << " - " << p.first << std::endl;
        prio.pop();
    }

}

int main() {
    lees_test();
}

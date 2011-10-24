#include "graaf.h"
#include "keten.cpp"

#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::cerr;

void lees(GraafMetKnoopEnTakdata<GERICHT, std::string, std::string>& graaf
        , std::map<std::string, int>& knopen) {
    // Al de woorden inlezen
    std::ifstream woordenlijst;
    woordenlijst.open("woordenlijst.txt");
    if (woordenlijst.fail()) {
        throw "Kon woordenlijst niet inlezen.";
    }
    std::string woord;
    woordenlijst >> woord;
    while (!woordenlijst.fail()) {
        int knoopID = graaf.voegKnoopToe(woord);
        knopen[woord] = knoopID;
        woordenlijst >> woord;
    }
    cout << "Alle woorden ingelezen." << endl;
    ;

    // Al de takken inlezen
    std::ifstream takkenlijst;
    takkenlijst.open("takkenlijst.txt");
    if (takkenlijst.fail()) {
        throw "Kon takkenlijst niet inlezen.";
    }
    std::string woordA;
    std::string woordB;
    std::string verbinding;
    takkenlijst >> woordA;
    takkenlijst >> woordB;
    takkenlijst >> verbinding;
    while (!takkenlijst.fail()) {
        int van = knopen[woordA];
        int naar = knopen[woordB];
        try {
            graaf.voegVerbindingToe(van, naar, verbinding);
        } catch (GraafExceptie e) {
            cerr << e << endl;
        }

        takkenlijst >> woordA;
        takkenlijst >> woordB;
        takkenlijst >> verbinding;
    }
    cout << "Alle verbindingen ingelezen." << endl;
}


void print_keten(std::stack<int>& st, GraafMetKnoopEnTakdata<GERICHT, std::string, std::string>& graaf) {
    std::vector<std::string> v;
    int van = st.top();
    st.pop();
    while (!st.empty()) {
        int naar = st.top();
        st.pop();
        std::string* verb = graaf.geefTakdata(van, naar);
        if (verb != 0) {
            v.push_back(*verb);
            cout << *verb << endl;
        }
        van = naar;
    }

    Keten keten(v);
    //std::cout << keten << endl;
}

int main() {

    GraafMetKnoopEnTakdata<GERICHT, std::string, std::string> graaf;
    std::map<std::string, int> knopen;

    lees(graaf, knopen);

    std::string begin_woord = "aal";
    int begin_knoop = knopen[begin_woord];

    // 1. Graaf omkeren
    GraafMetKnoopEnTakdata<GERICHT, std::string, std::string> omgekeerde_graaf;
    omgekeerde_graaf = graaf.keerom();

    // 2. DEZ in de omgekeerde graaf beginnende bij de begin knoop.
    std::stack<int> s = omgekeerde_graaf.diepte_eerst_zoeken(begin_knoop);

    // 3. Diepte eerst zoeken op de post order nummers in de gewone graaf.
    std::vector<Kleur> kleuren(graaf.aantalKnopen(), WIT);
    std::vector<std::stack<int> > componenten;

    while (!s.empty()) {
        int knoop_id = s.top();
        if (kleuren[knoop_id] == WIT) {
            std::stack<int> pad;
            graaf.behandel(knoop_id, kleuren, pad);
            componenten.push_back(pad);
        }
        s.pop();
    }

    std::cout << "Er zijn " << componenten.size() << " componenten gevonden." << std::endl;
    print_keten(componenten[0], graaf);
    return 0;
}

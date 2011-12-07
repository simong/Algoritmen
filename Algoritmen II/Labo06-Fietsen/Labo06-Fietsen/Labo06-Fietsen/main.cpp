#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <cstdlib>

#include <vector>
#include <map>

#include "tinyxml.h"

#include "graaf.h"

using namespace std;

class Knoop {
public:
    int nummer;
    double x;
    double y;
    double hoogte;
};


ostream &operator<<(ostream &os, const Knoop& k){
    return os << k.nummer;
}


void lees_graaf(GraafMetKnoopEnTakdata<ONGERICHT, Knoop, int>& graaf) {
    // De XML inlezen
    TiXmlDocument doc( "fietsgraaf.xml" );
    doc.LoadFile();
    TiXmlNode* netwerk;
    netwerk = doc.RootElement();
    
    
    // De knopen toevoegen.
    for (TiXmlNode* knooppunt = netwerk->FirstChild(); knooppunt!=0;knooppunt = knooppunt->NextSibling()){
        TiXmlElement* el = dynamic_cast<TiXmlElement*>(knooppunt);
        
        Knoop knoop;
        knoop.nummer = atoi(el->Attribute("nummer"));
        knoop.x      = atof(el->Attribute("xcoordinaat"));
        knoop.y      = atof(el->Attribute("ycoordinaat"));
        knoop.hoogte = atof(el->Attribute("hoogte"));
        
        graaf.voegKnoopToe(knoop);
    }
    
    
    // Verbindingen leggen.
    for (TiXmlNode* knooppunt = netwerk->FirstChild(); knooppunt!=0;knooppunt = knooppunt->NextSibling()){
        TiXmlElement* el = dynamic_cast<TiXmlElement*>(knooppunt);
        
        int van = atoi(el->Attribute("nummer"));
        for(TiXmlNode* route = knooppunt->FirstChild(); route != 0;route = route->NextSibling()){
            try {
                TiXmlElement* route_el = dynamic_cast<TiXmlElement*>(route);
                int naar = atoi(route_el->Attribute("doel"));
                graaf.voegVerbindingToe(van, naar, 1); // capaciteit = 1.
            }
            catch (GraafExceptie& e) {
                //cout << e.what() << endl;
            }
        }
        
    }
}

struct edge {
    int van;
    int naar;
    int rest;
    int verbnr;
};

bool verbinding_niet_in_pad(vector<edge>& pad, int buur, int rest_capaciteit) {
    for (vector<edge>::iterator it = pad.begin(); it != pad.end(); it++) {
        edge e = *it;
        if (e.naar == buur && e.rest == rest_capaciteit)
            return false;
    }
    
    return true;
}

bool zoek_pad(GraafMetKnoopEnTakdata<ONGERICHT, Knoop, int>& graaf ,vector<edge>& pad, vector<int>& flow, int van, int naar) {
    // Zal een pad in de graaf zoeken.
    // het pad zal in de pad-stack gepushed worden.
    
    // Misschien hebben we ons doel al bereikt?!
    if (van == naar)
        return true;
    
    // Helaas, doe DEZ en bepaal een pad.
    
    // buur => verbindingsnummer.
    map<int, int> buren = graaf[van];
    for (map<int, int>::iterator it = buren.begin(); it != buren.end();it++) {
        int buur   = (*it).first;
        int verbnr = (*it).second;
        
        // Kijk of we meer stroom over deze verbinding kunnen sturen.
        // Zoja, gebruik deze verbinding.
        int rest_capaciteit = *(graaf.geefTakdata(van, buur)) - flow[verbnr];
        if (rest_capaciteit > 0 && verbinding_niet_in_pad(pad, buur, rest_capaciteit)) {
            edge e;
            e.van  = van;
            e.naar = buur;
            e.rest = rest_capaciteit;
            e.verbnr = verbnr;
            pad.push_back(e);
            bool gevonden = zoek_pad(graaf, pad, flow, buur, naar);
            if (gevonden) 
                return true;
            else
                pad.pop_back();
        }
        
    }
    
    return false;
    
}

int main (int argc, const char * argv[])
{
    // De graaf.
    GraafMetKnoopEnTakdata<ONGERICHT, Knoop, int> graaf;
//    lees_graaf(graaf);
    
    Knoop A;
    Knoop B;
    Knoop C;
    Knoop D;
    Knoop E;
    Knoop F;
    
    graaf.voegKnoopToe(A);
    graaf.voegKnoopToe(B);
    graaf.voegKnoopToe(C);
    graaf.voegKnoopToe(D);
    graaf.voegKnoopToe(E);
    graaf.voegKnoopToe(F);
    
    graaf.voegVerbindingToe(0, 1, 3);
    graaf.voegVerbindingToe(0, 2, 2);
    
    graaf.voegVerbindingToe(1, 2, 2);
    graaf.voegVerbindingToe(1, 3, 3);
    
    graaf.voegVerbindingToe(2, 4, 2);
    
    
    graaf.voegVerbindingToe(3, 4, 4);
    graaf.voegVerbindingToe(3, 5, 2);
    
    graaf.voegVerbindingToe(4, 5, 3);
    
    // Meervoudige samenhang zoeken we het vergrotende pad tussen start en einde
    // dit levert een maximuum stroom op van 1 (aangezien de capaciteiten overal 1 zijn)
    // we verwijderen dan de knopen op dit vergrotend pad en herhalen ..
    
    // Hoeveel er op elke verbinding 'stroomt'.
    // Initieel 0.
    vector<int> flow(graaf.aantalVerbindingen());
    for (unsigned int i = 0; i < graaf.aantalVerbindingen();i++) {
        flow[i] = 0;
    }
    
    int van  = 0;
    int naar = 5;
    vector<edge> pad;
    bool gevonden = zoek_pad(graaf, pad, flow, van, naar);
    
    int k = 0;
    while (gevonden) {
        k++;
        // stroom die door dit pad kan berekenen. (dat is het mininiuum op een van de verbindingen)
        int run_flow = 89999;
        for (vector<edge>::iterator it = pad.begin(); it != pad.end(); it++) {
            edge e = *it;
            run_flow = min(run_flow, e.rest);
        }
        
        // Aanpassen.
        for (vector<edge>::iterator it = pad.begin(); it != pad.end(); it++) {
            edge e = *it;
            flow[e.naar] += run_flow;
            flow[e.van] -= run_flow;
        }
        
        pad.clear();
        gevonden = zoek_pad(graaf, pad, flow, van, naar);
    }
    
    int totaal = 0;
    map<int, int> buren = graaf[van];
    for (map<int, int>::iterator it = buren.begin(); it != buren.end();it++) {
        int buur = it->first;
        totaal += flow[buur];
    }
    
    cout << "totale netwerk flow is: " << totaal;
    
    
    
    
    return 0;
}


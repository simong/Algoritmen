#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <limits>

#include "floyd.h"
#include "graaf.h"
#include "tinystr.h"
#include "tinyxml.h"

const int MAX_INT = 10000000;

class Species {
public:
    std::string id;
    std::string name;

    Species() {
    }
    ;
    Species(std::string id, std::string name)
            : id(id), name(name) {
    }
    ;
};

std::ostream &operator<<(std::ostream &os, const Species &s) {
    os << s.id << ": " << s.name;
    return os;
}

struct verbinding {
    int distance;
    int nr;
    int van;
    int naar;

    bool operator<(const verbinding& v1) const {
        return v1.distance < distance;
    }
};

int find(int knoop, std::vector<int>& vertegenwoordigers) {
    return vertegenwoordigers[knoop];
}

// De union operatie
// van en naar zijn indexes naar de vertegenwoordigers
void merge(int van, int naar, std::vector<std::list<int> >& componenten,
        std::vector<int>& vertegenwoordigers) {

    std::list<int>* a = &(componenten[van]);
    std::list<int>* b = &(componenten[naar]);

    if (a->size() > b->size()) {
        swap(a, b);
        int temp = van;
        van = naar;
        naar = temp;
    }

    // a is nu de list met het minste elementen.
    // We gaan alle A knopen naar de vertegenwoordiger van b zetten.
    for (std::list<int>::iterator it = a->begin(); it != a->end(); it++) {
        vertegenwoordigers[*it] = vertegenwoordigers[naar];
    }

    // a aan b hangen.
    // De merge operatie zorgt ervoor dat a leeg wordt.
    b->merge(*a);
}

int main() {
    GraafMetKnoopEnTakdata<ONGERICHT, Species, int> graaf;
    std::map<std::string, int> knoopnrs;

    // Dit hebben we nodig voor kruskal
    std::vector<int> vertegenwoordigers;
    std::vector<std::list<int> > componenten;
    std::priority_queue<verbinding> verbindingen;

    TiXmlDocument doc("mammalsgraph_2.xml");
    bool loadOK = doc.LoadFile();

    if (loadOK) {
        TiXmlNode *network = doc.RootElement();

        // Alle knopen inlezen
        for (TiXmlElement *n = network->FirstChildElement(); n != 0;
                n = n->NextSiblingElement()) {
            std::string id = n->Attribute("ID");
            Species species(id, n->Attribute("name"));
            int knoop_nr = graaf.voegKnoopToe(species);
            knoopnrs[id] = knoop_nr;

            // Iedere knoop is voorlopig zijn eigen vertegenwoordiger.
            // Push back kan omdat er toch nog niks in vertegenwoordigers zit
            // en dat de 1e knoop die uit de graafklasse.voegKnoopToe komt = 0
            vertegenwoordigers.push_back(knoop_nr);

            // Iedere knoop is ook een boom op zich.
            std::list<int> lijst;
            lijst.push_back(knoop_nr);
            componenten.reserve(graaf.aantalKnopen());
            componenten.push_back(lijst);
        }

        // Alle verbindingen inlezen
        for (TiXmlElement *n = network->FirstChildElement(); n != 0;
                n = n->NextSiblingElement()) {
            int van = knoopnrs[n->Attribute("ID")];

            for (TiXmlElement *pad = n->FirstChildElement(); pad != 0;
                    pad = pad->NextSiblingElement()) {
                int naar = knoopnrs[pad->Attribute("species")];
                int distance = atoi(pad->Attribute("distance"));
                try {
                    int verbindings_nr = graaf.voegVerbindingToe(van, naar, distance);

                    verbinding v;
                    v.nr = verbindings_nr;
                    v.distance = distance;
                    v.van = van;
                    v.naar = naar;
                    verbindingen.push(v);
                } catch (GraafExceptie e) {
                    // Swallow it.
                }
            }
        }
    }
    else {
        throw "kon het xml bestand niet inlezen.";
    }

    // Extra opgavem
    // Heel dit stuk in een while

    // Kruskal
    // We stellen een MOB op
    // Als we de laatste k verbindingen van de MOB niet toevoegen zullen we k clusters hebben.
    // Kruskal werkt door het samenvoegen van bomen.
    // Dat samenvoegen gebeurt door telkens de verbinding met het kleinste gewicht tussen 2 bomen te kiezen.
    unsigned int k = 10;
    unsigned int merges = 0;
    while (!verbindingen.empty() && merges < (graaf.aantalKnopen() - k)) {
        verbinding v = verbindingen.top();

        // Zoek de vertegenwoordiger van de uiteinden van deze verbinding.
        int a = find(v.van, vertegenwoordigers);
        int b = find(v.naar, vertegenwoordigers);

        // Als de vertegenwoordigers verschillen, dan zijn dit 2 verschillende bomen.
        if (a != b) {
            // We doen een union operatie op deze 2 bomen.
            // merge=union omdat union een reserved keyword is.
            merge(a, b, componenten, vertegenwoordigers);
            merges++;
        }

        // Deze verbinding hebben we verder niet nodig.
        verbindingen.pop();
    }

    // De component van de mens opzoeken.
    int knoop_mens = knoopnrs["S747"];
    int vertegenwoordiger_mens = find(knoop_mens, vertegenwoordigers);

    // Heel de list tonen.
    std::list<int> component_boom = componenten[vertegenwoordiger_mens];
    for (std::list<int>::iterator it = component_boom.begin(); it != component_boom.end();
            it++) {
        Species* species = graaf.geefKnoopdata(*it);
        std::cout << *species << std::endl;
    }
    std::cout << "Er zitten " << component_boom.size() << " wezens in deze component"
            << std::endl;
    std::cout << std::endl << std::endl << std::endl << std::endl;

    // Centrum zoeken bestaat uit volgende stappen.
    // 1. Kortste paden tussen alle knopen berekenen.                               O(n*n*n)
    //      Floyd-Warshall
    // 2. Voor iedere knoop, de knoop bepalen waar hij het verst van ligt.          O(n*n)
    //
    // 3. Voor al die maximums, het minimuum er van nemen (kan meerdere zijn).      O(n)

    std::vector<int> componenten_knopen(component_boom.begin(), component_boom.end());
    int graph[component_boom.size()][component_boom.size()];
    int max_knopen[component_boom.size()];

    // Initialiseren (alle afstanden zijn MAX_INT).
    for (unsigned int i = 0; i < component_boom.size(); i++) {
        max_knopen[i] = 0;
        for (unsigned int j = 0; j < component_boom.size(); j++) {
            int* ptr = graaf.geefTakdata(componenten_knopen[i], componenten_knopen[j]);
            int kost = MAX_INT;
            if (ptr != 0) {
                kost = *ptr;
            }
            graph[i][j] = kost;
        }
    }

    // Floyd-warshall
    for (unsigned int k = 0; k < component_boom.size(); k++) {
        for (unsigned int i = 0; i < component_boom.size(); i++) {
            for (unsigned int j = 0; j < component_boom.size(); j++) {
                // graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                int kost = graph[i][k] + graph[k][j];
                if (kost < graph[i][j]) {
                    // Kortere weg gevonden.
                    graph[i][j] = kost;
                }
            }
        }
    }

    // Maxima's per knoop opzoeken
    for (unsigned int i = 0; i < component_boom.size(); i++) {
        int max = 0;
        for (unsigned int j = 0; j < component_boom.size(); j++) {
            if (i != j && graph[i][j] > max) {
                max = graph[i][j];
                max_knopen[i] = j;
            }
        }
    }

    // Minimas opzoeken
    int min = MAX_INT;
    vector<int> min_knopen;
    for (unsigned int i = 0; i < component_boom.size(); i++) {
        int afstand = graph[i][max_knopen[i]];
        if (afstand <= min) {
            if (afstand < min) {
                min_knopen.clear();
            }
            min_knopen.push_back(i);
            min = afstand;
        }
    }

    // De midden knopen uitprinten.
    for (unsigned int i = 0; i < min_knopen.size(); i++) {
        int straal = graph[i][max_knopen[i]];
        int knoop_centrum = componenten_knopen[min_knopen[i]];
        int knoop_verste = componenten_knopen[max_knopen[i]];
        Species* centrum_species = graaf.geefKnoopdata(knoop_centrum);
        Species* verste = graaf.geefKnoopdata(knoop_verste);
        std::cout << "Straal: " << straal << " - " << *centrum_species << " - Verste: "
                << *verste << std::endl;
    }
    std::cout << "Er zijn " << min_knopen.size() << " centrum knopen." << std::endl;

    std::cout << "Inifinity == " << MAX_INT;
    return 0;
}

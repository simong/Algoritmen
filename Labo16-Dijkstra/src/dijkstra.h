#ifndef __DIJKSTRA__
#define __DIJKSTRA__

#include <map>
#include <queue>
#include <vector>
#include <limits>
#include "ggraaf.h"

enum Kleur {
    WIT, GRIJS, ZWART
};

// Bepaalt de kortste afstanden en ouders langs het kortste pad vanuit een vaste knoop.
// Verwacht een gerichte gewogen graaf zonder negatieve verbindingsgewichten.
template<class T>
class Dijkstra {

public:
    T ONEINDIG;
    int OUDER_ONBEPAALD;
    int GEEN_OUDER;
    std::vector<Kleur> kleuren;
    std::vector<int> ouders;
    std::vector<double> afstanden;
    std::priority_queue<std::pair<double, int> > prioQueue;

    Dijkstra() {
        ONEINDIG = std::numeric_limits<T>::max();
        OUDER_ONBEPAALD = -2;
        GEEN_OUDER = -1;
    }

    // Voert het algoritme uit.
    // Resultaten kunnen achteraf opgevraagd worden via de lidfuncties.
    // Gooit een GraafExceptie op indien de graaf negatieve gewichten heeft.
    void start(const GewogenGraaf<GERICHT, T> &g, int startk) {
        int aantal = g.aantal_knopen();
        kleuren.reserve(aantal);
        ouders.reserve(aantal);
        afstanden.reserve(aantal);

        // In het begin is alles wit, zijn de ouders ongekend en oneindig ver.
        for (int i = 0; i < aantal; i++) {
            kleuren[i] = WIT;
            ouders[i] = OUDER_ONBEPAALD;
            afstanden[i] = ONEINDIG;
        }

        // Begin bij de startknoop.
        // Voeg al de buurknopen aan de priority queue.
        afstanden[startk] = 0;
        ouders[startk] = GEEN_OUDER;
        add_mogelijke_buren(g, startk);

        while (!prioQueue.empty()) {
            std::pair<double, int> p = prioQueue.top();
            if (kleuren[p.second] != ZWART) {
                add_mogelijke_buren(g, p.second);
            }
            prioQueue.pop();
        }
    }

    void add_mogelijke_buren(const GewogenGraaf<GERICHT, T> &g, int knoopNr) {
        // De afgelegde weg voor deze knoop.
        double afstand = afstanden[knoopNr];
        kleuren[knoopNr] = ZWART;

        // Haal de knoop zijn buren op.
        // Overloop ze, bereken de afstand en steek ze in de prioqueue.
        Knoop k = g[knoopNr];
        for (std::map<int, int>::iterator it = k.begin(); it != k.end(); it++) {
            int buurNr = (*it).first;
            if (kleuren[buurNr] != ZWART) {
                int verbindingNr = (*it).second;
                double kost = afstand + g.gewicht(verbindingNr);

                if (kost < afstanden[buurNr]) {
                    // We werken met een negatieve priority queue.. daarom * -1
                    std::pair<double, int> p((-1 * kost), buurNr);
                    prioQueue.push(p);

                    afstanden[buurNr] = kost;
                    ouders[buurNr] = knoopNr;
                    kleuren[buurNr] = GRIJS;
                }
            }
        }
    }

    // Geeft de ouder op het kortste pad van de startknoop naar knoop k.
    // Speciale gevallen:
    // - GEEN_OUDER voor startknoop;
    // - OUDER_ONBEPAALD voor niet-bezochte knopen.
    int ouder(int k) const {
        return ouders[k];
    }

    // Geeft de totale lengte (totaal gewicht) van het kortste pad van de startknoop naar knoop k.
    // Speciaal geval:
    // - ONEINDIG voor niet bezochte knopen.
    T afstand(int k) const {
        return afstanden[k];
    }
};

#endif

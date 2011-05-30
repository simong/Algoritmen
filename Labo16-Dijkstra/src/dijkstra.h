#ifndef __DIJKSTRA__
#define __DIJKSTRA__

#include <limits>
#include "ggraaf.h"


enum Kleur { WIT, GRIJS, ZWART };

// Bepaalt de kortste afstanden en ouders langs het kortste pad vanuit een vaste knoop.
// Verwacht een gerichte gewogen graaf zonder negatieve verbindingsgewichten.
template <class T>
class Dijkstra
{

public:
	T ONEINDIG;
	static const int OUDER_ONBEPAALD = -2;
	static const int GEEN_OUDER = -1;

	Dijkstra()
	{
		ONEINDIG = std::numeric_limits<T>::max();
	}

	// Voert het algoritme uit. 
	// Resultaten kunnen achteraf opgevraagd worden via de lidfuncties.
	// Gooit een GraafExceptie op indien de graaf negatieve gewichten heeft.
	void start(const GewogenGraaf<GERICHT, T> &g, int startk) 
	{
		// ...
	}

	
	// Geeft de ouder op het kortste pad van de startknoop naar knoop k.
	// Speciale gevallen: 
	// - GEEN_OUDER voor startknoop;
	// - OUDER_ONBEPAALD voor niet-bezochte knopen.
	int ouder(int k) const 
	{  
		return 0;
	}

	// Geeft de totale lengte (totaal gewicht) van het kortste pad van de startknoop naar knoop k.
	// Speciaal geval:
	// - ONEINDIG voor niet bezochte knopen.
	T afstand(int k) const 
	{ 
		return 0;
	}

	
};

#endif

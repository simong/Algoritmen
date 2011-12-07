#include "bitpatroon.h"
#include <queue>

typedef unsigned int uint;
typedef unsigned char uchar;

class Shiftand {
public:
    //naaldlengte moet kleiner dan patroonlengte zijn,
    //anders wordt een exceptie opgegooid.
    Shiftand(const uchar* naald, uint _naaldlengte);
    void zoek(std::queue<const uchar*>& plaats, const uchar* hooiberg, uint hooiberglengte);

private:
    Bitpatroon letterpatroon[256];
    uint naaldlengte;
};

Shiftand::Shiftand(const uchar* naald, uint _naaldlengte) {

    //S-tabel init
    naaldlengte = _naaldlengte;
    for (uint i = 0; i < 256; i++) {
        Bitpatroon b;
        letterpatroon[i] = b;
    }

    for (uint i = 0; i < naaldlengte; i++) {

        //We halen het bitpatroon op dat hoort bij de letter die op positie i in de naald zit
        Bitpatroon p = letterpatroon[naald[i]];

        //We willen een 1 op index i in het bitpatroon p
        Bitpatroon extra = Bitpatroon::eenbit(i);

        //Wegscrhijven
        letterpatroon[naald[i]] = p | extra;
    }

}

void Shiftand::zoek(std::queue<const uchar*>& plaats, const uchar* hooiberg,
        uint hooiberglengte) {
    //R schuiftabel opstellen (lengte m is voldoende)
    //Indien we ooit op index m een true hebben zitten we
    //op het einde van een gevonden patroon
    Bitpatroon vorige(0);
    Bitpatroon huidige;
    Bitpatroon matcher = Bitpatroon::eenbit(naaldlengte - 1);
    for (uint j = 0; j <= hooiberglengte; j++) {
        // SHIFT
        huidige = vorige.shiftrechts(1);
        //We moeten onze 1 erin shiften
        huidige = huidige | Bitpatroon::eenbit(0);

        // AND
        huidige = huidige & letterpatroon[hooiberg[j]];

        // MATCH CHECKEN
        if (huidige.en(matcher)) {
            plaats.push(&hooiberg[j - naaldlengte + 1]);
        }

        vorige = huidige;
    }

}

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include "rzwboom.h"
using std::cout;
using std::endl;

const int TESTAANTAL = 793;
const int RELPRIEM = 22; //getal moet relatief priem zijn met TESTAANTAL

void simple_test() {
	Rzwboom<int, int> boom;
	int data[13] = { 10, 3, 15, 2, 6, 12, 18, 4, 8, 11, 13, 16, 20 };
	int i = 0;
	while (i < 13) {
		boom.voegtoe(data[i], data[i]);
		i++;
	}
	boom.verwijder(3);
	cout << boom;
}


int main(int argc, char *argv[]) {
	cout << "Start" << endl;

	Rzwboom<int, double> boom;
	int i = 0;
	while (i < TESTAANTAL && boom.zwartediepte() != -1) {
		boom.voegtoe(i, double((i * RELPRIEM) % TESTAANTAL) / TESTAANTAL);
		i++;
	}
	cout << "Boom na toevoegen\n" << boom << '\n';
	i = 0;
	bool geslaagdeverwijdering = boom.verwijder((i * RELPRIEM) % TESTAANTAL);
	i++;
	while (i < TESTAANTAL && boom.zwartediepte() != -1 && geslaagdeverwijdering) {
		geslaagdeverwijdering = boom.verwijder((i * RELPRIEM) % TESTAANTAL);
		i++;
	}
	if (boom.zwartediepte() == -1 || !geslaagdeverwijdering) {
		cout << "Er ging iets mis\n";
		if (boom.zwartediepte() == -1)
			cout << "    De boom is geen geldige roodzwarte boom\n";
		if (!geslaagdeverwijdering)
			cout
					<< "    de sleutel is niet gevonden, of er is iets anders misgegaan bij verwijderen.\n";
		cout << "\n\n De laatste knoop die men probeerde te verwijderen was "
				<< ((i - 1) * RELPRIEM) % TESTAANTAL;
		//cout << "\n Het resultaat is\n" << boom;
	} else {
		//cout << "Boom na verwijderen is\n" << boom
		//		<< "\n Als deze leeg is is alles OK.\n";
	}
	return 0;
}

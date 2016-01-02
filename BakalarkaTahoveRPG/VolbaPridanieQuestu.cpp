#include "VolbaPridanieQuestu.h"



VolbaPridanieQuestu::VolbaPridanieQuestu(string paText, int dalsia):DialogVolba(paText,dalsia)
{
	pouzita = false;
}


VolbaPridanieQuestu::~VolbaPridanieQuestu()
{
}

void VolbaPridanieQuestu::akcia(Hrac* hrac) {
	if (!pouzita) {
		cout << "Pridanie Questu" << endl;
		pouzita = true;
	}
	else {
		cout << "Quest už bol pridany" << endl;
	}
}

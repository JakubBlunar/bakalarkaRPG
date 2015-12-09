#include "Mapa.h"
#include "Policko.h"


Mapa::Mapa() {
	int rozmer = 25;
	mapa = new Policko*[rozmer];
	for (int i = 0; i < rozmer; i++)
	{
		mapa[i] = new Policko(true);
	}


}



Mapa::~Mapa() {
	for (int i = 0; i < 25; ++i) {
		delete[] mapa[i];
	}
	delete[] mapa;
}





void Mapa::posun(int posunY, int posunX) {

}


void Mapa::render() {
	
}


void Mapa::update() {

}
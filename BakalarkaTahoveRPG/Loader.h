#ifndef loader_h
#define loader_h
#include <SFML\Graphics.hpp>
#include <map>
#include <string>

class Hra;
class Mapa;

class Loader {
public:
	static Loader* Instance();
	void setHra(Hra* paHra);
	void nacitajMapu(std::string paMeno,int paX,int paY,int smer);
	bool Getnacitava();
	Hra* Gethra();
private:
	Loader() {
		nacitava = false;
	};
	Loader(Loader const&) {};
	Loader& operator=(Loader const&) {};
	static Loader* instancia;

	bool nacitava;

	Hra* hra;
	std::map<int, sf::Texture*> textury;
	std::map<std::string, Mapa*> nacitaneMapy;

};

#endif // LOADER.H
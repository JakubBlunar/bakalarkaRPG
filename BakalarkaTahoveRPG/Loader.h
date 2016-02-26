#ifndef loader_h
#define loader_h
#include <SFML\Graphics.hpp>
#include <map>
#include <string>

class Npc;
class Hra;
class Mapa;
class DialogovyStrom;
class Nepriatel;

class Loader {
public:
	static Loader* Instance();
	void setHra(Hra* paHra);
	void nacitajMapu(std::string paMeno,int paX,int paY,int smer);
	sf::Font* nacitajFont(std::string menoFontu);
	DialogovyStrom* nacitajDialog(std::string paMeno);
	Nepriatel* nacitajNepriatela(std::string paMeno);

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
	
	void nacitajNpc(std::string menoMapy, Mapa* mapa);
	
	std::map<std::string, sf::Font*> nacitaneFonty;
	
	int  nahodneCislo(int min, int max);
};

#endif // LOADER.H
#ifndef loader_h
#define loader_h
#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include <vector>

#include "json-forwards.h"
#include "json.h"

using namespace std;

class Npc;
class Hra;
class Mapa;
class DialogovyStrom;
class Nepriatel;
class Predmet;
class Quest;
class Zameranie;

class Loader {
public:
	static Loader* Instance();
	void setHra(Hra* paHra);
	void nacitajMapu(string paMeno,int paX,int paY,int smer);
	sf::Font* nacitajFont(string menoFontu);
	DialogovyStrom* nacitajDialog(string paMeno);
	Nepriatel* nacitajNepriatela(string paMeno);
	vector<Predmet*>* nacitajObchod(string paMeno);
	Quest* nacitajQuest(string paMeno);
	bool Getnacitava();
	Hra* Gethra();
	
	Zameranie* nacitajZameranie(string paMeno);

	bool save();
	void load();

private:
	Loader() {
		nacitava = false;
	};
	Loader(Loader const&) {};
	Loader& operator=(Loader const&) {};
	static Loader* instancia;

	bool nacitava;

	Hra* hra;
	map<int, sf::Texture*> textury;
	map<string, Mapa*> nacitaneMapy;
	
	void nacitajNpc(string menoMapy, Mapa* mapa);
	
	map<string, sf::Font*> nacitaneFonty;
	
	Predmet* parsujPredmet(Json::Value jPredmet);

	int  nahodneCislo(int min, int max);
};

#endif // LOADER.H
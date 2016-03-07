#if !defined(Generator_h)
#define Generator_h

#include <string>
#include <vector>

using namespace std;

class Pouzitelny;
class Predmet;

class Generator
{
public:
	static Generator* Instance();

	Predmet* nahodnyElixir();
	Predmet* nahodnaZbran(int);
	Predmet* nahodneOblecenie(int);

private:
	Generator() {};
	Generator(Generator const&) {};
	Generator& operator=(Generator const&) {};
	static Generator* instancia;

	void generujStatistiky(Pouzitelny* paPredmet);
	int randomInt(int min, int max);

	vector<string>* najdiSubory(string cesta);
};

#endif
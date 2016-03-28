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

	Predmet* nahodnyElixir() const;
	Predmet* nahodnaZbran(int);
	Predmet* nahodneOblecenie(int);

private:
	Generator() {};
	Generator(Generator const&) {};
	Generator& operator=(Generator const&) {};
	static Generator* instancia;

	void generujStatistiky(Pouzitelny* paPredmet) const;
	int randomInt(int min, int max) const;

	vector<string>* najdiSubory(string cesta) const;
};

#endif
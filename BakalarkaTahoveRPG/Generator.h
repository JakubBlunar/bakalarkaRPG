#if !defined(Generator_h)
#define Generator_h

#include <string>
#include <vector>

using namespace std;

class Pouzitelny;
class Predmet;

/// <summary>
/// Generator sluzi na generovanie Predmetov
/// </summary>
class Generator
{
public:
	/// <summary>
	/// Staticka metoda , sluzi ako konstruktor
	/// </summary>
	/// <returns>Instancia</returns>
	static Generator* Instance();

	/// <summary>
	/// Vygeneruje nahodnı elixir
	/// </summary>
	/// <returns>novı elixir</returns>
	Predmet* nahodnyElixir() const;

	/// <summary>
	/// Vygeneruje zbran na danú uroven
	/// </summary>
	/// <param name="uroven">uroven v akej by sa mala pohybova uroven vytvorenej zbrane</param>
	/// <returns></returns>
	Predmet* nahodnaZbran(int uroven) const;

	/// <summary>
	/// Vygeneruje oblecenie na danú uroven
	/// </summary>
	/// <param name="uroven">uroven v akej by sa mala pohybova uroven vytvoreneho oblecenia</param>
	/// <returns></returns>
	Predmet* nahodneOblecenie(int uroven) const;

	/// <summary>
	/// Prehlada adresar na ceste a vrati nazvy suborov
	/// </summary>
	/// <param name="cesta">cesta na prehladanie</param>
	/// <returns>zoznam suborov</returns>
	vector<string>* najdiSubory(string cesta) const;

	/// <summary>
	/// Vráti nahodne èislo v rozsahu min max
	/// </summary>
	/// <param name="min">mininum</param>
	/// <param name="max">maximum</param>
	/// <returns>nahodne cislo</returns>
	int randomInt(int min, int max) const;
private:
	/// <summary>
	/// vytvorenie noveho generatora
	/// </summary>
	Generator() {};
	Generator(Generator const&) {};
	Generator& operator=(Generator const&) const
	{
		return *instancia;
	};
	static Generator* instancia;

	/// <summary>
	/// Obleceniu vygeneruje statistiky, ko¾ko bude hraèovi pridava
	/// </summary>
	/// <param name="paPredmet">predmet ktoremu treba generova</param>
	void generujStatistiky(Pouzitelny* paPredmet) const;

};

#endif
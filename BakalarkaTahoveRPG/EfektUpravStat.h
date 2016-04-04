#if !defined(EfektUpravStat_h)
#define EfektUpravStat_h

#include "Efekt.h"

class Statistika;

/// <summary>
/// Specializacia efektu , tento efekt upraví stat o nejaku hodnotu
/// </summary>
class EfektUpravStat :
	public Efekt
{
public:
	/// <summary>
	/// Konstruktor vytvarajuci efekt
	/// </summary>
	/// <param name="obrazok">obrazok efektu</param>
	/// <param name="paCo">stat ktorı bude upravova</param>
	/// <param name="paZaklad">zaklad z ktoreho sa bude pocitat vysledna hodnota o ktoru sa stat upraví</param>
	EfektUpravStat(std::string obrazok,std::string paCo, int paZaklad);
	
	/// <summary>
	/// Destruktor ktorı vola destruktor predka
	/// </summary>
	~EfektUpravStat();

	/// <summary>
	/// Aplikovanie efektu, upraví statistiku o hodnotu efektu.
	/// </summary>
	/// <param name="statistika">statistika , na ktoru sa má aplikovat</param>
	void aplikujSa(Statistika* statistika) override;

	/// <summary>
	/// Zrusi efekt, opak aplikacie
	/// </summary>
	/// <param name="statistika">statistika , z ktorej sa zrusi</param>
	void zrusUcinok(Statistika* statistika) override;

	/// <summary>
	/// Metoda vytvorí popis efektu
	/// </summary>
	/// <returns>popis efektu</returns>
	std::string popis() override;

	/// <summary>
	/// Metoda vypoèita vyslednu hodnotu efektu zo statistiky, ktorá sa ziskala v konstruktore.
	/// </summary>
	/// <returns>vysledna hodnota efektu</returns>
	int hodnotaEfektu() const;
private:
	std::string co;
	int zakladOkolko;
};
#endif

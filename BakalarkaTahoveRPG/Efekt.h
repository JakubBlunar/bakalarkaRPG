#if !defined(Efekt_h)
#define Efekt_h

#include <SFML\Graphics.hpp>

class Statistika;

/// <summary>
/// Trieda predstavuje efekt ktorı sa moze aplikovat na hraca alebo nepriatela a tım mu daèo sposobit.
/// Trvá urcitu dobu.
/// </summary>
class Efekt
{
public:

	/// <summary>
	/// Konstruktor ktorı nacita obrazok efektu do pamäte
	/// </summary>
	/// <param name="obrazok">nazov suboru obrazku</param>
	Efekt(std::string obrazok);

	/// <summary>
	/// Destruktor zmaze obrazok efektu
	/// </summary>
	virtual ~Efekt();

	/// <summary>
	/// Abstraktná metoda , ktoru musia implementova specifikacie efektu
	/// </summary>
	/// <param name="statistika">Statistika na ktoru sa aplikuje efekt</param>
	virtual void aplikujSa(Statistika* statistika) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="statistika">Statistika z ktorej sa zrusi efekt</param>
	virtual void zrusUcinok(Statistika* statistika) = 0;

	/// <summary>
	/// Metoda vytvorí textovı popis efektu
	/// </summary>
	/// <returns></returns>
	virtual std::string popis() = 0;

	/// <summary>
	/// Getter ktorı vrati cas doekdy trva efekt
	/// </summary>
	/// <returns> Cas dokedy trva efekt</returns>
	sf::Time GettrvanieDo() const;

	/// <summary>
	/// Metoda ktorı nastaví cas , dokedy trvá efekt
	/// </summary>
	/// <param name="paKoniec">Cas konca</param>
	void setTrvanieDo(sf::Time paKoniec);

	/// <summary>
	/// Getter ktorı vrati obrazok efektu
	/// </summary>
	/// <returns>obrazok</returns>
	sf::Sprite* Getobrazok() const;

	/// <summary>
	/// Setter, ktorı nastaví statistiku, z ktorej sa bude pocita hodnota efektu
	/// </summary>
	/// <param name="statistika">statistika hraca alebo nepriatela</param>
	void Setstatistikanapocitanie(Statistika* statistika);

protected:
	sf::Time trvanieDo;

	sf::Texture textura;
	sf::Sprite* obrazok;
	Statistika* statistikaNaPocitanie;
};

#endif


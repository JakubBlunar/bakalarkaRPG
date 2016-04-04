#if !defined(Efekt_h)
#define Efekt_h

#include <SFML\Graphics.hpp>

class Statistika;

/// <summary>
/// Trieda predstavuje efekt ktor� sa moze aplikovat na hraca alebo nepriatela a t�m mu da�o sposobit.
/// Trv� urcitu dobu.
/// </summary>
class Efekt
{
public:

	/// <summary>
	/// Konstruktor ktor� nacita obrazok efektu do pam�te
	/// </summary>
	/// <param name="obrazok">nazov suboru obrazku</param>
	Efekt(std::string obrazok);

	/// <summary>
	/// Destruktor zmaze obrazok efektu
	/// </summary>
	virtual ~Efekt();

	/// <summary>
	/// Abstraktn� metoda , ktoru musia implementova� specifikacie efektu
	/// </summary>
	/// <param name="statistika">Statistika na ktoru sa aplikuje efekt</param>
	virtual void aplikujSa(Statistika* statistika) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="statistika">Statistika z ktorej sa zrusi efekt</param>
	virtual void zrusUcinok(Statistika* statistika) = 0;

	/// <summary>
	/// Metoda vytvor� textov� popis efektu
	/// </summary>
	/// <returns></returns>
	virtual std::string popis() = 0;

	/// <summary>
	/// Getter ktor� vrati cas doekdy trva efekt
	/// </summary>
	/// <returns> Cas dokedy trva efekt</returns>
	sf::Time GettrvanieDo() const;

	/// <summary>
	/// Metoda ktor� nastav� cas , dokedy trv� efekt
	/// </summary>
	/// <param name="paKoniec">Cas konca</param>
	void setTrvanieDo(sf::Time paKoniec);

	/// <summary>
	/// Getter ktor� vrati obrazok efektu
	/// </summary>
	/// <returns>obrazok</returns>
	sf::Sprite* Getobrazok() const;

	/// <summary>
	/// Setter, ktor� nastav� statistiku, z ktorej sa bude pocita� hodnota efektu
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


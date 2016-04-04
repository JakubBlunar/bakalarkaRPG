#if !defined(stavBoj_h)
#define stavBoj_h
#include "Stav.h"

class Hrac;
class Boj;
class Tlacidlo;
class Akcia;

/// <summary>
/// Stav rozhrania ktor� zobrazuje boj medzi hracom a nepriatelom
/// </summary>
class StavBoj:public Stav
{
public:

	StavBoj(std::string paNazov, sf::RenderWindow* paOkno, Hra* paHra);
	~StavBoj();

	void onEnter() override;
	void onExit() override;
	void render() override;
	void update() override;

	/// <summary>
	/// Nastav� boj ktor� bude prebieha�
	/// </summary>
	/// <param name="boj"></param>
	void setBoj(Boj* boj);

private:
	/// <summary>
	/// Vykresli okno akcie nad akciu nad ktorou m� hr�� my� alebo ju ma ozna�enu klavesnicou
	/// </summary>
	/// <param name="akcia">akcia na vykreslenie</param>
	/// <param name="pozicia">pozicia na obrazovke kam vykresli�</param>
	void vykresliInfoAkcie(Akcia* akcia,sf::Vector2f pozicia) const;

	Boj* boj;
	Tlacidlo* tlacidla[3][9];
	std::vector<Akcia*>* hracoveAkcie;
	Tlacidlo* logHranice;
	Tlacidlo* doInventara;
	
	int oznacene;
	sf::RectangleShape ukazovatel;
};

#endif

#if !defined(Hrac_h)
#define Hrac_h

#include <SFML\Graphics.hpp>

class Mapa;
class Zameranie;
class Animacia;
class Statistika;
class Inventar;
class Predmet;
class QuestManager;

/// <summary>
/// Enum predstavuje smer pohladu ktor˝m sa hr·Ë pozer·
/// </summary>
enum SmerPohladu
{
	hore = 0,
	dole = 1,
	vlavo = 2,
	vpravo = 3,
	stoji = 4
};


/// <summary>
/// Trieda predstavuje hr·Ëa, jeho postavu , akÈ m· veci , ötatistiky , Ëo m· obleËenÈ , akÈ m· questy a kde sa nach·dza
/// </summary>
class Hrac
{

public:
	/// <summary>
	/// VytvorÌ hr·Ëa s dan˝m zameranÌm
	/// </summary>
	/// <param name="paZameranie">Zameranie ktorÈ bude maù</param>
	Hrac(Zameranie* paZameranie);
	virtual ~Hrac();

	/// <summary>
	/// Vr·ti smer pohæadu ktor˝m sa hr·Ë pozer·
	/// </summary>
	/// <returns></returns>
	SmerPohladu GetSmerPohladu() const;

	/// <summary>
	/// Vykresli obrazok z hr·Ëovej obrazovky na okno
	/// </summary>
	/// <param name="paOkno">okno hry na ktore sa vykresluje</param>
	void render(sf::RenderWindow* paOkno) const;

	/// <summary>
	/// Aktualizuje hraca
	/// </summary>
	void update();

	/// <summary>
	/// Zmeni smer pohladu hraca na smer zadan˝ v parametri
	/// </summary>
	/// <param name="smer">smer na ktor˝ sa m· hrac otocit</param>
	void zmenSmerPohladu(SmerPohladu smer);

	/// <summary>
	/// Posunie hraca o x,y pixelov
	/// </summary>
	/// <param name="x">pocet pixelov o x</param>
	/// <param name="y">pocet pixelov o y</param>
	void posun(int x, int y);

	/// <summary>
	/// Volanie v update , kde sa aktualizuje aj animacia
	/// </summary>
	void animaciaTick() const;

	/// <summary>
	/// NastavÌ pohyb hr·Ëa aby preöiel o jedno policko vpravo
	/// </summary>
	void chodVpravo();

	/// <summary>
	/// NastavÌ pohyb hr·Ëa aby preöiel o jedno policko vlavo
	/// </summary>
	void chodVlavo();

	/// <summary>
	/// NastavÌ pohyb hr·Ëa aby preöiel o jedno policko hore
	/// </summary>
	void chodHore();

	/// <summary>
	/// NastavÌ pohyb hr·Ëa aby preöiel o jedno policko dole
	/// </summary>
	void chodDole();

	/// <summary>
	/// vrati ci sa hrac h˝be alebo nie
	/// </summary>
	/// <returns>true ak sa h˝be , false ak nie</returns>
	bool GethybeSa() const;

	/// <summary>
	/// Nastavi poziciu x kde hrac stoji
	/// </summary>
	/// <param name="paX">pozicia x</param>
	void setPolickoX(int paX);

	/// <summary>
	/// Nastavi poziciu y kde hrac stoji
	/// </summary>
	/// <param name="paY">pozicia y</param>
	void setPolickoY(int paY);

	/// <summary>
	/// NastavÌ poziciu hraca od bodu 00 na mape
	/// </summary>
	/// <param name="paX">pozicia x</param>
	void setOffsetX(int paX);

	/// <summary>
	/// Nastavi poziciu od bodu 00 ba naoe
	/// </summary>
	/// <param name="paY">pozicia y</param>
	void setOffsetY(int paY);

	/// <summary>
	/// Vrati offset x hrac na mape
	/// </summary>
	/// <returns>posun x hraca po mape </returns>
	int GetoffsetX() const;

	/// <summary>
	/// Vrati offset y hraca na mape
	/// </summary>
	/// <returns>posun y hraca po mape</returns>
	int GetoffsetY() const;

	/// <summary>
	/// Vrati suradnicu x policka na ktorom hraca stoji
	/// </summary>
	/// <returns>pozicia x policka</returns>
	int GetpolickoX() const;

	/// <summary>
	/// Vrati suradnicu y policka na ktorom hrac stoji
	/// </summary>
	/// <returns>pozicia y policka</returns>
	int GetpolickoY() const;

	/// <summary>
	/// Nastavi hracovi mapu na ktorej je
	/// </summary>
	/// <param name="mapa">mapa na ktorej hrac stoji</param>
	void setMapa(Mapa* mapa);

	/// <summary>
	/// Vrati mapu na ktorej hrac stoji
	/// </summary>
	/// <returns>mapa na ktorej je hrac</returns>
	Mapa* getMapa() const;

	/// <summary>
	/// Vrati hracovu statistiku
	/// </summary>
	/// <returns>hracova statistika</returns>
	Statistika* Getstatistika() const;

	/// <summary>
	/// Nastavi hracovu statistiku
	/// </summary>
	/// <param name="paStatistika">nova statistika</param>
	void Setstatistika(Statistika* paStatistika);

	/// <summary>
	/// Vrati hracove zameranie
	/// </summary>
	/// <returns>zameranie hraca</returns>
	Zameranie* GetZameranie() const;

	/// <summary>
	/// Vrati hracov inventar
	/// </summary>
	/// <returns>inventar hraca</returns>
	Inventar* Getinventar() const;

	/// <summary>
	/// Vyhodi hracovi z inventara predmet na mapu
	/// </summary>
	/// <param name="predemet">predmet ktor˝ sa ma vyhodiù</param>
	void vyhodPredmet(Predmet* predemet) const;

	/// <summary>
	/// Prida hracovi skusenosti a zisti ci nem· novu uroven , ak ano tak mu prid· kuzla a aktualizuje statistiku
	/// </summary>
	/// <param name="pocet">pocet skusenosti</param>
	/// <param name="oznamenie">oznamenie ak nahodou ziskal uroven</param>
	void pridajSkusenosti(int pocet, bool oznamenie = true) const;

	/// <summary>
	/// Vrati manazera hracov˝ch questov
	/// </summary>
	/// <returns>manazer questov</returns>
	QuestManager* Getmanazerquestov() const;
	
	

private:
	Animacia* animaciaDole;
	Animacia* animaciaHore;
	Animacia* animaciaVlavo;
	Animacia* animaciaVpravo;
	Inventar* inventar;

	SmerPohladu smerPohladu;
	Statistika* statistika;
	Zameranie* zameranie;

	int polickoX;
	int polickoY;
	int offsetX;
	int offsetY;

	SmerPohladu smerPohybu;
	bool hybeSa;
	int pohybDelta;
	Mapa* mapa;

	QuestManager* manazerQuestov;
};

#endif
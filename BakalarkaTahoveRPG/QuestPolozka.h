#pragma once
#include "DialogovyStrom.h"
#include "Quest.h"

#include <string>
#include <map>

/// <summary>
/// Dialogova Polozka ktor� spravuje quest
/// </summary>
class QuestPolozka :
	public DialogPolozka
{
public:
	/// <summary>
	/// Vytvori novu polozku ktora spravuej quest s danym nazvom
	/// </summary>
	/// <param name="paNazovQuestu">Nazov questu ktor� bude spravova�</param>
	QuestPolozka(std::string paNazovQuestu);
	~QuestPolozka();
	
	/// <summary>
	/// Vrati text kore�pondujuci zo stavom questu ktor� spravuje
	/// </summary>
	/// <returns>string Text polozky</returns>
	std::string Gettext() override;

	/// <summary>
	/// Vlozi text, ktor� sa zobrazi v ur�itom stave questu
	/// </summary>
	/// <param name="paStav">Stav, pri akom ma tato polozka dany text</param>
	/// <param name="paText">text ktor� sa zobrazi v danom stave</param>
	void vlozText(StavQuestu paStav, std::string paText);

private:
	std::string nazovQuestu;
	std::map<StavQuestu, std::string> texty;
};


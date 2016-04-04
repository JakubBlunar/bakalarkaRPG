#pragma once
#include "DialogovyStrom.h"
#include "Quest.h"

#include <string>
#include <map>

/// <summary>
/// Dialogova Polozka ktorá spravuje quest
/// </summary>
class QuestPolozka :
	public DialogPolozka
{
public:
	/// <summary>
	/// Vytvori novu polozku ktora spravuej quest s danym nazvom
	/// </summary>
	/// <param name="paNazovQuestu">Nazov questu ktorı bude spravova</param>
	QuestPolozka(std::string paNazovQuestu);
	~QuestPolozka();
	
	/// <summary>
	/// Vrati text korešpondujuci zo stavom questu ktorı spravuje
	/// </summary>
	/// <returns>string Text polozky</returns>
	std::string Gettext() override;

	/// <summary>
	/// Vlozi text, ktorı sa zobrazi v urèitom stave questu
	/// </summary>
	/// <param name="paStav">Stav, pri akom ma tato polozka dany text</param>
	/// <param name="paText">text ktorı sa zobrazi v danom stave</param>
	void vlozText(StavQuestu paStav, std::string paText);

private:
	std::string nazovQuestu;
	std::map<StavQuestu, std::string> texty;
};


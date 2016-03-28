#pragma once
#include "DialogovyStrom.h"
#include "Quest.h"

#include <string>
#include <map>

class QuestPolozka :
	public DialogPolozka
{
public:
	QuestPolozka(std::string paNazovQuestu);
	~QuestPolozka();
	std::string Gettext() override;
	void vlozText(StavQuestu paStav, std::string paText);

private:
	std::string nazovQuestu;
	std::map<StavQuestu, std::string> texty;
};


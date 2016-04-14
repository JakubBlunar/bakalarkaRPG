#include "QuestPolozka.h"
#include "Loader.h"
#include "Hra.h"
#include "Hrac.h"
#include "QuestManager.h"



QuestPolozka::QuestPolozka(std::string paNazovQuestu) :DialogPolozka("")
{
	this->nazovQuestu = paNazovQuestu;
}


QuestPolozka::~QuestPolozka()
{
}

std::string QuestPolozka::Gettext() {

	Hrac* hrac = Loader::Instance()->Gethra()->Gethrac();
	
	if (hrac->Getmanazerquestov()->maQuest(nazovQuestu)) {
		Quest* quest = hrac->Getmanazerquestov()->getQuest(nazovQuestu);

		switch (quest->Getstav())
		{
		case StavQuestu::ROZROBENY:
			if (texty.count(StavQuestu::ROZROBENY)) {
				return texty.at(StavQuestu::ROZROBENY);
			}
			break;
		case StavQuestu::SPLNENIE_POZIADAVIEK:
			if (texty.count(StavQuestu::SPLNENIE_POZIADAVIEK)) {
				return texty.at(StavQuestu::SPLNENIE_POZIADAVIEK);
			}
			break;
		case StavQuestu::DOKONCENY:
			if (texty.count(StavQuestu::DOKONCENY)) {
				return texty.at(StavQuestu::DOKONCENY);
			}
			break;
		default:
			return "Undefined";
		}
	}
	else {
		return texty.at(StavQuestu::NEPRIJATY);
	}
	return "Undefined";
}

void QuestPolozka::vlozText(StavQuestu paStav, std::string paText) {
	if (texty.find(paStav) == texty.end()) {
		texty.insert(std::make_pair(paStav, paText));
	}
}
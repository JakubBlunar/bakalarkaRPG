#include "VolbaPredQpolozkou.h"

#include "Quest.h"
#include "QuestManager.h"
#include "Hrac.h"
#include "Loader.h"
#include "Hra.h"

VolbaPredQpolozkou::VolbaPredQpolozkou(int dalsia, Quest* paQuest) :DialogVolba("", dalsia)
{
	this->quest = paQuest;
}


VolbaPredQpolozkou::~VolbaPredQpolozkou()
{
}



void VolbaPredQpolozkou::akcia(Hrac* hrac) {

}

std::string VolbaPredQpolozkou::Gettext() {

	Hrac* hrac = Loader::Instance()->Gethra()->GetHrac();

	if (!hrac->Getmanazerquestov()->maQuest(quest->Getnazov())) {
		if (texty.count(StavQuestu::NEPRIJATY)) {
			return texty.at(StavQuestu::NEPRIJATY);
		}
	}
	else {
		Quest* quest = hrac->Getmanazerquestov()->getQuest(this->quest->Getnazov());

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
	return "Undefined";
}

void VolbaPredQpolozkou::vlozText(StavQuestu paStav, std::string paText) {
	texty.insert_or_assign(paStav, paText);
}

Quest* VolbaPredQpolozkou::getQuest() {
	return quest;
}
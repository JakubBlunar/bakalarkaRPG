#include "Npc.h"
#include "Hrac.h"
#include "Animacia.h"
#include "DialogovyStrom.h"
#include "Loader.h"
#include "Hra.h"
#include "StavDialog.h"

#include "Quest.h"
#include "QuestManager.h"

Npc::Npc(std::string paMeno,DialogovyStrom* dialog) {
	meno = paMeno;
	dialogStrom = dialog;
	animacia = nullptr;
}

Npc::~Npc() {
	delete animacia;
	delete dialogStrom;
}



std::string Npc::Getmeno() const
{
	return meno;
}

sf::Sprite* Npc::dajObrazok() const
{
	return animacia->dajObrazok();
}


void Npc::dialog(Hrac* hrac) 
{

	QuestManager* manager = hrac->Getmanazerquestov();
	Quest* quest = manager->Getzaciatocnyquestnpc(meno);

	if (quest != nullptr) {

	}
	else {
		quest = manager->Getkonciaciquestnpc(meno);
	}

	if (quest != nullptr) {
		dialogStrom->Setdialogquest(quest);
	}

	dialogStrom->init();
	dialogStrom->zacniDialog();
	Loader* loader = Loader::Instance();
	StavDialog* stav = static_cast<StavDialog*>(loader->Gethra()->dajStav("stavDialog"));
	stav->Setdialog(this);
	loader->Gethra()->zmenStavRozhrania("stavDialog");
}


void Npc::update() const
{

}

void Npc::Setanimacia(Animacia* animacia) 
{
	this->animacia = animacia;
}

DialogovyStrom* Npc::Getdialog() const
{
	return dialogStrom;
}

#include "Pouzitelny.h"


Pouzitelny::Pouzitelny(std::string meno, int typ, std::string paObrazok, int cena, int paUroven) :Predmet(meno,typ,paObrazok,cena,paUroven){
	obleceny = false;
	hp = 0;
	hpMult = 0;
	mp = 0;
	mpMult = 0;
	sila = 0;
	silaMult = 0;
	rychlost = 0;
	rychlostMult = 0;
	inteligencia = 0;
	inteligenciaMult = 0;
	armor = 0;
	armorMult = 0;

}



Pouzitelny::~Pouzitelny() {
}





int Pouzitelny::Getarmor() const
{

	return armor;
}


double Pouzitelny::GetarmorMult() const
{

	return armorMult;
}


int Pouzitelny::Gethp() const
{

	return hp;
}


double Pouzitelny::GethpMult() const
{

	return hpMult;
}


int Pouzitelny::Getinteligencia() const
{

	return inteligencia;
}


double Pouzitelny::GetinteligenciaMult() const
{

	return inteligenciaMult;
}


int Pouzitelny::Getmp() const
{

	return mp;
}


double Pouzitelny::GetmpMult() const
{

	return mpMult;
}


int Pouzitelny::Getrychlost() const
{

	return rychlost;
}


double Pouzitelny::GetrychlostMult() const
{

	return rychlostMult;
}


int Pouzitelny::Getsila() const
{

	return sila;
}


double Pouzitelny::GetsilaMult() const
{

	return silaMult;
}


bool Pouzitelny::Isobleceny() const
{

	return obleceny;
}


void Pouzitelny::Setarmor(int newVal) {

	armor = newVal;
}


void Pouzitelny::SetarmorMult(double newVal) {

	armorMult = newVal;
}


void Pouzitelny::Sethp(int newVal) {

	hp = newVal;
}


void Pouzitelny::SethpMult(double newVal) {

	hpMult = newVal;
}


void Pouzitelny::Setinteligencia(int newVal) {

	inteligencia = newVal;
}


void Pouzitelny::SetinteligenciaMult(double newVal) {

	inteligenciaMult = newVal;
}


void Pouzitelny::Setmp(int newVal) {

	mp = newVal;
}


void Pouzitelny::SetmpMult(double newVal) {

	mpMult = newVal;
}


void Pouzitelny::Setobleceny(bool newVal) {

	obleceny = newVal;
}


void Pouzitelny::Setrychlost(int newVal) {

	rychlost = newVal;
}


void Pouzitelny::SetrychlostMult(double newVal) {

	rychlostMult = newVal;
}


void Pouzitelny::Setsila(int newVal) {

	sila = newVal;
}


void Pouzitelny::SetsilaMult(double newVal) {

	silaMult = newVal;
}
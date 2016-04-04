#pragma once
#include "Policko.h"

class Hrac;

/// <summary>
/// Specifický typ policka , na ktorom moze byt hrac napadnutý
/// </summary>
class PolickoBoj: public Policko
{
public:
	/// <summary>
	/// Vytvorí nove policko a nastavi mu priechodnost podla parametra
	/// </summary>
	/// <param name="paPriechodne">ci je policko priechodne</param>
	PolickoBoj(bool paPriechodne);
	~PolickoBoj();

	/// <summary>
	/// Metoda ktorý vyhodnoti ci bol hrac napadnutý a ak ano spustí boj
	/// </summary>
	/// <param name="paHrac">aktualny hrac</param>
	void hracSkok(Hrac* paHrac) override;
};


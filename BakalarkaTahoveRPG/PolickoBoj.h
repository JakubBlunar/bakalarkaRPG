#pragma once
#include "Policko.h"

class Hrac;

/// <summary>
/// Specifick� typ policka , na ktorom moze byt hrac napadnut�
/// </summary>
class PolickoBoj: public Policko
{
public:
	/// <summary>
	/// Vytvor� nove policko a nastavi mu priechodnost podla parametra
	/// </summary>
	/// <param name="paPriechodne">ci je policko priechodne</param>
	PolickoBoj(bool paPriechodne);
	~PolickoBoj();

	/// <summary>
	/// Metoda ktor� vyhodnoti ci bol hrac napadnut� a ak ano spust� boj
	/// </summary>
	/// <param name="paHrac">aktualny hrac</param>
	void hracSkok(Hrac* paHrac) override;
};


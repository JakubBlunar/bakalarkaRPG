#if !defined(VolbaBoj_h)
#define VolbaBoj_h

#include <string>

#include "DialogovyStrom.h"

using namespace std;

class VolbaBoj :
	public DialogVolba
{
public:
	VolbaBoj(string paText, int dalsia, string paNepriatel);
	~VolbaBoj();
	void akcia(Hrac* hrac) override;
private:
	bool pouzita;
	string nepriatel;
};
#endif

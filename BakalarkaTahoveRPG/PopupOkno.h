#if !defined(PopupOkno_h)
#define PopupOkno_h

#include <string>
#include <queue>

using namespace std;

class PopupOkno
{
public:
	PopupOkno(string paText);
	~PopupOkno();
	void pridajStranku(string text);
	string aktualnaStrana();
	string dajDalsi();
	bool skoncil();
private:
	queue<string> texty;
	bool koniec;
};
#endif


#include "Hra.h"

#include <random>
#include <time.h>

int main()
{
	srand((unsigned int)time(NULL));

	Hra* hra = new Hra();
	hra->start();
    return 0;
}


#include "Hra.h"

#include <random>
#include <time.h>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
	srand((unsigned int)time(NULL));

	Hra* hra = new Hra();
	hra->start();
    return 0;
}


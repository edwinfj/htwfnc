#include "test.h"
#include "timers.h"
#include <ctype.h>

int main(int argc, char *argv[])
{
	int profM = 0, profF;
	profM = argc > 1 ? atoi(argv[1]) : profM;
	profF = profM;
	profF = argc > 2 ? atoi(argv[2]) : profF;
	test_MMM(profM);
	test_four(profF);
}
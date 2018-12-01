#ifndef __TEST_H__
#define __TEST_H__

#define NDIGIT 2

#define AROW 100
#define ACOL 100
#define BCOL 100
#define MAXV 100

inline static float randf(int L, int H)
{	
	return (float)(L + rand() % (H - L)) + (float)(rand() % 1eNDIGIT)/1eNDIGIT;
}


int test_MMM(int prof);

int test_four(int prof);

#endif
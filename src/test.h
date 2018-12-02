#ifndef __TEST_H__
#define __TEST_H__

#include <stdlib.h>

#define NDIGIT 2
#define MMM_LOW -100
#define MMM_HIGH 100
#define FFT_LOW -100
#define FFT_HIGH 100
#define AROW 10
#define ACOL 10
#define BCOL 10
#define FFT_N 2048
#define MMM_KLOOPS 1000
#define FFT_KLOOPS 1000
#define MMM_TOL 1e-9
#define FFT_TOL 1e-9

inline static float randf(int L, int H)
{	
	return (float)(L + rand() % (H - L)) + (float)(rand() % (int)1e2f)/1e2f;
}


void test_MMM(int prof);

void test_four(int prof);

#endif
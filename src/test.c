#include "test.h"
#include "kernels.h"
#include "timers.h"

#include <stdio.h>
#include <math.h>

void compare_MMM(float **a, float **b, int r, int c, float tol)
{
	int i, j;
	int serr = 0, herr = 0;

	printf("Compare matrix multiplication:\n");
	for (i = 0; i < r; ++i) {
		for (j = 0; j < c; ++j) {
			if (fabs(a[i][j] - b[i][j]) > tol) {
				++herr; ++serr;
				if (herr < 10)
					printf("Error: a[%d][%d]: %f, b[%d][%d]: %f\n", \
						i, j, a[i][j], i, j, b[i][j]);
				else if (herr == 10)
					printf("...\n");
			} else if (fabs(a[i][j] - b[i][j]) > 0) {
				++serr;
				if (serr < 10)
					printf("Warning: a[%d][%d]: %f, b[%d][%d]: %f\n", \
						i, j, a[i][j], i, j, b[i][j]);
				else if (serr == 10)
					printf("...\n");
			}
		}
	}
	printf("Finished comparing matrix multiplication:\n");
	printf("\tHard error %d, soft error %d -- %s\n", herr, serr, \
		herr == 0 ? "Passed" : "Failed");
	printf("\n");
}

void compare_four(float *data_ref, float *data_test, int n, float tol)
{
	int i, serr = 0, herr = 0;

	printf("Compare fft\n");
	for (i = 0; i < n; ++i) {
		if (fabs(data_ref[i] - data_test[i]) > tol) {
			++herr; ++serr;
			if (herr < 10)
				printf("Error: d_ref[%d]: %f, d_test[%d]: %f\n",
					i, data_ref[i], i, data_test[i]);
			else if (herr == 10)
				printf("...\n");
		} else if (fabs(data_ref[i] - data_test[i]) > 0) {
			++serr;
			if (serr < 10)
				printf("Warning: d_ref[%d]: %f, d_test[%d]: %f\n",
					i, data_ref[i], i, data_test[i]);
			else if (serr == 10)
				printf("...\n");
		}
	}
	printf("Finished comparing fft:\n");
	printf("\tHard error %d, soft error %d -- %s\n", herr, serr, \
		herr == 0 ? "Passed" : "Failed");
	printf("\n");
}


void test_MMM(int prof)
{
	float A[AROW][ACOL];
	float B[ACOL][BCOL];
	float C_ref[AROW][BCOL], C_test[AROW][BCOL];
	float *a[AROW], *b[ACOL], *c_ref[AROW], *c_test[AROW];
	int i, j;

	for (i = 0; i < AROW; ++i) {
		a[i] = &A[i][0];
		for (j = 0; j < ACOL; ++j)
			A[i][j] = randf(MMM_LOW, MMM_HIGH);
	}

	for (i = 0; i < ACOL; ++i) {
		b[i] = &B[i][0];
		for (j = 0; j < BCOL; ++j)
			B[i][j] = randf(MMM_LOW, MMM_HIGH);
	}

	for (i = 0; i < AROW; ++i) {
		c_ref[i] = &C_ref[i][0];
		c_test[i] = &C_test[i][0];
		for (j = 0; j < BCOL; ++j) 
			C_ref[i][j] = C_test[i][j] = 0;
	}

	naive_MMM(a, b, c_ref, AROW, ACOL, BCOL);
	naive_MMM(a, b, c_test, AROW, ACOL, BCOL);
	compare_MMM(c_ref, c_test, AROW, BCOL, MMM_TOL);

#ifdef RELEASE
	if (prof) {
		uint64_t t0, t1;
		HiResTime h0, h1;

		t0 = RDTSC();
		get_HiResTime(&h0);
		for (i = 0; i < MMM_KLOOPS; ++i) 
			naive_MMM(a, b, c_test, AROW, ACOL, BCOL);
		t1 = RDTSC();
		get_HiResTime(&h1);

		printf("naive_MMM takes %llu cycles, %.4lf ms\n", t1 - t0, \
			convert_HiResTime_to_ms(&h1) - convert_HiResTime_to_ms(&h0));
	}
#endif
}

void test_four(int prof)
{
	float d_ref[FFT_N << 1], d_test[FFT_N << 1];
	int n = FFT_N, i, isign = 1;

	for (i = 0; i < (n << 1); ++i)
		d_ref[i] = d_test[i] = randf(FFT_LOW, FFT_HIGH);
	
	four1(d_ref, &n, &isign);
	four1(d_test, &n, &isign);
	compare_four(d_ref, d_test, n, FFT_TOL);

#ifdef RELEASE
	if (prof) {
		uint64_t t0, t1;
		HiResTime h0, h1;

		t0 = RDTSC();
		get_HiResTime(&h0);
		for (i = 0; i < FFT_KLOOPS; ++i)
			four1(d_test, &n, &isign);
		t1 = RDTSC();
		get_HiResTime(&h1);

		printf("four1 takes %llu cycles, %.4lf ms\n", t1 - t0, \
			convert_HiResTime_to_ms(&h1) - convert_HiResTime_to_ms(&h0));
	}
#endif
}
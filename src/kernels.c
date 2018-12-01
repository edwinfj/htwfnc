#include "kernels.h"
#include <math.h>

/**
 * C := AB
 */
void naive_MMM(float **A, float **B, float **C, int AR, int AC, int BC)
{
	int i, j, k;

	for (i = 0; i < AR; ++i) {
		for (j = 0; j < BC; ++j) {
			for (k = 0; k < AC; ++k) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}


/**
 * radix-2 FFT applying Danielson-Lanczos Lemma
 */
#define SWAP(a, b) (tempr) = (a); (a) = (b); (b) = (tempr);
void four1(float *data, int *nn, int *isign)
{
	int n, mmax, m, j, i;
	double wtemp, wr, wpr, wpi, wi, theta, wpin;
	double tempr, tempi, datar, datai, data1r, data1i;

	n = *nn * 2;
	j = 0;
	for (i = 0; i < n; i += 2) {
		if (j > i) {
			SWAP(data[j], data[i]);
			SWAP(data[j+1], data[i+1]);
		}
		m = *nn;
		while (m >= 2 && j >= m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	theta = 3.141592653589785 * .5;
	if (*isign < 0)
		theta = -theta;
	wpin = 0;
	for (mmax = 2; n > mmax; mmax *= 2) {
		wpi = wpin;
		wpin = sin(theta);
		wpr = 1 - wpin * wpin - wpin * wpin;
		theta *= .5;
		wr = 1;
		wi = 0;
		for (m = 0; m < mmax; m += 2) {
			j = m + mmax;
			tempr = (double) wr * (data1r = data[j]);
			tempi = (double) wi * (data1i = data[j+1]);
			for (i = m; i < n - mmax * 2; i += mmax * 2) {
				tempr -= tempi;
				tempi = (double) wr * data1i + (double) wi * data1r;
				data1r = data[j + mmax * 2];
				data1i = data[j + mmax * 2 + 1];
				data[i] = (datar = data[i]) + tempr;
				data[i+1] = (datai = data[i+1]) + tempi;
				data[j] = datar - tempr;
				data[j+1] = datai - tempi;
				tempr = (double) wr * data1r;
				tempi = (double) wi * data1i;
				j += mmax * 2;
			}
			tempr -= tempi;
			tempi = (double) wr * data1i + (double) wi * data1r;
			data[i] = (datar = data[i]) + tempr;
			data[i+1] = (datai = data[i+1]) + tempi;
			data[j] = datar - tempr;
			data[j+1] = datai - tempi;
			wr = (wtemp = wr) * wpr - wi * wpi;
			wi = wtemp * wpi + wi * wpr;
		}
	}
}
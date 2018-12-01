#ifndef __KERNELS_H__
#define __KERNELS_H__


/**
 * Naive implementation of matrix multiplication.
 * C = AB
 */
void naive_MMM(float **A, float **B, float **C, int AR, int AC, int BC)


/**
 * Radix-2 FFT
 */
void four1(float *data, int *nn, int *isign);

#endif
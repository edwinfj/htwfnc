#ifndef __KERNELS_H__
#define __KERNELS_H__


/**
 * Naive implementation of matrix multiplication.
 * C = AB
 */
void naive_MMM(float **a, float **b, float **c, int ar, int ac, int bc);


/**
 * Radix-2 FFT
 */
void four1(float *data, int *nn, int *isign);

#endif
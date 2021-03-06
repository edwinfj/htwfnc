#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/errno.h>


inline static void CPUID(int eax, int ecx) 
{
	int ebx, edx;
	__asm__ volatile ("cpuid"
		:"+a"(eax), "=b"(ebx), "+c"(ecx), "=d"(edx)
		);
	printf("eax: %x\n", eax);
	printf("ebx: %x\n", ebx);
	printf("ecx: %x\n", ecx);
	printf("edx: %x\n", edx);
}


inline static uint64_t RDTSC()
{
	uint64_t rdx, rax;
	__asm__ volatile ("rdtsc"
		:"=d"(rdx), "=a"(rax)
		);
	return (rdx << 32) | rax;
}


typedef struct {
	uint64_t tv_s;
	uint64_t tv_ns;
} HiResTime;

inline static int get_HiResTime(HiResTime *t)
{
	int ret;
	ret = clock_gettime(CLOCK_REALTIME, (struct timespec*)t);
	if (ret) printf("Error: get_HiResTime failed. Errno %d\n.", errno);
	return ret;
}

inline static double convert_HiResTime_to_ms(HiResTime *t)
{
	return (double)t->tv_s * 1e3 + (double)t->tv_ns * 1e-6;
}

#endif
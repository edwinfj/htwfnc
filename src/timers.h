#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <stdio.h>
#include <stdint.h>


inline static void CPUID(int eax, int ecx) 
{
	int ebx, edx;
	__asm__ volatile ("cpuid"
		:"+a"(eax), "=b"(ebx), "+c"(ecx), "=d"(edx)
		:
		:"eax", "ebx", "ecx", "edx"
		);
	printf("eax: %x\n", eax);
	printf("ebx: %x\n", ebx);
	printf("ecx: %x\n", ecx);
	printf("edx: %x\n", edx);
}


inline static void RDTSC()
{

}


typedef struct {
	uint64_t tv_s;
	uint64_t tv_ns;
} HiResTime;



#endif
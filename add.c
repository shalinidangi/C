#define _GNU_SOURCE             
#include <pthread.h>
#include "add.h"

int opt_yield;

void basic_add(long long *pointer, long long value)
{
    long long sum = *pointer + value;
    *pointer = sum;
}

void extd_add(long long *pointer, long long value)
{
    long long sum = *pointer + value;
    if (opt_yield) {
        pthread_yield();
    }
    *pointer = sum;
}

void mutex_add(long long *pointer, long long value)
{
}

void spinlk_add(long long *pointer, long long value)
{
}

void sync_add(long long *pointer, long long value)
{
}

void add(long long *pointer, long long value, int add_type)
{
	switch(value)
	{
		case BASIC_ADD:
			basic_add(pointer, value);
			break;
		case EXTD_ADD:
			extd_add(pointer, value);
			break;
		case MUTEX_ADD:
			mutex_add(pointer, value);
			break;
		case SPINLK_ADD:
			spinlk_add(pointer, value);
			break;
		case SYNC_ADD:
			sync_add(pointer, value);
			break;
	}
}
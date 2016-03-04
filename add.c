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

void *add(void *args_ptr)
{
	add_args_t *arg_struct = (add_args_t *)args_ptr;
	long long *pointer = arg_struct->ptr;
	long long value = arg_struct->value;
	int add_type = arg_struct->add_type;

	switch(add_type)
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
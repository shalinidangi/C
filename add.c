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

void atomic_add(long long *pointer, long long value)
{
}

/* 
	ADD WRAPPER FUNCTION 
	- 	Takes a pointer to the struct with arguments 
		to pass to add() 
	- 	Determines which version of add() to call
	-	Calls add(1) *value* times and add(-1) *value* times
*/
void *add(void *args_ptr)
{
	// get parameters from argument struct
	add_args_t *arg_struct = (add_args_t *)args_ptr;
	long long *pointer = arg_struct->ptr;
	long long value = arg_struct->value;
	int add_type = arg_struct->add_type;

	// create function pointer for add()
	void (*addFxn) (long long *, long long);

	// make addFxn point to correct function
	switch (add_type)
	{
		case BASIC_ADD: 	addFxn = &basic_add; 	break; 
		case EXTD_ADD:		addFxn = &extd_add;		break;
		case MUTEX_ADD: 	addFxn = &mutex_add;	break;
		case SPINLK_ADD:	addFxn = &spinlk_add;	break;
		case ATOMIC_ADD:	addFxn = &atomic_add;	break;
	}

	*pointer = 0;

	int i;
	for (i = 0; i < value; i++)
		addFxn(pointer, 1);

	for (i = 0; i < value; i++)
		addFxn(pointer, -1);
}
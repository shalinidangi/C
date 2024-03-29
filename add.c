#define _GNU_SOURCE             
#include <stdio.h>
#include "add.h"

int opt_yield;
pthread_mutex_t mutex_lock;
volatile int lock_m = 0;

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
	pthread_mutex_lock(&mutex_lock);
	long long sum = *pointer + value;
	*pointer = sum;
	pthread_mutex_unlock(&mutex_lock);
}

void spinlk_add(long long *pointer, long long value)
{
	while (__sync_lock_test_and_set(&lock_m, 1)); 
	long long sum = *pointer + value; 
	*pointer = sum; 
	__sync_lock_release(&lock_m);
}

/* ================= ATOMIC ADD ====================
	- 	Compare value of orig to *pointer. If they match,
 		set *pointer = sum.
 	-	If the value doesn't match, reattempt until it matches
 		and we actually do the swap. 
 =================================================== */
void atomic_add(long long *pointer, long long value)
{
	int orig, sum;
	do
	{
		orig = *pointer; 
		sum = orig + value;
	} while (__sync_val_compare_and_swap(pointer, orig, sum) != orig);
}

/* ================= ADD WRAPPER ===================
	- 	Takes a pointer to the struct with arguments 
		to pass to add() 
	- 	Determines which version of add() to call
	-	Calls add(1) *value* times and add(-1) *value* times
 =================================================== */
void *add(void *args_ptr)
{
	// get parameters from argument struct
	add_args_t *arg_struct = (add_args_t *)args_ptr;
	long long *pointer = arg_struct->ptr;
	long long value = arg_struct->num_its;
	int add_type = arg_struct->add_type;
	opt_yield = arg_struct->opt_yield;

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

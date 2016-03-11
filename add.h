#ifndef ADD_H_   /* Include guard */
#define ADD_H_

#define BASIC_ADD		0
#define EXTD_ADD 		1
#define MUTEX_ADD		2
#define SPINLK_ADD		3
#define ATOMIC_ADD		4

#include<pthread.h>

extern pthread_mutex_t mutex_lock;

typedef struct add_args
{
	int opt_yield;		// whether to yield in add()
	long long *ptr;		// ptr to add value to 		
	int add_type;		// which add function to call
	int num_its; 		// number of iterations
} add_args_t;

void *add(void *args_ptr);


#endif // ADD_H_

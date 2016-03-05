#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "add.h"
#include "parse.h"

int main(int argc, char **argv)
{
	int add_type;

	switch (sync_type)
	{
		case MUTEX_SYNC:	add_type = MUTEX_ADD;	break;
		case SPINLK_SYNC:	add_type = SPINLK_ADD;	break;
		case ATOMIC_SYNC:	add_type = ATOMIC_ADD;	break;
		default: 			add_type = EXTD_ADD;	
	}

	long long result;

	parse(argc, argv);

	// allocate array to hold threads
	pthread_t *threads = malloc(sizeof(pthread_t) * n_threads);

	int i;
	for (i = 0; i < n_threads; i++)
	{
		add_args_t* args;
		args->ptr = &result;
		args->value = n_iters;
		args->add_type = add_type;

		int success = pthread_create(&threads[i], NULL, add, (void *)args);

		if(!success)
		{
			fprintf(stderr,"ERROR: pthread_create() returned: %d\n", success);
         	exit(EXIT_FAILURE);
		}

		pthread_join(threads[i], NULL);
	}


}
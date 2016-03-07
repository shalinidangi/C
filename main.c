#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "add.h"
#include "parse.h"

int main(int argc, char **argv)
{
	int add_type;
	long long result;
	parse(argc, argv);

	switch (sync_type)
	{
		case MUTEX_SYNC:	add_type = MUTEX_ADD;	break;
		case SPINLK_SYNC:	add_type = SPINLK_ADD;	break;
		case ATOMIC_SYNC:	add_type = ATOMIC_ADD;	break;
		default: 			add_type = EXTD_ADD;	
	}

	if (add_type == MUTEX_ADD)
	{
		if (pthread_mutex_init(&mutex_lock, NULL) != 0)
	    {
	        fprintf(stderr, "\n ERROR: mutex init failed\n");
	        exit(EXIT_FAILURE);
	    }
	}

	// print number of operations
	long num_ops = n_threads * n_iters * 2;

	fprintf(stdout, "%d threads x %d iterations x (add + subtract) = %ld operations\n",
		n_threads,
		n_iters,
		num_ops);

	// allocate array to hold threads
	pthread_t *threads = malloc(sizeof(pthread_t) * n_threads);

	int i;
	for (i = 0; i < n_threads; i++)
	{
		add_args_t args;
		args.ptr = &result;
		args.value = n_iters;
		args.add_type = add_type;

		int failure = pthread_create(&threads[i], NULL, add, (void *)(&args));

		if(failure)
		{
			fprintf(stderr,"ERROR: pthread_create() returned: %d\n", failure);
         	exit(EXIT_FAILURE);
		}

		pthread_join(threads[i], NULL);
	}


	if (add_type == MUTEX_ADD)
		pthread_mutex_destroy(&mutex_lock);

	if (result != 0)
		fprintf(stderr, "ERROR: final count = %lld\n", result);
}
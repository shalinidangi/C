#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/wait.h>
#include <time.h>

#include "add.h"
#include "parse.h"

#define BILLION 1000000000L

int main(int argc, char **argv)
{
	struct timespec start, end;

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

	// allocate array to hold threads
	pthread_t *threads = malloc(sizeof(pthread_t) * n_threads);

	clock_gettime(CLOCK_MONOTONIC, &start);
	int i;
	for (i = 0; i < n_threads; i++)
	{
		add_args_t args;
		args.ptr = &result;
		args.num_its = n_iters;
		args.add_type = add_type;

		int failure = pthread_create(&threads[i], NULL, add, (void *)(&args));

		if(failure)
		{
			fprintf(stderr,"ERROR: pthread_create() returned: %d\n", failure);
         	exit(EXIT_FAILURE);
		}

		pthread_join(threads[i], NULL);
	}

	// wait for all threads to finish, then get the system time
	int status;
	for (i = 0; i < n_threads; i++)
		wait(&status);

	clock_gettime(CLOCK_MONOTONIC, &end);
	long long diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

	// print number of operations
	long num_ops = n_threads * n_iters * 2;

	fprintf(stdout, "%d threads x %d iterations x (add + subtract) = %ld operations\n",
		n_threads,
		n_iters,
		num_ops);

	if (result != 0)
		fprintf(stderr, "ERROR: final count = %lld\n", result);

	fprintf(stdout, "elapsed time: %lld ns\n", diff);
	fprintf(stdout, "per operation: %lld ns\n", diff/num_ops);

	if (add_type == MUTEX_ADD)
		pthread_mutex_destroy(&mutex_lock);

	
}
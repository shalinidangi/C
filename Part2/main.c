#define _GNU_SOURCE
#include <pthread.h>
#include <stdint.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "SortedList.h"
#include "parse.h"
#include "list.h"

int main()
{
	int list_type;
	parse(argc, argv);

	switch (sync_type)
	{
		case MUTEX_SYNC:	list_type = MUTEX_LIST;	break;
		case SPINLK_SYNC:	list_type = SPINLK_LIST;	break;
		default: 			list_type = BASIC_LIST;	
	}

	if (list_type == MUTEX_LIST)
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
		list_args_t args;
		args.num_its = n_iters;
		args.list_type = list_type;

		int failure = pthread_create(&threads[i], NULL, list, (void *)(&args));

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
	long num_ops = n_threads * n_iters * 2 * 50;

	fprintf(stdout, "%d threads x %d iterations x (insert + lookup/delete) x (100/2 avg len) = %ld operations\n",
		n_threads,
		n_iters,
		num_ops);

	if (result != 0)
		fprintf(stderr, "ERROR: final count = %lld\n", result);

	fprintf(stdout, "elapsed time: %lld ns\n", diff);
	fprintf(stdout, "per operation: %lld ns\n", diff/num_ops);

	if (list_type == MUTEX_LIST)
		pthread_mutex_destroy(&mutex_lock);

	
}




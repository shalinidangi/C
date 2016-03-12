#define _GNU_SOURCE
#include <pthread.h>
#include <stdint.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "SortedList.h"
#include "parse.h"
#include "list.h"

#define BILLION 1000000000L

int main(int argc, char **argv)
{
	struct timespec start, end;
	
	int list_type = BASIC_LIST;
	parse(argc, argv);

	switch (sync_type)
	{
		case MUTEX_SYNC:	list_type = MUTEX_LIST;		break;
		case SPINLK_SYNC:	list_type = SPINLK_LIST;	break;
		default: 			list_type = BASIC_LIST;	
	}

	printf("sync-type was %c, list type is %d\n", sync_type, list_type);
	mutex_locks = (pthread_mutex_t*)malloc(n_lists * sizeof(pthread_mutex_t));
	if (mutex_locks == NULL)
	{
		fprintf(stderr,"ERROR: malloc() failed\n");
        exit(EXIT_FAILURE);
	}

	locks_m = (volatile int*)malloc(n_lists * sizeof(volatile int));
	if (locks_m == NULL)
	{
		fprintf(stderr,"ERROR: malloc() failed\n");
        exit(EXIT_FAILURE);
	}

	if (list_type == MUTEX_LIST)
	{
		int ix;
		for (ix = 0; ix < n_lists; ix++)
		{
			if (pthread_mutex_init(&mutex_locks[ix], NULL) != 0)
			{
				fprintf(stderr, "\n ERROR: mutex init failed\n");
	        	exit(EXIT_FAILURE);
			}
		}
	}
	else if (list_type == SPINLK_LIST)
	{
		int ix;
		for (ix = 0; ix < n_lists; ix++)
			locks_m[ix] = 0;
	}
	// create array of preinitialized list elements
	SortedListElement_t *elements = create_rand_list_elements(n_threads * n_iters);

	// allocate array to hold threads
	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * n_threads);
	if (threads == NULL)
	{
		fprintf(stderr,"ERROR: malloc() failed\n");
        exit(EXIT_FAILURE);
	}
	
	// Create sublists
	lists = (SortedList_t*)malloc(n_lists * sizeof(SortedList_t));
	if (lists == NULL)
	{
		fprintf(stderr,"ERROR: malloc() failed\n");
        exit(EXIT_FAILURE);		
	}

	int ix;
	for (ix = 0; ix < n_lists; ix++)
	{
		lists[ix].prev = &lists[ix];
  		lists[ix].next = &lists[ix];
  		lists[ix].key = NULL;
	}

	clock_gettime(CLOCK_MONOTONIC, &start);

	int i;
	for (i = 0; i < n_threads; i++)
	{
		list_args_t args;
		args.num_its = n_iters;
		printf("LIST TYPE IS STILL %d\n", list_type);
		args.list_type = list_type;
		args.elements = &elements[i * n_iters];
		args.num_sublists = n_lists;

		int failure = pthread_create(&threads[i], NULL, list, (void *)(&args));
		if(failure)
		{
			fprintf(stderr,"ERROR: pthread_create() returned: %d\n", failure);
         	exit(EXIT_FAILURE);
		}
		//pthread_join(threads[i], NULL);
	}


	for (i = 0; i < n_threads; i++)
	{
		int join_fail = pthread_join(threads[i], NULL);
		if (join_fail)
		{
			fprintf(stderr, "ERRORL pthread_join() returned %d\n", join_fail);
			exit(EXIT_FAILURE);
		}
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

	int len = SortedList_length(lists);
	if (len != 0)
		fprintf(stderr, "ERROR: final list length = %d\n", len);

	fprintf(stdout, "elapsed time: %lld ns\n", diff);
	fprintf(stdout, "per operation: %lld ns\n", diff/num_ops);

	if (list_type == MUTEX_LIST)
	{
		int jx;
		for (jx = 0; jx < n_lists; jx++)
		{
			pthread_mutex_destroy(&mutex_locks[jx]);
		}
	}
	exit(0);
}


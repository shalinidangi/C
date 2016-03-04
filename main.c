#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "add.h"
#include "parse.h"

int main()
{
	// TACO - delete these variables
	// placeholders for compilation - should actually get values from parsing
	int nthreads; 
	long long *ptr;
	long long value;
	int add_type;
	// ENDTACO

	// allocate array to hold threads
	pthread_t *threads = malloc(sizeof(pthread_t) * nthreads);

	int i;
	for(i = 0; i < nthreads; i++)
	{
		add_args_t args;
		args.ptr = ptr;
		args.value = value;
		args.add_type = add_type;

		int success = pthread_create(&threads[i], NULL, add, (void *)args);

		if(!success)
		{
			fprintf(stderr,"ERROR: pthread_create() returned: %d\n", success);
         	exit(EXIT_FAILURE);
		}

		pthread_join(threads[i], NULL);
	}


}
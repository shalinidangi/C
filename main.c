#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "add.h"
#include "parse.h"

int main(int argc, char **argv)
{
	// TACO - delete this variable
	// placeholder for compilation - should actually determine add_type based on parsing results
	int add_type = 0;
	// ENDTACO

	long long result;
	long long *ptr = &result;

	parse(argc, argv);

	// allocate array to hold threads
	pthread_t *threads = malloc(sizeof(pthread_t) * n_threads);

	int i;
	for (i = 0; i < n_threads; i++)
	{
		add_args_t* args;
		args->ptr = ptr;
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
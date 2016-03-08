#include <getopt.h>
#include <errno.h>
#include <stdlib.h>
#include "parse.h"

/* OPTIONS */
int n_threads;
int n_iters;
int set_yield;
char sync_type;

void parse(int argc, char **argv)
{
	// initialize options to default values
	n_threads = 1;
	n_iters = 1;
	set_yield = 0;
	sync_type = NOSYNC;
	
	while (1)
	{
		int result;

		// Add more long options as we progress.
		static struct option long_options[] = 
		{
			{"threads", 	required_argument, 	0, 	THREADS},
			{"iterations", 	required_argument, 	0,	ITERATIONS},
			{"yield", 		required_argument, 	0, 	YIELD},
			{"sync", 		required_argument, 	0, 	SYNC},
			{0, 0, 0, 0}
		};

		int option_index = 0;

		// Parse command line options until there are none remaining
		// getopt_long will return -1 when it is finished.
		result = getopt_long(argc, argv, "", long_options, &option_index);
		if (result == -1)
			break;

		switch(result)
		{
			case THREADS:
			{
				char *ptr;
				n_threads = strtol(optarg, &ptr, 10);
				break;
			}
			case ITERATIONS:
			{
				char *ptr;
				n_iters = strtol(optarg, &ptr, 10);
				break;
			}

			// TACO: fix this - should be --yield=[ids]
			case YIELD:
			{
				break;
			}
			case SYNC:
			{
				char c = optarg[0];
				if (c == MUTEX_SYNC || c == SPINLK_SYNC)
					sync_type = c;
			}
		}
	}
}

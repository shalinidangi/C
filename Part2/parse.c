#include <getopt.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "parse.h"
#include "SortedList.h"

/* OPTIONS */
int n_threads;
int n_iters;
int n_lists;
int opt_yield;
char sync_type;

void parse(int argc, char **argv)
{
	// initialize options to default values
	n_threads = 1;
	n_iters = 1;
	n_lists = 1;
	opt_yield = 0;
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
			{"lists", 		required_argument, 	0, 	LISTS},
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

			case YIELD:
			{
				int i;
				for(i = 0; i < 3; i++)
				{
					char c = optarg[0];

					if (c == '\0')
						break;
					
					switch(c)
					{
						case 'i':
							opt_yield |= INSERT_YIELD;	break;
						case 'd':
							opt_yield |= DELETE_YIELD;	break;
						case 's':
							opt_yield |= SEARCH_YIELD;	break;
						default: // invalid argumentls
							fprintf(stderr, "ERROR: Invalid argument to --yield option\nFormat should be --yield[ids]\n");
					}
				}
				break;
			}
			case SYNC:
			{
				char c = optarg[0];
				if (c == MUTEX_SYNC || c == SPINLK_SYNC)
					sync_type = c;
				break;
			}
			case LISTS:
			{
				char *ptr;
				n_lists = strtol(optarg, &ptr, 10);
				break;
			}

		}
	}
}

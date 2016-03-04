#include <getopt.h>
#include <errno.h>

void parse(int argc, char **argv)
{
	while (1)
	{
		int threads = 1;
		int iters = 1;
		// Add more long options as we progress.
		static struct option long_options[] = 
		{
			{"threads", required_argument, 0, 't'},
			{"iterations", required_argument, 0, 'i'},
			{0, 0, 0, 0}
		};

		// Parse command line options until there are none remaining
		// getopt_long will return -1 when it is finished.
		result = getopt_long(argc, argv, "", long_options, &option_index);
		if (result == -1)
			break;

		switch(result)
		{
			case 't':
			{
				char *ptr;
				int ret;
				ret = strtol(optArg, &ptr, 10);
				threads = ret;
				break;
			}
			case 'i':
			{
				char *ptr;
				int ret;
				ret = strtol(optArg, &ptr, 10);
				iters = ret;
				break;
			}
		}
	}
}

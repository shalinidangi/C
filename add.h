#ifndef ADD_H_   /* Include guard */
#define ADD_H_

#define BASIC_ADD		0
#define EXTD_ADD 		1
#define MUTEX_ADD		2
#define SPINLK_ADD		3
#define SYNC_ADD		4

typedef struct add_args
{
	long long *ptr;
	long long value;
	int add_type;
} add_args_t;

void add(long long *pointer, long long value, int add_type);


#endif // ADD_H_
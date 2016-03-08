#ifndef LIST_H_   /* Include guard */
#define LIST_H_

#define BASIC_LIST		0
#define MUTEX_LIST		1
#define SPINLK_LIST		2

extern pthread_mutex_t mutex_lock;

typedef struct list_args
{
	int list_type;		// which list function to call
	int num_its; 		// number of iterations
} list_args_t;

void *list(void *args_ptr);


#endif // LIST_H_
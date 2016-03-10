#ifndef LIST_H_   /* Include guard */
#define LIST_H_

#define BASIC_LIST		0
#define MUTEX_LIST		1
#define SPINLK_LIST		2

extern pthread_mutex_t* mutex_locks;
extern volatile int* locks_m;

typedef struct list_args
{
	int list_type;					// which list function to call
	int num_its; 					// number of iterations
	int num_sublists;				// number of sublists to break the list into
	SortedListElement_t *elements;	// array of elements to insert in list
} list_args_t;

void *list(void *args_ptr);
SortedListElement_t *create_rand_list_elements(int n_elements);


#endif // LIST_H_
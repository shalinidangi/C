#define _GNU_SOURCE
#include <pthread.h>

#include "SortedList.h"
#include "list.h"

void basic_list(void* args_ptr)
{

}


void mutex_list(void* args_ptr)
{

}

void spinlk_list(void* args_ptr)
{

}


/* ================= LIST WRAPPER ==================
 =================================================== */
void list(void* args_ptr)
{
	// get parameters from argument struct
	list_args_t *arg_struct = (lsit_args_t *)args_ptr;

	int list_type = arg_struct->list_type;

	// create function pointer for list()
	void (*listFxn) (void *);

	// make listFxn point to correct function
	switch (list_type)
	{
		case BASIC_LIST: 	listFxn = &basic_list; 	break; 
		case MUTEX_LIST: 	listFxn = &mutex_list;	break;
		case SPINLK_LIST:	listFxn = &spinlk_list;	break;
	}

	listFxn(args_ptr);
}





#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h> // testing purposes
#include "SortedList.h"
#include "list.h"

 pthread_mutex_t mutex_lock;

/*============= CREATE LIST ELEMENTS ==============
	* Returns a pointer to an array of 
		SortedListElements
	* Array will containing n_elements elements
	* Each element has a randomly generated key
=================================================*/													
SortedListElement_t *create_rand_list_elements (int n_elements)
{
	SortedListElement_t *arr = (SortedListElement_t *)malloc(sizeof(SortedListElement_t) * n_elements);

	int i;
	for (i = 0; i < n_elements; i++)
	{
		// Generate a random key
		char *key = "bob";	// TACO replace this with something more random than Bob

		// Create a list element with that key
		SortedListElement_t element;
		element.key = key;

		arr[i] = element;
	}

	return arr;
}

/* ================= LIST WRAPPER ================== */
void *list(void* args_ptr)
{
	// get parameters from argument struct
	list_args_t *arg_struct = (list_args_t *)args_ptr;
	int list_type = arg_struct->list_type;
	int num_its = arg_struct->num_its;
	SortedListElement_t *elements = arg_struct->elements;

	SortedList_t list;
	list.next = &list;
	list.prev = &list;
	list.key = NULL;

	// insert elements into list
	int i;
	for (i = 0; i < num_its; i++)
	{
		SortedList_insert(&list, &elements[i]);
	}

	int len = SortedList_length(&list);

	for (i = 0; i < num_its; i++)
	{
		SortedListElement_t *victim = SortedList_lookup(&list, elements[i].key);
		SortedList_delete(victim);
	}	
}






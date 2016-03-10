#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h> // testing purposes
#include <string.h>
#include "SortedList.h"
#include "list.h"

 pthread_mutex_t mutex_lock;

int hash(const char *key)
{
	int i = 0, hash = 7, len = strlen(key);

	for (; i < len; i++)
		hash = hash * 31 + key[i];
}

/*============= CREATE LIST ELEMENTS ==============
	* Returns a pointer to an array of 
		SortedListElements
	* Array will containing n_elements elements
	* Each element has a randomly generated key
=================================================*/													
SortedListElement_t *create_rand_list_elements (int n_elements)
{
	SortedListElement_t *arr = (SortedListElement_t *)malloc(sizeof(SortedListElement_t) * n_elements);

	time_t t;
	srand((unsigned) time(&t));

	int i;
	for (i = 0; i < n_elements; i++)
	{
		int len = rand() % 9;
		len++;
		
		char* key = (char*)malloc(sizeof(char) * (len + 1));
		
		// Generate a random key
		int j;
		for (j = 0; j < len; j++)
		{
			key[j] = (char)(rand() % 255);
		}
		key[j] = '\0';

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
	int num_lists = arg_struct->num_sublists;
	SortedListElement_t *elements = arg_struct->elements;

	// create n

	SortedList_t list;
	list.next = &list;
	list.prev = &list;
	list.key = NULL;

	// insert elements into list
	int i;
	for (i = 0; i < num_its; i++)
	{
		int l = hash(elements[i].key);	// which sublist to put element in 
		SortedList_insert(&list, &elements[i]);
	}

	int len = SortedList_length(&list);

	for (i = 0; i < num_its; i++)
	{
		SortedListElement_t *victim = SortedList_lookup(&list, elements[i].key);
		SortedList_delete(victim);
	}	
}






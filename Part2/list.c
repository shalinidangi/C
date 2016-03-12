#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h> // testing purposes
#include <string.h>
#include "SortedList.h"
#include "list.h"
#include "parse.h"

pthread_mutex_t* mutex_locks;
volatile int* locks_m;
SortedList_t* lists;

unsigned long long hash(const char *key)
{
	unsigned long long i = 0, hash = 7, len = strlen(key);

	for (; i < len; i++)
		hash = hash * 31 + key[i];
	return hash;
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

void acquire_lock(int list_type, int sublist_ix)
{
	if (list_type == NOSYNC)
	{
		return;
	}
	else if (list_type == MUTEX_LIST)
	{
		pthread_mutex_lock(&mutex_locks[sublist_ix]);
	}
	else if (list_type == SPINLK_LIST)
	{
		while(__sync_lock_test_and_set(&locks_m[sublist_ix], 1));
	}
}

void release_lock(int list_type, int sublist_ix)
{
	if (list_type == NOSYNC)
	{
		return;
	}
	else if (list_type == MUTEX_LIST)
	{
		pthread_mutex_unlock(&mutex_locks[sublist_ix]);
	}
	else if (list_type == SPINLK_LIST)
	{
		__sync_lock_release(&locks_m[sublist_ix]);
	}
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

	// insert elements into list
	int i;
	for (i = 0; i < num_its; i++)
	{
		unsigned long long l = hash(elements[i].key) % num_lists;	// which sublist to put element in
		acquire_lock(list_type, l);
		SortedList_insert(&lists[l], &elements[i]);
		release_lock(list_type, l);
	}

	int j;
	for (j = 0; j < num_lists; j++)
	{
		acquire_lock(list_type, j);
	}
	// TACO: re-implement _length to add up all sublists
	int len = SortedList_length(lists);
	if (len == -1)
		fprintf(stderr, "ERROR: length detected that a list is corrupted\n");
	for (j = 0; j < num_lists; j++)
	{
		release_lock(list_type, j);
	}

	for (i = 0; i < num_its; i++)
	{
		int l = hash(elements[i].key) % num_lists;

		acquire_lock(list_type, l);
		SortedListElement_t *victim = SortedList_lookup(&lists[l], elements[i].key);
		int res = SortedList_delete(victim);
		if (res == 1)
			fprintf(stderr, "ERROR: delete detected that a list is corrupted\n");
		release_lock(list_type, l);
	}	
}






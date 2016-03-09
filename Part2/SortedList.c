#define _GNU_SOURCE             
#include <pthread.h>
#include "SortedList.h"
#include <string.h>

int opt_yield;

// insert node in list while maintaining ascending order in list  
void SortedList_insert(SortedList_t *list, SortedListElement_t *element) 
{ 
	SortedListElement_t *p = list; 
	SortedListElement_t *n = list->next; //first element 
	// if list is empty, list->next = list 
	 
	// find the first node 'n' that is greater than the element 
	while (n != list) 
	{ 
		if (strcmp(element->key, n->key) <= 0) 
			break; 
		p = n; 
		n = n->next; 
	} 

	if (opt_yield & INSERT_YIELD)
		pthread_yield();
	 
	// insert an element
	element->prev = p; 
	element->next = n; 
	p->next = element; 
	n->prev = element; 
} 
 
int SortedList_delete(SortedListElement_t *element) 
{ 
	// actually do the deletion 
	SortedListElement_t *n = element->next; 
	SortedListElement_t *p = element->prev; 
	 
	if (n->prev != element) 
		return 1; 
	if (p->next != element) 
		return 1; 
	 
	if (opt_yield & DELETE_YIELD)
		pthread_yield();

	// delete the element
	n->prev = p; 
	p->next = n; 
	element->next = NULL; 
	element->prev = NULL; 
	return 0; 
} 

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key)
{
	SortedListElement_t *p = list;
	SortedListElement_t *n = list->next; //first element 
	// if list is empty, list->next = list 

	if (opt_yield & DELETE_YIELD)
		pthread_yield();

	while (n != list)
	{
		if (strcmp(key, n->key) == 0)
			return n;
		p = n;
		n = n->next;
	}

	return NULL;
}

int SortedList_length(SortedList_t *list)
{
	int count = 0;

	SortedListElement_t *p = list; // previous element
	SortedListElement_t *c = list->next; //first/current element 
	// if list is empty, list->next = list 
	SortedListElement_t *n; // next element

	if (opt_yield & SEARCH_YIELD)
		pthread_yield();

	while (c != list)
	{
		// Check all prev/next pointers
		if (n->prev != c) 
			return -1; 
		if (p->next != c) 
			return -1;

		count++;
		n = c->next;
		p = c;
		c = n;
	}

	return count;
}



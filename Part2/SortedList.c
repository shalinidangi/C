#define _GNU_SOURCE             
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include "SortedList.h"
#include "parse.h"


int opt_yield;

// insert node in list while maintaining ascending order in list  
void SortedList_insert(SortedList_t *list, SortedListElement_t *element) 
{
	if (!list || !element)
		return;

	SortedListElement_t *p = list; 
	SortedListElement_t *n = list->next; //first element 
	// if list is empty, list->next = list 
	 
	printf("starting while\n");
	// find the first node 'n' that is greater than the element 
	while (n != list) 
	{
		if (strcmp(element->key, n->key) <= 0) 
			break; 
		p = n; 
		n = n->next; 
	} 

	printf("done with while\n");
	if (opt_yield & INSERT_YIELD)
		pthread_yield();
	 
	// insert an element
	element->prev = p; 
	element->next = n; 
	p->next = element; 
	n->prev = element; 
	printf("inserted element\n");
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
	int count = 0, i = 0;
	SortedList_t *sublist;

	for(; i < n_lists; i++)
	{
		sublist = &list[i];
		SortedListElement_t *p = sublist; // previous element
		SortedListElement_t *c = sublist->next; //first/current element 
		// if list is empty, list->next = list 
		SortedListElement_t *n; // next element

		if (opt_yield & SEARCH_YIELD)
			pthread_yield();

		while (c != sublist)
		{
			n = c->next;

			// Check all prev/next pointers
			if (n->prev != c) 
				return -1; 
			if (p->next != c) 
				return -1;

			count++;
			p = c;
			c = n;
		}
	}
	
	return count;
}



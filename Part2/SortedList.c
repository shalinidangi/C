
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
	 
	element->prev = p; 
	element->next = n; 
	p->next = element; 
	n->prev = element; 
} 

 
int SortedList_delete(SortedListElement_t *element) 
{ 
	// call lookup function?

	// actually do the deletion 
	SortedListElement_t *n = element->next; 
	SortedListElement_t *p = element->prev; 
	 
	if (n->prev != element) 
		return -1; 
	if (p->next != element) 
		return 1; 
	 
	n->prev = p; 
	p->next = n; 
	element->next = NULL; 
	element->prev = NULL; 
	return 0; 
} 
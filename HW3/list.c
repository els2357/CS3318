/*
 * Updated 3/2/2023 - Alexandra Stefan
 */

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// ------------- Node functions

/* Creates a new node, with data value_in and NULL for next.
 */
struct node * new_node(int value_in) {
    struct node * result = (struct node *) malloc(sizeof (struct node));
    result->data = value_in;
    result->next = NULL;
    return result;
}

/*    --------  LIST functions    */

/* Deallocates memory for all nodes in the list. */
void destroy_list(nodePT L) {
    nodePT next;
	nodePT curr = L;
	L = NULL;   // can remove this line, not needed
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

/* 
Creates a new node with data d and inserts it at the beginning of list (*La).
It modifies content of the memory that La points to.
*/ 
void insert_front(struct node ** La, int d){
	if (La==NULL) {
		printf("Failed to insert at front. La is NULL.\n");
		return;
	}
	struct node * temp = malloc(sizeof(struct node));
	temp->data = d;
	temp->next = (*La);
	(*La) = temp;
}


/* Inserts newP after the node prev.
   Note that this is works on nodes. It does not matter how a list is represented.
   prev is just a node.
*/
void insert_node_after(nodePT prev, nodePT newP) {
    if (prev == NULL) {
        printf("\n Cannot insert after a NULL node. No action taken.");
    } else {
        newP->next = prev->next;
        prev->next = newP;
    }
}

/* 
   Parameters:
	- L a linked list (has the address of the first node).
	- prev - is either NULL or the address of a node node from list L. 
	- newP - address of a node to be inserted/linked in L. 
	         newP will be linked in L after prev.   
    If prev is NULL it means newP must be linked to the beginning of L,
	and will be the first node the list.
	
	Returns: the address of the first node in the updated list.
 */
nodePT insert_node(nodePT L, nodePT prev, nodePT newP){
	if (prev == NULL) {  // inserts at the begining of the list L
		newP->next = L;
		return newP;  // return address of the new first node
	}
	else {
		insert_node_after(prev, newP); // does not affect the list head
		return L;
	}
}

/* Delete the node after the node prev.
   Note that this is works on nodes. It does not matter how a list is represented.
   prev is just a node.
*/
void delete_node_after(nodePT prev) {
    if (prev == NULL) {
        printf("\n Cannot delete after a NULL node. No action taken.");
    } else {
		nodePT toDel = prev->next;
		if (toDel != NULL){
			prev->next = toDel->next;
			free(toDel);
		}
    }
}

/* 
    Parameters:
	- L a linked list (has the address of the first node).
	- prev - is either NULL or the address of a node node from list L. 
             If prev is NULL the first node of L will be deleted.
	
	Returns: the address of the first node in the updated list. 
 */
nodePT delete_node(nodePT L, nodePT prev){
	if (prev == NULL) { // delete the first node from L
		if (L==NULL) {  // no node in the list. nothing to delete
			return NULL;
		}
		else {    // delete the first node and return the address of the new first node
			nodePT newPtr = L->next;
			free(L);
			return newPtr;
		}
	}
	else {
		delete_node_after(prev); // does not affect the list head
		return L;
	}
}

// Swaps 2 nodes after prev.
// If prev is NULL or not enough nodes for swapping, it does nothing.
void swap_2_after(nodePT prev){
    if (prev == NULL) {
        printf("\n Cannot swap after a NULL node. No action taken.");
    } else {
		if ( (prev->next == NULL) || (prev->next->next == NULL) ) {
			printf("\nNot enough nodes!\n");
			return;
		}
		nodePT A = prev->next;  // 1st node in the swap, code crashes if NULL
		nodePT B = prev->next->next;  // 2nd node in the swap, code crashes if NUL
		nodePT C = B->next;  // first nodes after the nodes to be swapped (A, B). Ok to be NULL.
        prev->next = B; //8
		B->next = A;    //9
		A->next = C;    //10
    }
}

/*
 Iterates through list L and counts nodes.
 Returns the length of list L.
*/
int compute_length(nodePT L) {
    if (L == NULL) {
        return 0;
    }

    int counter = 0;
    struct node * curr;
    for (curr = L; curr != NULL; curr = curr->next) {
        counter++;
    }
    return counter;
}

// prints the linked list my_list
void print_list_vert(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list> : list is NULL\n");
        return;
    }
    int i = 0;
    struct node * curr;
    printf("\n List items:\n");
    for (i = 0, curr = my_list; (curr != NULL); curr = curr->next) {
        printf("item %d: %d\n", i, curr->data);
        i++;
    }
	printf(" Length of above list = %d\n", i);
}

// prints the linked list my_list
void print_list_horiz(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_horiz> : List is NULL\n");
        return;
    }
    int i = 0;
    struct node * curr;

    printf("\n List items: ");
    for (i = 0, curr = my_list; (curr != NULL); curr = curr->next) {
        printf("%5d    ", curr->data);
        i++;
    }
	printf("\n Length of above list = %d\n", i);
}

/*  Prints the nodes in list L. 
	For each node prints both the data and the memory address of that node
	(not the field next, but the address of the node)
 */
void print_list_pointer(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_pointer> : List is NULL\n");
        return;
    }

    int i = 0;
    struct node * curr;
    printf("\n List items:    ");
    for (i = 0, curr = my_list; (curr != NULL); curr = curr->next) {
        printf("%-16d ", curr->data);
        i++;
    }
    printf("\n List pointers: ");
    for (i = 0, curr = my_list; (curr != NULL); curr = curr->next) {
        printf("%-16p ", curr);
        i++;
    }
	printf("\n Length of above list = %d\n", i);
}

nodePT array_2_list(int arr[], int N)  {
	if (N==0) {
		return NULL;  // no data in the array. return empty list
	}

	int i;
	nodePT lastP, newP;
	nodePT L = new_node(arr[0]); // special case for first node
	printf("\n N=%d\n", N);
	lastP = L;  // the last node of L is also the first node so far.
	for (i = 1; i < N; i++) 	{
		newP = new_node(arr[i]);
		lastP->next = newP;
		lastP = newP;
	}
	return L;
}
/*
// Same code, but without the using the fct new_node
nodePT array_2_list(int arr[], int N)  {
	printf("\n N = %d\n", N);
	int j;
	nodePT lastP, newP;
	// special case for first node: create it and vase its pointer in L
	nodePT L = malloc(sizeof(struct node));
	L->data = arr[0];
	L->next = NULL;

	lastP = L;  // it is also the last node in the list so lastP points to it

	for (j = 1; j < N; j++) 	{
							// create new node and write data in it
		newP = malloc(sizeof(struct node));
		newP->data = arr[j];
		newP->next = NULL;

		lastP->next = newP;  // link the new node after the last node in the list, lastP

		lastP = newP;  // this new node, is now the last node in the list so make
					   // lastP point to it (i.e. copy in lastP the content of newP).
	}
	return L;
}
*/

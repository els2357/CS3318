/* 
 * Updated 3/2/2023 - Alexandra Stefan
 */


#ifndef LIST_H
#define	LIST_H

typedef struct node * nodePT;  // POINTER to NODE (memory address of NODE)
struct node {
    int data;
    struct node * next;  // it is the same as: nodePT next;
};

nodePT array_2_list(int arr[], int N);
    
/* Creates a new node, with data value_in and NULL for next. 
 */
nodePT new_node(int value_in);

/*  Note that these functions may not have all the security checks.
E.g. not all the functions reading and setting members of a node pointer, 
check that the node is not NULL  */


/*  --------  LIST  */

void destroy_list(nodePT L);

/* 
Creates a new node with data d and inserts it at the beginning of list (*La).
It modifies content of the memory that La points to.
*/ 
void insert_front(struct node ** La, int d);

/* Inserts newP after the node prev.
   Note that this is works on nodes. It does not matter how a list is represented.
   prev is just a node.
*/
void insert_node_after(nodePT prev, nodePT newP);

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
nodePT insert_node(nodePT L, nodePT prev, nodePT newP);

/* Delete the node after the node prev.
   Note that this is works on nodes. It does not matter how a list is represented.
   prev is just a node.
*/
void delete_node_after(nodePT prev);

/* 
    Parameters:
	- L a linked list (has the address of the first node).
	- prev - is either NULL or the address of a node node from list L. 
             If prev is NULL the first node of L will be deleted.
	
	Returns: the address of the first node in the updated list. 
 */
nodePT delete_node(nodePT L, nodePT prev);

// Swaps 2 nodes after prev.
// If prev is NULL or not enough nodes for swapping, it does nothing.
void swap_2_after(nodePT prev);

/*
 Iterates through list L and counts nodes.
 Returns the length of list L.
*/
int compute_length(nodePT L);  



// prints the linked list my_list
void print_list_vert(nodePT my_list);

// prints the linked list my_list
void print_list_horiz(nodePT my_list);

/*  Prints the nodes in list L. 
	For each node prints both the data and the memory address of that node
	(not the field next, but the address of the node)
 */
void print_list_pointer(nodePT my_list);

#endif	/* LIST_H */


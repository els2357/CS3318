/******Ethan Sprinkle**********
******************************/

#include <stdlib.h>
#include <stdio.h>

#include "heap.h"  

//#define DEBUG 1
#define DEBUG 0

int idxOfMaxValue (int * A, int p, int left, int right, int N);

struct heap_struct make_heap_empty(int cap)
{
	struct heap_struct empty_heap;
	empty_heap.items = (int*)calloc(cap, sizeof(int));
	empty_heap.N = 0;
	empty_heap.capacity = cap;
	return empty_heap;
}

struct heap_struct make_heap(int N, int * arr)
{
	struct heap_struct heapS;
	heapS.N = N;
	heapS.capacity = N;
	heapS.items = arr;
	if (DEBUG == 1) 
	{
		printf("In function make_heap, in DEBUG MODE, printing array BEFORE it gets turned into a heap :");
		print_heap(heapS);
	}
	for (int p = ((N-1)/2); p >=0; p--)
	{
		sink_down(p, N, arr);
		heapS.items = arr;
		if (DEBUG == 1)
		{
			printf("In function make_heap, in DEBUG MODE, printing array AFTER sink_down at index %d :", p);
			print_heap(heapS);
		}
	}
	return heapS;
}

void destroy(struct heap_struct * heapP)
{
	if(heapP->N != 0)
	{
		free(heapP->items);
		heapP->N = 0;
		heapP->capacity = 0;
	}
}


void print_heap(struct heap_struct heapS)
{
	int i = 0;
	printf("Heap:  size: %d, capacity: %d\n", heapS.N, heapS.capacity);
	printf("indexes:	");
	for(int i = 0; i < heapS.N; i++)
	{
		printf("%7d,", i);
	}
	printf("\n");
	printf("values:		");
	for(int i = 0; i < heapS.N; i++)
	{
		printf("%7d,", heapS.items[i]);
	}
	printf("\n\n");
}


void swim_up(int idx, int * arr)
{
	while ((idx>0) && (arr[idx]>arr[((idx-1)/2)]))
	{
		int temp = arr[idx];
		arr[idx] = arr[((idx-1)/2)];
		arr[((idx-1)/2)] = temp;
		idx = ((idx-1)/2);
	}
}


void sink_down(int i, int N, int * arr)
{
	int left = ((2*i)+1);
	int right = ((2*i)+2);
	int imv = idxOfMaxValue (arr, i, left, right, N);
	while((imv != i) && (imv < N))
	{
		int temp = arr[imv];
		arr[imv] = arr[i];
		arr[i] = temp;
		for (int k = 0; k < N; k++)
		i = imv;
		left =((2*i)+1);
		right = ((2*i)+2);
		imv = idxOfMaxValue (arr, i, left, right, N);
	}
}

void add(struct heap_struct * heapP, int new_item)
{
	if (heapP->N == heapP->capacity)
	{
		heapP->capacity = ((heapP->capacity)*2);
		heapP->items = realloc((heapP->items), ((sizeof(int)*(heapP->capacity))));
	}
	
	heapP->items[heapP->N] = new_item;
	(heapP->N)++;
	swim_up(((heapP->N)-1), heapP->items);
}

int peek(struct heap_struct heapS)
{
	int root;
	if(heapS.items == NULL)
	{
		printf("Heap is empty.\n");
		return 0;
	}
	root = heapS.items[0];
	return root;
}


int poll(struct heap_struct * heapP)
{
	if ((heapP->N) == 0)
	{
		printf("Heap is empty. Return value is -1.");
		return -1;
	}

	int max = heapP->items[0];
	heapP->items[0] = heapP->items[((heapP->N)-1)];
	(heapP->N)--;
	sink_down(0, heapP->N, heapP->items);
	/*if (heapP->N == 0)
	{
		destroy(heapP);
	}*/
	return max;
}

int idxOfMaxValue (int * A, int p, int left, int right, int N)
{
	int imv = p;
	if ((left < N) && (A[left] > A[imv]))
	{
		imv = left;
	}
	
	if ((right < N) && (A[right] > A[imv]))
	{
		imv = right;
	}
	return imv;
}

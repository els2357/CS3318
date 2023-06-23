/* 
  Alexandra Stefan
 
  Gradual testing of heap functions.
 */
 
/* compile: 
gcc -g gradual.c heap.c
run:
./a.out 

Valgrind:
valgrind --leak-check=full ./a.out 
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "heap.h"  

void t1_peek_destroy();
void t2_swimup_add();
void t3_sink_make_remove();  

int main(){	
	//t1_peek_destroy();
	//t2_swimup_add();
	//t3_sink_make_remove(); 
	return 0;
}


/*
Add your own test function.
It will test:
- sink_down()
- make_heap - it should use the bottom method that repeatedly calls sink_down
- poll()
*/
void t3_sink_make_remove(){
	printf("\nt3_sink_make_remove: Placeholder code\n");
}


/*
test functions 
- peek
- destroy 
- and an incomplete implementation of make_heap(): it will give an array that is already a heap.
When running just this test function, there should not be any memory leaks or other Valgrind errors.
*/
void t1_peek_destroy(){
	printf("\n---------------- Running :  t1_peek_destroy() -----------------\n");
		
	struct heap_struct heapS;
	int N = 3;
	int *arr = calloc(N, sizeof(int) ); // note that arr will not be freed here. It will be freed by destroy()
	arr[0] = 90;
	arr[1] = 70;
	arr[2] = 60;
	
	heapS = make_heap(N, arr);         
	print_heap(heapS);

	// test peek
	printf("peek:    %6d\n", peek(heapS) );
	print_heap(heapS);

	destroy(&heapS);   
	printf("After call to destroy (1)\n");
	print_heap(heapS);
	
	destroy(&heapS);   
	printf("After call to destroy (2)\n");
	print_heap(heapS);
		
	
	//   make, print and destroy another heap
	N = 4;
	arr = calloc(N, sizeof(int) );
	arr[0] = 13;
	arr[1] = 9;
	arr[2] = 11;
	arr[3] = 7;

	printf("\nMake another heap:\n");
	heapS = make_heap(N, arr);         
	print_heap(heapS);

	destroy(&heapS);   
	printf("After call to destroy (3)\n");
	print_heap(heapS);	
}


/*
Tests
- swim_up
- add 
*/
void t2_swimup_add(){
	printf("\n---------------- Running :  t2_swimup_add() -----------------\n");
	
	struct heap_struct heapS;	
	int N = 0, val = 0;
		
	N = 6;
	int *arr = calloc(N, sizeof(int) );
	arr[0] = 90;
	arr[1] = 70;
	arr[2] = 60;
	arr[3] = 10;
	arr[4] = 50;
	arr[5] = 40;	
	
	heapS = make_heap(N, arr);  
	print_heap(heapS);	

	// test swim up all the way to the root
	printf("After arr[4]=200 (array will not be a heap anymore)\n");	
	arr[4] = 200;
	print_heap(heapS);			
	swim_up(4, arr);
	printf("After calling swim_up at index 4 for fix the array back into a heap:\n");		
	print_heap(heapS);	
	

	// test swim up does not go up to the root
	printf("After arr[3]=130 (array will not be a heap anymore)\n");	
	arr[3] = 130;
	print_heap(heapS);		
	swim_up(3, arr);
	printf("After calling swim_up at index 3 for fix the array back into a heap:\n");	
	print_heap(heapS);	
	
	// test an add() operation where no swim up is needed. 
	// Resizing will also happen here. Check updated size and capacity.
	printf("After add:     %6d\n", 17);	
	add(&heapS, 17);
	print_heap(heapS);	
	
	// Test an add operation that moves new item 2 levels up.	
	val = 182;
	printf("add:     %6d\n", val);	
	add(&heapS, val);
	print_heap(heapS);	
	
	
	destroy(&heapS);
}




/******Ethan Sprinkle**********
******************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "heap.h"  

int main ()
{
	//Open file, read number of N elements and store elements in an array 
    char fname[51];
    int n = 0;
    int p = 0;
    char buffer[10];
    FILE *fp;
    
	printf("Enter the filename: ");
    scanf("%s", fname);
	fp =fopen(fname, "r");
	if (fp == NULL){
		printf("File could not be opened.\n");
		return -1;
	}
	fscanf(fp, "%d", &n);

    int* array = (int*)calloc(n, sizeof(int));

    for(int i=0; i<n; i++)
    {
        fscanf(fp, "%d", &array[i]);
    }

    struct heap_struct heapS;
    heapS = make_heap(n, array);
    print_heap(heapS);
    
    //Scan file up to number of P elements and perform that many operations of the appropriate type
    fscanf(fp, "%d", &p);
    for(int i=0; i<p; i++)
    {
        fscanf(fp, "%s", buffer);
        {
            int s = atoi(buffer);
            
            //If s !=0, then it's an integer to be added to the heap
            if (s != 0)
            {
                printf("add:     %6d\n", s);	
	            add(&heapS, s);
	            print_heap(heapS);
            }

            //Peek if input is "p" or "P"
            else if ((!strcmp(buffer, "p")) || (!strcmp(buffer, "P")))
            {
                printf("peek:    %6d\n", peek(heapS) );
                print_heap(heapS);
            }

            //Remove max value of heap if input is "*"
            else if((!strcmp(buffer, "*")))
            {
                printf("removed: %6d\n", poll(&heapS) );	
	            print_heap(heapS);
            }
        }
    }

    destroy(&heapS);
    fclose(fp);
    return 0;
}

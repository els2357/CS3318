/* 
 * Updated 2/23/2023 - Alexandra Stefan
 */

/* 
compile with -g to collect debugging info needed for Valgrind ( -lm links the math library): 
gcc -g bucket_sort.c list.c -lm

run with Valgrind:
valgrind --leak-check=full ./a.out

On some systems, but not all, you can also use the --show-leak-kinds=all flag:
valgrind --leak-check=full --show-leak-kinds=all ./a.out

run without Valgrind:
./a.out
*/


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "list.h"   // useful if you want to use functions from list.c

void print_array(int arr[], int N);
void run1();
void bucket_sort(int * arr, int N);
int arr_max(int * arr, int n);
int arr_min(int * arr, int n);
int bucket_index(int i, int max, int min, int N);

/* 
// function to insert a new node in a sorted list. E.g.: 
nodePT insert_sorted(nodePT L, nodePT newP);
//or
nodePT insert_sorted(nodePT L, int elem);
*/

int main()
{
	printf("This program will read a file name, load data for an array from there and print the sorted array.\n");
	printf("The array is sorted using bucket sort.\n");
	printf("This will be repeated as long as the user wants.\n");
	int option;
	do {
		run1();

		printf("\nDo you want to repeat? Enter 1 to repeat, or 0 to stop) ");
		char ch;
		scanf("%d%c",&option, &ch);  // ch is used to remove the Enter from the input buffer
 	} while (option == 1);

   return 0;
}

//-------------------------------------------------------------

void print_array(int arr[], int N)
{
	int j;
	printf("\n array: ");
	for(j= 0; j<N; j++){
		printf("%5d,", arr[j]);
	}
	printf("\n");
}

void run1()
{
	//Open file and read in number of elements 
    char fname[51];
    int n = 0;
    FILE *fp;
    
	printf("Enter the filename: ");
    scanf("%s", fname);
	fp =fopen(fname, "r");
	if (fp == NULL){
		printf("File could not be opened.\n");
		return;
	}
	fscanf(fp, "%d", &n);

    int* array = (int*)calloc(n, sizeof(int));

    for(int i=0; i<n; i++)
    {
        fscanf(fp, "%d", &array[i]);
    }

    print_array(array, n);
    bucket_sort(array, n);

    free (array);
    fclose(fp);
}

void bucket_sort(int * arr, int N)
{
    int min = arr_min(arr, N);
    int max = arr_max(arr, N);
    int idx;
    printf("Bucketsort: min = %d, max = %d, N = %d buckets\n", min, max, N);
    
    //Create array of Linked List of size N and init all values to NULL
    nodePT listArr[N];
    for (int j=0; j<N; j++)
    {
        listArr[j] = NULL;
    }

    //Bucket Sort Original Array
    for (int i=0; i<N; i++)
    {
        idx = bucket_index(arr[i], max, min, N);
        printf("arr[%d]= %5d, idx = %d\n", i, arr[i], idx);
        nodePT *L = &(listArr[idx]);
        nodePT temp = new_node(arr[i]);

        if ((*L != NULL) && ((temp->data) < ((*L)->data)))
        {
            insert_front(L, (temp->data));
            free(temp);
        }
    
        else
        {
            listArr[idx] = insert_node(*L, *L, temp);
        }
    }

    //Print Sorted Link List
    for (int i=0; i<N; i++)
    {
        printf("------ List at index %d : \n", i);
        print_list_horiz(listArr[i]);
    }

    //Print Sorted Array
    printf("array: ");
    for (int i=0; i<N; i++)
    {
        struct node * curr;
        for (curr = listArr[i]; (curr != NULL); curr = curr->next)
        {
            printf("%5d,", curr->data);
        }
    }
    printf("\n");

    //Destroy Linked List
    for (int i=0; i<N; i++)
    {  
        destroy_list(listArr[i]);
    }
}

//Finds and returns the largest value in array
int arr_max(int * arr, int n)
{
    int max = arr[0];
    for (int i=1; i<n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

//Finds and returns the smallest value in array
int arr_min(int * arr, int n)
{
    int min = arr[0];
    for (int i=1; i<n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

int bucket_index(int i, int max, int min, int N)
{
    int idx = (int)floor( ((i-((double)min))*N)/(1+((double)max)-((double)min)) );
    return idx;
}
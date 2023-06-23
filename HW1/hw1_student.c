#include "hw1_student.h"  // .h extenssion, not .c

// You do not need to change this print_1D function. It is included here for
// your convenience, in case you need to call it while debugging.
void print_1D(int sz, int * arr){
	for(int k = 0; k< sz; k++){
		printf("%8d", arr[k]);
	}
	printf("\n");
}


/* dynamically allocates an array and populates it with all values from arr
	that are strictly smaller than thresh.
	Returns:
		- the pointer to the dynamically allocated array.
		- NULL if all elements of arr are greater or equal to thres. In this case it does not allocate any memory, and sets content of sz_res to 0.
*/
int* get_scores_below(int thresh, int sz_arr, int * arr, int* sz_res){
	// change code here to correct function implementation
	int * new_arr = NULL; //pointer for new array
	*sz_res = 0;
	int k = 0;
	for (int i=0; i < sz_arr; i++){
		if (arr[i] < thresh){
			(*sz_res)++;
		}
	}

	if ((*sz_res) == 0){ //if no elements are less than thresh, return NULL and set sz_res to 0
		return NULL;
	}

	else{
		new_arr = (int *)malloc(sizeof(int)*(*sz_res));
		for (int j=0; j < sz_arr; j++){
			if (arr[j] < thresh){
				new_arr[k] = arr[j];
				k++;
			}
		}
		return new_arr;
	}
}


void update_min_max(int num_rows, int num_cols, int* arr2D[], int* arr_min, int* arr_max){
	// write your code here
	*arr_min = arr2D[0][0];
	*arr_max = arr2D[0][0];

	for (int r = 0; r<num_rows; r++){
		for(int c=0; c<num_cols; c++){
			if ((arr2D[r][c]) < *arr_min) *arr_min = arr2D[r][c];
			else if ((arr2D[r][c]) > *arr_max) *arr_max = arr2D[r][c];
		}
	}
}


// improve this code to print as required in the homework
void print_2D(int num_rows, int num_cols, int* arr2D[]){
	int r,c;
	printf("\n");
	printf("   |");
	for (c = 0; c<num_cols; c++){
		printf("%8d|", c);
	}
	printf("\n");
	printf("----");
	for (c = 0; c<num_cols; c++){
		printf("---------");
	}
	printf("\n");

	for (r = 0; r<num_rows; r++){
		printf("  %d|", r);
		for(c=0; c<num_cols; c++){
			printf("%8d|", arr2D[r][c]);
		}
		printf("\n");
	}
}

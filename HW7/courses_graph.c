// Student Name: Ethan Sprinkle
// Student ID: 	 1002002357
// Course: 		 CSE 3318 Spring 2023
// Assignment	 courses_graph.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1000
#define MAX_FILE_NAME 30
#define MAX_COURSE_NAME 30
#define MAX_CLASSES 500

//Prints Adj Matrix Table
void print( int ** table, int class_size )
{
	printf("Adjacency matrix: \n");
	
	//Print initial row
	printf("   |");
	for (int i = 0; i < class_size; i++)
	{
		printf("%3d", i);
	}
	
	printf("\n-");
	
	for (int i = 0; i < class_size; i++)
	{
		printf("----");
	}
	printf("\n");
	
	//Print table
	for (int i = 0; i < class_size; i++)
	{
		printf("%3d|", i);
		for (int j = 0; j < class_size; j++)
		{
			printf("%3d", table[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	return;
}

// Recursive function to topologically sort vertexes
int dfs_visit( int ** table, int u, int * color, int * pred, int num_classes, char ** vertex, int * res_array, int * res_index)
{
	int valid;
	color[u] = 1;
	for (int v = 0; v < num_classes; v++)
	{
		// search for edges
		if (table[u][v] == 1)
		{
			if (color[v] == 0)
			{
				pred[v] = u;
				valid = dfs_visit(table, v, color, pred, num_classes, vertex, res_array, res_index);
				if (valid == -1)
				{
					return -1;
				}
			}
			
			if (color[v] == 1)
			{
				printf("There was at least one cycle found. No possible ordering of courses. \n");
				return -1;
			}
		}
	}
	color[u] = 2;
	res_array[(*res_index)] = u;
	(*res_index)++;
	return 0;
}

// Depth first search
void dfs( int ** table, int num_classes, char ** vertex )
{
	int res_index = 0;
	// 0 = White
	// 1 = Gray
	// 2 = Black
	int * res_array = malloc(num_classes*sizeof(int));
	int * color = malloc(num_classes*sizeof(int));
	int * pred = malloc(num_classes*sizeof(int));
	int valid;
	
	for (int u = 0; u < num_classes; u++)
	{
		color[u] = 0;
		pred[u] = -1;
	}
	
	// return -1 if cycle is found
	int valid_return;
	
	for (int u = 0; u < num_classes; u++)
	{
		if (color[u] == 0)
		{
			valid_return = dfs_visit(table, u, color, pred, num_classes, vertex, res_array, &res_index);
			if (valid_return == -1)
			{
				free(res_array);
				free(color);
				free(pred);
				return;
			}
		}
	}
	
	// print topologically sorted vertexes
	printf("Order in which to take courses: \n");
	int temp = 0;
	for (int u = num_classes-1; u >= 0; u--)
	{
		printf("%s (corresponds to graph vertex %d)\n", vertex[res_array[u]], res_array[u]);
	}
	
	printf("\n");
	free(res_array);
	free(color);
	free(pred);
}

int main()
{
	FILE *fp;
	char * buffer = (char*) malloc( MAX_LINE_SIZE );
	char * filename = (char*) malloc( MAX_FILE_NAME );
	char c;
	
	printf("\nThis program will read from a file, a list of courses and their prerequisites and will print the list in which to take courses.\n");
	printf("Enter filename: ");
	scanf("%s%c", filename, &c);
	
	// open filename
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("\nERROR opening file. Exit.\n\n");
		free(buffer);
		free(filename);
		return (-1);
	}
	
	// parse input 
	char *token;
	char *tokens[MAX_CLASSES];
	
	// set tokens equal to NULL
	for (int i = 0; i < MAX_CLASSES; i++)
	{
		tokens[i] = NULL;
	}
	
	// creates an array of classes that will be populated by the first entry on each line
	char ** classes = (char**)malloc(sizeof(char*)*MAX_CLASSES);
	int class_index = 0;
	
	/*This loop reads from the file and stores only the first word in each line in the classes[] array*/
	
	// loop through file up to number of classes in file
	for (int i = 0; i < MAX_CLASSES; i++)
	{
	
		// if EOF/token is NULL, break out of loop
		if (fgets(buffer, MAX_LINE_SIZE, fp) == NULL)
		{
			break;
		}
		
		// tokenize line with " " delimiter and store tokens in a token array
		else
		{
			//grab and store first token
			int token_count = 0;
			token = strtok(buffer," ");
			*(classes+i) = (char*)malloc(MAX_COURSE_NAME);
			
			//loop through tokens
			while (token != NULL )
			{
				tokens[token_count++] = token;
				token = strtok(NULL, " ");
			}
			
			//replace terminating \n with NULL character for last token
			token_count = token_count-1;
			int size = strlen(tokens[token_count]);
			tokens[token_count][size-1] = '\0';
			
			//copy token[0] into class array
			strcpy(classes[class_index++], tokens[0]);
		}
	}

	fclose(fp);

	printf("Number of verticies in built graph: N = %d\n", class_index);
	printf("Vertex - coursename correspondence\n");
	for (int i = 0; i < class_index; i++)
	{
		printf("%d - %s\n", i, classes[i]);
	}
	printf("\n");
	
	// Reopen file to compare courses with prereqs
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("ERROR opening file. Exit.\n");
		return (-1);
	}
	
	// Create an adjacency matrix and init to zero
	
	int ** adjMatrix = (int**)malloc(sizeof(int*)*(class_index));
    for (int i=0; i < class_index; i++)
    {
    	*(adjMatrix+i) = (int*)malloc((class_index) * sizeof(int));
    }
    
	for (int i = 0; i < class_index; i++)
	{
		for (int j = 0; j < class_index; j++)
		{
			adjMatrix[i][j] = 0;
		}
	}
	
	/*This loop reads from the file and fills the adjacency matrix using the classes[] array*/
	
	// loop through file up to number of classes in file
	for (int i = 0; i < MAX_CLASSES; i++)
	{
	
		// if EOF/token == NULL, break out of loop
		if (fgets(buffer, MAX_LINE_SIZE, fp) == NULL)
		{
			break;
		}
		
		// tokenize line with " " delimiter and store tokens in a token array
		else
		{
			//grab and store first token
			int token_count = 0;
			token = strtok(buffer," ");
			
			//loop through tokens
			while (token != NULL )
			{
				tokens[token_count++] = token;
				token = strtok(NULL, " ");
			}
			
			//replace terminating \n with NULL character for last token
			token_count = token_count-1;
			int size = strlen(tokens[token_count]);
			tokens[token_count][size-1] = '\0';
			
			// if token_count == 0, no prereqs, continue loop
			if (token_count == 0)
			{
				continue;
			}
			
			//compares each class/token with classes[] entry
			for (int j = 1; j <= token_count; j++)
			{
				for (int k = 0; k < class_index; k++)
				{
					// if prerequsite is found, fill in AdjMatrix
					if(!(strcmp(classes[k], tokens[j])))
					{
						adjMatrix[k][i] = 1;
					}
				}
			}
		}
	}
	
	// Print adjacency Matrix
	print(adjMatrix, class_index);
	
	// DFS of AdjMatrix
	dfs(adjMatrix, class_index, classes);
	
	//Free Allocated Memory
	for (int i = 0; i < class_index; i++)
	{
		free(classes[i]);
		free(adjMatrix[i]);
	}
	free(adjMatrix);
	free(buffer);
	free(filename);
	free(classes);
	fclose(fp);
	
	return 0;
}

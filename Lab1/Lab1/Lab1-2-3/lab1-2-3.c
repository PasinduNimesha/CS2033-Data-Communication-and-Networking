// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "chain.h"
#include <string.h>

// function prototypes
void print_chain(chain * chn); 
void run(chain * chn);


int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}

// parse the input
void run(chain *chn) 
{
    node * curr = malloc(sizeof(node));
    int num_rows;
    // printf("Enter the number of rows in the initial matrix: ");
    scanf("%d", &num_rows); // Read the number of rows in the initial matrix
    scanf("%*c");
	char input[100];
    // printf("Enter the elements of row %d: ", 1);
    fgets(input, sizeof(input), stdin);

    int num_columns = 0;
    int element;
    char *token = strtok(input, " "); // Split input into tokens using space as delimiter
    int row1[100];
    while (token != NULL) {
        
        if (sscanf(token, "%d", &element) == 1) {
            num_columns++;
        }
        row1[num_columns-1] = element;
        token = strtok(NULL, " ");
    }
    


    matrix *initial_matrix = create_matrix(num_rows, num_columns);
    for (int j = 0; j < num_columns; ++j) {
        initial_matrix->data[0][j] = row1[j];
    }

    for (int i = 1; i < num_rows; ++i) {
        // printf("Enter the elements of row %d: ", i + 1);
        for (int j = 0; j < num_columns; ++j) {
            scanf("%d", &initial_matrix->data[i][j]);
        }
    }



    int index = 0;   
    insert_node_after(chn, 0, initial_matrix);
    curr = chn->head;
    int function_code = 1; 

    while(function_code != 0){
        
        scanf("%d", &function_code);
        switch (function_code)
        {
        case 2:
            // printf("Enter the elements of the new row: ");
            insert_node_after(chn, index, curr->mat);
            curr = curr->next;
            int *row = (int *)malloc(curr->mat->num_cols * sizeof(int));
            for (int i = 0; i < curr->mat->num_cols; ++i) {
                scanf("%d", &row[i]);
            }
            add_row(curr->mat, row); // Add the new row to the matrix
            break;
        case 3:
            insert_node_after(chn, index, curr->mat);
            curr = curr->next;
            // printf("Enter the elements of the new column: ");
            int *column = (int *)malloc(curr->mat->num_rows * sizeof(int));
            for (int i = 0; i < curr->mat->num_rows; ++i) {
                scanf("%d", &column[i]);
            }
            add_col(curr->mat, column); // Add the new column to the matrix
            break;
        case 4:
            insert_node_after(chn, index, curr->mat);
            curr = curr->next;
            // printf("Enter the number to be added to each element: ");
            int num;
            scanf("%d", &num);
            increment(curr->mat, num); // Add the number to each element of the matrix
            break;
        case 5:
            insert_node_after(chn, index, curr->mat);
            curr = curr->next;
            // printf("Enter the number to be multiplied to each element: ");
            int num2;
            scanf("%d", &num2);
            scalar_multiply(curr->mat, num2); // Multiply the number to each element of the matrix
            break;
        case 6:
            insert_node_after(chn, index, curr->mat);
            curr = curr->next;
            // printf("Enter the number to be divided to each element: ");
            int num3;
            scanf("%d", &num3);
            scalar_divide(curr->mat, num3); // Divide the number to each element of the matrix
            break;
        case 7:
            insert_node_after(chn, index, curr->mat);
            curr = curr->next;
            // printf("Enter the number to raise each element to: ");
            int num4;
            scanf("%d", &num4);
            scalar_power(curr->mat, num4); // Raise each element of the matrix to the power of the number
            break;
        case 8:
            delete_matrix(curr->mat); // Delete the matrix
        case 0:
            break;
        default:
            break;
        }
        index++;       
    }
	
}



//Print the chain
void print_chain(chain * chn)
{
    node * curr = chn->head;
    while (curr != NULL) {
        print_matrix(curr->mat);
        curr = curr->next;
        printf("\n");
    }  
}


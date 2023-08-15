#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

#include "chain.h" // do not modify this file
#include <math.h>

// put your function prototypes for additional helper functions below:


// implementation
matrix *create_matrix(int num_rows, int num_cols)
{   
    matrix *mat = (matrix *)malloc(sizeof(matrix));
    mat->num_rows = num_rows;
    mat->num_cols = num_cols;
    mat->data = (int **)malloc(num_rows * sizeof(int *));
    for (int i = 0; i < num_rows; ++i) {
        mat->data[i] = (int *)calloc(num_cols, sizeof(int));
    }
    return mat;
}

void add_row(matrix *mat, int *row)
{
    mat->data = (int **)realloc(mat->data, (mat->num_rows + 1) * sizeof(int *));
    mat->data[mat->num_rows] = (int *)malloc(mat->num_cols * sizeof(int));

    for (int i = 0; i < mat->num_cols; i++) {
        mat->data[mat->num_rows][i] = row[i];
    }
    mat->num_rows++;
}


void add_col(matrix *mat, int *col)
{
    for (int i = 0; i < mat->num_rows; ++i) {
        mat->data[i] = (int *)realloc(mat->data[i], (mat->num_cols + 1) * sizeof(int));
        mat->data[i][mat->num_cols] = col[i];
    }
    mat->num_cols++;
}

void increment(matrix *mat, int num)
{
    for(int i = 0; i < mat->num_rows; i++) {
        for(int j = 0; j < mat->num_cols; j++) {
            mat->data[i][j] += num;
        }
    }
}

void scalar_multiply(matrix *mat, int num)
{
    for(int i = 0; i < mat->num_rows; i++) {
        for(int j = 0; j < mat->num_cols; j++) {
            mat->data[i][j] *= num;
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    for(int i = 0; i < mat->num_rows; i++) {
        for(int j = 0; j < mat->num_cols; j++) {
            mat->data[i][j] /= num;
        }
    }
}

void scalar_power(matrix *mat, int num)
{
    for(int i = 0; i < mat->num_rows; i++) {
        for(int j = 0; j < mat->num_cols; j++) {
            mat->data[i][j] = pow(mat->data[i][j], num);
        }
    }
}

void delete_matrix(matrix *mat)
{
    for (int i = 0; i < mat->num_rows; ++i) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}


/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat) 
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            if (col_idx == mat->num_cols-1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

//Add the rest of the functions needed for the chain below

node *create_node(matrix *mat) {
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    new_node->prev = NULL;
    new_node->next = NULL;
    
    // Create a copy of the matrix
    matrix *mat_copy = create_matrix(mat->num_rows, mat->num_cols);
    for (int i = 0; i < mat->num_rows; ++i) {
        for (int j = 0; j < mat->num_cols; ++j) {
            mat_copy->data[i][j] = mat->data[i][j];
        }
    }
    
    new_node->mat = mat_copy;
    return new_node;
}


void insert_node_before(chain *chn, int index, matrix *mat) {
    node *new_node = create_node(mat);
    

    if (chn->head == NULL) {
        chn->head = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
        return;
    }

    node *current = chn->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    new_node->prev = current->prev;
    new_node->next = current;
    current->prev->next = new_node;
    current->prev = new_node;
}

// Insert a new node after the node at the given index
void insert_node_after(chain *chn, int index, matrix *mat) {
    node *new_node = create_node(mat);
    

    if (chn->head == NULL) {
        chn->head = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
        return;
    }

    node *current = chn->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    current->next = new_node;
}

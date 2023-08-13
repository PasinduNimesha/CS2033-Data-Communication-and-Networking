#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include <string.h>



// Create a new node with the given word
node *create_node(char *word) {
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->word = strdup(word);
    return new_node;
}

// Insert a new node before the node at the given index
void insert_node_before(list *lst, int index, char *word) {
    node *new_node = create_node(word);
    

    if (lst->head == NULL) {
        lst->size = 1;
        lst->head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        return;
    }
    if(index < 0){
        index = lst->size + index;
    }

    node *current = lst->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    new_node->prev = current->prev;
    new_node->next = current;
    current->prev->next = new_node;
    current->prev = new_node;
    lst->size++;
}

// Insert a new node after the node at the given index
void insert_node_after(list *lst, int index, char *word) {
    insert_node_before(lst, index + 1, word);
}

// Convert the list to a sentence
char *list_to_sentence(list *lst) {
    if (lst->head == NULL) {
        return NULL;
    }

    node *current = lst->head;
    int total_length = 0;
    while (current->next != lst->head) {
        total_length += strlen(current->word) + 1; // +1 for space
        current = current->next;
    }
    total_length += strlen(current->word) + 1; // +1 for null terminator

    char *sentence = (char *)malloc(total_length);
    if (sentence == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    current = lst->head;
    strcpy(sentence, current->word);
    strcat(sentence, " ");
    current = current->next;

    while (current != lst->head) {
        strcat(sentence, current->word);
        strcat(sentence, " ");
        current = current->next;
    }

    return sentence;
}

// Delete the node at the given index
void delete_node(list *lst, int index) {
    if(index < 0){
        index = lst->size + index;
    }
    if (lst->head == NULL) {
        return;
    }

    node *current = lst->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;

    if (current == lst->head) {
        lst->head = current->next;
    }

    free(current->word);
    free(current);
}

// Delete the entire list
void delete_list(list *lst) {
    if (lst->head == NULL) {
        return;
    }

    node *current = lst->head;
    node *next;

    while (current->next != lst->head) {
        next = current->next;
        free(current->word);
        free(current);
        current = next;
    }

    free(current->word);
    free(current);

    lst->head = NULL;
}


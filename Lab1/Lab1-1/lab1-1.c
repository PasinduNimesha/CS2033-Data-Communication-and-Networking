#include <stdio.h>
#include <stdlib.h>
#include "node.h"

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// Function prototypes
void print_list(list *lst);
void run(list *lst);

int main() {
    list *lst = (list *)malloc(sizeof(list));
    char initial_words[][MAX_WORD_LENGTH] = {"Sri", "Lanka", "is", "a", "Country"};
    lst->head = NULL;
    for(int i = 0; i < 5; i++) {
        insert_node_before(lst, i, initial_words[i]);
    }
    run(lst);
    print_list(lst);
    delete_list(lst);
    return 0;
}

void run(list *lst) {
    int choice, index;
    char word[MAX_WORD_LENGTH];

    while (1) {
        printf("Choose an option:\n");
        printf("1. Insert before\n");
        printf("2. Insert after\n");
        printf("3. Delete node\n");
        printf("4. Delete list\n");
        printf("0. Exit\n");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case INSERT_BEFORE:
                printf("Enter index and word: ");
                scanf("%d %s", &index, word);
                insert_node_before(lst, index, word);
                break;

            case INSERT_AFTER:
                printf("Enter index and word: ");
                scanf("%d %s", &index, word);
                insert_node_after(lst, index, word);
                break;

            case DELETE_NODE:
                printf("Enter index: ");
                scanf("%d", &index);
                delete_node(lst, index);
                break;

            case DELETE_LIST:
                delete_list(lst);
                break;

            default:
                printf("Invalid choice\n");
                break;
        }
    }
}

void print_list(list *lst) {
    node *current = lst->head;

    printf("Linked List: ");
    if (current != NULL) {
        do {
            printf("%s ", current->word);
            current = current->next;
        } while (current != lst->head);
    }
    printf("\n");
}



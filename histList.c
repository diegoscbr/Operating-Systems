#include "histList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new node
Node* createNode(char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = strdup(data); //copy the command from the string
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insertAtEnd(Node** headRef, char* data) {
    Node* current = *headRef;
    if (current == NULL) {
        *headRef = createNode(data);
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = createNode(data);
    }
}

void printList(Node* head) {
    Node* current = head;
    int i = 1;
    while (current != NULL) {
        printf("%d: %s\n", i, current->data);
        current = current->next;
        i++;
    }
}

void freeList(Node** headRef) {
    Node* current = *headRef;
    while (current != NULL) {
        Node* next = current->next; 
        free(current->data); // Free the data string 
        free(current);
        current = next;
    }
    *headRef = NULL;
}

/*TEST for histList.c*/
/*
int main() {
    Node* head = NULL;

    // Insert nodes into the list
    insertAtEnd(&head, "command1");
    insertAtEnd(&head, "command2");
    insertAtEnd(&head, "command3");

    // Print the list
    printf("Linked List: \n");
    printList(head);

    // Free the list
    freeList(&head);
    printf("Linked List: \n");
    printList(head);

    return 0;
}

*/

